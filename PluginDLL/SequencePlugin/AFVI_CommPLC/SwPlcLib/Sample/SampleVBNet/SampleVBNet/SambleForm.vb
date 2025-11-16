Imports SampleVBNet.SwPlcComSdk

Public Class SambleForm

    Private Sub AddLog(message As String)
        logListView.Items.Add(message)
        SelectLog(logListView.Items.Count - 1)
    End Sub

    Private Sub SelectLog(index As Integer)
        logListView.EnsureVisible(index)
        logListView.Focus()
        For Each item As ListViewItem In logListView.Items
            item.Selected = False
        Next
        logListView.Items(index).Selected = True
    End Sub

    Private Sub testButton_Click(sender As Object, e As EventArgs) Handles testButton.Click
        AddLog("***** Test(定義ファイル無し) *****")

        Dim message As String

        ' タグの作成
        ' タグを10個作成し、D1000～D1002を割り付けます
        Dim tags(3) As SwPlcTag
        For i As Integer = 0 To 3
            tags(i) = New SwPlcTag(
                    i,          ' タグID
                    "D",        ' レジスタ名
                    1000 + i,   ' アドレス
                    SwPlcDataType.SWPLC_DATATYPE_SHORT,    ' データ型 
                    1,          ' 要素数(連続したアドレスを配列として登録する場合は配列要素数で設定します)
                    False,      ' 0:モニタOff 1: モニタOn
                    False       ' 0:通知Off 1: 通知On
                )
        Next

        ' ポートオープン
        Dim libName As String
        Dim param As String
        Dim opt As String

        ' 接続パラメータ文字列を作成
        param = "Address=127.0.0.1;"                 ' 接続先アドレス
        param += "Port=50001;"                       ' 接続先ポート
        param += "Timeout=1000;"                     ' 通信タイムアウト時間(ms)
        param += "Retry=0;"                          ' 通信リトライ回数
        param += "LogFilePath=.\\;"                  ' 通信ログ出力先パス
        param += "LogFileName=TestLog;"              ' 通信ログファイル名
        param += "LogSize=100000;"                   ' 通信ログファイルサイズ(Byte)
        param += "LogNum=3"                          ' 通信ログファイル数

        ' 通信オプション設定文字列を作成
        ' ※PLC固有の通信パラメータを設定します。（PLC機種により内容が変わります)

        ' ダミーPLCへ接続します
        libName = "SwCom"
        opt = "ReadMaxSize=1024;"
        opt += "WriteMaxSize=1024;"

        '' 三菱PLCへ接続します
        'libName = "McCom"
        'opt = "Frame=3E;"
        'opt += "Code=ASCII;"
        'opt += "MonitoringTimer=0C;"
        'opt += "NetworkNo=00;"
        'opt += "PcNo=FF;"
        'opt += "ReqDestModIONo=03FF;"
        'opt += "ReqDestModStationNo=00;"
        'opt += "ReadBitMaxSize=7904;"
        'opt += "WriteBitMaxSize=7904;"
        'opt += "ReadWordMaxSize=960;"
        'opt += "WriteWordMaxSize=960"

        Dim handle As Integer
        Dim ret As Integer

        ret = SwPlcCom.SwPlcInitPort(
                handle,                     ' 通信ハンドル
                "TEST_PORT",                ' 通信ポート名
                libName,                    ' 通信ライブラリ名(McCom / OmronCom / KvCom / SwComなど)
                SwPlcCommType.SWPLC_TYPE_TCP,   ' 通信タイプ(TCP/UDP/Serial/Custom)
                tags,                       ' 登録タグ
                param,                      ' パラメータ
                opt                         ' オプション
              )

        If (ret <> SwPlcCode.SWPLC_OK) Then
            AddLog("通信ポートオープンエラー")
            Return
        End If

        AddLog("通信ポートオープン")

        ' Tag0～Tag2に書き込み
        ret = SwPlcCom.SwPlcWriteShort(handle, 0, 100)
        ret = SwPlcCom.SwPlcWriteShort(handle, 1, 200)
        ret = SwPlcCom.SwPlcWriteShort(handle, 2, 300)

        ' 実行
        ret = SwPlcCom.SwPlcExecute(handle)
        AddLog("書き込み実行")

        ' 完了待ち(3000ms待つ wait = 0待ちなし wait = -1: 完了まで待つ)
        ret = SwPlcCom.SwPlcResponse(handle, 3000)

        If (ret = SwPlcCode.SWPLC_RESPONSE_DONE) Then
            AddLog("書込み完了")
        Else
            AddLog("書込みエラー")
        End If

        ' Tag0～Tag2を読込み
        ret = SwPlcCom.SwPlcRead(handle, 0)
        ret = SwPlcCom.SwPlcRead(handle, 1)
        ret = SwPlcCom.SwPlcRead(handle, 2)
        ret = SwPlcCom.SwPlcExecute(handle)

        ' 完了待ち(3000ms待つ wait = 0待ちなし wait = -1: 完了まで待つ)
        ret = SwPlcCom.SwPlcResponse(handle, 3000)

        If (ret = SwPlcCode.SWPLC_RESPONSE_DONE) Then
            AddLog("読込み完了")
        Else
            AddLog("読込みエラー")
        End If

        ' PLCから読み込まれた値を取得
        Dim data As Short
        SwPlcCom.SwPlcGetShort(handle, 0, data)
        message = String.Format("Read Tag0 = {0}", data)
        AddLog(message)

        SwPlcCom.SwPlcGetShort(handle, 1, data)
        message = String.Format("Read Tag1 = {0}", data)
        AddLog(message)

        SwPlcCom.SwPlcGetShort(handle, 2, data)
        message = String.Format("Read Tag2 = {0}", data)
        AddLog(message)

        SwPlcCom.SwPlcClosePort(handle)

    End Sub

    Private Sub testWithFileButton_Click(sender As Object, e As EventArgs) Handles testWithFileButton.Click
        AddLog("***** Test(定義ファイル有り) *****")

        Dim csMessage As String
        Dim handle As Integer
        Dim ret As Integer
        ret = SwPlcCom.SwPlcLoadFile(handle, ".\\sample.xml")

        If (ret <> SwPlcCode.SWPLC_OK) Then
            AddLog("通信ポートオープンエラー")
            Return
        End If

        AddLog("通信ポートオープン")

        ' Tag0～Tag2に書き込み
        ret = SwPlcCom.SwPlcWriteShort(handle, 0, 100)
        ret = SwPlcCom.SwPlcWriteShort(handle, 1, 200)
        ret = SwPlcCom.SwPlcWriteShort(handle, 2, 300)

        ' 実行
        ret = SwPlcCom.SwPlcExecute(handle)
        AddLog("書き込み実行")

        ' 完了待ち(3000ms待つ wait = 0待ちなし wait = -1 完了まで待つ)
        ret = SwPlcCom.SwPlcResponse(handle, 3000)

        If (ret = SwPlcCode.SWPLC_RESPONSE_DONE) Then
            AddLog("書込み完了")
        Else
            AddLog("書込みエラー")
        End If

        ' Tag0～Tag2を読込み
        ret = SwPlcCom.SwPlcRead(handle, 0)
        ret = SwPlcCom.SwPlcRead(handle, 1)
        ret = SwPlcCom.SwPlcRead(handle, 2)
        ret = SwPlcCom.SwPlcExecute(handle)

        ' 完了待ち(3000ms待つ wait = 0待ちなし wait = -1 完了まで待つ)
        ret = SwPlcCom.SwPlcResponse(handle, 3000)

        If (ret = SwPlcCode.SWPLC_RESPONSE_DONE) Then
            AddLog("読込み完了")
        Else
            AddLog("読込みエラー")
        End If

        ' PLCから読み込まれた値を取得
        Dim data As Short
        SwPlcCom.SwPlcGetShort(handle, 0, data)
        csMessage = String.Format("Read Tag0 = {0}", data)
        AddLog(csMessage)

        SwPlcCom.SwPlcGetShort(handle, 1, data)
        csMessage = String.Format("Read Tag1 = {0}", data)
        AddLog(csMessage)

        SwPlcCom.SwPlcGetShort(handle, 2, data)
        csMessage = String.Format("Read Tag2 = {0}", data)
        AddLog(csMessage)

        SwPlcCom.SwPlcClosePort(handle)
    End Sub

    Private Sub closeButton_Click(sender As Object, e As EventArgs) Handles closeButton.Click
        Close()
    End Sub
End Class
