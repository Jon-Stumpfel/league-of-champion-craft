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
    enum TILE_TYPE { TT_PLAINS, TT_FOREST, TT_MOUNTAINS, TT_WATER, TT_FARM, TT_MILL, TT_MINE, TT_CASTLE };
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

        int m_nPixWidth;
        public int PixWidth
        {
            get { return m_nPixWidth; }
            set { m_nPixWidth = value; }
        }

        int m_nPixHeight;
        public int PixHeight
        {
            get { return m_nPixHeight; }
            set { m_nPixHeight = value; }
        }

        int m_nTileWidth;
        public int TileWidth
        {
            get { return m_nTileWidth; }
            set { m_nTileWidth = value; }
        }

        int m_nTileHeight;
        public int TileHeight
        {
            get { return m_nTileHeight; }
            set { m_nTileHeight = value; }
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

        public Rectangle CellAlgorithm(int id)
        {
            if (id >= 0 && id < 8)
                return Rectangle.Empty;

            Rectangle rSource = new Rectangle((id % 4) * PixWidth, (id / 4) * PixHeight, TileWidth, TileHeight);

            //rSource.Left	= (id % 4) * m_nTileWidth;
            //rSource.		= (id / 4) * m_nTileHeight;

            //rSource.right	= rSource.left	+ m_nTileWidth;
            //rSource.bottom	= rSource.top	+ m_nTileHeight;

            return rSource;

        }
    }
}
