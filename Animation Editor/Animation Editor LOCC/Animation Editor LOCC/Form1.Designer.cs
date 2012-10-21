namespace Animation_Editor_LOCC
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.startToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.setFileToSaveLoadFromToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.SaveFrameButton = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.animname = new System.Windows.Forms.TextBox();
            this.animlist = new System.Windows.Forms.ComboBox();
            this.numofframesinanim = new System.Windows.Forms.NumericUpDown();
            this.label13 = new System.Windows.Forms.Label();
            this.AnimType = new System.Windows.Forms.ComboBox();
            this.label12 = new System.Windows.Forms.Label();
            this.UnitType = new System.Windows.Forms.ComboBox();
            this.label11 = new System.Windows.Forms.Label();
            this.FrameDuration = new System.Windows.Forms.NumericUpDown();
            this.label10 = new System.Windows.Forms.Label();
            this.MessageProcBox = new System.Windows.Forms.TextBox();
            this.IsLoopingCheckBox = new System.Windows.Forms.CheckBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.AddFrameButton = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.AnchorPosY = new System.Windows.Forms.NumericUpDown();
            this.AnchorPosX = new System.Windows.Forms.NumericUpDown();
            this.RectBottomPos = new System.Windows.Forms.NumericUpDown();
            this.RectTopPos = new System.Windows.Forms.NumericUpDown();
            this.RectRightPos = new System.Windows.Forms.NumericUpDown();
            this.RectLeftPos = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.splitContainer3 = new System.Windows.Forms.SplitContainer();
            this.PreviewBox = new System.Windows.Forms.PictureBox();
            this.button5 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.SpriteSheet = new System.Windows.Forms.PictureBox();
            this.SaveLoadBrowser = new System.Windows.Forms.FolderBrowserDialog();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numofframesinanim)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.FrameDuration)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AnchorPosY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AnchorPosX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectBottomPos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectTopPos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectRightPos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectLeftPos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).BeginInit();
            this.splitContainer3.Panel1.SuspendLayout();
            this.splitContainer3.Panel2.SuspendLayout();
            this.splitContainer3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PreviewBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SpriteSheet)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.SystemColors.ControlLight;
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.startToolStripMenuItem,
            this.helpToolStripMenuItem,
            this.setFileToSaveLoadFromToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(733, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // startToolStripMenuItem
            // 
            this.startToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadToolStripMenuItem,
            this.loadImageToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.startToolStripMenuItem.Name = "startToolStripMenuItem";
            this.startToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.startToolStripMenuItem.Text = "Start";
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.loadToolStripMenuItem.Text = "Load XML";
            this.loadToolStripMenuItem.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
            // 
            // loadImageToolStripMenuItem
            // 
            this.loadImageToolStripMenuItem.Name = "loadImageToolStripMenuItem";
            this.loadImageToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.loadImageToolStripMenuItem.Text = "Load Image";
            this.loadImageToolStripMenuItem.Click += new System.EventHandler(this.loadImageToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.saveToolStripMenuItem.Text = "Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            this.helpToolStripMenuItem.Click += new System.EventHandler(this.helpToolStripMenuItem_Click);
            // 
            // setFileToSaveLoadFromToolStripMenuItem
            // 
            this.setFileToSaveLoadFromToolStripMenuItem.Name = "setFileToSaveLoadFromToolStripMenuItem";
            this.setFileToSaveLoadFromToolStripMenuItem.Size = new System.Drawing.Size(162, 20);
            this.setFileToSaveLoadFromToolStripMenuItem.Text = "Set File To Save/Load From";
            this.setFileToSaveLoadFromToolStripMenuItem.Click += new System.EventHandler(this.setFileToSaveLoadFromToolStripMenuItem_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 24);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.SpriteSheet);
            this.splitContainer1.Size = new System.Drawing.Size(733, 758);
            this.splitContainer1.SplitterDistance = 218;
            this.splitContainer1.TabIndex = 1;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.SaveFrameButton);
            this.splitContainer2.Panel1.Controls.Add(this.label2);
            this.splitContainer2.Panel1.Controls.Add(this.animname);
            this.splitContainer2.Panel1.Controls.Add(this.animlist);
            this.splitContainer2.Panel1.Controls.Add(this.numofframesinanim);
            this.splitContainer2.Panel1.Controls.Add(this.label13);
            this.splitContainer2.Panel1.Controls.Add(this.AnimType);
            this.splitContainer2.Panel1.Controls.Add(this.label12);
            this.splitContainer2.Panel1.Controls.Add(this.UnitType);
            this.splitContainer2.Panel1.Controls.Add(this.label11);
            this.splitContainer2.Panel1.Controls.Add(this.FrameDuration);
            this.splitContainer2.Panel1.Controls.Add(this.label10);
            this.splitContainer2.Panel1.Controls.Add(this.MessageProcBox);
            this.splitContainer2.Panel1.Controls.Add(this.IsLoopingCheckBox);
            this.splitContainer2.Panel1.Controls.Add(this.label9);
            this.splitContainer2.Panel1.Controls.Add(this.label8);
            this.splitContainer2.Panel1.Controls.Add(this.label7);
            this.splitContainer2.Panel1.Controls.Add(this.label4);
            this.splitContainer2.Panel1.Controls.Add(this.AddFrameButton);
            this.splitContainer2.Panel1.Controls.Add(this.label6);
            this.splitContainer2.Panel1.Controls.Add(this.label5);
            this.splitContainer2.Panel1.Controls.Add(this.AnchorPosY);
            this.splitContainer2.Panel1.Controls.Add(this.AnchorPosX);
            this.splitContainer2.Panel1.Controls.Add(this.RectBottomPos);
            this.splitContainer2.Panel1.Controls.Add(this.RectTopPos);
            this.splitContainer2.Panel1.Controls.Add(this.RectRightPos);
            this.splitContainer2.Panel1.Controls.Add(this.RectLeftPos);
            this.splitContainer2.Panel1.Controls.Add(this.label3);
            this.splitContainer2.Panel1.Controls.Add(this.label1);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.splitContainer3);
            this.splitContainer2.Size = new System.Drawing.Size(218, 758);
            this.splitContainer2.SplitterDistance = 432;
            this.splitContainer2.TabIndex = 0;
            // 
            // SaveFrameButton
            // 
            this.SaveFrameButton.Location = new System.Drawing.Point(12, 405);
            this.SaveFrameButton.Name = "SaveFrameButton";
            this.SaveFrameButton.Size = new System.Drawing.Size(185, 23);
            this.SaveFrameButton.TabIndex = 38;
            this.SaveFrameButton.Text = "Save Current Frame";
            this.SaveFrameButton.UseVisualStyleBackColor = true;
            this.SaveFrameButton.Click += new System.EventHandler(this.SaveFrameButton_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 38);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(75, 13);
            this.label2.TabIndex = 37;
            this.label2.Text = "Add Animation";
            // 
            // animname
            // 
            this.animname.Location = new System.Drawing.Point(84, 35);
            this.animname.Name = "animname";
            this.animname.Size = new System.Drawing.Size(131, 20);
            this.animname.TabIndex = 36;
            // 
            // animlist
            // 
            this.animlist.FormattingEnabled = true;
            this.animlist.Location = new System.Drawing.Point(84, 8);
            this.animlist.MaxDropDownItems = 1;
            this.animlist.Name = "animlist";
            this.animlist.Size = new System.Drawing.Size(131, 21);
            this.animlist.TabIndex = 35;
            this.animlist.SelectedIndexChanged += new System.EventHandler(this.animlist_SelectedIndexChanged);
            // 
            // numofframesinanim
            // 
            this.numofframesinanim.Location = new System.Drawing.Point(84, 62);
            this.numofframesinanim.Maximum = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.numofframesinanim.Name = "numofframesinanim";
            this.numofframesinanim.Size = new System.Drawing.Size(131, 20);
            this.numofframesinanim.TabIndex = 0;
            this.numofframesinanim.ValueChanged += new System.EventHandler(this.numofframesinanim_ValueChanged);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(21, 357);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(57, 13);
            this.label13.TabIndex = 29;
            this.label13.Text = "Anim Type";
            // 
            // AnimType
            // 
            this.AnimType.FormattingEnabled = true;
            this.AnimType.Items.AddRange(new object[] {
            "AT_IDLE",
            "AT_WALK_N",
            "AT_WALK_S",
            "AT_WALK_E",
            "AT_WALK_W",
            "AT_ATTACK_N",
            "AT_ATTACK_S",
            "AT_ATTACK_E",
            "AT_ATTACK_W",
            "AT_ABILITY_N",
            "AT_ABILITY_S",
            "AT_ABILITY_E",
            "AT_ABILITY_W",
            "AT_DEATH"});
            this.AnimType.Location = new System.Drawing.Point(84, 354);
            this.AnimType.Name = "AnimType";
            this.AnimType.Size = new System.Drawing.Size(131, 21);
            this.AnimType.TabIndex = 28;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(25, 329);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(53, 13);
            this.label12.TabIndex = 27;
            this.label12.Text = "Unit Type";
            // 
            // UnitType
            // 
            this.UnitType.FormattingEnabled = true;
            this.UnitType.Items.AddRange(new object[] {
            "UT_CASTLE",
            "UT_HERO",
            "UT_ARCHER",
            "UT_SWORDSMAN",
            "UT_CALVARY",
            "UT_SKELETON",
            "UT_ICEBLOCK"});
            this.UnitType.Location = new System.Drawing.Point(84, 326);
            this.UnitType.Name = "UnitType";
            this.UnitType.Size = new System.Drawing.Size(131, 21);
            this.UnitType.TabIndex = 26;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(-1, 301);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(79, 13);
            this.label11.TabIndex = 25;
            this.label11.Text = "Frame Duration";
            // 
            // FrameDuration
            // 
            this.FrameDuration.Location = new System.Drawing.Point(84, 299);
            this.FrameDuration.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.FrameDuration.Name = "FrameDuration";
            this.FrameDuration.Size = new System.Drawing.Size(131, 20);
            this.FrameDuration.TabIndex = 24;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(3, 276);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(75, 13);
            this.label10.TabIndex = 23;
            this.label10.Text = "Message Proc";
            // 
            // MessageProcBox
            // 
            this.MessageProcBox.Location = new System.Drawing.Point(84, 273);
            this.MessageProcBox.Name = "MessageProcBox";
            this.MessageProcBox.Size = new System.Drawing.Size(131, 20);
            this.MessageProcBox.TabIndex = 22;
            // 
            // IsLoopingCheckBox
            // 
            this.IsLoopingCheckBox.AutoSize = true;
            this.IsLoopingCheckBox.Location = new System.Drawing.Point(84, 381);
            this.IsLoopingCheckBox.Name = "IsLoopingCheckBox";
            this.IsLoopingCheckBox.Size = new System.Drawing.Size(64, 17);
            this.IsLoopingCheckBox.TabIndex = 21;
            this.IsLoopingCheckBox.Text = "Looping";
            this.IsLoopingCheckBox.UseVisualStyleBackColor = true;
            this.IsLoopingCheckBox.CheckedChanged += new System.EventHandler(this.IsLoopingCheckBox_CheckedChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 249);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(72, 13);
            this.label9.TabIndex = 20;
            this.label9.Text = "Anchor Pos Y";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 223);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(72, 13);
            this.label8.TabIndex = 19;
            this.label8.Text = "Anchor Pos X";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(12, 197);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(66, 13);
            this.label7.TabIndex = 18;
            this.label7.Text = "Rect Bottom";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(26, 171);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(52, 13);
            this.label4.TabIndex = 17;
            this.label4.Text = "Rect Top";
            // 
            // AddFrameButton
            // 
            this.AddFrameButton.Location = new System.Drawing.Point(40, 88);
            this.AddFrameButton.Name = "AddFrameButton";
            this.AddFrameButton.Size = new System.Drawing.Size(131, 23);
            this.AddFrameButton.TabIndex = 16;
            this.AddFrameButton.Text = "Add Frame";
            this.AddFrameButton.UseVisualStyleBackColor = true;
            this.AddFrameButton.Click += new System.EventHandler(this.AddFrameButton_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(20, 145);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(58, 13);
            this.label6.TabIndex = 15;
            this.label6.Text = "Rect Right";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(27, 119);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(51, 13);
            this.label5.TabIndex = 14;
            this.label5.Text = "Rect Left";
            // 
            // AnchorPosY
            // 
            this.AnchorPosY.Location = new System.Drawing.Point(84, 247);
            this.AnchorPosY.Maximum = new decimal(new int[] {
            100000000,
            0,
            0,
            0});
            this.AnchorPosY.Name = "AnchorPosY";
            this.AnchorPosY.Size = new System.Drawing.Size(131, 20);
            this.AnchorPosY.TabIndex = 12;
            this.AnchorPosY.ValueChanged += new System.EventHandler(this.AnchorPosY_ValueChanged);
            // 
            // AnchorPosX
            // 
            this.AnchorPosX.Location = new System.Drawing.Point(84, 221);
            this.AnchorPosX.Maximum = new decimal(new int[] {
            100000000,
            0,
            0,
            0});
            this.AnchorPosX.Name = "AnchorPosX";
            this.AnchorPosX.Size = new System.Drawing.Size(131, 20);
            this.AnchorPosX.TabIndex = 11;
            this.AnchorPosX.ValueChanged += new System.EventHandler(this.AnchorPosX_ValueChanged);
            // 
            // RectBottomPos
            // 
            this.RectBottomPos.Location = new System.Drawing.Point(84, 195);
            this.RectBottomPos.Maximum = new decimal(new int[] {
            100000000,
            0,
            0,
            0});
            this.RectBottomPos.Name = "RectBottomPos";
            this.RectBottomPos.Size = new System.Drawing.Size(131, 20);
            this.RectBottomPos.TabIndex = 10;
            this.RectBottomPos.ValueChanged += new System.EventHandler(this.RectBottomPos_ValueChanged);
            // 
            // RectTopPos
            // 
            this.RectTopPos.Location = new System.Drawing.Point(84, 169);
            this.RectTopPos.Maximum = new decimal(new int[] {
            100000000,
            0,
            0,
            0});
            this.RectTopPos.Name = "RectTopPos";
            this.RectTopPos.Size = new System.Drawing.Size(131, 20);
            this.RectTopPos.TabIndex = 9;
            this.RectTopPos.ValueChanged += new System.EventHandler(this.RectTopPos_ValueChanged);
            // 
            // RectRightPos
            // 
            this.RectRightPos.Location = new System.Drawing.Point(84, 143);
            this.RectRightPos.Maximum = new decimal(new int[] {
            100000000,
            0,
            0,
            0});
            this.RectRightPos.Name = "RectRightPos";
            this.RectRightPos.Size = new System.Drawing.Size(131, 20);
            this.RectRightPos.TabIndex = 8;
            this.RectRightPos.ValueChanged += new System.EventHandler(this.RectRightPos_ValueChanged);
            // 
            // RectLeftPos
            // 
            this.RectLeftPos.Location = new System.Drawing.Point(84, 117);
            this.RectLeftPos.Maximum = new decimal(new int[] {
            1000000000,
            0,
            0,
            0});
            this.RectLeftPos.Name = "RectLeftPos";
            this.RectLeftPos.Size = new System.Drawing.Size(131, 20);
            this.RectLeftPos.TabIndex = 7;
            this.RectLeftPos.ValueChanged += new System.EventHandler(this.RectLeftPos_ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(32, 64);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 13);
            this.label3.TabIndex = 0;
            this.label3.Text = "Frame #";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(25, 11);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Animation";
            // 
            // splitContainer3
            // 
            this.splitContainer3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer3.Location = new System.Drawing.Point(0, 0);
            this.splitContainer3.Name = "splitContainer3";
            this.splitContainer3.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer3.Panel1
            // 
            this.splitContainer3.Panel1.Controls.Add(this.PreviewBox);
            // 
            // splitContainer3.Panel2
            // 
            this.splitContainer3.Panel2.Controls.Add(this.button5);
            this.splitContainer3.Panel2.Controls.Add(this.button4);
            this.splitContainer3.Panel2.Controls.Add(this.button3);
            this.splitContainer3.Panel2.Controls.Add(this.button2);
            this.splitContainer3.Panel2.Controls.Add(this.button1);
            this.splitContainer3.Size = new System.Drawing.Size(218, 322);
            this.splitContainer3.SplitterDistance = 174;
            this.splitContainer3.TabIndex = 1;
            // 
            // PreviewBox
            // 
            this.PreviewBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PreviewBox.Location = new System.Drawing.Point(0, 0);
            this.PreviewBox.Name = "PreviewBox";
            this.PreviewBox.Size = new System.Drawing.Size(218, 174);
            this.PreviewBox.TabIndex = 0;
            this.PreviewBox.TabStop = false;
            // 
            // button5
            // 
            this.button5.Image = ((System.Drawing.Image)(resources.GetObject("button5.Image")));
            this.button5.Location = new System.Drawing.Point(113, 78);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(67, 45);
            this.button5.TabIndex = 4;
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button4
            // 
            this.button4.Image = ((System.Drawing.Image)(resources.GetObject("button4.Image")));
            this.button4.Location = new System.Drawing.Point(40, 78);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(67, 45);
            this.button4.TabIndex = 3;
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button3
            // 
            this.button3.Image = ((System.Drawing.Image)(resources.GetObject("button3.Image")));
            this.button3.Location = new System.Drawing.Point(154, 20);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(43, 41);
            this.button3.TabIndex = 2;
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button2
            // 
            this.button2.Image = ((System.Drawing.Image)(resources.GetObject("button2.Image")));
            this.button2.Location = new System.Drawing.Point(84, 20);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(40, 41);
            this.button2.TabIndex = 1;
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.Image = ((System.Drawing.Image)(resources.GetObject("button1.Image")));
            this.button1.Location = new System.Drawing.Point(15, 20);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(40, 41);
            this.button1.TabIndex = 0;
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // SpriteSheet
            // 
            this.SpriteSheet.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SpriteSheet.Location = new System.Drawing.Point(0, 0);
            this.SpriteSheet.Name = "SpriteSheet";
            this.SpriteSheet.Size = new System.Drawing.Size(511, 758);
            this.SpriteSheet.TabIndex = 0;
            this.SpriteSheet.TabStop = false;
            this.SpriteSheet.MouseDown += new System.Windows.Forms.MouseEventHandler(this.SpriteSheet_MouseDown);
            this.SpriteSheet.MouseMove += new System.Windows.Forms.MouseEventHandler(this.SpriteSheet_MouseMove);
            this.SpriteSheet.MouseUp += new System.Windows.Forms.MouseEventHandler(this.SpriteSheet_MouseUp);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(733, 782);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Animation Editor LOCC";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Shown += new System.EventHandler(this.Form1_Shown);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel1.PerformLayout();
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numofframesinanim)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.FrameDuration)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AnchorPosY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AnchorPosX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectBottomPos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectTopPos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectRightPos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectLeftPos)).EndInit();
            this.splitContainer3.Panel1.ResumeLayout(false);
            this.splitContainer3.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).EndInit();
            this.splitContainer3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.PreviewBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SpriteSheet)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem startToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.NumericUpDown FrameDuration;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox MessageProcBox;
        private System.Windows.Forms.CheckBox IsLoopingCheckBox;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button AddFrameButton;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown AnchorPosY;
        private System.Windows.Forms.NumericUpDown AnchorPosX;
        private System.Windows.Forms.NumericUpDown RectBottomPos;
        private System.Windows.Forms.NumericUpDown RectTopPos;
        private System.Windows.Forms.NumericUpDown RectRightPos;
        private System.Windows.Forms.NumericUpDown RectLeftPos;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.SplitContainer splitContainer3;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ToolStripMenuItem setFileToSaveLoadFromToolStripMenuItem;
        private System.Windows.Forms.FolderBrowserDialog SaveLoadBrowser;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.ComboBox AnimType;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.ComboBox UnitType;
        private System.Windows.Forms.NumericUpDown numofframesinanim;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox animname;
        private System.Windows.Forms.ComboBox animlist;
        private System.Windows.Forms.ToolStripMenuItem loadImageToolStripMenuItem;
        private System.Windows.Forms.Button SaveFrameButton;
        private System.Windows.Forms.PictureBox SpriteSheet;
        private System.Windows.Forms.PictureBox PreviewBox;
    }
}

