// --------------------------------------------------------------------------------------------------------------------
//  <copyright file="Program.cs" company="Microsoft">
//    Copyright (c) 2014 Microsoft
//  </copyright>
//  <owner>xinlu</owner>
//  <summary>
//  </summary>
//  --------------------------------------------------------------------------------------------------------------------
using System;
using System.IO;

namespace Microsoft.BingAds.SCP.Hydra
{
    using System.Threading;
    using Microsoft.Search.Autopilot;
    class Program
    {
        static public string configFilePath = "D:/HydraAutoTest/heheda/";
        static public int totalTestTime = 2000000000;
        static public int recordInterval = 200;

        static void Main(string[] args)
        {
            APRuntime.Initialize("HydraBenchmark.ini");
            string[] fileNameSet = Directory.GetFiles(configFilePath);
            StreamConfig streams = new StreamConfig(10000, 10);
            foreach (string x in fileNameSet)
            {
                string[] sp = x.Split(testConfig.configFileSeparator);
                if (sp.Length < 2 || sp[1] != testConfig.configFileSuffix) continue;
                AutoTest test = new AutoTest(streams, x, totalTestTime, recordInterval);
                Console.WriteLine("[Config Start]: {0}", x);
                test.Run(TestRunMode.SingleThread, configFilePath);
                //test.Run(TestRunMode.Parrallel);
            }
            return;
        }
    }
}
