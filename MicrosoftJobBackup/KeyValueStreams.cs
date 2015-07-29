using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Microsoft.BingAds.SCP.Hydra
{
    public class StreamConfig
    {
        public int streamCapacity;
        public int duplicatedRate;
        public StreamConfig(int capa = 10000, int dup = 0)
        {
            this.streamCapacity = capa;
            this.duplicatedRate = dup;
        }
    };

    public class KeyValueStreams
    {
        //Estimated that single request will occupy 200Bytes, 1 MB = 5000 requests
        //sendRate = 2000~3000/second
        //So 15w/min, need to consider a proper capacity
        //If we refresh the stream every 30 seconds, the capacity should be 7W-20W, the latency is bearableb

        private List<HydraPutRequest> requestQueue = new List<HydraPutRequest>();
        private List<HydraPutRequest> auxiliaryQueue = new List<HydraPutRequest>();
        private int queueCapacity;
        private int walkIndex;
        private int duplicatedPercantage;
        private Random rand = new Random();

        public KeyValueStreams(StreamConfig config)
        {
            this.queueCapacity = config.streamCapacity;
            this.walkIndex = 0;
            this.duplicatedPercantage = config.duplicatedRate;
            Thread auxiFillThread = new Thread(() => __fillStreamQueue(auxiliaryQueue));
            __fillStreamQueue(requestQueue);
            auxiFillThread.Start();
        }

        //add support to analyse a file and create a similar stream.
        // u need to exstract features from it.
        public KeyValueStreams(string learningFileName)
        {

        }

        private void __fillStreamQueue(List<HydraPutRequest> Q)
        {
            Q.Clear();
            walkIndex = 0;
            //fill the first part with unduplicated
            int duplicateNumber = queueCapacity / 100 * duplicatedPercantage;
            int freshNumber = queueCapacity - duplicateNumber;
            for (int i = 0; i < freshNumber; i++)
            {
                Q.Add(new HydraPutRequest());
            }
            for (int i = 0; i < duplicateNumber; i++)
            {
                int copyIndex = rand.Next(0, freshNumber);
                Q.Add(new HydraPutRequest(Q[copyIndex]));
            }
            for (int i = 0; i < duplicateNumber; i++)
            {
                int insertIndex = rand.Next(0, freshNumber + i - 1);// fresh + i = Q.Count
                var temp = Q[freshNumber + i];
                Q[freshNumber + i] = Q[insertIndex];
                Q[insertIndex] = temp;
                //do not insert, low efficiency
            }
        }

        //pour auxiliary pool to main pool and refill the auxiliary pool
        //but you must make sure, main pool not empty before regeneration finished
        //actually we can guarantee this condition always happens.

        private void Refresh()
        {
            Thread regenerateThread = new Thread(()=>__fillStreamQueue(this.auxiliaryQueue));
            this.requestQueue = this.auxiliaryQueue;
            walkIndex = 0;
            regenerateThread.Start();
        }

        public HydraPutRequest GetOne()
        {
            Console.WriteLine("                 Stream: {0}/{1}", walkIndex, queueCapacity);
            if (queueCapacity == 0)
            {
                return new HydraPutRequest();
            }
            else
            {
                if (walkIndex == queueCapacity)
                {
                    this.Refresh();//regerate
                }
                var ret = requestQueue[walkIndex];
                walkIndex++;
                return ret;
            }
        }
    }
}
