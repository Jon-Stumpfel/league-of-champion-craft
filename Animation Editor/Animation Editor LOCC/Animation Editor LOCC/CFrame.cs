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
    class CFrame
    {
        Rectangle rect = new Rectangle();
        public Rectangle Rect
        {
            get { return rect; }
            set { rect = value; }
        }

        int framenum = new int();
        public int FrameNum
        {
            get { return framenum; }
            set { framenum = value; }
        }

        float timeplayed = new float();
        public float TimePlayed
        {
            get { return timeplayed; }
            set { timeplayed = value; }
        }

        int anchorpointx = new int();
        public int AnchorPointX
        {
            get { return anchorpointx; }
            set { anchorpointx = value; }
        }

        int anchorpointy = new int();
        public int AnchorPointY
        {
            get { return anchorpointy; }
            set { anchorpointy = value; }
        }
    }
}
