using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using Microsoft.Search.Autopilot;

namespace Microsoft.BingAds.SCP.Hydra
{
    public struct TestRunMode
    {   //we don't use enum
        //because this string is used to generate folder names
        public const string SingleThread = "SingleThread";
        public const string Parrallel = "Parrallel";
    }

    public class testConfig
    {
        public int maxOutgoing;
        public int parrTopology;
        public int threadNum;
        public bool ifDumplicatedTest;
        #region Set()
        private void Set(int a = 100, int b = 5, int c = 1, int d = 0)
        {
            maxOutgoing = a;
            parrTopology = b;
            threadNum = c;
            ifDumplicatedTest = (d == 0);
        }
        private void Set(string[] bits)
        {
            if (bits.Length != 4)
            {
                Logger.Log("Wrong config string, need 4 parameters. This config was set to default.");
                this.Set();
            }
            else
            {
                try { this.Set(int.Parse(bits[0]), int.Parse(bits[1]), int.Parse(bits[2]), int.Parse(bits[3])); }
                catch
                {
                    Logger.Log("Error in parsing string to number, format doesn't match");
                    this.Set();
                }
            }
        }
        public void Set(string str) { this.Set(str.Split(' ')); }
        #endregion

        #region constructors
        public testConfig(int maxOG = 100, int pTP = 5, int tNM = 1, int DpT = 0) { this.Set(maxOG, pTP, tNM, DpT); }
        public testConfig(string[] bits) { this.Set(bits); }
        public testConfig(string str)
        {
            var bits = str.Split(' ');
            this.Set(bits);
        }
        #endregion
        //e.g. config = "100 5 1 0" -> filename = [0]mGo100tNum1topo5Dump_false.txt
        //mGo = maxOutgoing; tNum = threadNum; topo = topologyNum; Dump_ = ifDumpicated
        //feature is used to give file a special mark, avoid dumplicated fnames
        public String GenerateFileName(string feature = "default")
        {
            String ret = "mGo" + maxOutgoing.ToString() + "tNum" + threadNum.ToString() + "topo" + parrTopology.ToString() + "Dump_" + ifDumplicatedTest.ToString() + ".txt";
            if (feature != null)
            {
                return "[" + feature + "]" + ret;
            }
            return ret;
        }
    };

    public class AutoTest
    {
        public List<testConfig> testConfigSet = new List<testConfig>();
        public string testName = "default";
        public int totalTime;
        public int intervalTime;
        public AutoTest(String configFileName, int totalTime, int intervalTime, string testName = null)
        {
            this.totalTime = totalTime;
            this.intervalTime = intervalTime;
            this.testName = testName;
            Console.WriteLine("[Config Filename] : {0}", configFileName);
            if (testName == null)
            {
                string[] split = configFileName.Split('/');
                this.testName = split[split.Length - 1].Split('.')[0];
            }
            if (File.Exists(configFileName))
            {
                TextReader reader = File.OpenText(configFileName);
                string line;
                while ((line = reader.ReadLine()) != null)
                {
                    string[] bits = line.Split(' ');
                    if (bits.Length == 4)
                    {
                        testConfigSet.Add(new testConfig(bits));
                    }
                }
                reader.Close();
            }
            else
            {
                Console.WriteLine("Config file doesn't exist!");
            }
        }
        public void StartSingleTest(string filepath, int index, int totalTestSeconds = 10000, int recordInterval = 500)
        {
            testConfig config = testConfigSet[index];
            int recordTimes = totalTestSeconds / recordInterval;
            if (Directory.Exists(filepath) == false)
            {// if dir not exist, create it!
                Directory.CreateDirectory(filepath);
            }
            TextWriter fwrite = File.CreateText(filepath + config.GenerateFileName(index.ToString()));
            HydraClientBenchmark clientBenchmark = new HydraClientBenchmark(config.maxOutgoing);
            clientBenchmark.Start(config.threadNum, config.ifDumplicatedTest);
            Thread.Sleep(3000); //record after 3 second
            for (int i = 0; i < recordTimes; i++)
            {
                clientBenchmark.DumpToFile(fwrite);
                Console.WriteLine("{0}/{1}", i, recordTimes);
                Thread.Sleep(recordInterval); //get every second
            }
            fwrite.Close();
            clientBenchmark.KillAllThread();
        }
        public void Run(string mode = TestRunMode.SingleThread, string path = "D:/HydraAutoTest/")
        {
            string filepath = path + testName + "/" + mode + "/";
            List<Thread> threadLists = new List<Thread>();
            for (int i = 0; i < testConfigSet.Count; i++)
            {
                int temp = i;//must copy it
                threadLists.Add(new Thread(() => StartSingleTest(filepath, temp, totalTime, intervalTime)));
            }
            if (mode == TestRunMode.Parrallel)
            {
                Console.WriteLine("Parrallel mode start!");
                foreach (Thread t in threadLists) t.Start();
                foreach (Thread t in threadLists) t.Join();
            }
            else if (mode == TestRunMode.SingleThread)
            {
                Console.WriteLine("Single thread mode start!");
                foreach (Thread t in threadLists) { t.Start(); t.Join(); }
            }
        }
    }
}
