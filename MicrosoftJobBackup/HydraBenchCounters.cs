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
    internal class HydraBenchmarkRateCounter
    {
        private Int64 value = 0;
        private Int64 lastValue = 0;
        private DateTime lastDumpTime = DateTime.Now;

        public string Name { get; private set; }

        public HydraBenchmarkRateCounter(string name)
        {
            this.Name = name;
        }

        public void Increment()
        {
            Interlocked.Increment(ref this.value);
        }

        public double DumpRate()
        {
            Int64 currentValue = this.value;
            DateTime currentTime = DateTime.Now;

            double rate = (((double)currentValue) - this.lastValue) / (currentTime - this.lastDumpTime).TotalSeconds;

            this.lastValue = currentValue;
            this.lastDumpTime = currentTime;

            return rate;
        }
    }

    internal class HydraBenchmarkNumCounter
    {
        private Int64 total = 0;
        private Int64 num = 0;
        private Int64 lastTotal = 0;
        private Int64 lastNum = 0;

        public string Name { get; private set; }

        public HydraBenchmarkNumCounter(string name)
        {
            this.Name = name;
        }

        public void Set(Int64 value)
        {
            Interlocked.Add(ref this.total, value);
            Interlocked.Increment(ref this.num);
        }
        
        public double DumpAverageValue()
        {
            Int64 currentTotal = this.total;
            Int64 currentNum = this.num;

            double avg = (((double)currentTotal) - this.lastTotal) / (currentNum - this.lastNum);

            this.lastTotal = currentTotal;
            this.lastNum = currentNum;

            return avg;
        }
    }
    public class Observer
    {
        public long sendRate;
        public long successRate;
        public long failSendRate;
        public long failResponseRate;
        public long expiredRate;
        public long keyNotFoundRate;
        public long latency;
        public Observer(double x1, double x2, double x3, double x4, double x5, double x6, double x7)
        {
            sendRate = (long)x1;
            successRate = (long)x2;
            failSendRate = (long)x3;
            failResponseRate = (long)x4;
            expiredRate = (long)x5;
            keyNotFoundRate = (long)x6;
            latency = (long)x7;//ms
        }
    };
}
