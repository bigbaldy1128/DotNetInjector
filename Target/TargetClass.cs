using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Target
{
    public class TargetClass
    {
        [MethodImpl(MethodImplOptions.NoInlining)]
        public string Get()
        {
            return "A";
        }
    }
}
