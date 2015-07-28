using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Microsoft.BingAds.SCP.SampleApp
{
    public class ProAndConsModel
    {
        public static int resourcePool = 0;
        public static object lockForPool = new object();
        public static List<Resource> resourcesArr = new List<Resource>();
        public static Resource CenterPool = new Resource();
        public static List<Thread> ThreadLists = new List<Thread>();
        public class Resource
        {
            public int resources;
            public object lockForSelf = new object();
            public Resource() { resources = 0; }
        }
        public int getPoolValue() { return CenterPool.resources; }
        public int getThreadNum() { return ThreadLists.Capacity; }
        public class Producer
        {
            public Resource res;
            public Producer()
            {
                res = new Resource();
                resourcesArr.Add(res);
                Thread producer = new Thread(proIncrease);
                ThreadLists.Add(producer);
                producer.Start();
            }
            public void proIncrease()
            {
                while (true)
                {
                    lock (res.lockForSelf)
                    {
                        res.resources++;
                        Console.WriteLine("Producer: +1, selfPool:{0}", res.resources);
                    }
                    Thread.Sleep(2000);
                }
            }
        }
        public class Consumer
        {
            public Consumer()
            {
                Console.WriteLine("new consumer added!");
                Thread consumer = new Thread(consUse);
                ThreadLists.Add(consumer);
                consumer.Start();
            }
            public void consUse()
            {
                while (true)
                {
                    Thread.Sleep(2000);
                    lock (CenterPool.lockForSelf)
                    {
                        if (CenterPool.resources > 0)
                        {
                            CenterPool.resources--;
                            Console.WriteLine("\t\tConsumer: eat 1, MainPool:{0}", CenterPool.resources);
                        }
                        else
                        {
                            foreach (var x in resourcesArr)
                            {
                                lock (x.lockForSelf)
                                {
                                    CenterPool.resources += x.resources;
                                    x.resources = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        public void run(int proNum, int consNum)
        {
            for (int i = 0; i < proNum; i++) { var temp = new Producer(); }
            for (int i = 0; i < consNum; i++) { var temp = new Consumer(); }
            //foreach (var thread in ThreadLists) { thread.Join(); }
        }
    }
}
