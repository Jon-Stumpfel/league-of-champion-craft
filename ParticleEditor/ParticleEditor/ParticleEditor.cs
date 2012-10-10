using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace ParticleEditor
{
    public partial class ParticleEditor : Form
    {
        private Emitter emitter = Emitter.Instance1;
        public ParticleEditor()
        {
            InitializeComponent();
            // Initalizes the click and drag value thing...
            int value = tbAngle.Value;
            nudAngle.Value = value;
            
            value = (int)nudAngleRot.Value;
            tbAngleRot.Value = value;

            emitter.Alive = true;
            thread = new Thread(new ThreadStart(emitter.Run));
            thread.Start();
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

        private Thread thread;


        private void btPreview_Click(object sender, EventArgs e)
        {
            int R = int.Parse(btColorStart.ForeColor.R.ToString());
            int G = int.Parse(btColorStart.ForeColor.G.ToString());
            int B = int.Parse(btColorStart.ForeColor.B.ToString());
            emitter.ColorStart = Color.FromArgb(int.Parse(nudStartAlpha.Value.ToString()), R, G, B);

            R = int.Parse(btColorEnd.ForeColor.R.ToString());
            G = int.Parse(btColorEnd.ForeColor.G.ToString());
            B = int.Parse(btColorEnd.ForeColor.B.ToString());
            emitter.ColorEnd = Color.FromArgb(int.Parse(nudEndAlpha.Value.ToString()), R, G, B);

            emitter.ParticleCount = (int)nudParticleNum.Value;
            emitter.ImgHeight = (int)nudHeight.Value;
            emitter.ImgWidth = (int)nudWidth.Value;
            float pi = float.Parse(Math.PI.ToString());
            emitter.Angle = (float) nudAngle.Value * pi / 180;
            emitter.AngleRotation = (float)nudAngleRot.Value * pi / 180;
            emitter.RotationStart = (float)nudRotStart.Value;
            emitter.RotationEnd = (float)nudRotEnd.Value;
            emitter.ScaleStart = (float)nudScaleStart.Value;
            emitter.ScaleEnd = (float)nudScaleEnd.Value;
            emitter.SpawnMax = (float)nudSpawnMax.Value;
            emitter.SpawnMin = (float)nudSpawnMin.Value;
            emitter.LifeMax = (float)nudLifeMax.Value;
            emitter.LifeMin = (float)nudLifeMin.Value;

            Vector2D tmp = new Vector2D();
            tmp.Init((float)nudVelMaxStartX.Value, (float)nudVelMaxStartY.Value);
            emitter.VelStartMax = tmp;
            tmp.Init((float)nudVelMaxEndX.Value, (float)nudVelMaxEndY.Value);
            emitter.VelEndMax = tmp;
            tmp.Init((float)nudVelMinStartX.Value, (float)nudVelMinStartY.Value);
            emitter.VelStartMin = tmp;
            tmp.Init((float)nudVelMinEndX.Value, (float)nudVelMinEndY.Value);
            emitter.VelEndMin = tmp;
            tmp.Init((float)nudImgPosX.Value, (float)nudImgPosY.Value);
            emitter.ImgPos = tmp;

            emitter.Looping = cbLooping.Checked;
            int i = cbShape.SelectedIndex;

            if (i == 0)
                emitter.Type = Shape.POINT;
            else if( i == 1 )
                emitter.Type = Shape.CIRCLE;
            else if( i == 2 )
                emitter.Type = Shape.SQUARE;
            else if( i == 3 )
                emitter.Type = Shape.LINE;

            emitter.InitParticle();

            if (emitter.Alive == false)
            {
                emitter.InitParticle();
                emitter.Alive = true;
                thread = new Thread(new ThreadStart(emitter.Run));
                thread.Start();
            }
            else
            {
                emitter.InitParticle();
            }
        }

        private void ParticleEditor_FormClosing(object sender, FormClosingEventArgs e)
        {
            thread.Abort();
        }
    }
}
