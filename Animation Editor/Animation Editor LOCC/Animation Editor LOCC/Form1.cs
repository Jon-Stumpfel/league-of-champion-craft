using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Linq;

namespace Animation_Editor_LOCC
{
    public partial class Form1 : Form
    {
        SGP.ManagedDirect3D d3D = SGP.ManagedDirect3D.Instance;
        SGP.ManagedTextureManager tm = SGP.ManagedTextureManager.Instance;
        DateTime timetocheckagainst = System.DateTime.Now;
        DateTime timethatisconstantlyupdated = System.DateTime.Now;
        int anchorx = 0;
        int anchory = 0;
        int pictureid = -1;
        bool pause = false;
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
            selectionrect.X = selectionrect.Y = selectionrect.Width = selectionrect.Height = 0;
        }

        public void Update()
        {
            timethatisconstantlyupdated = System.DateTime.Now;
            TimeSpan temptime = timethatisconstantlyupdated - timetocheckagainst;
            if (animations != null)
            {
                for (int i = 0; i < animations.Count; i++)
                {
                    if (animlist.SelectedItem != null)
                    {
                        //check the time on each animation's current frame, update to next frame if you need to.
                        if (animations[i].FrameVec[animations[i].CurrFrame].TimePlayed / 100 <= temptime.TotalSeconds
                            && animations[i].NameOfAnim == animlist.SelectedItem.ToString())
                        {
                            if (pause == true)
                            {

                            }
                            else
                            {
                                if (animations[i].FrameVec.Count - 1 == animations[i].CurrFrame)
                                    animations[i].CurrFrame = 0;
                                else
                                    animations[i].CurrFrame += 1;
                            }
                            timetocheckagainst = System.DateTime.Now;
                        }
                    }
                }
            }
        }

        public void Render()
        {
            d3D.Clear(PreviewBox, Color.White);

            d3D.DeviceBegin();
            d3D.SpriteBegin();

            //Preview Box
            if (animations != null)
            {
                for (int i = 0; i < animations.Count; i++)
                {
                    if (animlist.SelectedItem != null)
                    {
                        if (animations[i].NameOfAnim == animlist.SelectedItem.ToString() && pictureid != -1)
                        {
                            Point AnchorOffset = new Point();
                            AnchorOffset.X = animations[i].FrameVec[animations[i].CurrFrame].Rect.X - animations[i].FrameVec[animations[i].CurrFrame].AnchorPointX;
                            AnchorOffset.Y = animations[i].FrameVec[animations[i].CurrFrame].Rect.Y - animations[i].FrameVec[animations[i].CurrFrame].AnchorPointY;
                            tm.Draw(pictureid, 50-AnchorOffset.X, 50-AnchorOffset.Y, 1.0f, 1.0f, animations[i].FrameVec[animations[i].CurrFrame].Rect, 0, 0, 0, Color.White.ToArgb());
                        }
                    }
                }
            }
            d3D.SpriteEnd();
            d3D.DeviceEnd();

            d3D.Present();

            d3D.Clear(SpriteSheet, Color.White);

            d3D.DeviceBegin();
            d3D.SpriteBegin();
            Rectangle therect = new Rectangle();
            therect.X = 0;
            therect.Y = 0;
            therect.Width = SpriteSheet.Size.Width;
            therect.Height = SpriteSheet.Size.Height;
            if (pictureid != -1)
                tm.Draw(pictureid, 100, 0, 1.0f, 1.0f, therect, 0, 0, 0, Color.White.ToArgb());
            d3D.Sprite.Flush();
            Rectangle temprect = new Rectangle();
            temprect.X = anchorx-2;
            temprect.Y = anchory-2;
            temprect.Width = 4;
            temprect.Height = 4;
            d3D.DrawRect(temprect, Color.Red);
            d3D.DrawEmptyRect(selectionrect, Color.Blue);
            d3D.SpriteEnd();
            d3D.DeviceEnd();

            d3D.Present();
        }

