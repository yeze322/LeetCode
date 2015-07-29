using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using Microsoft.Bond;
using Microsoft.Search.Autopilot;
using System.IO;
using System.Reflection;

namespace Microsoft.BingAds.SCP.Hydra
{
    public class HydraClientBenchmark
    {
        public static readonly CustomLogID LogId = new CustomLogID("HydraBenchmark");
        private List<Thread> threadSet = new List<Thread>();
        private KeyValueStreams reqStream;
        private String workingDir;
        private Semaphore outgoingRequestPool;

        private HydraBenchmarkRateCounter sendCounter = new HydraBenchmarkRateCounter("SendRate");
        private HydraBenchmarkRateCounter successCounter = new HydraBenchmarkRateCounter("SuccessRate");
        private HydraBenchmarkRateCounter failSendCounter = new HydraBenchmarkRateCounter("FailSendRate");
        private HydraBenchmarkRateCounter failResponseCounter = new HydraBenchmarkRateCounter("FailResponseRate");
        private HydraBenchmarkRateCounter expiredCounter = new HydraBenchmarkRateCounter("Expired");
        private HydraBenchmarkRateCounter keyNotFoundCounter = new HydraBenchmarkRateCounter("KeyNotFound");

        private HydraBenchmarkNumCounter latencyCounter = new HydraBenchmarkNumCounter("Latency");

        private void __Init(int maxOutgoing)
        {
            this.outgoingRequestPool = new Semaphore(maxOutgoing, maxOutgoing);
            workingDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
        }

        public HydraClientBenchmark(int maxOutgoing)
        {
            __Init(maxOutgoing);
            this.reqStream = new KeyValueStreams(new StreamConfig());
        }

        public HydraClientBenchmark(int maxOutgoing, KeyValueStreams stream)
        {
            __Init(maxOutgoing);
            this.reqStream = stream;
        }
        
        public void KillAllThread()
        {
            foreach (Thread t in threadSet)
            {
                t.Abort();
            }
        }
        public void Start(int parr = 1)
        {
            for (int i = 0; i < parr; i++)
                this.threadSet.Add(new Thread(() => SendRequestThreadEntry()));
            foreach (Thread x in this.threadSet)
            {
                x.Start();
            }
        }
        private HydraBenchmarkRateCounter IncreaseResponseAnalyser(HydraResponseCode response)
        {
            switch (response)
            {
                case HydraResponseCode.Hydra_Success:
                    return successCounter;
                case HydraResponseCode.Hydra_Expired:
                    return expiredCounter;
                case HydraResponseCode.Hydra_KeyNotFound:
                    return keyNotFoundCounter;
                default:
                    return failResponseCounter;
            }
        }
        // request function, thread function
        private void SendRequestThreadEntry()
        {
            Logger.LogInfo(LogId, "HydraBenchmark", "Start send request thread");
            //IHydraClient client = new HydraClient("HydraBenchmark.ini");
            IHydraClient client = new HydraClient(Path.Combine(workingDir, "HydraClientExampleManaged.ini"), Path.Combine(workingDir, "HydraCluster.ini"));
            while (true)
            {
                HydraPutRequest putRequest = this.reqStream.GetOne();

                while (!this.outgoingRequestPool.WaitOne(30000))
                {
                    Logger.LogWarning(LogId, "HydraBenchmark", "Max outgoing in 30 seconds!");
                }
                DateTime sentTime = DateTime.Now;

                AsyncCallback callback = ar =>
                {
                    this.outgoingRequestPool.Release();
                    HydraPutResponse putResponse = client.EndPut(ar);
                    this.latencyCounter.Set((Int64)(DateTime.Now - sentTime).TotalMilliseconds);
                    IncreaseResponseAnalyser(putResponse.hydraResponseCode).Increment();
                };

                try
                {
                    client.BeginPut(putRequest, callback, null);
                    this.sendCounter.Increment();
                }
                catch (Exception e)
                {
                    try
                    {
                        this.outgoingRequestPool.Release();//here has some bugs, but I don't know why, so I just catch it.
                        this.failSendCounter.Increment();
                    }
                    catch { }
                    Logger.LogError(LogId, "HydraBenchmark", "BeginPut with exception: {0}", e);
                }
            }
        }

        // get counter's value
        public Observer Get()
        {
            Observer ret = new Observer(
                this.sendCounter.DumpRate(), this.successCounter.DumpRate(), this.failSendCounter.DumpRate(),
                this.failResponseCounter.DumpRate(), this.expiredCounter.DumpRate(), this.keyNotFoundCounter.DumpRate(),
                this.latencyCounter.DumpAverageValue()
                );
            return ret;
        }
        public void Dump()
        {
            var ret = this.Get();
            Console.WriteLine("running... {0}, {1}, {2}", ret.sendRate, ret.successRate, ret.latency);
        }
        public void DumpToFile(TextWriter writer)
        {
            var ret = this.Get();
            writer.WriteLine("{0} {1}", ret.sendRate, ret.latency);
        }
    }
}
