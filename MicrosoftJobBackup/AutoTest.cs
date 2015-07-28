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
        //public int parrTopology;
        public int threadNum;
        public const int paraNums = 2;
        public const string configFileSuffix = "config";
        public const char configFileSeparator = '.';
        public testConfig(int maxOG = 100, int tNum = 1)
        {
            maxOutgoing = maxOG;
            threadNum = tNum;
        }
        //e.g. config = "100 5 1 0" -> filename = [0]mGo100tNum1topo5Dump_false.txt
        //mGo = maxOutgoing; tNum = threadNum; topo = topologyNum; Dump_ = ifDumpicated
        //feature is used to give file a special mark, avoid dumplicated fnames
        public String GenerateFileName(string feature = "default")
        {
            String ret = "mGo" + maxOutgoing.ToString() + "tNum" + threadNum.ToString() + ".txt";
            if (feature != null)
            {
                return "[" + feature + "]" + ret;
            }
            return ret;
        }
    };

    public class AutoTest
    {
        /// <summary>
        /// AutoTest is used to run a test under one config file.
        /// Generally, you need to input a *.config file which contains lines of (int,int) as (maxOutgoing, threadNumbers)
        /// </summary>
        
        private string testName;
        // You can define your own testName which will influence the output file path
        // (By default, the testName is set to the config files' preffix.)
        // For example: config file name is - test1.config, then a folder named "test1" will be created whitch is used to save your outputs
        // The output's root path can also be influenced in the method Run() by changing the second parameter 'outputPath'
        private int totalTime;
        private int intervalTime;
        
        private List<testConfig> testConfigSet = new List<testConfig>();
        //there is a handler usally binded on "Console.Write", u can modify it to adjust different output requirements
        private delegate void handler(string str, params object[] paras);
        private handler REPORTER = new handler(Console.WriteLine);

        private void __ReadFileToConfigList(string fname)
        {
            if (!File.Exists(fname))
            {
                REPORTER("Config file doesn't exist!");
                return;
            }
            TextReader reader = File.OpenText(fname);
            string line;
            while ((line = reader.ReadLine()) != null)
            {
                string[] bits = line.Split(' ');
                if (bits.Length == testConfig.paraNums)
                {
                    int maxOutgoing = int.Parse(bits[0]);
                    int threadNumber = int.Parse(bits[1]);
                    testConfigSet.Add(new testConfig());
                }
            }
            reader.Close();
        }

        public AutoTest(String configFileName, int totalTime, int intervalTime, string testName = null)
        {
            this.totalTime = totalTime;
            this.intervalTime = intervalTime;
            this.testName = testName;
            REPORTER("[Load Config File] :" + configFileName);
            if (testName == null)
            {
                string[] split = configFileName.Split('/');
                //testname is set as config file name by default
                this.testName = split[split.Length - 1].Split('.')[0];
            }
            __ReadFileToConfigList(configFileName);
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
            clientBenchmark.Start(config.threadNum);
            Thread.Sleep(3000); //record after 3 second
            for (int i = 0; i < recordTimes; i++)
            {
                clientBenchmark.DumpToFile(fwrite);
                REPORTER("{0}/{1}", i + 1, recordTimes);
                Thread.Sleep(recordInterval); //get every second
            }
            fwrite.Close();
            clientBenchmark.KillAllThread();
        }

        public void Run(string mode = TestRunMode.SingleThread, string outputPath = "D:/HydraAutoTest/")
        {
            string filepath = outputPath + testName + "/" + mode + "/";
            List<Thread> threadLists = new List<Thread>();
            for (int i = 0; i < testConfigSet.Count; i++)
            {
                int temp = i;//must copy it
                threadLists.Add(new Thread(() => StartSingleTest(filepath, temp, totalTime, intervalTime)));
            }
            if (mode == TestRunMode.Parrallel)
            {
                REPORTER("Parrallel mode start!");
                foreach (Thread t in threadLists) t.Start();
                foreach (Thread t in threadLists) t.Join();
            }
            else if (mode == TestRunMode.SingleThread)
            {
                REPORTER("Single thread mode start!");
                foreach (Thread t in threadLists) { t.Start(); t.Join(); }
            }
        }
    }
}
