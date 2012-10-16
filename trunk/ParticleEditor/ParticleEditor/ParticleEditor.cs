using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Xml.Linq;
using System.IO;

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

            if (emitter.Type == Shape.LINE)
            {
                nudPointX.Visible = true;
                nudPoint2X.Visible = true;
                nudPointY.Visible = true;
                nudPoint2Y.Visible = true;
                lPoint.Visible = true;
                lPoint2.Visible = true;
                lPointX.Visible = true;
                lPointY.Visible = true;
                lPoint2X.Visible = true;
                lPoint2Y.Visible = true;

                nudRad.Visible = false;
                lRad.Visible = false;

                nudHeight.Visible = false;
                lHeight.Visible = false;
                nudWidth.Visible = false;
                lWidth.Visible = false;

                Vector2D tmp;
                tmp.x = (int)nudPointX.Value;
                tmp.y = (int)nudPointY.Value;
                emitter.Point = tmp;
                tmp.x = (int)nudPoint2X.Value;
                tmp.y = (int)nudPoint2Y.Value;
                emitter.Point2 = tmp;
            }
            else if (emitter.Type == Shape.CIRCLE)
            {
                nudPointX.Visible = false;
                nudPoint2X.Visible = false;
                nudPointY.Visible = false;
                nudPoint2Y.Visible = false;
                lPoint.Visible = false;
                lPoint2.Visible = false;
                lPointX.Visible = false;
                lPointY.Visible = false;
                lPoint2X.Visible = false;
                lPoint2Y.Visible = false;

                nudRad.Visible = true;
                lRad.Visible = true;

                nudHeight.Visible = false;
                lHeight.Visible = false;
                nudWidth.Visible = false;
                lWidth.Visible = false;

                emitter.Radius = (float)nudRad.Value;
            }
            else if (emitter.Type == Shape.SQUARE)
            {
                nudPointX.Visible = false;
                nudPoint2X.Visible = false;
                nudPointY.Visible = false;
                nudPoint2Y.Visible = false;
                lPoint.Visible = false;
                lPoint2.Visible = false;
                lPointX.Visible = false;
                lPointY.Visible = false;
                lPoint2X.Visible = false;
                lPoint2Y.Visible = false;

                nudRad.Visible = false;
                lRad.Visible = false;

                nudHeight.Visible = true;
                lHeight.Visible = true;
                nudWidth.Visible = true;
                lWidth.Visible = true;

                emitter.Width = (int)nudWidth.Value;
                emitter.Height = (int)nudHeight.Value;
            }
            else
            {
                nudPointX.Visible = false;
                nudPoint2X.Visible = false;
                nudPointY.Visible = false;
                nudPoint2Y.Visible = false;
                lPoint.Visible = false;
                lPoint2.Visible = false;
                lPointX.Visible = false;
                lPointY.Visible = false;
                lPoint2X.Visible = false;
                lPoint2Y.Visible = false;

                nudRad.Visible = false;
                lRad.Visible = false;

                nudHeight.Visible = false;
                lHeight.Visible = false;
                nudWidth.Visible = false;
                lWidth.Visible = false;

            }
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

        private string filepath;

        public ParticleEditor()
        {
            InitializeComponent();

            SGP.ManagedDirect3D d3d = SGP.ManagedDirect3D.Instance;
            d3d.InitManagedDirect3D(panel1);
            SGP.ManagedTextureManager mtm = SGP.ManagedTextureManager.Instance;
            mtm.InitManagedTextureManager(d3d.Device, d3d.Sprite);

            XElement xRoot;
            if (File.Exists("Config.xml"))
            {
                xRoot = XElement.Load("Config.xml");

                XAttribute xPath = xRoot.Attribute("Path");
                filepath = xPath.Value;
            }

            if (filepath == null)
            {
                FolderBrowserDialog fbd = new FolderBrowserDialog();
                fbd.ShowDialog();
                filepath = fbd.SelectedPath;
            }

            Alive = true;
            emitter.Circlejpg = tm.LoadTexture("circle.png", Color.FromArgb(255, 255, 255, 255).ToArgb());
            Vector2D pos = new Vector2D();
            pos.Init(230, 270);
            emitter.Pos = pos;
            emitter.Type = Shape.POINT;
            cbShape.SelectedIndex = 0;
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

        private void cbShape_TabIndexChanged(object sender, EventArgs e)
        {
            if (cbShape.SelectedIndex == 0)
            {
                emitter.Type = Shape.POINT;
            }
            else if (cbShape.SelectedIndex == 1)
            {
                emitter.Type = Shape.CIRCLE;
                emitter.Radius = (float)nudRad.Value;
            }
            else if (cbShape.SelectedIndex == 2)
            {
                emitter.Type = Shape.SQUARE;
                emitter.Width = (int)nudWidth.Value;  
                emitter.Height = (int)nudHeight.Value;
            }
            else
            {
                emitter.Type = Shape.LINE;
                Vector2D tmp;
                tmp.x = (float)nudPointX.Value;
                tmp.y = (float)nudPointY.Value;
                emitter.Point = tmp;
                tmp.x = (float)nudPoint2X.Value;
                tmp.Y = (float)nudPoint2Y.Value;
                emitter.Point2 = tmp;
            }
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            emitter.Imgpath = null;
            btColorStart.BackColor = Color.White;
            btColorEnd.BackColor = Color.White;
            nudStartAlpha.Value = 255;
            nudEndAlpha.Value = 255;
            nudScaleStart.Value = 1;
            nudScaleEnd.Value = 1;
            nudRotStart.Value = 0;
            nudRotEnd.Value = 0;
            cbShape.SelectedIndex = 0;
            cbLooping.Checked = false;
            nudRad.Value = 0;
            nudHeight.Value = 50;
            nudWidth.Value = 50;
            nudPointX.Value = 250;
            nudPointY.Value = 250;
            nudPoint2X.Value = 250;
            nudPoint2Y.Value = 250;
            nudParticleNum.Value = 10;
            nudSpawnMax.Value = 1;
            nudSpawnMin.Value = 1;
            nudLifeMax.Value = 1;
            nudLifeMin.Value = 1;
            nudVelMaxStartX.Value = 150;
            nudVelMaxStartY.Value = 150;
            nudVelMaxEndX.Value = 100;
            nudVelMaxEndY.Value = 100;
            nudVelMinStartX.Value = 100;
            nudVelMinStartY.Value = 100;
            nudVelMinEndX.Value = 50;
            nudVelMinEndY.Value = 50;
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (particlefile == null)
            {
                string s = "No Particle Selected";
                DialogResult mb = MessageBox.Show(s);
                return;
            }

            Uri uri1;
            SaveFileDialog sf = new SaveFileDialog();
            if (DialogResult.OK == sf.ShowDialog())
            {
                uri1 = new Uri(Path.Combine(filepath, sf.FileName));
                File.WriteAllText(uri1.LocalPath + ".lua", rtbLua.Text);


                XElement xRoot = new XElement("Ability");

                XAttribute xRange = new XAttribute("Range", nudRange.Value);
                xRoot.Add(xRange);
                XAttribute xAP = new XAttribute("APCost", nudAP.Value);
                xRoot.Add(xAP);
                XAttribute xCD = new XAttribute("Cooldown", nudCD.Value);
                xRoot.Add(xCD);
                XAttribute xTarget = new XAttribute("Target", nudTarget.Value);
                xRoot.Add(xTarget);
                XAttribute xSpellName = new XAttribute("SpellName", tbSpellName.Text);
                xRoot.Add(xSpellName);

                XAttribute xAttack;
                if (cbAttack.Checked)
                    xAttack = new XAttribute("Attack", 1);
                else
                    xAttack = new XAttribute("Attack", 0);
                xRoot.Add(xAttack);

                XAttribute xPhase;
                if (rbAttackPhase.Checked == true)
                    xPhase = new XAttribute("Phase", 0);
                else
                    xPhase = new XAttribute("Phase", 1);

                xRoot.Add(xPhase);

                Uri folder = new Uri(filepath);
                Uri lua = new Uri(uri1.LocalPath);
                Uri relative = folder.MakeRelativeUri(lua);
                XAttribute xLUA = new XAttribute("LuaPath", relative.ToString().Remove(0, 5) + ".lua");
                xRoot.Add(xLUA);

                Uri particle = new Uri(particlefile);
                Uri relative2 = folder.MakeRelativeUri(particle);
                XAttribute xParticle = new XAttribute("ParticlePath", relative.ToString().Remove(0, 5) + ".xml");
                xRoot.Add(xParticle);

                for (int x = 0; x < 9; x++)
                {
                    for (int y = 0; y < 9; y++)
                    {
                        if (grid[x, y].Selected == true)
                        {
                            XElement xTile = new XElement("Tile");
                            xRoot.Add(xTile);

                            XAttribute xPosX = new XAttribute("PosX", x - 4);
                            xTile.Add(xPosX);

                            XAttribute xPosY = new XAttribute("PosY", -y + 4);
                            xTile.Add(xPosY);
                        }
                    }
                }

                xRoot.Save(uri1.LocalPath + ".xml");
            }
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XElement xRoot = new XElement("ChosenPath");
            XAttribute xPath = new XAttribute("Path", filepath);
            xRoot.Add(xPath);
            xRoot.Save("Config.xml");

            this.DestroyHandle();
        }

        private void exitToolStripMenuItem_Click(object sender, FormClosingEventArgs e)
        {

        }
    }
}
