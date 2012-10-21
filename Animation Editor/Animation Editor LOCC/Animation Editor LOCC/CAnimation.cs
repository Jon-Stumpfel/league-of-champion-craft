using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Animation_Editor_LOCC
{
    class CAnimation
    {
        List<CFrame> framevec = new List<CFrame>();
        public List<CFrame> FrameVec
        {
            get { return framevec; }
            set { framevec = value; }
        }

        bool animlooping = new bool();
        public bool AnimLooping
        {
            get { return animlooping; }
            set { animlooping = value; }
        }

        string imagepath = "";
        public string ImagePath
        {
            get { return imagepath; }
            set { imagepath = value; }
        }

        int unittype = new int();
        public int UnitType
        {
            get { return unittype; }
            set { unittype = value; }
        }

        int animtype = new int();
        public int AnimType
        {
            get { return animtype; }
            set { animtype = value; }
        }

        int currframe = new int();
        public int CurrFrame
        {
            get { return currframe; }
            set { currframe = value; }
        }

        float elapsedtime = new float();
        public float ElapsedTime
        {
            get { return elapsedtime; }
            set { elapsedtime = value; }
        }

        string nameofanim = "Default";
        public string NameOfAnim
        {
            get { return nameofanim; }
            set { nameofanim = value; }
        }
    }
}