        private void IsLoopingCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (IsLoopingCheckBox.Checked == true)
            {
                for (int i = 0; i < animations.Count; i++)
                {
                    if (animations[i].NameOfAnim == animlist.SelectedItem.ToString())
                    {
                        animations[i].AnimLooping = true;
                    }
                }
            }
            else
            {
                for (int i = 0; i < animations.Count; i++)
                {
                    if (animations[i].NameOfAnim == animlist.SelectedItem.ToString())
                    {
                        animations[i].AnimLooping = false;
                    }
                }
            }
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog OpenThis = new OpenFileDialog();
            OpenThis.Filter = "XML Files|*xml";
            OpenThis.InitialDirectory = folderpath;
            if (DialogResult.OK == OpenThis.ShowDialog())
            {
                XElement pRoot = XElement.Load(OpenThis.FileName);
                IEnumerable<XElement> xAnimations = pRoot.Elements();
                foreach (XElement Animation in xAnimations)
                {
                    CAnimation tempanim = new CAnimation();
                    tempanim.UnitType = (int)Animation.Attribute("UnitType");
                    tempanim.AnimType = (int)Animation.Attribute("AnimType");
                    tempanim.AnimLooping = (bool)Animation.Attribute("IsLooping");
                    tempanim.ImagePath = (string)Animation.Attribute("ImgName");
                    tempanim.CurrFrame = (int)Animation.Attribute("CurrentFrame");
                    tempanim.NameOfAnim = (string)Animation.Attribute("AnimationName");
                    IEnumerable<XElement> xFrames = Animation.Elements();
                    foreach (XElement Frame in xFrames)
                    {
                        CFrame tempframe = new CFrame();
                        tempframe.FrameNum = (int)Frame.Attribute("FrameNumber");
                        tempframe.TimePlayed = (int)Frame.Attribute("TimeForFrameToRun");
                        Rectangle temprect = new Rectangle();
                        temprect.Y = (int)Frame.Attribute("top");
                        temprect.X = (int)Frame.Attribute("left");
                        temprect.Width = (int)Frame.Attribute("right") - temprect.X;
                        temprect.Height = (int)Frame.Attribute("bottom") - temprect.Y;
                        tempframe.Rect = temprect;
                        tempframe.AnchorPointX = (int)Frame.Attribute("AnchorX");
                        tempframe.AnchorPointY = (int)Frame.Attribute("AnchorY");
                        tempanim.FrameVec.Add(tempframe);
                    }
                    Animations.Add(tempanim);
                    animlist.Items.Add(tempanim.NameOfAnim);
                }
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog SaveThis = new SaveFileDialog();
            SaveThis.Filter = "XML Files|*xml";
            SaveThis.InitialDirectory = folderpath;
            if (DialogResult.OK == SaveThis.ShowDialog())
            {
                XElement pRoot = new XElement("Animations");
                for (int i = 0; i < Animations.Count; i++)
                {
                    XElement Animation = new XElement("Animation");
                    if (animlist.SelectedItem != null)
                    {
                        if (animations[i].NameOfAnim == animlist.SelectedItem.ToString())
                        {
                            Animation.Add(new XAttribute("UnitType", UnitType.SelectedIndex));
                            Animation.Add(new XAttribute("AnimType", AnimType.SelectedIndex));
                            if (IsLoopingCheckBox.Checked == true)
                                Animation.Add(new XAttribute("IsLooping", 1));
                            else
                                Animation.Add(new XAttribute("IsLooping", 0));
                        }
                        else
                        {
                            Animation.Add(new XAttribute("UnitType", Animations[i].UnitType.ToString()));
                            Animation.Add(new XAttribute("AnimType", Animations[i].AnimType.ToString()));
                            if (animations[i].AnimLooping == true)
                                Animation.Add(new XAttribute("IsLooping", 1));
                            else
                                Animation.Add(new XAttribute("IsLooping", 0));
                        }
                    }
                    Animation.Add(new XAttribute("ImgName", Animations[i].ImagePath));
                    Animation.Add(new XAttribute("CurrentFrame", Animations[i].CurrFrame.ToString()));
                    Animation.Add(new XAttribute("AnimationName", Animations[i].NameOfAnim));
                    for (int f = 0; f < Animations[i].FrameVec.Count; f++)
                    {
                        XElement Frame = new XElement("Frame");
                        Frame.Add(new XAttribute("FrameNumber", Animations[i].FrameVec[f].FrameNum.ToString()));
                        Frame.Add(new XAttribute("TimeForFrameToRun", Animations[i].FrameVec[f].TimePlayed.ToString()));
                        Frame.Add(new XAttribute("top", Animations[i].FrameVec[f].Rect.Top.ToString()));
                        Frame.Add(new XAttribute("right", Animations[i].FrameVec[f].Rect.Right.ToString()));
                        Frame.Add(new XAttribute("bottom", Animations[i].FrameVec[f].Rect.Bottom.ToString()));
                        Frame.Add(new XAttribute("left", Animations[i].FrameVec[f].Rect.Left.ToString()));
                        Frame.Add(new XAttribute("AnchorX", Animations[i].FrameVec[f].AnchorPointX.ToString()));
                        Frame.Add(new XAttribute("AnchorY", Animations[i].FrameVec[f].AnchorPointY.ToString()));
                        Animation.Add(Frame);
                    }
                    pRoot.Add(Animation);
                }
                if(SaveThis.FileName.EndsWith(".xml"))
                {
                    pRoot.Save(SaveThis.FileName);
                }
                else
                    pRoot.Save(SaveThis.FileName + ".xml");
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            looping = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

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
                tempanim.ImagePath = "";
                tempanim.UnitType = 0;
                tempanim.NameOfAnim = animname.Text;
                animations.Add(tempanim);
                animlist.Items.Add(tempanim.NameOfAnim);
            }
        }

