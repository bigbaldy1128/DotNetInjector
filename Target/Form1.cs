using DotNetDetour;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Target
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //Monitor.Install();
            //MyClass<string> my = new MyClass<string>();
            //MessageBox.Show(my.Get("1"));
            MessageBox.Show(new TargetClass().Get());
        }
    }
}
