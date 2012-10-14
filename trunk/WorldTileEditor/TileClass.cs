using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Linq;

namespace WorldTileEditor
{
    enum TILE_TYPE { TT_PLAINS=0, TT_FOREST=1, TT_MOUNTAINS=2, TT_WATER=3, TT_FARM=4, TT_MILL=5, TT_MINE=6, TT_CASTLE=7 };
    class TileClass
    {

        TILE_TYPE m_eTType;
        internal TILE_TYPE TType
        {
            get { return m_eTType; }
            set { m_eTType = value; }
        }

        int m_nPlayerID;
        public int PlayerID
        {
            get { return m_nPlayerID; }
            set { m_nPlayerID = value; }
        }

        Point m_sPos;
        public Point Position
        {
            get { return m_sPos; }
            set { m_sPos = value; }
        }


        Byte ucStatus;
        public Byte Status
        {
            get { return ucStatus; }
            set { ucStatus = value; }
        }

        bool bfrozen;
        public bool Frozen
        {
            get { return bfrozen; }
            set { bfrozen = value; }
        }

        bool bresource;
        public bool Resource
        {
            get { return bresource; }
            set { bresource = value; }
        }

        bool boccupied;
        public bool Occupied
        {
            get { return boccupied; }
            set { boccupied = value; }
        }

        bool bcapturing;
        public bool Capturing
        {
            get { return bcapturing; }
            set { bcapturing = value; }
        }

        bool bcaptured;
        public bool Captured
        {
            get { return bcaptured; }
            set { bcaptured = value; }
        }

        bool bisDead;
        public bool IsDead
        {
            get { return bisDead; }
            set { bisDead = value; }
        }

        bool bisPassable;
        public bool IsPassable
        {
            get { return bisPassable; }
            set { bisPassable = value; }
        }

        Rectangle rect;
        public Rectangle Rect
        {
            get { return rect; }
            set { rect = value; }
        }

        public TileClass()
        {
            TType = TILE_TYPE.TT_PLAINS;
            Status = 0;
            PlayerID = 0;
            Position = new Point();
            Frozen = false;
            Resource = false;
            Occupied = false;
            Capturing = false;
            Captured = false;
            IsDead = false;
            IsPassable = false;
            Rect = new Rectangle(0, 0, 64, 64);
        }

        public TileClass(TILE_TYPE eTile, bool bResouceTile, Point sPos)
        {
            TType = TILE_TYPE.TT_PLAINS;
            Status = 0;
            Resource = bResouceTile;
            if (Resource)
            {
                Status += 2;
            }
            PlayerID = 0;
            Position = sPos;
        }

    }
}
