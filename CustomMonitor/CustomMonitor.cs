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
        [Monitor("Target","TargetClass")]
        public string Get()
        {
            return "竟然被hook了";
        }
    }
}
