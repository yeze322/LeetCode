// --------------------------------------------------------------------------------------------------------------------
//  <copyright file="MultiTypeEventTopology.cs" company="Microsoft">
//    Copyright (c) 2013 Microsoft
//  </copyright>
//  <owner>junqian</owner>
//  <createdate>04/21/2013</createdate>
// --------------------------------------------------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Threading;
using Microsoft.BingAds.SCP;
using Microsoft.BingAds.SCP.SampleApp;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.BingAds.SCP.Hydra;
using Microsoft.Bond;
using System.IO;
using System.Reflection;
using Microsoft.Search.Autopilot;

namespace Microsoft.BingAds.SCP.SampleApp
{

    #region useless
    public class MteSpout : BasicSpout
    {
        public MteSpout(string name)
            : base(name)
        {
        }

        public IEnumerable<Message> GetNext()
        {
            Thread.Sleep(5000);
            WordEvent we = new WordEvent();
            we.Word = "abc";
            yield return we;
        }

        public override void Run(RuntimeContext context, IChannel channel)
        {
            while (true)
            {
                var messages = this.GetNext();
                foreach (var message in messages)
                {
                    channel.Emit(message);
                }
            }
        }
    }

    public class MteBolt : BasicBolt
    {
        public MteBolt(string name)
            : base(name)
        {
        }

        public void OnEvent(Message e)
        {
            WordEvent we = e as WordEvent;
            if (we == null)
            {
                return;
            }

            EventA A = new EventA();
            A.A = we.Word + "A";
            this.Emit(A);

            EventB B = new EventB();
            B.B = we.Word + "B";
            this.Emit(B);

            EventC C = new EventC();
            C.C = we.Word + "C";
            this.Emit(C);
        }

        public override void OnReceive(IEnumerable<Message> messages)
        {
            foreach (var message in messages)
            {
                this.OnEvent(message);
            }
        }
    }

    public class BoltA : BasicBolt
    {
        public BoltA(string name)
            : base(name)
        {
        }

        public void OnEvent(Message e)
        {
            EventA a = e as EventA;
            Console.WriteLine(a.A);
        }

        public override void OnReceive(IEnumerable<Message> messages)
        {
            foreach (var message in messages)
            {
                this.OnEvent(message);
            }
        }
    }

    public class BoltAA : BasicBolt
    {
        public BoltAA(string name)
            : base(name)
        {
        }

        public void OnEvent(Message e)
        {
            EventA a = e as EventA;
            Console.WriteLine(a.A);
        }

        public override void OnReceive(IEnumerable<Message> messages)
        {
            foreach (var message in messages)
            {
                this.OnEvent(message);
            }
        }
    }

    public class BoltB : BasicBolt
    {
        public BoltB(string name)
            : base(name)
        {
        }

        public void OnEvent(Message e)
        {
            EventB b = e as EventB;
            Console.WriteLine(b.B);
        }

        public override void OnReceive(IEnumerable<Message> messages)
        {
            foreach (var message in messages)
            {
                this.OnEvent(message);
            }
        }
    }

    public class BoltC : BasicBolt
    {
        public BoltC(string name)
            : base(name)
        {
        }

        public void OnEvent(Message e)
        {
            EventC c = e as EventC;
            Console.WriteLine(c.C);
        }

        public override void OnReceive(IEnumerable<Message> messages)
        {
            foreach (var message in messages)
            {
                this.OnEvent(message);
            }
        }
    }

    public class MultiTypeEventTopology : Topology
    {
        protected override void OnInit()
        {
            this.SetSpout(new MteSpout("mtes"));
            this.SetBolt(new MteBolt("bolt"));
            this.SetBolt(new BoltA("a"), 3);
            this.SetBolt(new BoltB("b"), 3);
            this.SetBolt(new BoltC("c"), 3);
            this.SetStream("mtes", "bolt", new Stream<WordEvent>());
            this.SetStream("bolt", "a", new Stream<EventA>(new FieldGrouping<EventA>(a => new string[] { a.A })));
            this.SetStream("bolt", "b", new Stream<EventB>(new ShuffleGrouping()));
            this.SetStream("bolt", "c", new Stream<EventC>(new AllGrouping()));
        }
    }