        private void numofframesinanim_ValueChanged(object sender, EventArgs e)
        {
            if (animations.Count > 0)
            {
                for (int i = 0; i < animations.Count; i++)
                {
                    if (animations[i].NameOfAnim == animlist.SelectedItem.ToString())
                    {
                        AnchorPosX.Value = Animations[i].FrameVec[(int)numofframesinanim.Value].AnchorPointX;
                        AnchorPosY.Value = Animations[i].FrameVec[(int)numofframesinanim.Value].AnchorPointY;
                        RectLeftPos.Value = Animations[i].FrameVec[(int)numofframesinanim.Value].Rect.Left;
                        RectRightPos.Value = Animations[i].FrameVec[(int)numofframesinanim.Value].Rect.Right;
                        RectTopPos.Value = Animations[i].FrameVec[(int)numofframesinanim.Value].Rect.Top;
                        RectBottomPos.Value = Animations[i].FrameVec[(int)numofframesinanim.Value].Rect.Bottom;
                        animations[i].CurrFrame = (int)numofframesinanim.Value;
                    }
                }
            }
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
                        numofframesinanim.Maximum = animations[i].FrameVec.Count-1;
                        numofframesinanim.Value = 0;
                        if (animations[i].ImagePath != "")
                        {
                            string filedir = folderpath + "\\" + animations[i].ImagePath;
                            pictureid = tm.LoadTexture(filedir, 0);
                        }
                        UnitType.SelectedIndex = animations[i].UnitType;
                        AnimType.SelectedIndex = animations[i].AnimType;
                        AnchorPosY.Value = animations[i].FrameVec[animations[i].CurrFrame].AnchorPointY;
                        AnchorPosX.Value = animations[i].FrameVec[animations[i].CurrFrame].AnchorPointX;
                        FrameDuration.Value = (decimal)animations[i].FrameVec[animations[i].CurrFrame].TimePlayed;
                        RectLeftPos.Value = animations[i].FrameVec[animations[i].CurrFrame].Rect.X;
                        RectTopPos.Value = animations[i].FrameVec[animations[i].CurrFrame].Rect.Y;
                        IsLoopingCheckBox.Checked = Animations[i].AnimLooping;
                    }
                }
            }
        }

        private void loadImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog OpenThis = new OpenFileDialog();
            OpenThis.InitialDirectory = folderpath;
            if (DialogResult.OK == OpenThis.ShowDialog())
            {
                string filedir = folderpath + "\\" + OpenThis.SafeFileName;
                pictureid = tm.LoadTexture(filedir, 0);
                for (int i = 0; i < animations.Count; i++)
                {
                    if (animations[i].NameOfAnim == animlist.SelectedItem.ToString())
                    {
                        animations[i].ImagePath = OpenThis.SafeFileName;
                    }
                }
            }
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
                    RectLeftPos.Value = e.X;
                    if (selectionrect.Width == -1)
                    {
                        RectRightPos.Value = e.X;
                    }
                    if (selectionrect.Height == -1)
                    {
                        RectBottomPos.Value = e.Y;
                    }
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
                int diff = (selectionrect.X + selectionrect.Width) - (int)RectRightPos.Value;
                Rectangle temp = new Rectangle();
                temp.X = selectionrect.X;
                temp.Y = selectionrect.Y;
                temp.Width = selectionrect.Width - diff;
                temp.Height = selectionrect.Height;
                selectionrect = temp;
            }
        }

        private void RectTopPos_ValueChanged(object sender, EventArgs e)
        {
            if (selectionrect.Y != -1)
            {
                int diff = selectionrect.Y - (int)RectTopPos.Value;
                Rectangle temp = new Rectangle();
                temp.X = selectionrect.X;
                temp.Y = selectionrect.Y - diff;
                temp.Width = selectionrect.Width;
                temp.Height = selectionrect.Height + diff;
                selectionrect = temp;
            }
        }

        private void RectBottomPos_ValueChanged(object sender, EventArgs e)
        {
            if (selectionrect.Y != -1)
            {
                int diff = (selectionrect.Y + selectionrect.Height) - (int)RectBottomPos.Value;
                Rectangle temp = new Rectangle();
                temp.X = selectionrect.X;
                temp.Y = selectionrect.Y;
                temp.Width = selectionrect.Width;
                temp.Height = selectionrect.Height - diff;
                selectionrect = temp;
            }
        }

        private void AnchorPosX_ValueChanged(object sender, EventArgs e)
        {
            if (anchorx != -10)
            {
                anchorx = (int)AnchorPosX.Value;
            }
        }

        private void AnchorPosY_ValueChanged(object sender, EventArgs e)
        {
            anchory = (int)AnchorPosY.Value;
        }

        private void SaveFrameButton_Click(object sender, EventArgs e)
        {
            if (animations != null)
            {
                for (int i = 0; i < animations.Count; i++)
                {
                    if (animations[i].NameOfAnim == animlist.SelectedItem.ToString()
                        && animlist.SelectedItem != null)
                    {
                        animations[i].UnitType = UnitType.SelectedIndex;
                        animations[i].AnimType = AnimType.SelectedIndex;
                        animations[i].FrameVec[(int)numofframesinanim.Value].AnchorPointX = (int)AnchorPosX.Value;
                        animations[i].FrameVec[(int)numofframesinanim.Value].AnchorPointY = (int)AnchorPosY.Value;
                        animations[i].FrameVec[(int)numofframesinanim.Value].Rect = new Rectangle((int)RectLeftPos.Value, (int)RectTopPos.Value,
                            (int)RectRightPos.Value - (int)RectLeftPos.Value, (int)RectBottomPos.Value - (int)RectTopPos.Value);
                        animations[i].FrameVec[(int)numofframesinanim.Value].TimePlayed = (int)FrameDuration.Value;
                        animations[i].FrameVec[(int)numofframesinanim.Value].FrameNum = (int)numofframesinanim.Value;
                    }
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            pause = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            pause = false;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < animations.Count; i++)
            {
                if (animations[i].NameOfAnim == animlist.SelectedItem.ToString())
                {
                    animations[i].CurrFrame = 0;
                }
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < animations.Count; i++)
            {
                if (animations[i].NameOfAnim == animlist.SelectedItem.ToString())
                {
                    if (animations[i].CurrFrame == 0)
                        animations[i].CurrFrame = animations[i].FrameVec.Count - 1;
                    else
                        animations[i].CurrFrame--;
                }
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < animations.Count; i++)
            {
                if (animations[i].NameOfAnim == animlist.SelectedItem.ToString())
                {
                    if (animations[i].CurrFrame == animations[i].FrameVec.Count-1)
                        animations[i].CurrFrame = 0;
                    else
                        animations[i].CurrFrame++;
                }
            }
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            SaveLoadBrowser = new FolderBrowserDialog();
            SaveLoadBrowser.ShowDialog();
            folderpath = SaveLoadBrowser.SelectedPath;
        }
    }
}
