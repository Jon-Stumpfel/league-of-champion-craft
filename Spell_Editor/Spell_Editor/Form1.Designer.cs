namespace Spell_Editor
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
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadParticleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadIconToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.changePathToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.panel1 = new System.Windows.Forms.Panel();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rbMovePhase = new System.Windows.Forms.RadioButton();
            this.rbAttackPhase = new System.Windows.Forms.RadioButton();
            this.tbSpellName = new System.Windows.Forms.TextBox();
            this.nudTarget = new System.Windows.Forms.NumericUpDown();
            this.nudCD = new System.Windows.Forms.NumericUpDown();
            this.nudRange = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.cbAttack = new System.Windows.Forms.CheckBox();
            this.nudAP = new System.Windows.Forms.NumericUpDown();
            this.rtbLua = new System.Windows.Forms.RichTextBox();
            this.loadSoundToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudTarget)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudCD)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudRange)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudAP)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1017, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.loadToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(44, 24);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(111, 24);
            this.newToolStripMenuItem.Text = "&New";
            this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(111, 24);
            this.saveToolStripMenuItem.Text = "&Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(111, 24);
            this.loadToolStripMenuItem.Text = "&Load";
            this.loadToolStripMenuItem.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(111, 24);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadParticleToolStripMenuItem,
            this.loadIconToolStripMenuItem,
            this.loadSoundToolStripMenuItem,
            this.changePathToolStripMenuItem});
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(47, 24);
            this.editToolStripMenuItem.Text = "Edit";
            // 
            // loadParticleToolStripMenuItem
            // 
            this.loadParticleToolStripMenuItem.Name = "loadParticleToolStripMenuItem";
            this.loadParticleToolStripMenuItem.Size = new System.Drawing.Size(164, 24);
            this.loadParticleToolStripMenuItem.Text = "Load Particle";
            this.loadParticleToolStripMenuItem.Click += new System.EventHandler(this.loadParticleToolStripMenuItem_Click);
            // 
            // loadIconToolStripMenuItem
            // 
            this.loadIconToolStripMenuItem.Name = "loadIconToolStripMenuItem";
            this.loadIconToolStripMenuItem.Size = new System.Drawing.Size(164, 24);
            this.loadIconToolStripMenuItem.Text = "Load Icon";
            this.loadIconToolStripMenuItem.Click += new System.EventHandler(this.loadIconToolStripMenuItem_Click);
            // 
            // changePathToolStripMenuItem
            // 
            this.changePathToolStripMenuItem.Name = "changePathToolStripMenuItem";
            this.changePathToolStripMenuItem.Size = new System.Drawing.Size(164, 24);
            this.changePathToolStripMenuItem.Text = "Change Path";
            this.changePathToolStripMenuItem.Click += new System.EventHandler(this.changePathToolStripMenuItem_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 28);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.rtbLua);
            this.splitContainer1.Size = new System.Drawing.Size(1017, 613);
            this.splitContainer1.SplitterDistance = 474;
            this.splitContainer1.TabIndex = 1;
            this.splitContainer1.TabStop = false;
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
            this.splitContainer2.Panel1.Controls.Add(this.panel1);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.groupBox6);
            this.splitContainer2.Size = new System.Drawing.Size(474, 613);
            this.splitContainer2.SplitterDistance = 475;
            this.splitContainer2.TabIndex = 0;
            this.splitContainer2.TabStop = false;
            // 
            // panel1
            // 
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(470, 471);
            this.panel1.TabIndex = 0;
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.graphicsPanel1_Paint);
            this.panel1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.graphicsPanel1_MouseDown);
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.groupBox1);
            this.groupBox6.Controls.Add(this.tbSpellName);
            this.groupBox6.Controls.Add(this.nudTarget);
            this.groupBox6.Controls.Add(this.nudCD);
            this.groupBox6.Controls.Add(this.nudRange);
            this.groupBox6.Controls.Add(this.label4);
            this.groupBox6.Controls.Add(this.label5);
            this.groupBox6.Controls.Add(this.label2);
            this.groupBox6.Controls.Add(this.label3);
            this.groupBox6.Controls.Add(this.label1);
            this.groupBox6.Controls.Add(this.cbAttack);
            this.groupBox6.Controls.Add(this.nudAP);
            this.groupBox6.Location = new System.Drawing.Point(2, 3);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(464, 124);
            this.groupBox6.TabIndex = 0;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Spell";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rbMovePhase);
            this.groupBox1.Controls.Add(this.rbAttackPhase);
            this.groupBox1.Location = new System.Drawing.Point(315, 10);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(146, 108);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Phase";
            // 
            // rbMovePhase
            // 
            this.rbMovePhase.AutoSize = true;
            this.rbMovePhase.Location = new System.Drawing.Point(18, 66);
            this.rbMovePhase.Name = "rbMovePhase";
            this.rbMovePhase.Size = new System.Drawing.Size(94, 21);
            this.rbMovePhase.TabIndex = 0;
            this.rbMovePhase.Text = "Movement";
            this.rbMovePhase.UseVisualStyleBackColor = true;
            // 
            // rbAttackPhase
            // 
            this.rbAttackPhase.AutoSize = true;
            this.rbAttackPhase.Checked = true;
            this.rbAttackPhase.Location = new System.Drawing.Point(18, 30);
            this.rbAttackPhase.Name = "rbAttackPhase";
            this.rbAttackPhase.Size = new System.Drawing.Size(68, 21);
            this.rbAttackPhase.TabIndex = 0;
            this.rbAttackPhase.TabStop = true;
            this.rbAttackPhase.Text = "Attack";
            this.rbAttackPhase.UseVisualStyleBackColor = true;
            // 
            // tbSpellName
            // 
            this.tbSpellName.Location = new System.Drawing.Point(175, 87);
            this.tbSpellName.Name = "tbSpellName";
            this.tbSpellName.Size = new System.Drawing.Size(134, 22);
            this.tbSpellName.TabIndex = 0;
            // 
            // nudTarget
            // 
            this.nudTarget.Location = new System.Drawing.Point(90, 40);
            this.nudTarget.Name = "nudTarget";
            this.nudTarget.Size = new System.Drawing.Size(59, 22);
            this.nudTarget.TabIndex = 0;
            // 
            // nudCD
            // 
            this.nudCD.Location = new System.Drawing.Point(90, 88);
            this.nudCD.Name = "nudCD";
            this.nudCD.Size = new System.Drawing.Size(59, 22);
            this.nudCD.TabIndex = 0;
            // 
            // nudRange
            // 
            this.nudRange.Location = new System.Drawing.Point(8, 40);
            this.nudRange.Name = "nudRange";
            this.nudRange.Size = new System.Drawing.Size(64, 22);
            this.nudRange.TabIndex = 0;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(87, 18);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(83, 17);
            this.label4.TabIndex = 1;
            this.label4.Text = "Target Num";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(172, 65);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(80, 17);
            this.label5.TabIndex = 1;
            this.label5.Text = "Spell Name";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(87, 65);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(69, 17);
            this.label2.TabIndex = 1;
            this.label2.Text = "Cooldown";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(8, 18);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(50, 17);
            this.label3.TabIndex = 1;
            this.label3.Text = "Range";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 65);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(57, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Ap Cost";
            // 
            // cbAttack
            // 
            this.cbAttack.AutoSize = true;
            this.cbAttack.Location = new System.Drawing.Point(175, 40);
            this.cbAttack.Name = "cbAttack";
            this.cbAttack.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.cbAttack.Size = new System.Drawing.Size(83, 21);
            this.cbAttack.TabIndex = 0;
            this.cbAttack.Text = "Is Attack";
            this.cbAttack.UseVisualStyleBackColor = true;
            // 
            // nudAP
            // 
            this.nudAP.Location = new System.Drawing.Point(8, 88);
            this.nudAP.Name = "nudAP";
            this.nudAP.Size = new System.Drawing.Size(64, 22);
            this.nudAP.TabIndex = 0;
            // 
            // rtbLua
            // 
            this.rtbLua.AcceptsTab = true;
            this.rtbLua.Dock = System.Windows.Forms.DockStyle.Fill;
            this.rtbLua.Location = new System.Drawing.Point(0, 0);
            this.rtbLua.Name = "rtbLua";
            this.rtbLua.Size = new System.Drawing.Size(535, 609);
            this.rtbLua.TabIndex = 0;
            this.rtbLua.Text = "";
            // 
            // loadSoundToolStripMenuItem
            // 
            this.loadSoundToolStripMenuItem.Name = "loadSoundToolStripMenuItem";
            this.loadSoundToolStripMenuItem.Size = new System.Drawing.Size(164, 24);
            this.loadSoundToolStripMenuItem.Text = "Load Sound";
            this.loadSoundToolStripMenuItem.Click += new System.EventHandler(this.loadSoundToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1017, 641);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Ability Editor";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.exitToolStripMenuItem_Click);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudTarget)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudCD)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudRange)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudAP)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadParticleToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem changePathToolStripMenuItem;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.RichTextBox rtbLua;
        private System.Windows.Forms.TextBox tbSpellName;
        private System.Windows.Forms.NumericUpDown nudTarget;
        private System.Windows.Forms.NumericUpDown nudRange;
        private System.Windows.Forms.NumericUpDown nudAP;
        private System.Windows.Forms.NumericUpDown nudCD;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox cbAttack;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rbMovePhase;
        private System.Windows.Forms.RadioButton rbAttackPhase;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ToolStripMenuItem loadIconToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadSoundToolStripMenuItem;
    }
}

