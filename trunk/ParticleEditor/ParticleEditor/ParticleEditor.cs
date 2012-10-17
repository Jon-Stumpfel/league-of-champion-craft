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
            if (emitter.Imgpath == null)
            {
                string s = "No Particle Selected";
                DialogResult mb = MessageBox.Show(s);
                return;
            }

            SaveFileDialog sf = new SaveFileDialog();
            sf.ShowDialog();
            
            XElement xRoot = new XElement("Particle");
            Uri folder = new Uri(filepath);
            Uri img = new Uri(emitter.Imgpath);
            Uri rel = folder.MakeRelativeUri(img);

            XAttribute xImage = new XAttribute("Image", rel.ToString().Remove(0,5));
            xRoot.Add(xImage);

            XAttribute xColorStartA = new XAttribute("ColorStartA", nudStartAlpha.Value);
            xRoot.Add(xColorStartA);
            XAttribute xColorStartR = new XAttribute("ColorStartR", btColorStart.BackColor.R);
            xRoot.Add(xColorStartR);
            XAttribute xColorStartG = new XAttribute("ColorStartG", btColorStart.BackColor.G);
            xRoot.Add(xColorStartG);
            XAttribute xColorStartB = new XAttribute("ColorStartB", btColorStart.BackColor.B);
            xRoot.Add(xColorStartB);

            XAttribute xColorEndA = new XAttribute("ColorEndA", nudEndAlpha.Value);
            xRoot.Add(xColorEndA);
            XAttribute xColorEndR = new XAttribute("ColorEndR", btColorEnd.BackColor.R);
            xRoot.Add(xColorEndR);
            XAttribute xColorEndG = new XAttribute("ColorEndG", btColorEnd.BackColor.G);
            xRoot.Add(xColorEndG);
            XAttribute xColorEndB = new XAttribute("ColorEndB", btColorEnd.BackColor.B);
            xRoot.Add(xColorEndB);

            XAttribute xScaleStart = new XAttribute("ScaleStart", nudScaleStart.Value);
            xRoot.Add(xScaleStart);
            XAttribute xScaleEnd = new XAttribute("ScaleEnd", nudScaleEnd.Value);
            xRoot.Add(xScaleEnd);

            XAttribute xRotationStart = new XAttribute("RotStart", nudRotStart.Value);
            xRoot.Add(xRotationStart);
            XAttribute xRotationEnd = new XAttribute("RotEnd", nudRotEnd.Value);
            xRoot.Add(xRotationEnd);

            XAttribute xShape = new XAttribute("Shape", cbShape.SelectedIndex);
            xRoot.Add(xShape);

            XAttribute xLoop = new XAttribute("Looping", cbLooping.Checked ? 1 : 0);
            xRoot.Add(xLoop);

            XAttribute xRadius = new XAttribute("Radius", nudRad.Value);
            xRoot.Add(xRadius);

            XAttribute xHeight = new XAttribute("Height", nudHeight.Value);
            xRoot.Add(xHeight);

            XAttribute xWidth = new XAttribute("Width", nudWidth.Value);
            xRoot.Add(xWidth);

            XAttribute xPointX = new XAttribute("PointX", nudPointX.Value);
            xRoot.Add(xPointX);
            XAttribute xPointY = new XAttribute("PointY", nudPointY.Value);
            xRoot.Add(xPointY);
            XAttribute xPoint2X = new XAttribute("Point2X", nudPoint2X.Value);
            xRoot.Add(xPoint2X);
            XAttribute xPoint2Y = new XAttribute("Point2Y", nudPoint2Y.Value);
            xRoot.Add(xPoint2Y);

            XAttribute xParticleNum = new XAttribute("NumParticles", nudParticleNum.Value);
            xRoot.Add(xParticleNum);

            XAttribute xSpawnMax = new XAttribute("SpawnMax", nudSpawnMax.Value);
            xRoot.Add(xSpawnMax);
            XAttribute xSpawnMin = new XAttribute("SpawnMin", nudSpawnMin.Value);
            xRoot.Add(xSpawnMin);

            XAttribute xLifeMax = new XAttribute("LifeMax", nudLifeMax.Value);
            xRoot.Add(xLifeMax);
            XAttribute xLifeMin = new XAttribute("LifeMin", nudLifeMin.Value);
            xRoot.Add(xLifeMin);

            XAttribute xVelStartMaxX = new XAttribute("VelStartMaxX", nudVelMaxStartX.Value);
            xRoot.Add(xVelStartMaxX);
            XAttribute xVelStartMaxY = new XAttribute("VelStartMaxY", nudVelMaxStartY.Value);
            xRoot.Add(xVelStartMaxY);
            XAttribute xVelStartMinX = new XAttribute("VelStartMinX", nudVelMinStartX.Value);
            xRoot.Add(xVelStartMinX);
            XAttribute xVelStartMinY = new XAttribute("VelStartMinY", nudVelMinStartY.Value);
            xRoot.Add(xVelStartMinY);

            XAttribute xVelEndMaxX = new XAttribute("VelEndMaxX", nudVelMaxEndX.Value);
                xRoot.Add(xVelEndMaxX);                                       
            XAttribute xVelEndMaxY = new XAttribute("VelEndMaxY", nudVelMaxEndY.Value);
                xRoot.Add(xVelEndMaxY);                                       
            XAttribute xVelEndMinX = new XAttribute("VelEndMinX", nudVelMinEndX.Value);
                xRoot.Add(xVelEndMinX);                                       
            XAttribute xVelEndMinY = new XAttribute("VelEndMinY", nudVelMinEndY.Value);
                xRoot.Add(xVelEndMinY);

            xRoot.Save(sf.FileName + ".xml");
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files|*.*|Xml Files|*.xml";
            dlg.FilterIndex = 2;
            dlg.InitialDirectory = filepath;

            if (DialogResult.OK == dlg.ShowDialog())
            {
                XElement xRoot = XElement.Load(dlg.FileName); ;

                XAttribute xImage = xRoot.Attribute("Image");
                Uri uri = new Uri(Path.Combine(filepath, xImage.Value));
                emitter.Imgpath = uri.LocalPath;

                XAttribute xColorStartA = xRoot.Attribute("ColorStartA");
                nudStartAlpha.Value = decimal.Parse(xColorStartA.Value);
                XAttribute xColorStartR = xRoot.Attribute("ColorStartR");
                int r = int.Parse(xColorStartR.Value);
                XAttribute xColorStartG = xRoot.Attribute("ColorStartG");
                int g = int.Parse(xColorStartG.Value);
                XAttribute xColorStartB = xRoot.Attribute("ColorStartB");
                int b = int.Parse(xColorStartB.Value);

                btColorStart.BackColor = Color.FromArgb(255, r, g, b);

                XAttribute xColorEndA = xRoot.Attribute("ColorEndA");
                nudStartAlpha.Value = int.Parse(xColorStartA.Value);
                XAttribute xColorEndR = xRoot.Attribute("ColorEndR");
                r = int.Parse(xColorEndR.Value);
                XAttribute xColorEndG = xRoot.Attribute("ColorEndG");
                g = int.Parse(xColorEndG.Value);
                XAttribute xColorEndB = xRoot.Attribute("ColorEndB");
                b = int.Parse(xColorEndB.Value);
                btColorEnd.BackColor = Color.FromArgb(255, r, g, b);

                XAttribute xScaleStart = xRoot.Attribute("ScaleStart");
                nudScaleStart.Value = decimal.Parse(xScaleStart.Value);
                XAttribute xScaleEnd = xRoot.Attribute("ScaleEnd");
                nudScaleEnd.Value = decimal.Parse(xScaleEnd.Value);

                XAttribute xRotationStart = xRoot.Attribute("RotStart");
                nudRotStart.Value = decimal.Parse(xRotationStart.Value);
                XAttribute xRotationEnd = xRoot.Attribute("RotEnd");
                nudRotEnd.Value = decimal.Parse(xRotationEnd.Value);
                XAttribute xShape = xRoot.Attribute("Shape");
                cbShape.SelectedIndex = int.Parse(xShape.Value);

                XAttribute xLoop = xRoot.Attribute("Looping");
                int baba = int.Parse(xLoop.Value);
                if (baba == 0)
                    cbLooping.Checked = false;
                else
                    cbLooping.Checked = true;

                XAttribute xRadius = xRoot.Attribute("Radius");
                nudRad.Value = decimal.Parse(xRadius.Value);
                XAttribute xHeight = xRoot.Attribute("Height");
                nudHeight.Value = decimal.Parse(xHeight.Value);
                XAttribute xWidth = xRoot.Attribute("Width");
                nudWidth.Value = decimal.Parse(xWidth.Value);

                XAttribute xPointX = xRoot.Attribute("PointX");
                nudPointX.Value = decimal.Parse(xPointX.Value);
                XAttribute xPointY = xRoot.Attribute("PointY");
                nudPointY.Value = decimal.Parse(xPointY.Value);
                XAttribute xPoint2X = xRoot.Attribute("Point2X");
                nudPoint2X.Value = decimal.Parse(xPoint2X.Value);
                XAttribute xPoint2Y = xRoot.Attribute("Point2Y");
                nudPoint2Y.Value = decimal.Parse(xPoint2Y.Value);

                XAttribute xParticleNum = xRoot.Attribute("NumParticles");
                nudParticleNum.Value = decimal.Parse(xParticleNum.Value);

                XAttribute xSpawnMax = xRoot.Attribute("SpawnMax");
                nudSpawnMax.Value = decimal.Parse(xSpawnMax.Value);
                XAttribute xSpawnMin = xRoot.Attribute("SpawnMin");
                nudSpawnMin.Value = decimal.Parse(xSpawnMin.Value);

                XAttribute xLifeMax = xRoot.Attribute("LifeMax");
                nudLifeMax.Value = decimal.Parse(xLifeMax.Value);
                XAttribute xLifeMin = xRoot.Attribute("LifeMin");
                nudLifeMin.Value = decimal.Parse(xLifeMin.Value);

                XAttribute xVelStartMaxX = xRoot.Attribute("VelStartMaxX");
                nudVelMaxStartX.Value = decimal.Parse(xVelStartMaxX.Value);
                XAttribute xVelStartMaxY = xRoot.Attribute("VelStartMaxY");
                nudVelMaxStartY.Value = decimal.Parse(xVelStartMaxY.Value);
                XAttribute xVelStartMinX = xRoot.Attribute("VelStartMinX");
                nudVelMinStartX.Value = decimal.Parse(xVelStartMinX.Value);
                XAttribute xVelStartMinY = xRoot.Attribute("VelStartMinY");
                nudVelMinStartY.Value = decimal.Parse(xVelStartMinY.Value);

                XAttribute xVelEndMaxX = xRoot.Attribute("VelEndMaxX");
                nudVelMaxEndX.Value = decimal.Parse(xVelEndMaxX.Value);
                XAttribute xVelEndMaxY = xRoot.Attribute("VelEndMaxY");
                nudVelMaxEndY.Value = decimal.Parse(xVelEndMaxY.Value);
                XAttribute xVelEndMinX = xRoot.Attribute("VelEndMinX");
                nudVelMinEndX.Value = decimal.Parse(xVelEndMinX.Value);
                XAttribute xVelEndMinY = xRoot.Attribute("VelEndMinY");
                nudVelMinEndY.Value = decimal.Parse(xVelEndMinY.Value);
            }
        }

        public void ExitSave()
        {
            XElement xRoot = new XElement("ChosenPath");
            XAttribute xPath = new XAttribute("Path", filepath);
            xRoot.Add(xPath);
            xRoot.Save("Config.xml");
        }

        private void changePathToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            fbd.ShowDialog();
            filepath = fbd.SelectedPath;
        }

        private void ParticleEditor_FormClosing(object sender, FormClosingEventArgs e)
        {
            ExitSave();
            alive = false;
        }
    }
}
