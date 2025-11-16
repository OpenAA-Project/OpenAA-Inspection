using System;
using System.Windows.Forms;
using SwPlcComSdk;

namespace SampleCS
{
    public partial class SampleForm : Form
    {
        public SampleForm()
        {
            InitializeComponent();
        }

        private void AddLog(string message)
        {
            logListView.Items.Add(message);
            SelectLog(logListView.Items.Count - 1);
        }

        private void SelectLog(int index)
        {
            logListView.EnsureVisible(index);
            logListView.Focus();
            foreach (ListViewItem item in logListView.Items)
            {
                item.Selected = false;
            }
            logListView.Items[index].Selected = true;
        }

        private void testButton_Click(object sender, EventArgs e)
        {
            AddLog("***** Test(定義ファイル無し) *****");

            string message;

            // タグの作成
            // タグを10個作成し、D1000～D1002を割り付けます
            SwPlcTag[] tags = new SwPlcTag[3];
            for (int i = 0; i < 3; i++)
            {
                tags[i] = new SwPlcTag(
                    i,          // タグID
                    "D",        // レジスタ名
                    1000 + i,   // アドレス
                    SwPlcDataType.SWPLC_DATATYPE_SHORT,    // データ型 
                    1,          // 要素数(連続したアドレスを配列として登録する場合は配列要素数で設定します)
                    false,      // 0:モニタOff 1:モニタOn
                    false       // 0:通知Off 1:通知On
                );    
            }

            // ポートオープン
            string libName;
            string param;
            string option;

            // 接続パラメータ文字列を作成
            param = "Address=127.0.0.1;";                 // 接続先アドレス
            param += "Port=50001;";                       // 接続先ポート
            param += "Timeout=1000;";                     // 通信タイムアウト時間(ms)
            param += "Retry=0;";                          // 通信リトライ回数
            param += "LogFilePath=.\\;";                  // 通信ログ出力先パス
            param += "LogFileName=TestLog;";              // 通信ログファイル名
            param += "LogSize=100000;";                   // 通信ログファイルサイズ(byte)
            param += "LogNum=3";                          // 通信ログファイル数

            // 通信オプション設定文字列を作成
            // ※PLC固有の通信パラメータを設定します。（PLC機種により内容が変わります)

            // ダミーPLCへ接続します
            libName = "SwCom";
            option = "ReadMaxSize=1024;";
            option += "WriteMaxSize=1024;";

            //// 三菱PLCへ接続します
            //libName = "McCom";
            //option = "Frame=3E;";
            //option += "Code=ASCII;";
            //option += "MonitoringTimer=0C;";
            //option += "NetworkNo=00;";
            //option += "PcNo=FF;";
            //option += "ReqDestModIONo=03FF;";
            //option += "ReqDestModStationNo=00;";
            //option += "ReadBitMaxSize=7904;";
            //option += "WriteBitMaxSize=7904;";
            //option += "ReadWordMaxSize=960;";
            //option += "WriteWordMaxSize=960";

            int handle;
            SwPlcCode ret;

            ret = SwPlcCom.SwPlcInitPort(
                out handle,                 // 通信ハンドル
                "TEST_PORT",                // 通信ポート名
                libName,                    // 通信ライブラリ名(McCom/OmronCom/KvCom/SwComなど)
                SwPlcCommType.SWPLC_TYPE_TCP,   // 通信タイプ(TCP/UDP/Serial/Custom)
                tags,                       // 登録タグ
                param,                      // パラメータ
                option                      // オプション
                );

            if (ret != (int)SwPlcCode.SWPLC_OK)
            {
                AddLog("通信ポートオープンエラー");
                return;
            }

            AddLog("通信ポートオープン");

            // Tag0～Tag2に書き込み
            ret = SwPlcCom.SwPlcWriteShort(handle, 0, 100);
            ret = SwPlcCom.SwPlcWriteShort(handle, 1, 200);
            ret = SwPlcCom.SwPlcWriteShort(handle, 2, 300);

            // 実行
            ret = SwPlcCom.SwPlcExecute(handle);
            AddLog("書き込み実行");

            // 完了待ち(3000ms待つ wait = 0:待ちなし wait = -1:完了まで待つ)
            ret = SwPlcCom.SwPlcResponse(handle, 3000);

            if (ret == SwPlcCode.SWPLC_RESPONSE_DONE)
            {
                AddLog("書込み完了");
            }
            else
            {
                AddLog("書込みエラー");
            }

            // Tag0～Tag2を読込み
            ret = SwPlcCom.SwPlcRead(handle, 0);
            ret = SwPlcCom.SwPlcRead(handle, 1);
            ret = SwPlcCom.SwPlcRead(handle, 2);
            ret = SwPlcCom.SwPlcExecute(handle);

            // 完了待ち(3000ms待つ wait = 0:待ちなし wait = -1:完了まで待つ)
            ret = SwPlcCom.SwPlcResponse(handle, 3000);

            if (ret == SwPlcCode.SWPLC_RESPONSE_DONE)
            {
                AddLog("読込み完了");
            }
            else
            {
                AddLog("読込みエラー");
            }

            // PLCから読み込まれた値を取得
            short data = 0;
            SwPlcCom.SwPlcGetShort(handle, 0, ref data);
            message = string.Format("Read Tag0 = {0}", data);
            AddLog(message);

            SwPlcCom.SwPlcGetShort(handle, 1, ref data);
            message = string.Format("Read Tag1 = {0}", data);
            AddLog(message);

            SwPlcCom.SwPlcGetShort(handle, 2, ref data);
            message = string.Format("Read Tag2 = {0}", data);
            AddLog(message);

            SwPlcCom.SwPlcClosePort(handle);
        }