    public class SameEventTopology : Topology
    {
        protected override void OnInit()
        {
            this.SetSpout(new MteSpout("S"));
            this.SetBolt(new MteBolt("B"));
            this.SetBolt(new BoltA("A"));
            this.SetBolt(new BoltAA("AA"));
            this.SetStream("S", "B", new Stream<WordEvent>());
            this.SetStream("B", "A", new Stream<EventA>());
            this.SetStream("B", "AA", new Stream<EventA>());
        }
    }
    #endregion
    #region server model test
    public class HydraBenchmarkSpout : BasicSpout
    {
        public HydraBenchmarkSpout(string name)
            : base(name)
        {
        }
        public override void Run(RuntimeContext context, IChannel channel)
        {
            IPerfCounter mainPoolCounter = PerfCounterFactory.Create(PerfCounterImplType.AutoPilot, "iperf_ex", "tds1", PerfCounterType.Number);
            IPerfCounter extraCouter = PerfCounterFactory.Create(PerfCounterImplType.Automatic, "iperf_ex", "tds2", PerfCounterType.Number);
            ProAndConsModel server = new ProAndConsModel();
            Thread serverThread = new Thread(() => server.run(2, 2));
            serverThread.Start();
            while (true)
            {
                String workingDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
                InstrumentationHelper.Info("location", workingDir);

                mainPoolCounter.Set(server.getPoolValue());
                extraCouter.Set(server.getThreadNum());
                Thread.Sleep(500);
            }
        }
    }
    #endregion
    public class HydraBenchmarkTransplant : BasicSpout
    {
        public const int maxOutgoing = 1000;
        public String sectionName = "TransplantObserver";
        public testConfig TESTCONFIG = new testConfig(100,1);
        public struct CounterSet
        {
            public IPerfCounter sentRate;
            public IPerfCounter successRate;
            public IPerfCounter failSendRate;
            public IPerfCounter failResponseRate;
            public IPerfCounter expiredRate;
            public IPerfCounter keyNotFoundRate;
            public IPerfCounter latency;
            public void AssignFromObserver(Observer observer)
            {
                sentRate.Set(observer.sendRate);
                successRate.Set(observer.successRate);
                failSendRate.Set(observer.failSendRate);
                failResponseRate.Set(observer.failResponseRate);
                expiredRate.Set(observer.expiredRate);
                keyNotFoundRate.Set(observer.keyNotFoundRate);
                latency.Set(observer.latency);
            }
        };
        public CounterSet counters;
        private IPerfCounter __CreateCounter(string counterName)
        {
            return PerfCounterFactory.Create(PerfCounterImplType.AutoPilot, sectionName, counterName, PerfCounterType.Number);
        }
        public HydraBenchmarkTransplant(string name)
            : base(name)
        {
            counters.sentRate = __CreateCounter("sendRate");
            counters.successRate = __CreateCounter("successRate");
            counters.failSendRate = __CreateCounter("failSendRate");
            counters.failResponseRate = __CreateCounter("failResponseRate");
            counters.expiredRate = __CreateCounter("expiredRate");
            counters.keyNotFoundRate = __CreateCounter("keyNotFoundRate");
            counters.latency = __CreateCounter("latency");
        }

        public override void Run(RuntimeContext context, IChannel channel)
        {
            HydraClientBenchmark clientBenchmark = new HydraClientBenchmark(TESTCONFIG.maxOutgoing);
            clientBenchmark.Start(TESTCONFIG.threadNum);
            while (true)
            {
                Observer observer = clientBenchmark.Get();
                counters.AssignFromObserver(observer);
                InstrumentationHelper.Debug(
                    "report:",
                    "success[-]: [counters: {0},{1},{2},{3},{4},{5},{6}]",
                    observer.sendRate, observer.successRate, observer.failSendRate, observer.failResponseRate,
                    observer.expiredRate, observer.keyNotFoundRate, observer.latency
                    );
                Thread.Sleep(1000);
            }
        }
    }

    public class HydraBenchmarkTopology : Topology
    {
        protected override void OnInit()
        {
            this.SetSpout(new HydraBenchmarkTransplant("HydraBenchmarkTransplant"), 5);
        }
    }
}