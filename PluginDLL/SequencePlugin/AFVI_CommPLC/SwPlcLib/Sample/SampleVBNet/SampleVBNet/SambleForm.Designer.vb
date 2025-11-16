<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class SambleForm
    Inherits System.Windows.Forms.Form

    'フォームがコンポーネントの一覧をクリーンアップするために dispose をオーバーライドします。
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows フォーム デザイナーで必要です。
    Private components As System.ComponentModel.IContainer

    'メモ: 以下のプロシージャは Windows フォーム デザイナーで必要です。
    'Windows フォーム デザイナーを使用して変更できます。  
    'コード エディターを使って変更しないでください。
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.logListView = New System.Windows.Forms.ListView()
        Me.columnHeader1 = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.closeButton = New System.Windows.Forms.Button()
        Me.testWithFileButton = New System.Windows.Forms.Button()
        Me.testButton = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'logListView
        '
        Me.logListView.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.columnHeader1})
        Me.logListView.FullRowSelect = True
        Me.logListView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None
        Me.logListView.Location = New System.Drawing.Point(12, 12)
        Me.logListView.Name = "logListView"
        Me.logListView.Size = New System.Drawing.Size(474, 230)
        Me.logListView.TabIndex = 5
        Me.logListView.UseCompatibleStateImageBehavior = False
        Me.logListView.View = System.Windows.Forms.View.Details
        '
        'columnHeader1
        '
        Me.columnHeader1.Width = 452
        '
        'closeButton
        '
        Me.closeButton.Location = New System.Drawing.Point(411, 248)
        Me.closeButton.Name = "closeButton"
        Me.closeButton.Size = New System.Drawing.Size(75, 35)
        Me.closeButton.TabIndex = 2
        Me.closeButton.Text = "閉じる"
        Me.closeButton.UseVisualStyleBackColor = True
        '
        'testWithFileButton
        '
        Me.testWithFileButton.Location = New System.Drawing.Point(153, 248)
        Me.testWithFileButton.Name = "testWithFileButton"
        Me.testWithFileButton.Size = New System.Drawing.Size(135, 35)
        Me.testWithFileButton.TabIndex = 3
        Me.testWithFileButton.Text = "Test(定義ファイル有り)"
        Me.testWithFileButton.UseVisualStyleBackColor = True
        '
        'testButton
        '
        Me.testButton.Location = New System.Drawing.Point(12, 248)
        Me.testButton.Name = "testButton"
        Me.testButton.Size = New System.Drawing.Size(135, 35)
        Me.testButton.TabIndex = 4
        Me.testButton.Text = "Test(定義ファイル無し)"
        Me.testButton.UseVisualStyleBackColor = True
        '
        'SambleForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(498, 295)
        Me.Controls.Add(Me.logListView)
        Me.Controls.Add(Me.closeButton)
        Me.Controls.Add(Me.testWithFileButton)
        Me.Controls.Add(Me.testButton)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "SambleForm"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Sample"
        Me.ResumeLayout(False)

    End Sub

    Private WithEvents logListView As ListView
    Private WithEvents columnHeader1 As ColumnHeader
    Private WithEvents closeButton As Button
    Private WithEvents testWithFileButton As Button
    Private WithEvents testButton As Button
End Class
