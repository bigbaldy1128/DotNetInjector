using DotNetDetour;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace CustomMonitor
{
    public class CustomMonitor:IMethodMonitor
    {
        [Monitor("Target","TargetClass","Target.exe")]
        public string Get()
        {
            return "B" + Ori();
        }

        [MethodImpl(MethodImplOptions.NoInlining)]
        [Original]
        public string Ori()
        {
            return null;
        }
    }
}
