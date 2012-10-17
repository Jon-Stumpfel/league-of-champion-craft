﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;


namespace WorldTileEditor
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
            //Application.Run(new Form1());
            Form1 theform = new Form1();

            theform.Show();

            while (theform.Looping)
            {
                theform.UpdateTool();
                theform.RenderTool();
                Application.DoEvents();
            }

        }
    }
}
