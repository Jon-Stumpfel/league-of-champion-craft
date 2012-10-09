using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace World_Tile_Editor
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary> 
        /// 
        
        [STAThread]
        static void Main()
        {

            SaveFileDialog savedlg = new SaveFileDialog();
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            //savedlg.ShowDialog();
            Application.Run(new Form1());
        }
    }
}
