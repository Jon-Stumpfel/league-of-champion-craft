using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
namespace Animation_Editor_LOCC
{
    public partial class Form1 : Form
    {
        SGP.ManagedDirect3D d3D = SGP.ManagedDirect3D.Instance;
        SGP.ManagedTextureManager tm = SGP.ManagedTextureManager.Instance;

        int anchorx = -10;
        int anchory = -10;
        int pictureid = -1;
        string folderpath = "C:\\";
        public string FolderPath
        {
            get { return folderpath; }
            set { folderpath = value; }
        }

        bool looping = true;
        public bool Looping
        {
            get { return looping; }
            set { looping = value; }
        }

        Rectangle selectionrect = new Rectangle();
        public Rectangle Rect
        {
            get { return selectionrect; }
            set { selectionrect = value; }
        }

        List<CAnimation> animations = new List<CAnimation>();
        List<CAnimation> Animations
        {
            get { return animations; }
            set { animations = value; }
        }

        CAnimation curranim = new CAnimation();
        CAnimation CurrAnim
        {
            get { return curranim; }
            set { curranim = value; }
        }

        public Form1()
        {
            InitializeComponent();
            looping = true;
            d3D.InitManagedDirect3D(PreviewBox);
            d3D.InitManagedDirect3D(SpriteSheet);
            tm.InitManagedTextureManager(d3D.Device, d3D.Sprite);
            this.FormClosing += Form1_FormClosing;
            this.animname.KeyPress += new System.Windows.Forms.KeyPressEventHandler(CheckKeys);
            selectionrect.X = selectionrect.Y = selectionrect.Width = selectionrect.Height = -1;
        }

        public void Update()
        {
            if (animations != null)
            {
                for (int i = 0; i < animations.Count; i++)
                {
                    //check the time on each animation's current frame, update to next frame if you need to.
                }
            }
        }

        public void Render()
        {
            d3D.Clear(PreviewBox, Color.Beige);

            d3D.DeviceBegin();
            d3D.SpriteBegin();

            //Preview Box

            d3D.SpriteEnd();
            d3D.DeviceEnd();

            d3D.Present();

            d3D.Clear(SpriteSheet, Color.Beige);

            d3D.DeviceBegin();
            d3D.SpriteBegin();
            Rectangle therect = new Rectangle();
            therect.X = 0;
            therect.Y = 0;
            therect.Width = SpriteSheet.Size.Width;
            therect.Height = SpriteSheet.Size.Height;
            if (pictureid != -1)
                tm.Draw(pictureid, 0, 0, 1.0f, 1.0f, therect, 0, 0, 0, 0);
            d3D.Sprite.Flush();
            Rectangle temprect = new Rectangle();
            temprect.X = anchorx-5;
            temprect.Y = anchory-5;
            temprect.Width = 10;
            temprect.Height = 10;
            d3D.DrawRect(temprect, Color.DarkGreen);
            d3D.DrawEmptyRect(selectionrect, Color.Blue);
            d3D.SpriteEnd();
            d3D.DeviceEnd();

            d3D.Present();
        }

        private void IsLoopingCheckBox_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog OpenThis = new OpenFileDialog();
            OpenThis.Filter = "XML Files|*xml";
            OpenThis.InitialDirectory = folderpath;
            OpenThis.ShowDialog();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog SaveThis = new SaveFileDialog();
            SaveThis.Filter = "XML Files|*xml";
            SaveThis.InitialDirectory = folderpath;
            SaveThis.ShowDialog();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            looping = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            System.Xml.XmlDocument testxml = new System.Xml.XmlDocument();
        }

        private void setFileToSaveLoadFromToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveLoadBrowser = new FolderBrowserDialog();
            SaveLoadBrowser.ShowDialog();
            folderpath = SaveLoadBrowser.SelectedPath;
        }

        private void AddFrameButton_Click(object sender, EventArgs e)
        {
            CFrame tempframe = new CFrame();
            tempframe.FrameNum = 0;
            Rectangle temprect = new Rectangle();
            temprect.X = 0;
            temprect.Y = 0;
            temprect.Width = 0;
            temprect.Height = 0;
            tempframe.Rect = temprect;
            tempframe.TimePlayed = 0.0f;
            tempframe.AnchorPointX = 0;
            tempframe.AnchorPointY = 0;
            if (animations.Capacity >= 0 && animlist.SelectedIndex >= 0)
            {
                animations[animlist.SelectedIndex].FrameVec.Add(tempframe);
                numofframesinanim.Maximum++;
            }
        }

        private void CheckKeys(object sender, System.Windows.Forms.KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)13)
            {
                CAnimation tempanim = new CAnimation();
                tempanim.AnimLooping = false;
                tempanim.AnimType = 0;
                tempanim.CurrFrame = 0;
                tempanim.ElapsedTime = 0.0f;
                CFrame tempframe = new CFrame();
                tempframe.FrameNum = 0;
                Rectangle temprect = new Rectangle();
                temprect.X = 0;
                temprect.Y = 0;
                temprect.Width = 0;
                temprect.Height = 0;
                tempframe.Rect = temprect;
                tempframe.TimePlayed = 0.0f;
                tempframe.AnchorPointX = 0;
                tempframe.AnchorPointY = 0;
                tempanim.FrameVec.Add(tempframe);
                tempanim.ImagePath = "footman.png";
                tempanim.UnitType = 0;
                tempanim.NameOfAnim = animname.Text;
                animations.Add(tempanim);
                animlist.Items.Add(tempanim.NameOfAnim);
            }
        }

        private void numofframesinanim_ValueChanged(object sender, EventArgs e)
        {
            //this is the current frame, check the current frame and update all other boxes accordingly.
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            looping = false;
            Application.Exit();
        }

        private void helpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult HELP = MessageBox.Show("Just a few notes for this editor:"
            + Environment.NewLine + Environment.NewLine + "FRAME DURATION:" + Environment.NewLine + 
            "The Frame duration is in centiseconds. I know, it's weird, just keep in mind that every 100 in the box is one full second."
             + Environment.NewLine + Environment.NewLine + "ADDING AN ANIMATION/STARTING ANIMATIONS:" + Environment.NewLine + 
            "In order to have an animation to start with, type in the text box labeled for animation, HIT ENTER, then select the animaiton."
            + Environment.NewLine + Environment.NewLine + "PLACING TOP-LEFT FRAME CORNER/PLACING BOTTOM-RIGHT FRAME CORNER:"
            +Environment.NewLine + "Middle-click on the position to place the top-left corner. Left-click to place the bottom-right corner.");
        }

        private void animlist_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (animations.Count > 0)
            {
                for (int i = 0; i < animations.Count; i++)
                {
                    if (animations[i].NameOfAnim == animlist.SelectedItem.ToString())
                    {
                        numofframesinanim.Maximum = animations[i].FrameVec.Capacity;
                        numofframesinanim.Value = 0;
                    }
                }
            }
        }

        private void loadImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog OpenThis = new OpenFileDialog();
            OpenThis.InitialDirectory = folderpath;
            OpenThis.ShowDialog();
            string filedir = folderpath + "\\" + OpenThis.SafeFileName;
            pictureid = tm.LoadTexture(filedir, 0);
        }

        private void SpriteSheet_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Middle)
            {
                selectionrect.X = e.X;
                selectionrect.Y = e.Y;
                if (e.Y >= 0 && e.X >= 0 && e.X <= SpriteSheet.Size.Width && e.Y <= SpriteSheet.Size.Height)
                {
                    RectTopPos.Value = e.Y;
                }
                if (e.Y >= 0 && e.X >= 0 && e.X <= SpriteSheet.Size.Width && e.Y <= SpriteSheet.Size.Height)
                {
                    RectLeftPos.Value = e.X;
                }
            }
            if (e.Button == MouseButtons.Left)
            {
                selectionrect.Width = e.X - selectionrect.X;
                selectionrect.Height = e.Y - selectionrect.Y;
                if (e.Y >= 0 && e.X >= 0 && e.X <= SpriteSheet.Size.Width && e.Y <= SpriteSheet.Size.Height)
                {
                    RectBottomPos.Value = e.Y;
                }
                if (e.Y >= 0 && e.X >= 0 && e.X <= SpriteSheet.Size.Width && e.Y <= SpriteSheet.Size.Height)
                {
                    RectRightPos.Value = e.X;
                }
            }
            if (e.Button == MouseButtons.Right)
            {
                anchorx = e.X;
                anchory = e.Y;
                if (e.Y >= 0 && e.X >= 0 && e.X <= SpriteSheet.Size.Width && e.Y <= SpriteSheet.Size.Height)
                {
                    AnchorPosX.Value = e.X;
                }
                if (e.Y >= 0 && e.X >= 0 && e.X <= SpriteSheet.Size.Width && e.Y <= SpriteSheet.Size.Height)
                {
                    AnchorPosY.Value = e.Y;
                }
            }
        }

        private void SpriteSheet_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Middle)
            {
                selectionrect.X = e.X;
                selectionrect.Y = e.Y;
                if (e.Y >= 0 && e.X >= 0 && e.X <= SpriteSheet.Size.Width && e.Y <= SpriteSheet.Size.Height)
                {
                    RectTopPos.Value = e.Y;
                }
                if (e.Y >= 0 && e.X >= 0 && e.X <= SpriteSheet.Size.Width && e.Y <= SpriteSheet.Size.Height)
                {
                    RectLeftPos.Value = e.X;
                }
            }
            if (e.Button == MouseButtons.Left)
            {
                selectionrect.Width = e.X - selectionrect.X;
                selectionrect.Height = e.Y - selectionrect.Y;
                if (e.Y >= 0 && e.X >= 0 && e.X <= SpriteSheet.Size.Width && e.Y <= SpriteSheet.Size.Height)
                {
                    RectBottomPos.Value = e.Y;
                }
                if (e.Y >= 0 && e.X >= 0 && e.X <= SpriteSheet.Size.Width && e.Y <= SpriteSheet.Size.Height)
                {
                    RectRightPos.Value = e.X;
                }
            }
            if (e.Button == MouseButtons.Right)
            {
                anchorx = e.X;
                anchory = e.Y;
                if (e.Y >= 0 && e.X >= 0 && e.X <= SpriteSheet.Size.Width && e.Y <= SpriteSheet.Size.Height)
                {
                    AnchorPosX.Value = e.X;
                }
                if (e.Y >= 0 && e.X >= 0 && e.X <= SpriteSheet.Size.Width && e.Y <= SpriteSheet.Size.Height)
                {
                    AnchorPosY.Value = e.Y;
                }
            }
        }

        private void SpriteSheet_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Middle)
            {
                selectionrect.X = e.X;
                selectionrect.Y = e.Y;
            }
            if (e.Button == MouseButtons.Left)
            {
                selectionrect.Width = e.X - selectionrect.X;
                selectionrect.Height = e.Y - selectionrect.Y;
            }
            if (e.Button == MouseButtons.Right)
            {
                anchorx = e.X;
                anchory = e.Y;
            }
        }

        private void RectLeftPos_ValueChanged(object sender, EventArgs e)
        {
            if (selectionrect.X != -1)
            {
                int diff = selectionrect.X - (int)RectLeftPos.Value;
                Rectangle temp = new Rectangle();
                temp.X = selectionrect.X - diff;
                temp.Y = selectionrect.Y;
                temp.Width = selectionrect.Width + diff;
                temp.Height = selectionrect.Height;
                selectionrect = temp;
            }
        }

        private void RectRightPos_ValueChanged(object sender, EventArgs e)
        {
            if (selectionrect.X != -1)
            {
                int diff = selectionrect.Right - (int)RectRightPos.Value;
                Rectangle temp = new Rectangle();
                temp.X = selectionrect.X;
                temp.Y = selectionrect.Y;
                temp.Width = diff + selectionrect.Right - selectionrect.Left;
                temp.Height = selectionrect.Height;
                selectionrect = temp;
            }
        }

        private void RectTopPos_ValueChanged(object sender, EventArgs e)
        {

        }

        private void RectBottomPos_ValueChanged(object sender, EventArgs e)
        {

        }

        private void AnchorPosX_ValueChanged(object sender, EventArgs e)
        {

        }

        private void AnchorPosY_ValueChanged(object sender, EventArgs e)
        {

        }
    }
}
