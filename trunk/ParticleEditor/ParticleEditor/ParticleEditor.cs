using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ParticleEditor
{
    public partial class ParticleEditor : Form
    {
        public ParticleEditor()
        {
            InitializeComponent();
            // Initalizes the click and drag value thing...
            int value = tbAngle.Value;
            nudAngle.Value = value;

            value = (int)nudAngleRot.Value;
            tbAngleRot.Value = value;
        }

        private void tbAngle_Scroll(object sender, EventArgs e)
        {
            int value = tbAngle.Value;
            nudAngle.Value = value;
        }

        private void tbAngleRot_Scroll(object sender, EventArgs e)
        {
            int value = tbAngleRot.Value;
            nudAngleRot.Value = value;
        }

        private void nudAngle_ValueChanged(object sender, EventArgs e)
        {
            int value = (int)nudAngle.Value;
            tbAngle.Value = value;
        }

        private void nudAngleRot_ValueChanged(object sender, EventArgs e)
        {
            int value = (int)nudAngleRot.Value;
            tbAngleRot.Value = value;
        }

        private void btColorStart_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            cd.ShowDialog();
            btColorStart.BackColor = cd.Color;
        }

        private void btColorEnd_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            cd.ShowDialog();
            btColorEnd.BackColor = cd.Color;
        }
    }
}
