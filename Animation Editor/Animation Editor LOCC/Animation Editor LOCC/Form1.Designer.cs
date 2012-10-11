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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.startToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
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
            this.FramesComboBox = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.AddAnimTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.AnimationComboBox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.AnchorPosY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AnchorPosX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectBottomPos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectTopPos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectRightPos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectLeftPos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.SystemColors.ControlLight;
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.startToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(730, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // startToolStripMenuItem
            // 
            this.startToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.loadToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.startToolStripMenuItem.Name = "startToolStripMenuItem";
            this.startToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.startToolStripMenuItem.Text = "Start";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.newToolStripMenuItem.Text = "New";
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.loadToolStripMenuItem.Text = "Load";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.saveToolStripMenuItem.Text = "Save";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
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
            this.splitContainer1.Panel2.Controls.Add(this.pictureBox1);
            this.splitContainer1.Size = new System.Drawing.Size(730, 422);
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
            this.splitContainer2.Panel1.Controls.Add(this.FramesComboBox);
            this.splitContainer2.Panel1.Controls.Add(this.label3);
            this.splitContainer2.Panel1.Controls.Add(this.AddAnimTextBox);
            this.splitContainer2.Panel1.Controls.Add(this.label2);
            this.splitContainer2.Panel1.Controls.Add(this.AnimationComboBox);
            this.splitContainer2.Panel1.Controls.Add(this.label1);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.pictureBox2);
            this.splitContainer2.Size = new System.Drawing.Size(218, 422);
            this.splitContainer2.SplitterDistance = 294;
            this.splitContainer2.TabIndex = 0;
            // 
            // IsLoopingCheckBox
            // 
            this.IsLoopingCheckBox.AutoSize = true;
            this.IsLoopingCheckBox.Location = new System.Drawing.Point(84, 273);
            this.IsLoopingCheckBox.Name = "IsLoopingCheckBox";
            this.IsLoopingCheckBox.Size = new System.Drawing.Size(64, 17);
            this.IsLoopingCheckBox.TabIndex = 21;
            this.IsLoopingCheckBox.Text = "Looping";
            this.IsLoopingCheckBox.UseVisualStyleBackColor = true;
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
            this.AnchorPosY.Name = "AnchorPosY";
            this.AnchorPosY.Size = new System.Drawing.Size(131, 20);
            this.AnchorPosY.TabIndex = 12;
            // 
            // AnchorPosX
            // 
            this.AnchorPosX.Location = new System.Drawing.Point(84, 221);
            this.AnchorPosX.Name = "AnchorPosX";
            this.AnchorPosX.Size = new System.Drawing.Size(131, 20);
            this.AnchorPosX.TabIndex = 11;
            // 
            // RectBottomPos
            // 
            this.RectBottomPos.Location = new System.Drawing.Point(84, 195);
            this.RectBottomPos.Name = "RectBottomPos";
            this.RectBottomPos.Size = new System.Drawing.Size(131, 20);
            this.RectBottomPos.TabIndex = 10;
            // 
            // RectTopPos
            // 
            this.RectTopPos.Location = new System.Drawing.Point(84, 169);
            this.RectTopPos.Name = "RectTopPos";
            this.RectTopPos.Size = new System.Drawing.Size(131, 20);
            this.RectTopPos.TabIndex = 9;
            // 
            // RectRightPos
            // 
            this.RectRightPos.Location = new System.Drawing.Point(84, 143);
            this.RectRightPos.Name = "RectRightPos";
            this.RectRightPos.Size = new System.Drawing.Size(131, 20);
            this.RectRightPos.TabIndex = 8;
            // 
            // RectLeftPos
            // 
            this.RectLeftPos.Location = new System.Drawing.Point(84, 117);
            this.RectLeftPos.Name = "RectLeftPos";
            this.RectLeftPos.Size = new System.Drawing.Size(131, 20);
            this.RectLeftPos.TabIndex = 7;
            // 
            // FramesComboBox
            // 
            this.FramesComboBox.FormattingEnabled = true;
            this.FramesComboBox.Location = new System.Drawing.Point(84, 61);
            this.FramesComboBox.Name = "FramesComboBox";
            this.FramesComboBox.Size = new System.Drawing.Size(131, 21);
            this.FramesComboBox.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(37, 64);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Frames";
            // 
            // AddAnimTextBox
            // 
            this.AddAnimTextBox.Location = new System.Drawing.Point(84, 35);
            this.AddAnimTextBox.Name = "AddAnimTextBox";
            this.AddAnimTextBox.Size = new System.Drawing.Size(131, 20);
            this.AddAnimTextBox.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 38);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(75, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Add Animation";
            // 
            // AnimationComboBox
            // 
            this.AnimationComboBox.BackColor = System.Drawing.SystemColors.Window;
            this.AnimationComboBox.FormattingEnabled = true;
            this.AnimationComboBox.Location = new System.Drawing.Point(84, 8);
            this.AnimationComboBox.Name = "AnimationComboBox";
            this.AnimationComboBox.Size = new System.Drawing.Size(131, 21);
            this.AnimationComboBox.TabIndex = 1;
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
            // pictureBox2
            // 
            this.pictureBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox2.Location = new System.Drawing.Point(0, 0);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(218, 124);
            this.pictureBox2.TabIndex = 0;
            this.pictureBox2.TabStop = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(508, 422);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(730, 446);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Animation Editor LOCC";
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
            ((System.ComponentModel.ISupportInitialize)(this.AnchorPosY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AnchorPosX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectBottomPos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectTopPos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectRightPos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RectLeftPos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem startToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown AnchorPosY;
        private System.Windows.Forms.NumericUpDown AnchorPosX;
        private System.Windows.Forms.NumericUpDown RectBottomPos;
        private System.Windows.Forms.NumericUpDown RectTopPos;
        private System.Windows.Forms.NumericUpDown RectRightPos;
        private System.Windows.Forms.NumericUpDown RectLeftPos;
        private System.Windows.Forms.ComboBox FramesComboBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox AddAnimTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox AnimationComboBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button AddFrameButton;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.CheckBox IsLoopingCheckBox;
    }
}

