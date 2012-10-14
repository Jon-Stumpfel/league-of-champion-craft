using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Linq;
using System.IO;

namespace Spell_Editor
{
    public partial class Form1 : Form
    {
        public struct Grid
        {
            private bool selected;

            public bool Selected
            {
                get { return selected; }
                set { selected = value; }
            }
            private Rectangle rect;

            public Rectangle Rect
            {
                get { return rect; }
                set { rect = value; }
            }
        }

        public Grid[,] grid = new Grid[9, 9];

        public int GridWidth = 52, GridHeight = 52;

        public string filepath, particlefile;

        public Form1()
        {
            InitializeComponent();

            d3d.InitManagedDirect3D(panel1);

            XElement xRoot;
            if( File.Exists("Config.xml") )
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
            
            for (int x = 0; x < 9; x++)
            {
                for (int y = 0; y < 9; y++)
                {
                    Rectangle rect = Rectangle.Empty;
                    rect.X = x * GridWidth;
                    rect.Y = y * GridHeight;
                    Size s = new Size(GridWidth, GridHeight);
                    rect.Size = s;
                    grid[x, y].Rect = rect;
                    grid[x, y].Selected = false;
                }
            }
        }

        SGP.ManagedDirect3D d3d = SGP.ManagedDirect3D.Instance;

        private void MouseClick(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                for (int x = 0; x < 9; x++)
                {
                    for (int y = 0; y < 9; y++)
                    {
                        Point p = new Point(e.X, e.Y);
                        if (grid[x, y].Rect.Contains(p))
                        {
                            if (grid[x, y].Selected)
                                grid[x, y].Selected = false;
                            else
                                grid[x, y].Selected = true;
                        }
                    }
                }
                panel1.Invalidate();
            }
        }

        private void graphicsPanel1_MouseDown(object sender, MouseEventArgs e)
        {
            MouseClick(e);
        }

        private void graphicsPanel1_Paint(object sender, PaintEventArgs e)
        {
            d3d.DeviceBegin();
            d3d.SpriteBegin();

            d3d.Clear(Color.Beige);
            d3d.Sprite.Flush();
            d3d.DrawRect(grid[4, 4].Rect, Color.Blue);

            for (int x = 0; x < 9; x++)
            {
                for (int y = 0; y < 9; y++)
                {
                    if (grid[x, y].Selected)
                    {
                        d3d.DrawRect(grid[x, y].Rect, Color.Red);
                        d3d.DrawEmptyRect(grid[x, y].Rect, Color.Black);
                    }
                    else
                        d3d.DrawEmptyRect(grid[x, y].Rect, Color.Black);
                }
            }

            d3d.DeviceEnd();
            d3d.SpriteEnd();

            d3d.Present(panel1);
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            for (int x = 0; x < 9; x++)
            {
                for (int y = 0; y < 9; y++)
                {
                    grid[x, y].Selected = false;
                }
            }

            nudAP.Value = 0;
            nudCD.Value = 0;
            nudRange.Value = 0;
            nudTarget.Value = 0;
            tbSpellName.Text = "";
            cbAttack.Checked = false;
            rbAttackPhase.Checked = true;
            rtbLua.ResetText();
            panel1.Invalidate();
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
                XAttribute xLUA = new XAttribute("LuaPath", relative + ".lua");
                xRoot.Add(xLUA);

                Uri particle = new Uri(particlefile);
                Uri relative2 = folder.MakeRelativeUri(particle);
                XAttribute xParticle = new XAttribute("ParticlePath", relative + ".xml");
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

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files|*.*|Xml Files|*.xml";
            dlg.FilterIndex = 2;
            dlg.InitialDirectory = filepath;

            if (DialogResult.OK == dlg.ShowDialog())
            {
                XElement xRoot = XElement.Load(dlg.FileName);

                XAttribute xRange = xRoot.Attribute("Range");
                nudRange.Value = decimal.Parse(xRange.Value);

                XAttribute xAP = xRoot.Attribute("APCost");
                nudAP.Value = decimal.Parse(xAP.Value);

                XAttribute xCD = xRoot.Attribute("Cooldown");
                nudCD.Value = decimal.Parse(xCD.Value);

                XAttribute xTarget = xRoot.Attribute("Target");
                nudTarget.Value = decimal.Parse(xTarget.Value);

                XAttribute xSpellName = xRoot.Attribute("SpellName");
                tbSpellName.Text = xSpellName.Value;

                XAttribute xAttack = xRoot.Attribute("Attack");
                int val = int.Parse(xAttack.Value);

                if (val == 0)
                    cbAttack.Checked = false;
                else
                    cbAttack.Checked = true;

                XAttribute xPhase = xRoot.Attribute("Phase");

                val = int.Parse(xPhase.Value);

                if (val == 0)
                {
                    rbAttackPhase.Checked = true;
                }
                else
                {
                    rbMovePhase.Checked = true;
                }

                XAttribute xLUA = xRoot.Attribute("LuaPath");
                Uri uri1 = new Uri(Path.Combine(filepath, xLUA.Value.Remove(0,5)));
                rtbLua.LoadFile(uri1.LocalPath, RichTextBoxStreamType.PlainText);

                XAttribute xParticle = xRoot.Attribute("ParticlePath");
                Uri uri2 = new Uri(Path.Combine(filepath, xParticle.Value.Remove(0,5)));

                IEnumerable<XElement> xTiles = xRoot.Elements();

                foreach (XElement xTile in xTiles)
                {
                    XAttribute xPosX = xTile.Attribute("PosX");
                    int PosX = int.Parse(xPosX.Value);

                    XAttribute xPosY = xTile.Attribute("PosY");
                    int PosY = int.Parse(xPosY.Value);

                    grid[PosX + 4, -PosY + 4].Selected = true;
                }

                panel1.Invalidate();
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
           XElement xRoot = new XElement("ChosenPath");
           XAttribute xPath = new XAttribute("Path", filepath);
           xRoot.Add(xPath);
           xRoot.Save("Config.xml");

            this.DestroyHandle();
        }

        private void changePathToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            fbd.ShowDialog();
            filepath = fbd.SelectedPath;
        }

        private void loadParticleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog of = new OpenFileDialog();
            if (DialogResult.OK == of.ShowDialog())
            {
                particlefile = of.FileName;
            }
        }
    }
}
