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
        private Emitter emitter = Emitter.Instance;
        private bool alive;

        public bool Alive
        {
            get { return alive; }
            set { alive = value; }
        }

        public void Update(float fElapsedTime)
        {
            double rad = Math.PI / 180;
            emitter.Angle = float.Parse(nudAngle.Value.ToString()) * float.Parse(rad.ToString());
            emitter.AngleRotation = float.Parse(nudAngleRot.Value.ToString()) * float.Parse(rad.ToString());

            emitter.Update(fElapsedTime);

            if (nudSpawnMin.Value > nudSpawnMax.Value)
                nudSpawnMax.Value = nudSpawnMin.Value;

            if (nudLifeMin.Value > nudLifeMax.Value)
                nudLifeMax.Value = nudLifeMin.Value;

            if (nudVelMinEndX.Value > nudVelMaxEndX.Value)
                nudVelMaxEndX.Value = nudVelMinEndX.Value;

            if (nudVelMinStartX.Value > nudVelMaxStartX.Value)
                nudVelMaxStartX.Value = nudVelMinStartX.Value;

            if (nudVelMinEndY.Value > nudVelMaxEndY.Value)
                nudVelMaxEndY.Value = nudVelMinEndY.Value;

            if (nudVelMinStartY.Value > nudVelMaxStartY.Value)
                nudVelMaxStartY.Value = nudVelMinStartY.Value;
            
        }

        SGP.ManagedDirect3D d3d = SGP.ManagedDirect3D.Instance;
        SGP.ManagedTextureManager tm = SGP.ManagedTextureManager.Instance;

        public void Render()
        {

            d3d.DeviceBegin();
            d3d.SpriteBegin();

            d3d.Clear(Color.Beige);
            d3d.Sprite.Flush();

            emitter.Render();

            d3d.SpriteEnd();
            d3d.DeviceEnd();

            d3d.Present();
            
        }

        public ParticleEditor()
        {
            InitializeComponent();

            SGP.ManagedDirect3D d3d = SGP.ManagedDirect3D.Instance;
            d3d.InitManagedDirect3D(panel1);
            SGP.ManagedTextureManager mtm = SGP.ManagedTextureManager.Instance;
            mtm.InitManagedTextureManager(d3d.Device, d3d.Sprite);

            int value = tbAngle.Value;
            nudAngle.Value = value;
            
            value = (int)nudAngleRot.Value;
            tbAngleRot.Value = value;

            Alive = true;

            Vector2D pos = new Vector2D();
            pos.Init(230, 270);
            emitter.Pos = pos;
            emitter.Type = Shape.POINT;
            cbShape.SelectedIndex = 0;
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

        private void btPreview_Click(object sender, EventArgs e)
        {
            int R = int.Parse(btColorStart.BackColor.R.ToString());
            int G = int.Parse(btColorStart.BackColor.G.ToString());
            int B = int.Parse(btColorStart.BackColor.B.ToString());
            emitter.ColorStart = Color.FromArgb(int.Parse(nudStartAlpha.Value.ToString()), R, G, B);

            R = int.Parse(btColorEnd.BackColor.R.ToString());
            G = int.Parse(btColorEnd.BackColor.G.ToString());
            B = int.Parse(btColorEnd.BackColor.B.ToString());
            emitter.ColorEnd = Color.FromArgb(int.Parse(nudEndAlpha.Value.ToString()), R, G, B);

            emitter.ParticleCount = (int)nudParticleNum.Value;
            float pi = float.Parse(Math.PI.ToString());

            double rad = Math.PI / 180;
            emitter.Angle = float.Parse(nudAngle.Value.ToString()) * float.Parse(rad.ToString());
            emitter.AngleRotation = float.Parse(nudAngleRot.Value.ToString()) * float.Parse(rad.ToString());
            
            double r = (double)nudRotStart.Value * rad;
            emitter.RotationStart = float.Parse(r.ToString());
            r = (double)nudRotEnd.Value * rad;
            emitter.RotationEnd = float.Parse(r.ToString());

            emitter.ScaleStart = float.Parse(nudScaleStart.Value.ToString());
            emitter.ScaleEnd = float.Parse(nudScaleEnd.Value.ToString());
            emitter.SpawnMax = float.Parse(nudSpawnMax.Value.ToString());
            emitter.SpawnMin = float.Parse(nudSpawnMin.Value.ToString());
            emitter.LifeMax = float.Parse(nudLifeMax.Value.ToString());
            emitter.LifeMin = float.Parse(nudLifeMin.Value.ToString());

            Vector2D tmp = new Vector2D();
            tmp.Init((float)nudVelMaxStartX.Value, (float)nudVelMaxStartY.Value);
            emitter.VelStartMax = tmp;
            tmp.Init((float)nudVelMaxEndX.Value, (float)nudVelMaxEndY.Value);
            emitter.VelEndMax = tmp;
            tmp.Init((float)nudVelMinStartX.Value, (float)nudVelMinStartY.Value);
            emitter.VelStartMin = tmp;
            tmp.Init((float)nudVelMinEndX.Value, (float)nudVelMinEndY.Value);
            emitter.VelEndMin = tmp;

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

            Vector2D pos = new Vector2D();
            pos.Init(230, 270);
            emitter.Pos = pos;

            if (emitter.Imgpath == null)
            {
                string s = "No Image Selected";
                DialogResult mb = MessageBox.Show(s);
                return;
            }

            emitter.InitParticle();
        }

        private void ParticleEditor_FormClosing(object sender, FormClosingEventArgs e)
        {
            alive = false;
        }

        private void btStopPrev_Click(object sender, EventArgs e)
        {
            emitter.Clear();
        }

        private void loadImg_Click(object sender, EventArgs e)
        {
            OpenFileDialog of = new OpenFileDialog();
            DialogResult result = of.ShowDialog();
            emitter.Imgpath = of.FileName;
        }
    }
}
