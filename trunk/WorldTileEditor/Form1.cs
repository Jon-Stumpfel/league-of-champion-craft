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
        //TextureId: The int used to catch normal tile set map Image
        int normtextureId;
        public int NormtextureId
        {
            get { return normtextureId; }
            set { normtextureId = value; }
        }


        //TileSetSize_RC: RC=(Rows&Columns) wdith==columns ; height==rows
        //this is for Calucatlating the rows and columns on the TilesetImage
        Size tilesetSize_RC = new Size(4, 2);
        public Size TileSetSize_RC
        {
            get { return tilesetSize_RC; }
            set { tilesetSize_RC = value; }
        }

        //Selected Tile Point: the top right point of the selected tile in the tileset
        //We jerryrig this to calucate the enum of a Tile;
        Point selectedTilePoint = new Point(0, 0);


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
        TileClass SelectedTile = new TileClass();


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
            
            String filename = "MapEditorTiles.png";
            NormtextureId= tm.LoadTexture(filename, 0);

        }

        public void UpdateTool()
        {
            UpdateTileset();
            UpdateMap();
        }

        public void RenderTool()
        {
            Point offset = new Point(0, 0);
            offset.X += MapGraphicsPanel.AutoScrollPosition.X;
            offset.Y += MapGraphicsPanel.AutoScrollPosition.Y;
            d3D.Clear(TilesetGraphicsPanel, Color.White);

            d3D.DeviceBegin();
            d3D.SpriteBegin();

            for (int i = 0; i < TileSetSize_RC.Height; ++i)
            {
                for (int j = 0; j < TileSetSize_RC.Width; ++j)
                {
                    Point magicpoint = new Point(i, j);
                    if (magicpoint == selectedTilePoint)
                    {
                        Rectangle drawrect = new Rectangle(j * TilePixelSize.Width + offset.X, i * TilePixelSize.Height + offset.Y, TilePixelSize.Width, TilePixelSize.Height);
                        d3D.DrawEmptyRect(drawrect, Color.Goldenrod);
                    }
                    else
                    {
                        Rectangle drawrect = new Rectangle(j * TilePixelSize.Width + offset.X, i * TilePixelSize.Height + offset.Y, TilePixelSize.Width, TilePixelSize.Height);
                        d3D.DrawEmptyRect(drawrect, Color.Black);
                    }
                }
            }
            Rectangle drawrect1 = new Rectangle(0,0, TilePixelSize.Width, TilePixelSize.Height);



            d3D.SpriteEnd();
            d3D.DeviceEnd();
            d3D.Present();

            d3D.Clear(MapGraphicsPanel, Color.White);

            d3D.DeviceBegin();
            d3D.SpriteBegin();

            for (int i = 0; i < Mapsize.Height; ++i)
            {
                for (int j = 0; j < Mapsize.Width; ++j)
                {
                    Rectangle drawrect = new Rectangle(j * TilePixelSize.Width + offset.X, i * TilePixelSize.Height + offset.Y, TilePixelSize.Width, TilePixelSize.Height);
                    d3D.DrawEmptyRect(drawrect, Color.Black);
                }
            }
            Rectangle drawrect3 = new Rectangle(0, 0, TilePixelSize.Width, TilePixelSize.Height);

             //tm.Draw(textureId, 0, 0, 1.0f, 1.0f, drawrect1,0,0,0.0f,0);
          
            d3D.SpriteEnd();
            d3D.DeviceEnd();
            d3D.Present();
           
        }

        private void MapGraphicsPanel_Paint(object sender, PaintEventArgs e)
        { 
            Point offset = new Point(0, 0);
            offset.X += MapGraphicsPanel.AutoScrollPosition.X;
            offset.Y += MapGraphicsPanel.AutoScrollPosition.Y;
            
        }

        private void TilesetGraphicsPanel_Paint(object sender, PaintEventArgs e)
        {
            //Point offset = new Point(0, 0);
            //offset.X += TilesetGraphicsPanel.AutoScrollPosition.X;
            //offset.Y += TilesetGraphicsPanel.AutoScrollPosition.Y;
            //Pen Selection = new Pen(Color.Goldenrod, 5.0f);
            //e.Graphics.DrawRectangle(Selection, new Rectangle(SelectedTile.X * TilePixelSize.Width,
            //                                                  SelectedTile.Y * TilePixelSize.Height,
            //                                                  TilePixelSize.Width, TilePixelSize.Height));
            
            
        }

        private void TilesetGraphicsPanel_MouseClick(object sender, MouseEventArgs e)
        {
            int Xoutofrange = tilesetSize_RC.Width * TilePixelSize.Width;
            int Youtofrange = tilesetSize_RC.Height * TilePixelSize.Height;

            if (e.Location.X > 0 && e.Location.Y > 0 && e.Location.X < Xoutofrange && e.Location.Y < Youtofrange)
            {
                selectedTilePoint.X = e.X / tilePixelSize.Width;
                selectedTilePoint.Y = e.Y / tilePixelSize.Height;
            }
            UpdateTileset();
            
        }
        // updates for a whole new tile
        public void UpdateTileset()
        {

        }
        // OR showing more tiles on the map
        public void UpdateMap()
        {

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
