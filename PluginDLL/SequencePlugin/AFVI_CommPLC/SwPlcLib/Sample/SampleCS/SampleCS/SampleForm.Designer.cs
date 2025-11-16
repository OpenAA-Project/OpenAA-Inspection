namespace SampleCS
{
    partial class SampleForm
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.testButton = new System.Windows.Forms.Button();
            this.testWithFileButton = new System.Windows.Forms.Button();
            this.logListView = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.closeButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // testButton
            // 
            this.testButton.Location = new System.Drawing.Point(12, 248);
            this.testButton.Name = "testButton";
            this.testButton.Size = new System.Drawing.Size(135, 35);
            this.testButton.TabIndex = 0;
            this.testButton.Text = "Test(定義ファイル無し)";
            this.testButton.UseVisualStyleBackColor = true;
            this.testButton.Click += new System.EventHandler(this.testButton_Click);
            // 
            // testWithFileButton
            // 
            this.testWithFileButton.Location = new System.Drawing.Point(153, 248);
            this.testWithFileButton.Name = "testWithFileButton";
            this.testWithFileButton.Size = new System.Drawing.Size(135, 35);
            this.testWithFileButton.TabIndex = 0;
            this.testWithFileButton.Text = "Test(定義ファイル有り)";
            this.testWithFileButton.UseVisualStyleBackColor = true;
            this.testWithFileButton.Click += new System.EventHandler(this.testWithFileButton_Click);
            // 
            // logListView
            // 
            this.logListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1});
            this.logListView.FullRowSelect = true;
            this.logListView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this.logListView.Location = new System.Drawing.Point(12, 12);
            this.logListView.Name = "logListView";
            this.logListView.Size = new System.Drawing.Size(474, 230);
            this.logListView.TabIndex = 1;
            this.logListView.UseCompatibleStateImageBehavior = false;
            this.logListView.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Width = 452;
            // 
            // closeButton
            // 
            this.closeButton.Location = new System.Drawing.Point(411, 248);
            this.closeButton.Name = "closeButton";
            this.closeButton.Size = new System.Drawing.Size(75, 35);
            this.closeButton.TabIndex = 0;
            this.closeButton.Text = "閉じる";
            this.closeButton.UseVisualStyleBackColor = true;
            this.closeButton.Click += new System.EventHandler(this.closeButton_Click);
            // 
            // SampleForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(498, 295);
            this.Controls.Add(this.logListView);
            this.Controls.Add(this.closeButton);
            this.Controls.Add(this.testWithFileButton);
            this.Controls.Add(this.testButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SampleForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Sample";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button testButton;
        private System.Windows.Forms.Button testWithFileButton;
        private System.Windows.Forms.ListView logListView;
        private System.Windows.Forms.Button closeButton;
        private System.Windows.Forms.ColumnHeader columnHeader1;
    }
}

