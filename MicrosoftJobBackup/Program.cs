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

        static void Main(string[] args)
        {
            APRuntime.Initialize("HydraBenchmark.ini");
            string configFilePath = "D:/HydraAutoTest/maxOutGoingTest/";
            string[] fileNameSet = Directory.GetFiles(configFilePath);
            int totalTestTime = 10000;
            int recordInterval = 200;
            foreach (string x in fileNameSet)
            {
                string[] sp = x.Split('.');
                if (sp.Length < 2 || sp[1] != "config") continue;

                AutoTest test = new AutoTest(x, totalTestTime, recordInterval);
                Console.WriteLine("[Config Start]: {0}", x);
                test.Run(TestRunMode.SingleThread, configFilePath);
                //test.Run(TestRunMode.Parrallel);
            }
            return;
        }
    }
}
