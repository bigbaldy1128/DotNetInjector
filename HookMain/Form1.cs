using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HookMain
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        [DllImport("Inject", CallingConvention = CallingConvention.Cdecl)]
        static extern bool Inject(uint pid);

        private void button1_Click(object sender, EventArgs e)
        {
            Inject((uint)Process.GetProcessesByName("Target").First().Id);
        }
    }
}
