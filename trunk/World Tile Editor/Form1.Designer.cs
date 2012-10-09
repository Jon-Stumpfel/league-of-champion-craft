namespace World_Tile_Editor
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadMapToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadTileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MainContainer = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.graphicsPanel2 = new World_Tile_Editor.GraphicsPanel();
            this.Tile_Options = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.HeightcomboBox = new System.Windows.Forms.ComboBox();
            this.WidthcomboBox = new System.Windows.Forms.ComboBox();
            this.Map_Options = new System.Windows.Forms.GroupBox();
            this.ColumnsnumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.RowsNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.graphicsPanel1 = new World_Tile_Editor.GraphicsPanel();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MainContainer)).BeginInit();
            this.MainContainer.Panel1.SuspendLayout();
            this.MainContainer.Panel2.SuspendLayout();
            this.MainContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.Tile_Options.SuspendLayout();
            this.Map_Options.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ColumnsnumericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RowsNumericUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.optionsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(605, 25);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.loadToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(38, 21);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(106, 22);
            this.newToolStripMenuItem.Text = "&New";
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadMapToolStripMenuItem,
            this.loadImageToolStripMenuItem});
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(106, 22);
            this.loadToolStripMenuItem.Text = "&Load";
            // 
            // loadMapToolStripMenuItem
            // 
            this.loadMapToolStripMenuItem.Name = "loadMapToolStripMenuItem";
            this.loadMapToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.loadMapToolStripMenuItem.Text = "Load &Map";
            // 
            // loadImageToolStripMenuItem
            // 
            this.loadImageToolStripMenuItem.Name = "loadImageToolStripMenuItem";
            this.loadImageToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.loadImageToolStripMenuItem.Text = "Load &Image";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(106, 22);
            this.saveToolStripMenuItem.Text = "&Save";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(106, 22);
            this.exitToolStripMenuItem.Text = "&Exit";
            // 
            // optionsToolStripMenuItem
            // 
            this.optionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadTileToolStripMenuItem});
            this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            this.optionsToolStripMenuItem.Size = new System.Drawing.Size(67, 21);
            this.optionsToolStripMenuItem.Text = "&Options";
            // 
            // loadTileToolStripMenuItem
            // 
            this.loadTileToolStripMenuItem.Name = "loadTileToolStripMenuItem";
            this.loadTileToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.loadTileToolStripMenuItem.Text = "&Load TileSet";
            this.loadTileToolStripMenuItem.Click += new System.EventHandler(this.loadTileToolStripMenuItem_Click);
            // 
            // MainContainer
            // 
            this.MainContainer.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.MainContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.MainContainer.Location = new System.Drawing.Point(0, 25);
            this.MainContainer.Name = "MainContainer";
            // 
            // MainContainer.Panel1
            // 
            this.MainContainer.Panel1.Controls.Add(this.splitContainer2);
            // 
            // MainContainer.Panel2
            // 
            this.MainContainer.Panel2.BackColor = System.Drawing.SystemColors.Window;
            this.MainContainer.Panel2.Controls.Add(this.graphicsPanel1);
            this.MainContainer.Size = new System.Drawing.Size(605, 408);
            this.MainContainer.SplitterDistance = 174;
            this.MainContainer.TabIndex = 1;
            // 
            // splitContainer2
            // 
            this.splitContainer2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.BackColor = System.Drawing.SystemColors.Window;
            this.splitContainer2.Panel1.Controls.Add(this.graphicsPanel2);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.Tile_Options);
            this.splitContainer2.Panel2.Controls.Add(this.Map_Options);
            this.splitContainer2.Size = new System.Drawing.Size(174, 408);
            this.splitContainer2.SplitterDistance = 180;
            this.splitContainer2.TabIndex = 0;
            // 
            // graphicsPanel2
            // 
            this.graphicsPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.graphicsPanel2.Location = new System.Drawing.Point(0, 0);
            this.graphicsPanel2.Name = "graphicsPanel2";
            this.graphicsPanel2.Size = new System.Drawing.Size(170, 176);
            this.graphicsPanel2.TabIndex = 0;
            // 
            // Tile_Options
            // 
            this.Tile_Options.Controls.Add(this.label4);
            this.Tile_Options.Controls.Add(this.label3);
            this.Tile_Options.Controls.Add(this.HeightcomboBox);
            this.Tile_Options.Controls.Add(this.WidthcomboBox);
            this.Tile_Options.Location = new System.Drawing.Point(12, 103);
            this.Tile_Options.Name = "Tile_Options";
            this.Tile_Options.Size = new System.Drawing.Size(148, 98);
            this.Tile_Options.TabIndex = 1;
            this.Tile_Options.TabStop = false;
            this.Tile_Options.Text = "Tile Options";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(10, 55);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(49, 17);
            this.label4.TabIndex = 3;
            this.label4.Text = "Height";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(10, 28);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 17);
            this.label3.TabIndex = 2;
            this.label3.Text = "Width";
            // 
            // HeightcomboBox
            // 
            this.HeightcomboBox.FormattingEnabled = true;
            this.HeightcomboBox.Location = new System.Drawing.Point(74, 52);
            this.HeightcomboBox.Name = "HeightcomboBox";
            this.HeightcomboBox.Size = new System.Drawing.Size(68, 24);
            this.HeightcomboBox.TabIndex = 1;
            // 
            // WidthcomboBox
            // 
            this.WidthcomboBox.FormattingEnabled = true;
            this.WidthcomboBox.Location = new System.Drawing.Point(74, 22);
            this.WidthcomboBox.Name = "WidthcomboBox";
            this.WidthcomboBox.Size = new System.Drawing.Size(68, 24);
            this.WidthcomboBox.TabIndex = 0;
            // 
            // Map_Options
            // 
            this.Map_Options.Controls.Add(this.ColumnsnumericUpDown);
            this.Map_Options.Controls.Add(this.RowsNumericUpDown);
            this.Map_Options.Controls.Add(this.label2);
            this.Map_Options.Controls.Add(this.label1);
            this.Map_Options.Location = new System.Drawing.Point(12, 15);
            this.Map_Options.Name = "Map_Options";
            this.Map_Options.Size = new System.Drawing.Size(148, 82);
            this.Map_Options.TabIndex = 0;
            this.Map_Options.TabStop = false;
            this.Map_Options.Text = "Map Options";
            // 
            // ColumnsnumericUpDown
            // 
            this.ColumnsnumericUpDown.Location = new System.Drawing.Point(74, 45);
            this.ColumnsnumericUpDown.Name = "ColumnsnumericUpDown";
            this.ColumnsnumericUpDown.Size = new System.Drawing.Size(68, 22);
            this.ColumnsnumericUpDown.TabIndex = 3;
            // 
            // RowsNumericUpDown
            // 
            this.RowsNumericUpDown.Location = new System.Drawing.Point(74, 17);
            this.RowsNumericUpDown.Name = "RowsNumericUpDown";
            this.RowsNumericUpDown.Size = new System.Drawing.Size(68, 22);
            this.RowsNumericUpDown.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(7, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 17);
            this.label2.TabIndex = 1;
            this.label2.Text = "Columns";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(42, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "Rows";
            // 
            // graphicsPanel1
            // 
            this.graphicsPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.graphicsPanel1.Location = new System.Drawing.Point(0, 0);
            this.graphicsPanel1.Name = "graphicsPanel1";
            this.graphicsPanel1.Size = new System.Drawing.Size(423, 404);
            this.graphicsPanel1.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(605, 433);
            this.Controls.Add(this.MainContainer);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "World Tile Editor";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.MainContainer.Panel1.ResumeLayout(false);
            this.MainContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.MainContainer)).EndInit();
            this.MainContainer.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.Tile_Options.ResumeLayout(false);
            this.Tile_Options.PerformLayout();
            this.Map_Options.ResumeLayout(false);
            this.Map_Options.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ColumnsnumericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RowsNumericUpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadMapToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadImageToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
        private System.Windows.Forms.SplitContainer MainContainer;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.GroupBox Tile_Options;
        private System.Windows.Forms.GroupBox Map_Options;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox HeightcomboBox;
        private System.Windows.Forms.ComboBox WidthcomboBox;
        private System.Windows.Forms.NumericUpDown ColumnsnumericUpDown;
        private System.Windows.Forms.NumericUpDown RowsNumericUpDown;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ToolStripMenuItem loadTileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private GraphicsPanel graphicsPanel1;
        private GraphicsPanel graphicsPanel2;
    }
}

