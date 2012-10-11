using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SGP;

namespace WorldTileEditor
{
    public partial class Form1 : Form
    {
        SGP.ManagedDirect3D d3D = SGP.ManagedDirect3D.Instance;
        SGP.ManagedTextureManager tm = SGP.ManagedTextureManager.Instance;

        public bool looping = true;
        public bool Looping
        {
            get { return looping; }
            set { looping = value; }
        }

        TileClass[,] Map = new TileClass[10, 10];

        Size Mapsize = new Size(10, 10);

        enum TileSize
        {
            ___8 = 8,
            __16 = 16,
            __32 = 32,
            __64 = 64,
            _128 = 128
        }

        //TileSetSize_RC: RC=(Rows&Columns)
        //this is for Calucatlating the rows and columns on the TilesetImage
        Size tilesetSize_RC = new Size(2, 4);
        public Size TileSetSize_RC
        {
            get { return tilesetSize_RC; }
            set { tilesetSize_RC = value; }
        }

        //TilesetImage: the actual source file Image; 
        //use this varible' width and hieght to set the minsize of the window
        Bitmap tilesetImage = new Bitmap(Properties.Resources._default);
        public Bitmap Tileset
        {
            get { return tilesetImage; }
            set { tilesetImage = value; }
        }

        //TilePixelSize: the width and hieght of a tile, for the map or the tileset
        //messing with this will break the game right now. all the tiles need to be squares
        Size tilePixelSize = new Size(64, 64);
        public Size TilePixelSize
        {
            get { return tilePixelSize; }
            set { tilePixelSize = value; }
        }

        //SelectedTile: The Top-Right point of a selected tile on the tilset
        //this will be used to calculate switch tile is selected and will be placed on the map
        //TileClass SelectedTile = new TileClass();
        Point SelectedTile = new Point();


        public Form1()
        {
            Looping = true;
            InitializeComponent();
            this.WidthcomboBox1.DataSource = System.Enum.GetValues(typeof(TileSize));
            WidthcomboBox1.SelectedItem = TileSize.__64;
            this.HeightcomboBox2.DataSource = System.Enum.GetValues(typeof(TileSize));
            HeightcomboBox2.SelectedItem = TileSize.__64;
            d3D.InitManagedDirect3D(TilesetGraphicsPanel);
            d3D.InitManagedDirect3D(MapGraphicsPanel);
            tm.InitManagedTextureManager(d3D.Device, d3D.Sprite);
        }

        public void UpdateTool()
        {
            UpdateTileset();
            UpdateMap();
        }

        public void RenderTool()
        {
            //tm.LoadTexture("Resources\\_default.png", 0);
            Point offset = new Point(0, 0);
            offset.X += MapGraphicsPanel.AutoScrollPosition.X;
            offset.Y += MapGraphicsPanel.AutoScrollPosition.Y;

            for (int i = 0; i < TileSetSize_RC.Width; ++i)
            {
                for (int j = 0; j < TileSetSize_RC.Height; ++j)
                {
                    Rectangle drawrect= new Rectangle(j * TilePixelSize.Width + offset.X,i * TilePixelSize.Height + offset.Y,TilePixelSize.Width,TilePixelSize.Height);
                    d3D.DeviceBegin();
                    d3D.DrawRect(drawrect, 0, 0, 255);
                    d3D.Present();
                    d3D.DeviceEnd();
                }
            }
        }

        private void MapGraphicsPanel_Paint(object sender, PaintEventArgs e)
        { 
            Point offset = new Point(0, 0);
            offset.X += MapGraphicsPanel.AutoScrollPosition.X;
            offset.Y += MapGraphicsPanel.AutoScrollPosition.Y;
        }

        private void TilesetGraphicsPanel_Paint(object sender, PaintEventArgs e)
        {
            Point offset = new Point(0, 0);
            offset.X += TilesetGraphicsPanel.AutoScrollPosition.X;
            offset.Y += TilesetGraphicsPanel.AutoScrollPosition.Y;
            //e.Graphics.DrawImage(Tileset, offset);

            //width==rows; height =columns
            //use pixelsize when you need to create squares around the tiles
            //for (int i = 0; i < TileSetSize_RC.Width; ++i)
            //{
            //    for (int j = 0; j < TileSetSize_RC.Height; ++j)
            //    {
            //        e.Graphics.DrawRectangle(Pens.AntiqueWhite, new Rectangle(j * TilePixelSize.Width + offset.X, i * TilePixelSize.Height + offset.Y, TilePixelSize.Width, TilePixelSize.Height));
            //    }

            //}
            Pen Selection = new Pen(Color.Goldenrod, 5.0f);
            e.Graphics.DrawRectangle(Selection, new Rectangle(SelectedTile.X * TilePixelSize.Width,
                                                              SelectedTile.Y * TilePixelSize.Height,
                                                              TilePixelSize.Width, TilePixelSize.Height));
            
       
        }

        private void TilesetGraphicsPanel_MouseClick(object sender, MouseEventArgs e)
        {
            int Xoutofrange = tilesetSize_RC.Width * TilePixelSize.Width;
            int Youtofrange = tilesetSize_RC.Height * TilePixelSize.Height;

            if (e.Location.X > 0 && e.Location.Y > 0 && e.Location.X < Xoutofrange && e.Location.Y < Youtofrange)
            {
                SelectedTile.X = e.X / tilesetSize_RC.Width;
                SelectedTile.Y = e.Y / tilesetSize_RC.Height;
            }
            UpdateTileset();
            
        }
        // updates for a whole new tile
        public void UpdateTileset()
        {
            Graphics g = TilesetGraphicsPanel.CreateGraphics();
            Tileset.SetResolution(g.DpiX, g.DpiY);
            TilesetGraphicsPanel.AutoScrollMinSize = Tileset.Size;
        }
        // OR showing more tiles on the map
        public void UpdateMap()
        {
            Graphics g = MapGraphicsPanel.CreateGraphics();
            Tileset.SetResolution(g.DpiX, g.DpiY);
            MapGraphicsPanel.AutoScrollMinSize = Tileset.Size;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            looping = false;
        }
    }
}
