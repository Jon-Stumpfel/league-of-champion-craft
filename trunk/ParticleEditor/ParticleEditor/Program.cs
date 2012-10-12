using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Threading;

namespace ParticleEditor
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
            ParticleEditor pe = new ParticleEditor();
            pe.Show();


            DateTime cur = DateTime.Now, now;
            float elapsedTime;
            while (pe.Alive)
            {
                now = DateTime.Now;
                TimeSpan tmp = (now - cur);
                elapsedTime = float.Parse(tmp.TotalSeconds.ToString());
                cur = now;

               
                pe.Update(elapsedTime);
                pe.Render();

                Application.DoEvents();
            }
        }
    }
}
