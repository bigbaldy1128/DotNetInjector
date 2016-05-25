using DotNetDetour;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace ComForHook
{
    [Guid("00C74C42-D58C-40E9-B09F-B09D129A4057")]
    public interface IHook
    {
        void Apply();
    }

    [Guid("56C2BC3F-942F-4967-BFD2-D5E07281DB49")]
    public class Hook : IHook
    {
        public void Apply()
        {
            Monitor.Install("monitors");
        }
    }
}
