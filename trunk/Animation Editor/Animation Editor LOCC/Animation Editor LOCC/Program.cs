using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Animation_Editor_LOCC
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Form1 THEFORM = new Form1();

            THEFORM.Show();

            while (THEFORM.Looping)
            {
                THEFORM.Update();
                THEFORM.Render();

                Application.DoEvents();
            }
        }
    }
}
