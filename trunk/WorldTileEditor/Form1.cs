using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SGP;
using System.Xml.Linq;


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
        String relativePath = "C:/";
        public String RelativePath
        {
            get { return relativePath; }
            set { relativePath = value; }
        }
        public struct Tileset
        {
            Rectangle rect;

            public Rectangle Rect
            {
                get { return rect; }
                set { rect = value; }
            }

            bool selected;
            public bool Selected
            {
                get { return selected; }
                set { selected = value; }
            }
        }

        public Rectangle CellAlgorithm(int id)
        {
            if (id < 0 && id > 8)
                return Rectangle.Empty;

            Rectangle rSource = new Rectangle(  (id % 4) * TilePixelSize.Width,
                                                (id / 4) * TilePixelSize.Height,
                                                TilePixelSize.Width, 
                                                TilePixelSize.Height);
            //rSource.Left	    = (id % 4) * m_nTileWidth;
            //rSource.Top	    = (id / 4) * m_nTileHeight;
            //rSource.right	    = rSource.left	+ m_nTileWidth;
            //rSource.bottom	= rSource.top	+ m_nTileHeight;

            return rSource;

        }

        TileClass[,] Map;

        Size Mapsize_RC = new Size(10, 10);
        Size MapPixelSize = new Size(0, 0);

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
        public Point SelectedTilePoint
        {
            get { return selectedTilePoint; }
            set { selectedTilePoint = value; }
        }

        TILE_TYPE selectTileType =TILE_TYPE.TT_PLAINS;
        internal TILE_TYPE SelectTileType
        {
            get { return selectTileType; }
            set { selectTileType = value; }
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
            TilePixelSize = new Size((int)WidthcomboBox1.Items[WidthcomboBox1.SelectedIndex], (int)HeightcomboBox2.Items[HeightcomboBox2.SelectedIndex]);
            MapPixelSize = TilePixelSize;
            Size minsize = new Size(TilePixelSize.Width * TileSetSize_RC.Width, TilePixelSize.Width * TileSetSize_RC.Height);
            TilesetGraphicsPanel.AutoScrollMinSize= minsize;

            String filename = "MapEditorTiles.png";
            NormtextureId= tm.LoadTexture(filename, 0);

            //MapGraphicsPanel.HorizontalScroll.Minimum=-200;
            //MapGraphicsPanel.AutoScrollPosition = new Point(0, 0);


            Map = new TileClass[10, 10];
            for (int x = 0;x < Mapsize_RC.Width; ++x)
            {
                for (int y = 0; y < Mapsize_RC.Height; ++y)
                {
                    Map[x, y] = new TileClass();
                    Rectangle temprect= new Rectangle(x * TilePixelSize.Width, y * TilePixelSize.Height, TilePixelSize.Width, TilePixelSize.Height);
                    Map[x, y].Rect = temprect;
                }
            }
        }

        public void UpdateTool()
        {
            //UpdateTileset();
            //UpdateMap();
        }

        public void RenderTool()
        {
            //Do stuff for the The Tilset
            Point Tilesetoffset = new Point(0, 0);
            Tilesetoffset.X += TilesetGraphicsPanel.AutoScrollPosition.X;
            Tilesetoffset.Y += TilesetGraphicsPanel.AutoScrollPosition.Y;
            d3D.Clear(TilesetGraphicsPanel, Color.White);

            d3D.DeviceBegin();
            d3D.SpriteBegin();  
            
            Rectangle fulltileset = new Rectangle(0, 0, TilePixelSize.Width * TileSetSize_RC.Width, TilePixelSize.Height * TileSetSize_RC.Height);
            tm.Draw(NormtextureId, Tilesetoffset.X, Tilesetoffset.Y, 1.0f, 1.0f, fulltileset, 0, 0, 0.0f, 0);
            d3D.Sprite.Flush();

            for (int i = 0; i < TileSetSize_RC.Height; ++i)
            {
                for (int j = 0; j < TileSetSize_RC.Width; ++j)
                {
                    Point pos = new Point(j * TilePixelSize.Width + Tilesetoffset.X, i * TilePixelSize.Height + Tilesetoffset.Y);
                    Rectangle drawrect = new Rectangle(pos.X , pos.Y , TilePixelSize.Width , TilePixelSize.Height);
                    d3D.DrawEmptyRect(drawrect, Color.Black);
                }
            }

            Point pos2 = new Point(selectedTilePoint.X * TilePixelSize.Width + Tilesetoffset.X, selectedTilePoint.Y * TilePixelSize.Height + Tilesetoffset.Y);
            Rectangle rect2 = new Rectangle(pos2.X, pos2.Y, TilePixelSize.Width, TilePixelSize.Height);
                    
           d3D.DrawEmptyRect(rect2, Color.Goldenrod);

            d3D.SpriteEnd();
            d3D.DeviceEnd();
            d3D.Present();

            //Do stuff for the map
            d3D.Clear(MapGraphicsPanel, Color.White);

            Point Mapoffset = new Point(0, 0);
            Mapoffset.X += MapGraphicsPanel.AutoScrollPosition.X;
            Mapoffset.Y += MapGraphicsPanel.AutoScrollPosition.Y;
            Size minsize = new Size(MapPixelSize.Width * Mapsize_RC.Width, MapPixelSize.Height * Mapsize_RC.Height);
            //a2+b2=c2
            minsize.Width *= minsize.Width;
            minsize.Height *= minsize.Height;
            int a2b2 = minsize.Width + minsize.Height;

            minsize.Width = (int)Math.Sqrt(a2b2);
            minsize.Height = (int)Math.Sqrt(a2b2);

            MapGraphicsPanel.AutoScrollMinSize = minsize;

            minsize.Width = minsize.Width / 2;
            minsize.Height = minsize.Height / 2;
           

            d3D.DeviceBegin();
            d3D.SpriteBegin();

            for (int i = 0; i < Mapsize_RC.Height; ++i)
            {
                for (int j = 0; j < Mapsize_RC.Width; ++j)
                {
                    int TWidth= TilePixelSize.Width;
                    int THeight= TilePixelSize.Height;
                    int x = i*TWidth;//(TilePixelSize.Width / 2 * i) - (TilePixelSize.Height / 2 * j)+350;
                    int y = j*THeight;//(TilePixelSize.Width / 2 * i) + (TilePixelSize.Height / 2 * j) + 15;
			        Rectangle Rsource= new Rectangle (0,0,0,0);

                    float fRad = 0.0f;//(float)(45 * 3.14159286 / 180);
                   
                    switch(Map[i,j].TType)
                        {	
                    case TILE_TYPE.TT_PLAINS:
                        {
                    		Rsource = CellAlgorithm((int)TILE_TYPE.TT_PLAINS);
                                        tm.Draw(NormtextureId,x+Mapoffset.X,y+Mapoffset.Y,1.0F,1.0F,Rsource, (TWidth / 2), (THeight/ 2), fRad,Color.White);
                    	}
                    	break;
                    case TILE_TYPE.TT_FOREST:
                    	{
                    		Rsource = CellAlgorithm((int)TILE_TYPE.TT_FOREST);
                            tm.Draw(NormtextureId, x + Mapoffset.X, y + Mapoffset.Y, 1.0F, 1.0F, Rsource, (TWidth / 2), (THeight / 2), fRad, Color.White);
                    	}
                    	break;
                    case TILE_TYPE.TT_MOUNTAINS:
                    	{
                    		Rsource = CellAlgorithm((int)TILE_TYPE.TT_MOUNTAINS);
                            tm.Draw(NormtextureId, x + Mapoffset.X, y + Mapoffset.Y, 1.0F, 1.0F, Rsource, (TWidth / 2), (THeight / 2), fRad, Color.White);
                    	}
                    	break;
                    case TILE_TYPE.TT_WATER:
                    	{
                    		Rsource = CellAlgorithm((int)TILE_TYPE.TT_WATER);
                            tm.Draw(NormtextureId, x + Mapoffset.X, y + Mapoffset.Y, 1.0F, 1.0F, Rsource, (TWidth / 2), (THeight / 2), fRad, Color.White);
                    	}
                    	break;
                    case TILE_TYPE.TT_FARM:
                    	{
                    		Rsource = CellAlgorithm((int)TILE_TYPE.TT_FARM);
                            tm.Draw(NormtextureId, x + Mapoffset.X, y + Mapoffset.Y, 1.0F, 1.0F, Rsource, (TWidth / 2), (THeight / 2), fRad, Color.White);
                    	}
                    	break;
                    case TILE_TYPE.TT_MILL:
                    	{
                    		Rsource = CellAlgorithm((int)TILE_TYPE.TT_MILL);
                            tm.Draw(NormtextureId, x + Mapoffset.X, y + Mapoffset.Y, 1.0F, 1.0F, Rsource, (TWidth / 2), (THeight / 2), fRad, Color.White);
           	            }
                    	break;
                    case TILE_TYPE.TT_MINE:
                    	{
                    		Rsource = CellAlgorithm((int)TILE_TYPE.TT_MINE);
                            tm.Draw(NormtextureId, x + Mapoffset.X, y + Mapoffset.Y, 1.0F, 1.0F, Rsource, (TWidth / 2), (THeight / 2), fRad, Color.White);
                	    }
                    	break;
                    case TILE_TYPE.TT_CASTLE:
                    	{
                    		Rsource = CellAlgorithm((int)TILE_TYPE.TT_CASTLE);
                            tm.Draw(NormtextureId, x + Mapoffset.X, y + Mapoffset.Y, 1.0F, 1.0F, Rsource, (TWidth / 2), (THeight / 2), fRad, Color.White);
             	        }
				        break;
			            }
                }
            }
            d3D.Sprite.Flush();
            for (int i = 0; i < Mapsize_RC.Height; ++i)
            {
                for (int j = 0; j < Mapsize_RC.Width; ++j)
                {
                    Point rectoffset=new Point(Map[i,j].Rect.Location.X+Mapoffset.X, Map[i,j].Rect.Location.Y+Mapoffset.Y);

                    Rectangle offsetrect = new Rectangle(rectoffset, Map[i, j].Rect.Size);
                    d3D.DrawEmptyRect(offsetrect, Color.Black);
                }
            }
            d3D.SpriteEnd();
            d3D.DeviceEnd();
            d3D.Present();
           
        }

        private void MapGraphicsPanel_Paint(object sender, PaintEventArgs e) {}

        private void TilesetGraphicsPanel_Paint(object sender, PaintEventArgs e) {}

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

            Point matchtilepoint= new Point (0,0);
            if (SelectedTilePoint == matchtilepoint)
            {
                selectTileType = TILE_TYPE.TT_PLAINS;
            }

            matchtilepoint = new Point(1,0);
            if (SelectedTilePoint == matchtilepoint)
            {
                selectTileType = TILE_TYPE.TT_FOREST;
            }

            matchtilepoint = new Point(2, 0);
            if (SelectedTilePoint == matchtilepoint)
            {
                selectTileType = TILE_TYPE.TT_MOUNTAINS;
            }

            matchtilepoint = new Point(3, 0);
            if (SelectedTilePoint == matchtilepoint)
            {
                selectTileType = TILE_TYPE.TT_WATER;
            }

            matchtilepoint = new Point(0, 1);
            if (SelectedTilePoint == matchtilepoint)
            {
                selectTileType = TILE_TYPE.TT_FARM;
            }
            matchtilepoint = new Point(1, 1);
            if (SelectedTilePoint == matchtilepoint)
            {
                selectTileType = TILE_TYPE.TT_MILL;
            }

            matchtilepoint = new Point(2, 1);
            if (SelectedTilePoint == matchtilepoint)
            {
                selectTileType = TILE_TYPE.TT_MINE;
            }

            matchtilepoint = new Point(3, 1);
            if (SelectedTilePoint == matchtilepoint)
            {
                selectTileType = TILE_TYPE.TT_CASTLE;
            }
        }
              
        private void MapGraphicsPanel_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Point offset = new Point(0, 0);
                offset.X += MapGraphicsPanel.AutoScrollPosition.X;
                offset.Y += MapGraphicsPanel.AutoScrollPosition.Y;

                int x = (e.X - offset.X);
                int y = (e.Y - offset.Y);

                Point nuPpoint = new Point(x, y);

                for (int i = 0; i < Mapsize_RC.Width; i++)
                {
                    for (int j = 0; j < Mapsize_RC.Height; j++)
                    {
                        if (Map[i, j].Rect.Contains(nuPpoint))
                            Map[i, j].TType = SelectTileType;
                    }
                }
            }
            //UpdateMap();
        }
 
        // updates for a whole new tile
        public void UpdateTileset()
        {

        }

        // OR showing more tiles on the map
        public void UpdateMap()
        {

        }

        private void Form1_Load(object sender, EventArgs e){}

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            looping = false;
        }

        private void setPathToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog SaveFolderPath = new FolderBrowserDialog();
            SaveFolderPath.ShowDialog();
            RelativePath = SaveFolderPath.SelectedPath;
        }

        private void saveToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            SaveFileDialog SaveFolderPath = new SaveFileDialog();
            SaveFolderPath.Filter = "XML File(*.xml)|*.xml";
            SaveFolderPath.FilterIndex = 1;
            SaveFolderPath.InitialDirectory = RelativePath;
            SaveFolderPath.ShowDialog();
        }

        private void loadToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            OpenFileDialog SaveFolderPath = new OpenFileDialog();
            SaveFolderPath.InitialDirectory = RelativePath;
            //SaveFolderPath.ShowDialog();

            if (DialogResult.OK==SaveFolderPath.ShowDialog())
            {           	
            	XElement xRoot = XElement.Load(SaveFolderPath.FileName);
                if (xRoot==null)
                {
                    String title = "Failure to Load";
                    String content = "Load Failed: xRoot== NUll";
                    MessageBox.Show(content, title, MessageBoxButtons.OK); 
                     return;
                }
 
            	XAttribute maprows= xRoot.Attribute("Rows");
            	XAttribute mapcolumns= xRoot.Attribute("Columns");

                Mapsize_RC.Width = Convert.ToInt32(mapcolumns.Value);
                Mapsize_RC.Height = Convert.ToInt32(maprows.Value);

                //THIS IS GOING TO BE A PROBLEM
            	//XAttribute texturefile= xRoot.Attribute("FileName");
                //String filename=Convert.ToString(texturefile);
                //NormtextureId = tm.LoadTexture(SaveFolderPath.FileName, 0);
            
            	XElement pTiles = (XElement) xRoot.FirstNode;
                XElement xTile = (XElement) pTiles.FirstNode;
            
                Map = new TileClass[Mapsize_RC.Width, Mapsize_RC.Height];
            
                XAttribute tempdata1,tempdata2;

                for (int x = 0; x < Mapsize_RC.Width; ++x)
            	{
                    for (int y = 0; y < Mapsize_RC.Height; ++y)
            		{
                        tempdata1 = xTile.Attribute("PosX");
                        tempdata2 = xTile.Attribute("PosY");
            			Map[x,y].Position = new Point(Convert.ToInt32(tempdata1.Value),Convert.ToInt32(tempdata2.Value));

                        tempdata1 = xTile.Attribute("PixWidth");
                        tempdata2 = xTile.Attribute("PixHeight");
                        TilePixelSize = new Size(Convert.ToInt32(tempdata1.Value), Convert.ToInt32(tempdata2.Value));

                        //tempdata1 = xTile.Attribute("TileWidth");
                        //tempdata2 = xTile.Attribute("TileHeight");

                        tempdata1 = xTile.Attribute("Status");
            			Map[x,y].Status = Convert.ToByte(tempdata1.Value);

                        tempdata1 = xTile.Attribute("PlayerID");
            			Map[x,y].PlayerID=(Convert.ToInt32(tempdata1.Value));

                        tempdata1 = xTile.Attribute("TType");
            			Map[x,y].TType = (TILE_TYPE)Convert.ToInt32(tempdata1.Value);
            
            			xTile = (XElement)xTile.NextNode;
            		}
            	}
            }
        }



        private void newToolStripMenuItem2_Click(object sender, EventArgs e)
        {

        }

        private void newToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            String title = "New Map Warning";
            String content = "    You are about to delete your current work,\n\tdo you want to save?";
            MessageBox.Show(content, title, MessageBoxButtons.YesNo);
        }
        private void fileToolStripMenuItem1_Click(object sender, EventArgs e){}
    }

}