        private void testWithFileButton_Click(object sender, EventArgs e)
        {
            AddLog("***** Test(定義ファイル有り) *****");

            string message;
            int handle;
            SwPlcCode ret;
            ret = SwPlcCom.SwPlcLoadFile(out handle, ".\\sample.xml");

            if (ret != (int)SwPlcCode.SWPLC_OK)
            {
                AddLog("通信ポートオープンエラー");
                return;
            }

            AddLog("通信ポートオープン");

            // Tag0～Tag2に書き込み
            ret = SwPlcCom.SwPlcWriteShort(handle, 0, 100);
            ret = SwPlcCom.SwPlcWriteShort(handle, 1, 200);
            ret = SwPlcCom.SwPlcWriteShort(handle, 2, 300);

            // 実行
            ret = SwPlcCom.SwPlcExecute(handle);
            AddLog("書き込み実行");

            // 完了待ち(3000ms待つ wait = 0:待ちなし wait = -1:完了まで待つ)
            ret = SwPlcCom.SwPlcResponse(handle, 3000);

            if (ret == SwPlcCode.SWPLC_RESPONSE_DONE)
            {
                AddLog("書込み完了");
            }
            else
            {
                AddLog("書込みエラー");
            }

            // Tag0～Tag2を読込み
            ret = SwPlcCom.SwPlcRead(handle, 0);
            ret = SwPlcCom.SwPlcRead(handle, 1);
            ret = SwPlcCom.SwPlcRead(handle, 2);
            ret = SwPlcCom.SwPlcExecute(handle);

            // 完了待ち(3000ms待つ wait = 0:待ちなし wait = -1:完了まで待つ)
            ret = SwPlcCom.SwPlcResponse(handle, 3000);

            if (ret == SwPlcCode.SWPLC_RESPONSE_DONE)
            {
                AddLog("読込み完了");
            }
            else
            {
                AddLog("読込みエラー");
            }

            // PLCから読み込まれた値を取得
            short data = 0;
            SwPlcCom.SwPlcGetShort(handle, 0, ref data);
            message = string.Format("Read Tag0 = {0}", data);
            AddLog(message);

            SwPlcCom.SwPlcGetShort(handle, 1, ref data);
            message = string.Format("Read Tag1 = {0}", data);
            AddLog(message);

            SwPlcCom.SwPlcGetShort(handle, 2, ref data);
            message = string.Format("Read Tag2 = {0}", data);
            AddLog(message);

            SwPlcCom.SwPlcClosePort(handle);
        }

        private void closeButton_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
