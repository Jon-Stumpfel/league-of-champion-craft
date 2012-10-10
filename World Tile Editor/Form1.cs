using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Linq;

namespace World_Tile_Editor
{
   
    public partial class Form1 : Form
    {
        //TilesetImage: the actual source file Image; 
        //use this varible' width and hieght to set the minsize of the window
        Bitmap tilesetImage = new Bitmap(Properties.Resources._default);
        public Bitmap Tileset
        {
            get { return tilesetImage; }
            set { tilesetImage = value; }
        }

        //TileSetSize_RC: RC=(Rows&Columns)
        //this is for Calucatlating the rows and columns on the TilesetImage
        Size tilesetSize_RC = new Size(2, 4);
        public Size TileSetSize_RC
        {
            get { return tilesetSize_RC; }
            set { tilesetSize_RC = value; }
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
        public Point SelectedTile = new Point(0, 0);

        //this is what you will use to select a tile on the tileset
        //public event MouseEventHandler TileSelect;

        //invalidates to refresh
        public void InvalidateTilesetPanel()
        {
            TilesetGraphicsPanel.Invalidate();
        }
        public void InvalidateMapPanel()
        {
            MapGraphicsPanel.Invalidate();
        }

        // updates for a whole new tile
        public void UpdateTileset()
        {
            Graphics g= TilesetGraphicsPanel.CreateGraphics();
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

        public Form1()
        {
            InitializeComponent();

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void loadTileToolStripMenuItem_Click(object sender, EventArgs e){}

        private void TilesetGraphicsPanel_Paint(object sender, PaintEventArgs e)
        {
            Point offset = new Point(0, 0);
            offset.X += TilesetGraphicsPanel.AutoScrollPosition.X;
            offset.Y += TilesetGraphicsPanel.AutoScrollPosition.Y;
            e.Graphics.DrawImage(Tileset, offset);

            //width==rows; height =columns
            //use pixelsize when you need to create squares around the tiles
            for (int i = 0; i < TileSetSize_RC.Width; ++i)
            {
                for (int j = 0; j < TileSetSize_RC.Height; ++j)
                {
                    e.Graphics.DrawRectangle(Pens.AntiqueWhite, new Rectangle(j * TilePixelSize.Width + offset.X,
                                             i * TilePixelSize.Height + offset.Y, TilePixelSize.Width, TilePixelSize.Height));
                }

            }
            Pen Selection = new Pen(Color.Azure, 5.0f);
            e.Graphics.DrawRectangle(Selection, new Rectangle(SelectedTile.X * TilePixelSize.Width + offset.X,
                                                              SelectedTile.Y * TilePixelSize.Height + offset.Y,
                                                              TilePixelSize.Width, TilePixelSize.Height));
        
        }

        private void TilesetGraphicsPanel_MouseClick(object sender, MouseEventArgs e)
        {
            int Xoutofrange = tilesetSize_RC.Width  * TilePixelSize.Width;
            int Youtofrange = tilesetSize_RC.Height * TilePixelSize.Height;

            if (e.Location.X > 0 && e.Location.Y > 0 && e.Location.X < Xoutofrange && e.Location.Y < Youtofrange)
            {
                SelectedTile.X = e.X / tilesetSize_RC.Width;
                SelectedTile.Y = e.Y / tilesetSize_RC.Height;
                TilesetGraphicsPanel.Invalidate();
            }
            TilesetGraphicsPanel.Update();

        }
        

        private void MapGraphicsPanel_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
