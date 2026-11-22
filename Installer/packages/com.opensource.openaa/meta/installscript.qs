function base64FromBytes(bytes) {
    var chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    var out = "";
    var i = 0;
    while (i < bytes.length) {
        var b0 = bytes[i++];
        var hasB1 = (i < bytes.length);
        var b1 = hasB1 ? bytes[i++] : 0;
        var hasB2 = (i < bytes.length);
        var b2 = hasB2 ? bytes[i++] : 0;

        out += chars.charAt(b0 >> 2);
        out += chars.charAt(((b0 & 3) << 4) | (b1 >> 4));
        out += hasB1 ? chars.charAt(((b1 & 15) << 2) | (b2 >> 6)) : "=";
        out += hasB2 ? chars.charAt(b2 & 63) : "=";
    }
    return out;
}

function toUtf8Base64(str) {
    var bytes = [];
    for (var i = 0; i < str.length; i++) {
        var c = str.charCodeAt(i);
        if (c < 0x80) {
            bytes.push(c);
        } else if (c < 0x800) {
            bytes.push(0xc0 | (c >> 6));
            bytes.push(0x80 | (c & 0x3f));
        } else if (c >= 0xd800 && c <= 0xdbff && i + 1 < str.length) {
            var c2 = str.charCodeAt(++i);
            var cp = 0x10000 + (((c & 0x3ff) << 10) | (c2 & 0x3ff));
            bytes.push(0xf0 | (cp >> 18));
            bytes.push(0x80 | ((cp >> 12) & 0x3f));
            bytes.push(0x80 | ((cp >> 6) & 0x3f));
            bytes.push(0x80 | (cp & 0x3f));
        } else {
            bytes.push(0xe0 | (c >> 12));
            bytes.push(0x80 | ((c >> 6) & 0x3f));
            bytes.push(0x80 | (c & 0x3f));
        }
    }
    return base64FromBytes(bytes);
}

function toUtf16LeBase64(str) {
    var bytes = [];
    for (var i = 0; i < str.length; i++) {
        var code = str.charCodeAt(i);
        bytes.push(code & 0xff);
        bytes.push((code >> 8) & 0xff);
    }
    return base64FromBytes(bytes);
}

function psQuote(s) {
    return "'" + String(s || "").replace(/'/g, "''") + "'";
}

function Component() {
    if (installer.isInstaller()) {
        installer.setValue("RemoveTargetDir", "false");
        installer.setMessageBoxAutomaticAnswer("OverwriteTargetDirectory", QMessageBox.Yes);
        installer.setMessageBoxAutomaticAnswer("stopProcessesForUpdates", QMessageBox.Ignore);

        installer.addWizardPage(component, "DataPathPage", QInstaller.ReadyForInstallation);
        installer.addWizardPage(component, "WorkingDirPage", QInstaller.ReadyForInstallation);
        installer.addWizardPage(component, "FirebirdPage", QInstaller.ReadyForInstallation);
    }

    component.loaded.connect(this, Component.prototype.installerLoaded);
    installer.installationFinished.connect(this, Component.prototype.onInstallationFinished);
}

function isWindows() {
    return (systemInfo.productType === "windows" || systemInfo.kernelType === "winnt");
}

function normalizePath(p) {
    if (!p) return "";
    if (isWindows()) {
        return p.replace(/\//g, "\\").replace(/\\+$/, "");
    }
    var res = p.replace(/\\/g, "/").replace(/\/+/g, "/").replace(/\/+$/, "");
    return res === "" ? "/" : res;
}

function cleanupOldInstallMetadata(dirPath) {
    if (!installer.isInstaller() || !dirPath || dirPath === "") return;
    var targetDir = normalizePath(dirPath);
    var sep = isWindows() ? "\\" : "/";
    var metaFiles = [
        "components.xml", "maintenancetool.exe", "maintenancetool",
        "maintenancetool.dat", "maintenancetool.ini",
        "InstallationLog.txt", "network.xml", "finalize.ps1", "finalize.sh", "root_setup.sh"
    ];
    if (installer.fileExists(targetDir + sep + "components.xml") ||
        installer.fileExists(targetDir + sep + "finalize.ps1") ||
        installer.fileExists(targetDir + sep + "finalize.sh")) {
        for (var i = 0; i < metaFiles.length; i++) {
            var f = targetDir + sep + metaFiles[i];
            if (installer.fileExists(f)) {
                if (isWindows()) {
                    installer.execute("cmd.exe", ["/c", "del", "/f", "/q", f]);
                } else {
                    installer.execute("rm", ["-f", f]);
                }
            }
        }
    }
}

Component.prototype.installerLoaded = function() {
    if (!installer.isInstaller()) return;

    var homeDir = normalizePath(installer.value("HomeDir"));
    var sep = isWindows() ? "\\" : "/";

    var defaultTargetDir = isWindows() ? "C:\\OpenAA" : (homeDir + "/OpenAA");
    if (installer.value("TargetDir") === "" || (!isWindows() && installer.value("TargetDir").indexOf("/OpenAA") === 0)) {
        installer.setValue("TargetDir", defaultTargetDir);
    }

    installer.setValue("RemoveTargetDir", "false");
    cleanupOldInstallMetadata(installer.value("TargetDir"));

    var txtSelectFolderTitle = qsTr("Select Folder");

    var pageDP = gui.pageByObjectName("DynamicDataPathPage");
    if (pageDP) {
        pageDP.title = qsTr("Database Folder");
        var lineEditDP = pageDP.findChild("dataPathLineEdit");
        var btnDP = pageDP.findChild("browseButton");
        var defaultDbDir = isWindows() ? "C:\\Data" : (homeDir + "/Data");

        if (lineEditDP && lineEditDP.text === "") lineEditDP.text = defaultDbDir;
        if (btnDP) {
            try { btnDP.clicked.disconnect(); } catch(e) {}
            btnDP.clicked.connect(function() {
                var currentPath = (lineEditDP && lineEditDP.text !== "") ? lineEditDP.text : homeDir;
                var dir = QFileDialog.getExistingDirectory(pageDP, txtSelectFolderTitle, currentPath);
                if (dir.length > 0) lineEditDP.text = normalizePath(dir);
            });
        }
    }

    var pageWD = gui.pageByObjectName("DynamicWorkingDirPage");
    if (pageWD) {
        pageWD.title = qsTr("Setting Folder");
        var lineEditWD = pageWD.findChild("workingDirLineEdit");
        var btnWD = pageWD.findChild("browseButton");

        if (lineEditWD && lineEditWD.text === "") lineEditWD.text = homeDir + sep + "OpenAA";
        if (btnWD) {
            try { btnWD.clicked.disconnect(); } catch(e) {}
            btnWD.clicked.connect(function() {
                var current = (lineEditWD && lineEditWD.text !== "") ? lineEditWD.text : homeDir;
                var dir = QFileDialog.getExistingDirectory(pageWD, txtSelectFolderTitle, current);
                if (dir.length > 0) lineEditWD.text = normalizePath(dir);
            });
        }
    }

    var pageFB = gui.pageByObjectName("DynamicFirebirdPage");
    if (pageFB) {
        pageFB.title = qsTr("Firebird Installation");
    }
}

function checkFirebirdInstalled() {
    if (isWindows()) {
        var psCheck5 =
            "$inst = (Get-ItemProperty -Path 'HKLM:\\SOFTWARE\\Firebird Project\\Firebird Server\\Instances' -Name 'DefaultInstance' -ErrorAction SilentlyContinue).DefaultInstance; " +
            "if ($inst -and (Test-Path (Join-Path $inst 'firebird.exe'))) { " +
            "  $ver = (Get-Item (Join-Path $inst 'firebird.exe')).VersionInfo.ProductVersion; " +
            "  if ($ver -match '^5\\.0') { exit 0 } " +
            "} " +
            "exit 1";
        var res = installer.execute("powershell.exe", ["-NoProfile", "-ExecutionPolicy", "Bypass", "-Command", psCheck5]);
        return (res && res[1] === 0);
    } else {
        var checkCmd =
            "exec < /dev/null; " +
            "if ls /opt/firebird/lib/libfbclient.so.5.0.* >/dev/null 2>&1; then exit 0; " +
            "elif [ -x /opt/firebird/bin/isql ] && /opt/firebird/bin/isql -z < /dev/null 2>&1 | grep -qE '5\\.0\\.(3|4)'; then exit 0; " +
            "elif dpkg-query -W -f='${Status} ${Version}\\n' 'firebird*' 2>/dev/null | grep '^install ok installed' | grep -qE '5\\.0\\.(3|4)'; then exit 0; " +
            "else exit 1; fi";
        var res = installer.execute("/bin/bash", ["-c", checkCmd]);
        return (res && res[1] === 0);
    }
}

function checkOldFirebirdInstalled() {
    if (isWindows()) {
        var psCheckOld =
            "$svc = Get-Service -Name 'Firebird*' -ErrorAction SilentlyContinue; " +
            "$proc = Get-Process -Name 'fbserver','fbguard','firebird' -ErrorAction SilentlyContinue; " +
            "$reg = Get-ItemProperty -Path 'HKLM:\\SOFTWARE\\Firebird Project\\Firebird Server\\Instances' -Name 'DefaultInstance' -ErrorAction SilentlyContinue; " +
            "if ($svc -or $proc -or $reg) { exit 0 } else { exit 1 }";
        var res = installer.execute("powershell.exe", ["-NoProfile", "-ExecutionPolicy", "Bypass", "-Command", psCheckOld]);
        return (res && res[1] === 0);
    } else {
        var checkOldCmd =
            "exec < /dev/null; " +
            "if dpkg-query -W -f='${Status} ${Package}\\n' 'firebird*' 'libfbclient*' 2>/dev/null | grep -q '^install ok installed'; then exit 0; " +
            "elif pgrep -x fbserver >/dev/null 2>&1 || pgrep -x fbguard >/dev/null 2>&1 || pgrep -x firebird >/dev/null 2>&1; then exit 0; " +
            "elif [ -d /opt/firebird ]; then exit 0; " +
            "else exit 1; fi";
        var res = installer.execute("/bin/bash", ["-c", checkOldCmd]);
        return (res && res[1] === 0);
    }
}

Component.prototype.isFirebirdPageVisible = function() {
    if (!installer.isInstaller()) return false;
    return !checkFirebirdInstalled();
}

Component.prototype.dynamicContentsSelectionChanged = function() {
    if (!installer.isInstaller()) return;
    var page = gui.pageByObjectName("DynamicFirebirdPage");
    if (page) {
        page.visible = !checkFirebirdInstalled();
    }
}

function buildWindowsFinalizeScript(targetDir, dbDir, setDir, overwriteDB, homeDir, updateFb, installFb5) {
    return "$InstallDir = (" + psQuote(targetDir) + " -replace '/', '\\').TrimEnd('\\')\r\n" +
        "$DatabaseDir = (" + psQuote(dbDir) + " -replace '/', '\\').TrimEnd('\\')\r\n" +
        "$SettingDir = (" + psQuote(setDir) + " -replace '/', '\\').TrimEnd('\\')\r\n" +
        "$OverwriteDB = " + psQuote(overwriteDB) + "\r\n" +
        "$HomeDir = " + psQuote(homeDir) + "\r\n" +
        "$UpdateFB = " + psQuote(updateFb) + "\r\n" +
        "$InstallFB5 = " + psQuote(installFb5) + "\r\n" +
        "\r\n" +
        "# 2.1.1: Firebird on Windows\r\n" +
        "if ($UpdateFB -eq 'true') {\r\n" +
        "    Get-Service -Name 'Firebird*' -ErrorAction SilentlyContinue | Stop-Service -Force -ErrorAction SilentlyContinue\r\n" +
        "    Get-Process -Name 'fbguard','fbserver','firebird' -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue\r\n" +
        "    $oldInst = (Get-ItemProperty -Path 'HKLM:\\SOFTWARE\\Firebird Project\\Firebird Server\\Instances' -Name 'DefaultInstance' -ErrorAction SilentlyContinue).DefaultInstance\r\n" +
        "    if ($oldInst) {\r\n" +
        "        $unins = Get-ChildItem -Path $oldInst -Filter 'unins*.exe' -ErrorAction SilentlyContinue | Select-Object -First 1\r\n" +
        "        if ($unins) {\r\n" +
        "            Start-Process -FilePath $unins.FullName -ArgumentList '/VERYSILENT /SUPPRESSMSGBOXES /NORESTART' -Wait -ErrorAction SilentlyContinue\r\n" +
        "        }\r\n" +
        "    }\r\n" +
        "}\r\n" +
        "if ($InstallFB5 -eq 'true') {\r\n" +
        "    $fbExe = Join-Path $InstallDir 'external\\Firebird-5.0.3.1683-0-windows-x64.exe'\r\n" +
        "    if (Test-Path -LiteralPath $fbExe) {\r\n" +
        "        Start-Process -FilePath $fbExe -ArgumentList '/SILENT /SUPPRESSMSGBOXES /NORESTART' -Wait\r\n" +
        "    }\r\n" +
        "}\r\n" +
        "\r\n" +
        "if (!(Test-Path -LiteralPath $DatabaseDir)) { New-Item -ItemType Directory -Path $DatabaseDir -Force | Out-Null }\r\n" +
        "$sourceDB = Join-Path $InstallDir 'OpenAA.FDB'\r\n" +
        "$targetDB = Join-Path $DatabaseDir 'OpenAA.FDB'\r\n" +
        "if ((!(Test-Path -LiteralPath $targetDB)) -or ($OverwriteDB -eq 'true')) {\r\n" +
        "    if (Test-Path -LiteralPath $sourceDB) { Copy-Item -LiteralPath $sourceDB -Destination $targetDB -Force }\r\n" +
        "}\r\n" +
        "if (!(Test-Path -LiteralPath $SettingDir)) { New-Item -ItemType Directory -Path $SettingDir -Force | Out-Null }\r\n" +
        "$globalDatCreated = $false\r\n" +
        "$newFiles = Get-ChildItem -Path $InstallDir -Filter '*.NEW' -File\r\n" +
        "foreach ($newFile in $newFiles) {\r\n" +
        "    $copiedNewPath = Join-Path $SettingDir $newFile.Name\r\n" +
        "    if ($newFile.FullName -ne $copiedNewPath) { Copy-Item -LiteralPath $newFile.FullName -Destination $copiedNewPath -Force }\r\n" +
        "    $baseName = $newFile.Name.Substring(0, $newFile.Name.Length - 4)\r\n" +
        "    $targetFile = Join-Path $SettingDir $baseName\r\n" +
        "    if (!(Test-Path -LiteralPath $targetFile)) {\r\n" +
        "        Rename-Item -LiteralPath $copiedNewPath -NewName $baseName -Force\r\n" +
        "        if ($baseName -ieq 'Global.dat') { $globalDatCreated = $true }\r\n" +
        "    } else {\r\n" +
        "        Remove-Item -LiteralPath $copiedNewPath -Force\r\n" +
        "    }\r\n" +
        "}\r\n" +
        "$WshShell = New-Object -ComObject WScript.Shell\r\n" +
        "$DesktopPath = [Environment]::GetFolderPath('Desktop')\r\n" +
        "$TutorialFolder = Join-Path $DesktopPath 'Tutrial'\r\n" +
        "if (!(Test-Path -LiteralPath $TutorialFolder)) { New-Item -ItemType Directory -Path $TutorialFolder -Force | Out-Null }\r\n" +
        "function Create-AppShortcut($LinkPath, $TargetExe, $CmdArguments) {\r\n" +
        "    $Shortcut = $WshShell.CreateShortcut($LinkPath)\r\n" +
        "    $Shortcut.TargetPath = $TargetExe\r\n" +
        "    if (![string]::IsNullOrEmpty($CmdArguments)) { $Shortcut.Arguments = $CmdArguments }\r\n" +
        "    $Shortcut.WorkingDirectory = $InstallDir\r\n" +
        "    $Shortcut.IconLocation = \"$TargetExe,0\"\r\n" +
        "    $Shortcut.Save()\r\n" +
        "}\r\n" +
        "$qParam = 'Q' + $SettingDir\r\n" +
        "$senarioFiles = Get-ChildItem -Path $InstallDir -Filter 'Senario*.gui' -File\r\n" +
        "foreach ($sFile in $senarioFiles) {\r\n" +
        "    $num = if ($sFile.BaseName -match '^Senario(\\d+)') { $matches[1] } else { $sFile.BaseName.Substring(7) }\r\n" +
        "    $linkPath = Join-Path $TutorialFolder ('Senario' + $num + '.lnk')\r\n" +
        "    Create-AppShortcut $linkPath (Join-Path $InstallDir 'InspectionFastPlayer.exe') \"$qParam G$($sFile.Name) NDM W1 -R\"\r\n" +
        "}\r\n" +
        "Create-AppShortcut (Join-Path $DesktopPath 'Inspection.lnk') (Join-Path $InstallDir 'InspectionFastPlayer.exe') \"$qParam GSenario51-ImageBank.gui NDM W1 -R\"\r\n" +
        "Create-AppShortcut (Join-Path $DesktopPath 'EditParameter.lnk') (Join-Path $InstallDir 'EditParameter.exe') $qParam\r\n" +
        "Create-AppShortcut (Join-Path $DesktopPath 'DataManagement.lnk') (Join-Path $InstallDir 'DataManagement.exe') $qParam\r\n" +
        "Create-AppShortcut (Join-Path $DesktopPath 'TutrialExecuter.lnk') (Join-Path $InstallDir 'TutrialExecuter.exe') ''\r\n" +
        "Create-AppShortcut (Join-Path $DesktopPath 'EditGUI.lnk') (Join-Path $InstallDir 'EditGUI.exe') $qParam\r\n" +
        "Create-AppShortcut (Join-Path $DesktopPath 'FileRegistryEditor.lnk') (Join-Path $InstallDir 'FileRegistryEditor.exe') $qParam\r\n" +
        "$MgmtFolder = Join-Path $DesktopPath 'Management'\r\n" +
        "if (!(Test-Path -LiteralPath $MgmtFolder)) { New-Item -ItemType Directory -Path $MgmtFolder -Force | Out-Null }\r\n" +
        "foreach ($app in @('EditGlobalOnMaster','MakeMasterReport','PIOViewer','ReportDisk','TesterLightDLL','XMLExplorer','XMLServerV3','EditAnyDataInLibrary','EditStatusComment')) {\r\n" +
        "    Create-AppShortcut (Join-Path $MgmtFolder ($app + '.lnk')) (Join-Path $InstallDir ($app + '.exe')) ''\r\n" +
        "}\r\n" +
        "$editParamExe = Join-Path $InstallDir 'EditParameter.exe'\r\n" +
        "if (($globalDatCreated -or ($OverwriteDB -eq 'true')) -and (Test-Path -LiteralPath $editParamExe)) {\r\n" +
        "    $dbFile = Join-Path $DatabaseDir 'OpenAA.FDB'\r\n" +
        "    Start-Process -FilePath $editParamExe -ArgumentList \"PLocalDatabase_FileName=$dbFile C V $qParam\" -WorkingDirectory $InstallDir -Wait\r\n" +
        "}\r\n" +
        "if (Test-Path -LiteralPath $editParamExe) {\r\n" +
        "    Start-Process -FilePath $editParamExe -ArgumentList \"PImageFilePath=$DatabaseDir C V $qParam\" -WorkingDirectory $InstallDir -Wait\r\n" +
        "}\r\n";
}

function buildLinuxFinalizeScript() {
    return "#!/bin/bash\n" +
        "exec < /dev/null > /tmp/openaa_finalize.log 2>&1\n" +
        "INSTALL_DIR=\"${1%/}\"\n" +
        "DB_DIR=\"${2%/}\"\n" +
        "SET_DIR=\"${3%/}\"\n" +
        "OVERWRITE_DB=\"$4\"\n" +
        "HOME_DIR=\"${5%/}\"\n" +
        "UPDATE_FB=\"$6\"\n" +
        "INSTALL_FB5=\"$7\"\n\n" +
        "shopt -s nullglob\n" +
        "echo \"Starting finalize.sh: INSTALL_DIR=$INSTALL_DIR, DB_DIR=$DB_DIR, SET_DIR=$SET_DIR, OVERWRITE_DB=$OVERWRITE_DB, HOME_DIR=$HOME_DIR, DISPLAY=${DISPLAY:-}, WAYLAND_DISPLAY=${WAYLAND_DISPLAY:-}\"\n\n" +
        "REAL_USER=$(stat -c '%U' \"$HOME_DIR\" 2>/dev/null || echo \"${SUDO_USER:-$(whoami)}\")\n\n" +
        "resolve_exe() {\n" +
        "    local base=\"$1\"\n" +
        "    if [ -f \"$INSTALL_DIR/${base}App\" ]; then\n" +
        "        echo \"$INSTALL_DIR/${base}App\"\n" +
        "    elif [ -f \"$INSTALL_DIR/$base\" ]; then\n" +
        "        echo \"$INSTALL_DIR/$base\"\n" +
        "    else\n" +
        "        local found=$(find \"$INSTALL_DIR\" -maxdepth 1 \\( -type f -o -type l \\) \\( -iname \"${base}App\" -o -iname \"$base\" \\) | head -n 1)\n" +
        "        if [ -n \"$found\" ]; then echo \"$found\"; else echo \"$INSTALL_DIR/$base\"; fi\n" +
        "    fi\n" +
        "}\n\n" +
        "ICON_DIR=\"\"\n" +
        "if [ -d \"$INSTALL_DIR/icon\" ]; then ICON_DIR=\"$INSTALL_DIR/icon\"\n" +
        "elif [ -d \"$INSTALL_DIR/ico\" ]; then ICON_DIR=\"$INSTALL_DIR/ico\"\n" +
        "fi\n\n" +
        "resolve_icon() {\n" +
        "    local base=\"$1\"\n" +
        "    local exe_name=$(basename \"$(resolve_exe \"$base\")\")\n" +
        "    for candidate in \"$ICON_DIR/${exe_name}.png\" \"$ICON_DIR/${base}.png\" \"$INSTALL_DIR/${exe_name}.png\" \"$INSTALL_DIR/${base}.png\"; do\n" +
        "        if [ -f \"$candidate\" ]; then echo \"$candidate\"; return; fi\n" +
        "    done\n" +
        "    if [ -n \"$ICON_DIR\" ]; then\n" +
        "        local found_icon=$(find \"$ICON_DIR\" -maxdepth 1 -type f \\( -iname \"${exe_name}.png\" -o -iname \"${base}.png\" \\) | head -n 1)\n" +
        "        if [ -n \"$found_icon\" ]; then echo \"$found_icon\"; return; fi\n" +
        "    fi\n" +
        "    for fallback in \"$ICON_DIR/OpenAA.png\" \"$ICON_DIR/installer_OpenAAIcon.png\" \"$INSTALL_DIR/OpenAA.png\" \"$INSTALL_DIR/installer_OpenAAIcon.png\" \"$INSTALL_DIR/logo.png\"; do\n" +
        "        if [ -f \"$fallback\" ]; then echo \"$fallback\"; return; fi\n" +
        "    done\n" +
        "    echo \"application-x-executable\"\n" +
        "}\n\n" +
        "# Load state left by root_setup from user-writable SET_DIR\n" +
        "GLOBAL_DAT_CREATED=false\n" +
        "STATE_FILE=\"$SET_DIR/.openaa_post_state.env\"\n" +
        "if [ -f \"$STATE_FILE\" ]; then\n" +
        "    source \"$STATE_FILE\" 2>/dev/null || true\n" +
        "    rm -f \"$STATE_FILE\" 2>/dev/null || true\n" +
        "fi\n" +
        "echo \"State after root_setup: GLOBAL_DAT_CREATED=$GLOBAL_DAT_CREATED\"\n\n" +
        "# Fallback 2-B: Database directory & OpenAA.FDB copy\n" +
        "mkdir -p \"$DB_DIR\" 2>/dev/null || true\n" +
        "if [ ! -f \"$DB_DIR/OpenAA.FDB\" ] || [ \"$OVERWRITE_DB\" = \"true\" ]; then\n" +
        "    [ -f \"$INSTALL_DIR/OpenAA.FDB\" ] && cp -f \"$INSTALL_DIR/OpenAA.FDB\" \"$DB_DIR/OpenAA.FDB\" 2>/dev/null || true\n" +
        "fi\n" +
        "chmod a+x \"$HOME_DIR\" 2>/dev/null || true\n" +
        "CUR_PATH=\"$DB_DIR\"\n" +
        "while [ -n \"$CUR_PATH\" ] && [ \"$CUR_PATH\" != \"/\" ] && [ \"$CUR_PATH\" != \".\" ]; do\n" +
        "    chmod a+x \"$CUR_PATH\" 2>/dev/null || true\n" +
        "    CUR_PATH=$(dirname \"$CUR_PATH\")\n" +
        "done\n" +
        "chmod -R 777 \"$DB_DIR\" 2>/dev/null || true\n" +
        "[ -f \"$DB_DIR/OpenAA.FDB\" ] && chmod 666 \"$DB_DIR/OpenAA.FDB\" 2>/dev/null || true\n\n" +
        "# Fallback 2-C: Copy and rename any remaining .NEW/.new files if root_setup did not process them\n" +
        "mkdir -p \"$SET_DIR\" \"$SET_DIR/.config\" 2>/dev/null || true\n" +
        "while IFS= read -r -d '' newfile; do\n" +
        "    filename=$(basename \"$newfile\")\n" +
        "    basename_no_new=\"${filename%.[Nn][Ee][Ww]}\"\n" +
        "    if [ ! \"$newfile\" -ef \"$SET_DIR/$filename\" ]; then\n" +
        "        cp -f \"$newfile\" \"$SET_DIR/$filename\" 2>/dev/null || true\n" +
        "    fi\n" +
        "    if [ ! -f \"$SET_DIR/$basename_no_new\" ]; then\n" +
        "        if mv -f \"$SET_DIR/$filename\" \"$SET_DIR/$basename_no_new\" 2>/dev/null; then\n" +
        "            echo \"Fallback created setting file: $SET_DIR/$basename_no_new\"\n" +
        "            [ \"${basename_no_new,,}\" = \"global.dat\" ] && GLOBAL_DAT_CREATED=true\n" +
        "        fi\n" +
        "    else\n" +
        "        rm -f \"$SET_DIR/$filename\" 2>/dev/null || true\n" +
        "    fi\n" +
        "    if [ ! \"$newfile\" -ef \"$SET_DIR/$filename\" ]; then\n" +
        "        rm -f \"$newfile\" 2>/dev/null || true\n" +
        "    fi\n" +
        "done < <(find \"$INSTALL_DIR\" -maxdepth 1 \\( -type f -o -type l \\) -iname \"*.new\" -print0 2>/dev/null)\n" +
        "if [ ! \"$SET_DIR\" -ef \"$INSTALL_DIR\" ]; then\n" +
        "    chmod -R 777 \"$SET_DIR\" 2>/dev/null || true\n" +
        "fi\n\n" +
        "# Use launch_openaa.sh created by elevated setup; fallback to SET_DIR only if missing\n" +
        "LAUNCHER=\"$INSTALL_DIR/launch_openaa.sh\"\n" +
        "if [ ! -x \"$LAUNCHER\" ]; then\n" +
        "    LAUNCHER=\"$SET_DIR/launch_openaa.sh\"\n" +
        "    cat <<EOF > \"$LAUNCHER\"\n" +
        "#!/bin/bash\n" +
        "INSTALL_DIR=\"$INSTALL_DIR\"\n" +
        "SET_DIR=\"$SET_DIR\"\n" +
        "DEFAULT_HOME=\"$HOME_DIR\"\n" +
        "if [ -z \"\\$HOME\" ] || [ \"\\$HOME\" = \"/\" ]; then\n" +
        "    export HOME=\"\\$DEFAULT_HOME\"\n" +
        "fi\n" +
        "export XDG_CONFIG_HOME=\"\\$SET_DIR/.config\"\n" +
        "mkdir -p \"\\$XDG_CONFIG_HOME\" 2>/dev/null || true\n" +
        "export LD_LIBRARY_PATH=\"\\$INSTALL_DIR/qtlib:\\$INSTALL_DIR:\\$INSTALL_DIR/lib:/opt/firebird/lib\\${LD_LIBRARY_PATH:+:\\$LD_LIBRARY_PATH}\"\n" +
        "if [ -d \"\\$INSTALL_DIR/plugins\" ]; then\n" +
        "    export QT_PLUGIN_PATH=\"\\$INSTALL_DIR/plugins\"\n" +
        "elif [ -d \"\\$INSTALL_DIR/platforms\" ]; then\n" +
        "    export QT_PLUGIN_PATH=\"\\$INSTALL_DIR\"\n" +
        "fi\n" +
        "cd \"\\$INSTALL_DIR\" || exit 1\n" +
        "TARGET_EXE=\"\\$1\"\n" +
        "shift\n" +
        "exec \"\\$TARGET_EXE\" \"\\$@\"\n" +
        "EOF\n" +
        "    chmod 755 \"$LAUNCHER\" 2>/dev/null || true\n" +
        "fi\n\n" +
        "DESKTOP_DIR=$(HOME=\"$HOME_DIR\" xdg-user-dir DESKTOP 2>/dev/null || echo \"$HOME_DIR/Desktop\")\n" +
        "TUTRIAL_DIR=\"$DESKTOP_DIR/Tutrial\"\n" +
        "mkdir -p \"$TUTRIAL_DIR\"\n\n" +
        "create_desktop_shortcut() {\n" +
        "    local link_path=\"$1\"\n" +
        "    local name=\"$2\"\n" +
        "    local base_exe=\"$3\"\n" +
        "    shift 3\n" +
        "    local target_exe=$(resolve_exe \"$base_exe\")\n" +
        "    local icon_path=$(resolve_icon \"$base_exe\")\n" +
        "    local exec_line=\"\\\"$LAUNCHER\\\" \\\"$target_exe\\\"\"\n" +
        "    for arg in \"$@\"; do\n" +
        "        if [ -n \"$arg\" ]; then\n" +
        "            exec_line=\"$exec_line \\\"$arg\\\"\"\n" +
        "        fi\n" +
        "    done\n" +
        "    cat <<EOF > \"$link_path\"\n" +
        "[Desktop Entry]\n" +
        "Version=1.0\n" +
        "Type=Application\n" +
        "Name=$name\n" +
        "Exec=$exec_line\n" +
        "Icon=$icon_path\n" +
        "Path=$INSTALL_DIR\n" +
        "Terminal=false\n" +
        "StartupNotify=true\n" +
        "EOF\n" +
        "    chmod 755 \"$link_path\"\n" +
        "    command -v gio >/dev/null 2>&1 && gio set \"$link_path\" metadata::trusted true 2>/dev/null || true\n" +
        "    mkdir -p \"$HOME_DIR/.local/share/applications\"\n" +
        "    local app_link=\"$HOME_DIR/.local/share/applications/OpenAA_$(basename \"$link_path\")\"\n" +
        "    cp -f \"$link_path\" \"$app_link\"\n" +
        "    chmod 755 \"$app_link\"\n" +
        "}\n\n" +
        "Q_PARAM=\"Q$SET_DIR\"\n" +
        "for sfile in \"$INSTALL_DIR\"/Senario*.gui; do\n" +
        "    sname=$(basename \"$sfile\")\n" +
        "    sbase=\"${sname%.gui}\"\n" +
        "    if [[ \"$sbase\" =~ ^Senario([0-9]+) ]]; then num=\"${BASH_REMATCH[1]}\"\n" +
        "    else num=\"${sbase:7}\"; fi\n" +
        "    create_desktop_shortcut \"$TUTRIAL_DIR/Senario${num}.desktop\" \"Senario${num}\" \"InspectionFastPlayer\" \"$Q_PARAM\" \"G$sname\" \"NDM\" \"W1\" \"-R\"\n" +
        "done\n\n" +
        "create_desktop_shortcut \"$DESKTOP_DIR/Inspection.desktop\" \"Inspection\" \"InspectionFastPlayer\" \"$Q_PARAM\" \"GSenario51-ImageBank.gui\" \"NDM\" \"W1\" \"-R\"\n" +
        "create_desktop_shortcut \"$DESKTOP_DIR/EditParameter.desktop\" \"EditParameter\" \"EditParameter\" \"$Q_PARAM\"\n" +
        "create_desktop_shortcut \"$DESKTOP_DIR/DataManagement.desktop\" \"DataManagement\" \"DataManagement\" \"$Q_PARAM\"\n" +
        "create_desktop_shortcut \"$DESKTOP_DIR/TutrialExecuter.desktop\" \"TutrialExecuter\" \"TutrialExecuter\"\n" +
        "create_desktop_shortcut \"$DESKTOP_DIR/EditGUI.desktop\" \"EditGUI\" \"EditGUI\" \"$Q_PARAM\"\n" +
        "create_desktop_shortcut \"$DESKTOP_DIR/FileRegistryEditor.desktop\" \"FileRegistryEditor\" \"FileRegistryEditor\" \"$Q_PARAM\"\n\n" +
        "MGMT_DIR=\"$DESKTOP_DIR/Management\"\n" +
        "mkdir -p \"$MGMT_DIR\"\n" +
        "for app in EditGlobalOnMaster MakeMasterReport PIOViewer ReportDisk TesterLightDLL XMLExplorer XMLServerV3 EditAnyDataInLibrary EditStatusComment; do\n" +
        "    create_desktop_shortcut \"$MGMT_DIR/${app}.desktop\" \"$app\" \"$app\"\n" +
        "done\n\n" +
        "# Configure KDE Dolphin to execute .desktop files in folders without prompting\n" +
        "mkdir -p \"$HOME_DIR/.config\"\n" +
        "if command -v kwriteconfig6 >/dev/null 2>&1; then\n" +
        "    XDG_CONFIG_HOME=\"$HOME_DIR/.config\" kwriteconfig6 --file kiorc --group \"Executable scripts\" --key \"behaviourOnLaunch\" \"execute\" 2>/dev/null || true\n" +
        "elif command -v kwriteconfig5 >/dev/null 2>&1; then\n" +
        "    XDG_CONFIG_HOME=\"$HOME_DIR/.config\" kwriteconfig5 --file kiorc --group \"Executable scripts\" --key \"behaviourOnLaunch\" \"execute\" 2>/dev/null || true\n" +
        "else\n" +
        "    KIORC=\"$HOME_DIR/.config/kiorc\"\n" +
        "    if [ -f \"$KIORC\" ] && grep -q '^\\[Executable scripts\\]' \"$KIORC\"; then\n" +
        "        if grep -q '^behaviourOnLaunch=' \"$KIORC\"; then\n" +
        "            sed -i 's/^behaviourOnLaunch=.*/behaviourOnLaunch=execute/' \"$KIORC\"\n" +
        "        else\n" +
        "            sed -i '/^\\[Executable scripts\\]/a behaviourOnLaunch=execute' \"$KIORC\"\n" +
        "        fi\n" +
        "    else\n" +
        "        printf '\\n[Executable scripts]\\nbehaviourOnLaunch=execute\\n' >> \"$KIORC\"\n" +
        "    fi\n" +
        "fi\n" +
        "command -v kbuildsycoca6 >/dev/null 2>&1 && HOME=\"$HOME_DIR\" kbuildsycoca6 --noincremental >/dev/null 2>&1 || true\n" +
        "command -v kbuildsycoca5 >/dev/null 2>&1 && HOME=\"$HOME_DIR\" kbuildsycoca5 --noincremental >/dev/null 2>&1 || true\n\n" +
        "# Configure Raspberry Pi OS (PCManFM) to execute .desktop files without prompting\n" +
        "mkdir -p \"$HOME_DIR/.config/libfm\"\n" +
        "LIBFM_CONF=\"$HOME_DIR/.config/libfm/libfm.conf\"\n" +
        "if [ -f \"$LIBFM_CONF\" ] && grep -q '^\\[config\\]' \"$LIBFM_CONF\"; then\n" +
        "    if grep -q '^quick_exec=' \"$LIBFM_CONF\"; then\n" +
        "        sed -i 's/^quick_exec=.*/quick_exec=1/' \"$LIBFM_CONF\"\n" +
        "    else\n" +
        "        sed -i '/^\\[config\\]/a quick_exec=1' \"$LIBFM_CONF\"\n" +
        "    fi\n" +
        "else\n" +
        "    printf '\\n[config]\\nquick_exec=1\\n' >> \"$LIBFM_CONF\"\n" +
        "fi\n\n" +
        "# 100 & 101: Run EditParameter in user desktop session with fallback QPA backends\n" +
        "run_edit_param_user() {\n" +
        "    local exe=\"$1\"\n" +
        "    shift\n" +
        "    local rc=1\n" +
        "    local global_dat=\"$SET_DIR/Global.dat\"\n" +
        "    local before_hash=\"\"\n" +
        "    [ -f \"$global_dat\" ] && before_hash=$(sha256sum \"$global_dat\" 2>/dev/null | awk '{print $1}')\n" +
        "    for qpa in \"\" \"xcb\" \"offscreen\"; do\n" +
        "        echo \"Executing EditParameter (qpa='${qpa}'): $exe $*\"\n" +
        "        (\n" +
        "            cd \"$INSTALL_DIR\" || exit 1\n" +
        "            export HOME=\"$HOME_DIR\"\n" +
        "            export XDG_CONFIG_HOME=\"$SET_DIR/.config\"\n" +
        "            mkdir -p \"$XDG_CONFIG_HOME\"\n" +
        "            export LD_LIBRARY_PATH=\"$INSTALL_DIR/qtlib:$INSTALL_DIR:$INSTALL_DIR/lib:/opt/firebird/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}\"\n" +
        "            if [ -d \"$INSTALL_DIR/plugins\" ]; then\n" +
        "                export QT_PLUGIN_PATH=\"$INSTALL_DIR/plugins\"\n" +
        "            elif [ -d \"$INSTALL_DIR/platforms\" ]; then\n" +
        "                export QT_PLUGIN_PATH=\"$INSTALL_DIR\"\n" +
        "            fi\n" +
        "            if [ -n \"$qpa\" ]; then export QT_QPA_PLATFORM=\"$qpa\"; else unset QT_QPA_PLATFORM; fi\n" +
        "            if command -v timeout >/dev/null 2>&1; then\n" +
        "                timeout 30 \"$exe\" \"$@\" < /dev/null\n" +
        "            else\n" +
        "                \"$exe\" \"$@\" < /dev/null\n" +
        "            fi\n" +
        "        )\n" +
        "        rc=$?\n" +
        "        local after_hash=\"\"\n" +
        "        [ -f \"$global_dat\" ] && after_hash=$(sha256sum \"$global_dat\" 2>/dev/null | awk '{print $1}')\n" +
        "        echo \"EditParameter result (qpa='${qpa}'): rc=$rc, Global.dat hash before=${before_hash:-none} after=${after_hash:-none}\"\n" +
        "        [ \"$rc\" -eq 0 ] && return 0\n" +
        "    done\n" +
        "    return \"$rc\"\n" +
        "}\n\n" +
        "EDIT_PARAM_EXE=$(resolve_exe \"EditParameter\")\n" +
        "echo \"Resolved EditParameter binary: $EDIT_PARAM_EXE (GLOBAL_DAT_CREATED=$GLOBAL_DAT_CREATED, OVERWRITE_DB=$OVERWRITE_DB)\"\n" +
        "if [ -x \"$EDIT_PARAM_EXE\" ]; then\n" +
        "    if [ \"$GLOBAL_DAT_CREATED\" = \"true\" ] || [ \"$OVERWRITE_DB\" = \"true\" ]; then\n" +
        "        run_edit_param_user \"$EDIT_PARAM_EXE\" \"PLocalDatabase_FileName=$DB_DIR/OpenAA.FDB\" C V \"$Q_PARAM\" || true\n" +
        "    else\n" +
        "        echo \"Skipping EditParameter (100): Global.dat already existed in $SET_DIR and OVERWRITE_DB is false.\"\n" +
        "    fi\n" +
        "    run_edit_param_user \"$EDIT_PARAM_EXE\" \"PImageFilePath=$DB_DIR\" C V \"$Q_PARAM\" || true\n" +
        "else\n" +
        "    echo \"Warning: EditParameter executable not found or not executable: $EDIT_PARAM_EXE\"\n" +
        "fi\n\n" +
        "chown -R \"$REAL_USER\":firebird \"$DB_DIR\" 2>/dev/null || chown -R \"$REAL_USER\":\"$REAL_USER\" \"$DB_DIR\" 2>/dev/null || true\n" +
        "if [ ! \"$SET_DIR\" -ef \"$INSTALL_DIR\" ]; then\n" +
        "    chown -R \"$REAL_USER\":\"$REAL_USER\" \"$SET_DIR\" 2>/dev/null || true\n" +
        "    chmod -R 777 \"$SET_DIR\" 2>/dev/null || true\n" +
        "fi\n" +
        "chown -R \"$REAL_USER\":\"$REAL_USER\" \"$TUTRIAL_DIR\" \"$MGMT_DIR\" \"$HOME_DIR/.config/kiorc\" \"$HOME_DIR/.config/libfm\" \"$HOME_DIR/.local/share/applications\" 2>/dev/null || true\n" +
        "chown \"$REAL_USER\":\"$REAL_USER\" \"$DESKTOP_DIR\"/*.desktop 2>/dev/null || true\n" +
        "chmod -R 777 \"$DB_DIR\" 2>/dev/null || true\n" +
        "[ -f \"$DB_DIR/OpenAA.FDB\" ] && chmod 666 \"$DB_DIR/OpenAA.FDB\" 2>/dev/null || true\n" +
        "echo \"finalize.sh completed.\"\n";
}

Component.prototype.createOperations = function() {
    cleanupOldInstallMetadata(installer.value("TargetDir"));

    var homeDir = normalizePath(installer.value("HomeDir"));
    var sep = isWindows() ? "\\" : "/";

    var dbDir = isWindows() ? "C:\\Data" : (homeDir + "/Data");
    var overwriteDB = "false";
    var pageDP = gui.pageByObjectName("DynamicDataPathPage");
    if (pageDP) {
        var dpEdit = pageDP.findChild("dataPathLineEdit");
        var ovCheck = pageDP.findChild("overwriteCheckBox");
        if (dpEdit && dpEdit.text !== "") dbDir = normalizePath(dpEdit.text);
        if (ovCheck && ovCheck.checked) overwriteDB = "true";
    }
    installer.setValue("OpenAA_DbDir", dbDir);
    installer.setValue("OpenAA_OverwriteDB", overwriteDB);

    var setDir = homeDir + sep + "OpenAA";
    var pageWD = gui.pageByObjectName("DynamicWorkingDirPage");
    if (pageWD) {
        var wdEdit = pageWD.findChild("workingDirLineEdit");
        if (wdEdit && wdEdit.text !== "") setDir = normalizePath(wdEdit.text);
    }
    installer.setValue("OpenAA_SetDir", setDir);

    var targetDir = normalizePath(installer.value("TargetDir"));

    var updateFb = "false";
    var installFb5 = "false";

    if (installer.isInstaller()) {
        if (!checkFirebirdInstalled()) {
            if (checkOldFirebirdInstalled()) {
                var ans = QMessageBox.question(
                    "fb_update",
                    qsTr("Firebird Update"),
                    qsTr("Older version of Firebird is detected. Do you want to remove it and install Firebird 5.0.4?"),
                    QMessageBox.Yes | QMessageBox.No,
                    QMessageBox.Yes
                );
                if (ans === QMessageBox.Yes) {
                    updateFb = "true";
                    installFb5 = "true";
                }
            } else {
                installFb5 = "true";
            }
        }
    }
    installer.setValue("OpenAA_UpdateFB", updateFb);
    installer.setValue("OpenAA_InstallFB5", installFb5);

    // 200: Uninstall cleanup
    // Do NOT delete installerResources or extracted files synchronously while maintenancetool is still running.
    if (isWindows()) {
        var escapedTargetDir = targetDir.replace(/'/g, "''");
        var undoPsCmd =
            "$DesktopPath = [Environment]::GetFolderPath('Desktop'); " +
            "$items = @('Tutrial', 'Management', 'Inspection.lnk', 'EditParameter.lnk', 'DataManagement.lnk', 'TutrialExecuter.lnk', 'EditGUI.lnk', 'FileRegistryEditor.lnk'); " +
            "foreach ($item in $items) { " +
            "    $p = Join-Path $DesktopPath $item; " +
            "    if (Test-Path -LiteralPath $p) { Remove-Item -LiteralPath $p -Recurse -Force -ErrorAction SilentlyContinue } " +
            "}; " +
            "$instDir = '" + escapedTargetDir + "'; " +
            "if ($instDir -and (Test-Path -LiteralPath $instDir)) { " +
            "    $env:OPENAA_INST_DIR = $instDir; " +
            "    Start-Process -FilePath 'powershell.exe' -WindowStyle Hidden -ArgumentList '-NoProfile -ExecutionPolicy Bypass -Command \"while (Get-Process -Name maintenancetool* -ErrorAction SilentlyContinue) { Start-Sleep -Milliseconds 500 }; Start-Sleep -Seconds 1; if (Test-Path -LiteralPath $env:OPENAA_INST_DIR) { Remove-Item -LiteralPath $env:OPENAA_INST_DIR -Recurse -Force -ErrorAction SilentlyContinue }\"' " +
            "}";

        component.addOperation(
            "Execute", "cmd.exe", "/c", "echo", "OpenAA installation started",
            "UNDOEXECUTE", "powershell.exe", "-NoProfile", "-ExecutionPolicy", "Bypass", "-Command", undoPsCmd
        );
    } else {
        var escapedLinuxDir = targetDir.replace(/'/g, "'\\''");
        var escapedHomeDir = homeDir.replace(/'/g, "'\\''");
        var undoShCmd =
            "HOME_DIR='" + escapedHomeDir + "'; " +
            "DESKTOP_DIR=$(HOME=\"$HOME_DIR\" xdg-user-dir DESKTOP 2>/dev/null || echo \"$HOME_DIR/Desktop\"); " +
            "for item in 'Tutrial' 'Management' 'Inspection.desktop' 'EditParameter.desktop' 'DataManagement.desktop' 'TutrialExecuter.desktop' 'EditGUI.desktop' 'FileRegistryEditor.desktop'; do " +
            "  rm -rf \"$DESKTOP_DIR/$item\"; " +
            "done; " +
            "rm -f \"$HOME_DIR/.local/share/applications/OpenAA_\"*.desktop; " +
            "rm -f /etc/ld.so.conf.d/openaa.conf /etc/ld.so.conf.d/zz-openaa.conf 2>/dev/null || true; " +
            "ldconfig 2>/dev/null || true; " +
            "INST_DIR='" + escapedLinuxDir + "'; " +
            "if [ -n \"$INST_DIR\" ] && [ \"$INST_DIR\" != \"/\" ] && [ \"$INST_DIR\" != \"$HOME_DIR\" ] && [ -d \"$INST_DIR\" ]; then " +
            "  nohup /bin/bash -c 'DIR=\"$1\"; i=0; while pgrep -x maintenancetool >/dev/null 2>&1 && [ $i -lt 120 ]; do sleep 0.5; i=$((i+1)); done; sleep 1; rm -rf \"$DIR\"' _ \"$INST_DIR\" </dev/null >/dev/null 2>&1 & " +
            "fi";

        component.addElevatedOperation(
            "Execute", "/bin/echo", "OpenAA installation started",
            "UNDOEXECUTE", "/bin/bash", "-c", undoShCmd
        );
    }

    component.createOperations();

    if (!isWindows()) {
        // 2.1.2 & 2.1.3 & 2-B & 2-C: Linux x64 / Raspberry Pi 64bit elevated setup script
        // Run via temporary /tmp script without Delete/AppendFile operations so uninstall never attempts backup restore
        var rootSh = "#!/bin/bash\n" +
        "exec < /dev/null > /tmp/openaa_fb_install.log 2>&1\n" +
        "shopt -s nullglob\n" +
        "UPDATE_FB=\"$1\"\n" +
        "INSTALL_FB5=\"$2\"\n" +
        "INSTALL_DIR=\"${3%/}\"\n" +
        "DB_DIR=\"${4%/}\"\n" +
        "SET_DIR=\"${5%/}\"\n" +
        "HOME_DIR=\"${6%/}\"\n" +
        "OVERWRITE_DB=\"$7\"\n" +
        "export DEBIAN_FRONTEND=noninteractive\n\n" +
        "echo \"Starting root_setup: UPDATE_FB=$UPDATE_FB, INSTALL_FB5=$INSTALL_FB5, INSTALL_DIR=$INSTALL_DIR, DB_DIR=$DB_DIR, SET_DIR=$SET_DIR, OVERWRITE_DB=$OVERWRITE_DB\"\n" +
        "rm -f /tmp/openaa_post_state.env 2>/dev/null || true\n" +
        "chmod -R a+rX \"$INSTALL_DIR\" 2>/dev/null || true\n\n" +
        "# Generate launch_openaa.sh directly with root privileges\n" +
        "cat <<EOF_LAUNCH > \"$INSTALL_DIR/launch_openaa.sh\"\n" +
        "#!/bin/bash\n" +
        "INSTALL_DIR=\"$INSTALL_DIR\"\n" +
        "SET_DIR=\"$SET_DIR\"\n" +
        "DEFAULT_HOME=\"$HOME_DIR\"\n" +
        "if [ -z \"\\$HOME\" ] || [ \"\\$HOME\" = \"/\" ]; then\n" +
        "    export HOME=\"\\$DEFAULT_HOME\"\n" +
        "fi\n" +
        "export XDG_CONFIG_HOME=\"\\$SET_DIR/.config\"\n" +
        "mkdir -p \"\\$XDG_CONFIG_HOME\" 2>/dev/null || true\n" +
        "export LD_LIBRARY_PATH=\"\\$INSTALL_DIR/qtlib:\\$INSTALL_DIR:\\$INSTALL_DIR/lib:/opt/firebird/lib\\${LD_LIBRARY_PATH:+:\\$LD_LIBRARY_PATH}\"\n" +
        "if [ -d \"\\$INSTALL_DIR/plugins\" ]; then\n" +
        "    export QT_PLUGIN_PATH=\"\\$INSTALL_DIR/plugins\"\n" +
        "elif [ -d \"\\$INSTALL_DIR/platforms\" ]; then\n" +
        "    export QT_PLUGIN_PATH=\"\\$INSTALL_DIR\"\n" +
        "fi\n" +
        "cd \"\\$INSTALL_DIR\" || exit 1\n" +
        "TARGET_EXE=\"\\$1\"\n" +
        "shift\n" +
        "exec \"\\$TARGET_EXE\" \"\\$@\"\n" +
        "EOF_LAUNCH\n" +
        "chmod 755 \"$INSTALL_DIR/launch_openaa.sh\" 2>/dev/null || true\n\n" +
        "for base in InspectionFastPlayer EditParameter DataManagement TutrialExecuter EditGUI FileRegistryEditor EditGlobalOnMaster MakeMasterReport PIOViewer ReportDisk TesterLightDLL XMLExplorer XMLServerV3 EditAnyDataInLibrary EditStatusComment; do\n" +
        "    [ -f \"$INSTALL_DIR/$base\" ] && chmod 755 \"$INSTALL_DIR/$base\"\n" +
        "    [ -f \"$INSTALL_DIR/${base}App\" ] && chmod 755 \"$INSTALL_DIR/${base}App\"\n" +
        "done\n\n" +
        "# Generate qt.conf if bundled Qt plugins exist and qt.conf is not provided\n" +
        "if [ ! -f \"$INSTALL_DIR/qt.conf\" ]; then\n" +
        "    if [ -d \"$INSTALL_DIR/plugins\" ]; then\n" +
        "        printf \"[Paths]\\nPlugins = plugins\\n\" > \"$INSTALL_DIR/qt.conf\"\n" +
        "        chmod a+r \"$INSTALL_DIR/qt.conf\"\n" +
        "    elif [ -d \"$INSTALL_DIR/platforms\" ]; then\n" +
        "        printf \"[Paths]\\nPlugins = .\\n\" > \"$INSTALL_DIR/qt.conf\"\n" +
        "        chmod a+r \"$INSTALL_DIR/qt.conf\"\n" +
        "    fi\n" +
        "fi\n\n" +
        "ICON_DIR=\"\"\n" +
        "if [ -d \"$INSTALL_DIR/icon\" ]; then ICON_DIR=\"$INSTALL_DIR/icon\"\n" +
        "elif [ -d \"$INSTALL_DIR/ico\" ]; then ICON_DIR=\"$INSTALL_DIR/ico\"\n" +
        "fi\n" +
        "if [ -n \"$ICON_DIR\" ]; then\n" +
        "    chmod -R a+rX \"$ICON_DIR\" 2>/dev/null || true\n" +
        "    for png_path in \"$ICON_DIR\"/*.png; do\n" +
        "        icon_base=$(basename \"$png_path\" .png)\n" +
        "        if [[ ! \"$icon_base\" =~ App$ ]] && [ -f \"$INSTALL_DIR/${icon_base}App\" ]; then\n" +
        "            cp -f \"$png_path\" \"$ICON_DIR/${icon_base}App.png\" 2>/dev/null || true\n" +
        "            chmod a+r \"$ICON_DIR/${icon_base}App.png\" 2>/dev/null || true\n" +
        "        fi\n" +
        "    done\n" +
        "fi\n\n" +
        "# Install minimal non-Qt OS prerequisites (Firebird 5.0.4 dependencies and XCB libraries)\n" +
        "if [ \"$UPDATE_FB\" = \"true\" ] || [ \"$INSTALL_FB5\" = \"true\" ] || ! ldconfig -p 2>/dev/null | grep -q 'libxcb-cursor\\.so\\.0'; then\n" +
        "    apt-get update -y < /dev/null || true\n" +
        "    for pkg in tar gzip binutils libtommath1 libtommath-dev libtomcrypt1 libtomcrypt-dev libncurses6 libncurses5 libncurses-dev libicu-dev libxcb-cursor0 libxcb-xinerama0 libxcb-icccm4 libxcb-image0 libxcb-keysyms1 libxcb-render-util0 libxcb-shape0 libxkbcommon-x11-0; do\n" +
        "        apt-get install -y -o Dpkg::Options::='--force-confdef' -o Dpkg::Options::='--force-confold' \"$pkg\" < /dev/null 2>/dev/null || true\n" +
        "    done\n" +
        "fi\n\n" +
        "for libdir in /usr/lib/x86_64-linux-gnu /usr/lib/aarch64-linux-gnu /lib/x86_64-linux-gnu /lib/aarch64-linux-gnu /usr/lib64 /usr/lib; do\n" +
        "    if [ -d \"$libdir\" ]; then\n" +
        "        [ -e \"$libdir/libtommath.so.1\" ] && [ ! -e \"$libdir/libtommath.so.0\" ] && ln -sf \"$libdir/libtommath.so.1\" \"$libdir/libtommath.so.0\"\n" +
        "        [ -e \"$libdir/libtomcrypt.so.1\" ] && [ ! -e \"$libdir/libtomcrypt.so.0\" ] && ln -sf \"$libdir/libtomcrypt.so.1\" \"$libdir/libtomcrypt.so.0\"\n" +
        "        [ -e \"$libdir/libncurses.so.6\" ] && [ ! -e \"$libdir/libncurses.so.5\" ] && ln -sf \"$libdir/libncurses.so.6\" \"$libdir/libncurses.so.5\"\n" +
        "        [ -e \"$libdir/libtinfo.so.6\" ] && [ ! -e \"$libdir/libtinfo.so.5\" ] && ln -sf \"$libdir/libtinfo.so.6\" \"$libdir/libtinfo.so.5\"\n" +
        "    fi\n" +
        "done\n" +
        "ldconfig\n\n" +
        "if [ \"$UPDATE_FB\" = \"true\" ]; then\n" +
        "    systemctl stop firebird3.0 firebird4.0 firebird.service firebird-superserver.service firebird.socket 2>/dev/null || true\n" +
        "    pkill -9 -x fbserver 2>/dev/null || true\n" +
        "    pkill -9 -x fbguard 2>/dev/null || true\n" +
        "    pkill -9 -x firebird 2>/dev/null || true\n" +
        "    OLD_PKGS=$(dpkg-query -W -f='${Status}\\t${Package}\\n' 'firebird*' 'libfbclient*' 'libib-util*' 2>/dev/null | awk -F'\\t' '/^install ok installed/ {print $2}')\n" +
        "    if [ -n \"$OLD_PKGS\" ]; then\n" +
        "        apt-get remove --purge -y -o Dpkg::Options::='--force-confdef' -o Dpkg::Options::='--force-confold' $OLD_PKGS < /dev/null || \\\n" +
        "        dpkg --remove --force-remove-reinstreq $OLD_PKGS < /dev/null || true\n" +
        "        apt-get autoremove -y < /dev/null || true\n" +
        "    fi\n" +
        "    rm -rf /opt/firebird /etc/firebird /var/run/firebird\n" +
        "    rm -f /etc/init.d/firebird* /lib/systemd/system/firebird* /etc/systemd/system/firebird*\n" +
        "    systemctl daemon-reload 2>/dev/null || true\n" +
        "    ldconfig\n" +
        "fi\n\n" +
        "if [ \"$UPDATE_FB\" = \"true\" ] || [ \"$INSTALL_FB5\" = \"true\" ]; then\n" +
        "    ARCH=$(uname -m)\n" +
        "    FB_TAR=\"\"\n" +
        "    if [ \"$ARCH\" = \"x86_64\" ]; then\n" +
        "        if [ -f \"$INSTALL_DIR/external/Firebird-5.0.4.1812-0-linux-x64.tar.gz\" ]; then\n" +
        "            FB_TAR=\"$INSTALL_DIR/external/Firebird-5.0.4.1812-0-linux-x64.tar.gz\"\n" +
        "        else\n" +
        "            FB_TAR=$(ls \"$INSTALL_DIR/external/\"Firebird-5*linux*x64*.tar.gz 2>/dev/null | head -n 1)\n" +
        "        fi\n" +
        "    elif [ \"$ARCH\" = \"aarch64\" ] || [ \"$ARCH\" = \"arm64\" ]; then\n" +
        "        if [ -f \"$INSTALL_DIR/external/Firebird-5.0.4.1812-0-linux-arm64.tar.gz\" ]; then\n" +
        "            FB_TAR=\"$INSTALL_DIR/external/Firebird-5.0.4.1812-0-linux-arm64.tar.gz\"\n" +
        "        else\n" +
        "            FB_TAR=$(ls \"$INSTALL_DIR/external/\"Firebird-5*linux*arm64*.tar.gz 2>/dev/null | head -n 1)\n" +
        "        fi\n" +
        "    fi\n" +
        "    if [ -n \"$FB_TAR\" ] && [ -f \"$FB_TAR\" ]; then\n" +
        "        TMP_DIR=$(mktemp -d)\n" +
        "        tar -xzf \"$FB_TAR\" -C \"$TMP_DIR\"\n" +
        "        FB_EXTRACTED=$(find \"$TMP_DIR\" -maxdepth 1 -type d -name 'Firebird-*' | head -n 1)\n" +
        "        if [ -z \"$FB_EXTRACTED\" ]; then FB_EXTRACTED=\"$TMP_DIR\"; fi\n" +
        "        cd \"$FB_EXTRACTED\"\n" +
        "        chmod +x install.sh 2>/dev/null || true\n" +
        "        ./install.sh -silent < /dev/null\n" +
        "        if [ ! -f /opt/firebird/bin/isql ] && [ -f buildroot.tar.gz ]; then\n" +
        "            getent group firebird >/dev/null || groupadd -r firebird\n" +
        "            getent passwd firebird >/dev/null || useradd -r -g firebird -d /opt/firebird -s /sbin/nologin firebird\n" +
        "            tar -xzf buildroot.tar.gz -C /\n" +
        "            chown -R firebird:firebird /opt/firebird\n" +
        "            if [ -f /opt/firebird/misc/firebird.service ]; then\n" +
        "                cp -f /opt/firebird/misc/firebird.service /etc/systemd/system/firebird.service\n" +
        "            fi\n" +
        "        fi\n" +
        "        echo \"/opt/firebird/lib\" > /etc/ld.so.conf.d/firebird.conf\n" +
        "        ln -sf /opt/firebird/bin/isql /usr/bin/isql-fb 2>/dev/null || true\n" +
        "        ln -sf /opt/firebird/bin/gbak /usr/bin/gbak 2>/dev/null || true\n" +
        "        ldconfig\n" +
        "        systemctl daemon-reload 2>/dev/null || true\n" +
        "        systemctl enable firebird.service 2>/dev/null || systemctl enable firebird-superserver.service 2>/dev/null || true\n" +
        "        cd /\n" +
        "        rm -rf \"$TMP_DIR\"\n" +
        "    fi\n" +
        "fi\n\n" +
        "# Link libfbclient.so.2 into system library directories\n" +
        "FB_LIB_REAL=$(ls /opt/firebird/lib/libfbclient.so.5* 2>/dev/null | head -n 1)\n" +
        "if [ -n \"$FB_LIB_REAL\" ]; then\n" +
        "    ln -sf \"$FB_LIB_REAL\" /opt/firebird/lib/libfbclient.so.2 2>/dev/null || true\n" +
        "    ln -sf /opt/firebird/lib/libfbclient.so.2 /opt/firebird/lib/libfbclient.so 2>/dev/null || true\n" +
        "    for syslib in /usr/lib/x86_64-linux-gnu /usr/lib/aarch64-linux-gnu /usr/lib; do\n" +
        "        if [ -d \"$syslib\" ]; then\n" +
        "            ln -sf /opt/firebird/lib/libfbclient.so.2 \"$syslib/libfbclient.so.2\" 2>/dev/null || true\n" +
        "            ln -sf /opt/firebird/lib/libfbclient.so.2 \"$syslib/libfbclient.so\" 2>/dev/null || true\n" +
        "        fi\n" +
        "    done\n" +
        "    chmod -R a+rX /opt/firebird/lib 2>/dev/null || true\n" +
        "fi\n\n" +
        "# Permanent fix A: Register INSTALL_DIR (and INSTALL_DIR/lib if present) and Firebird lib in ldconfig\n" +
        "rm -f /etc/ld.so.conf.d/openaa.conf\n" +
        "{\n" +
        "    echo \"$INSTALL_DIR\"\n" +
        "    [ -d \"$INSTALL_DIR/lib\" ] && echo \"$INSTALL_DIR/lib\"\n" +
        "    echo \"/opt/firebird/lib\"\n" +
        "} > /etc/ld.so.conf.d/zz-openaa.conf\n" +
        "ldconfig\n\n" +
        "# Configure Firebird authentication and ensure SYSDBA password is 'masterkey'\n" +
        "if [ -x /opt/firebird/bin/isql ] && [ -f /opt/firebird/security5.fdb ]; then\n" +
        "    echo \"Configuring Firebird SYSDBA / masterkey login...\"\n" +
        "    systemctl stop firebird.service firebird-superserver.service 2>/dev/null || true\n" +
        "    pkill -x fbguard 2>/dev/null || true\n" +
        "    pkill -x firebird 2>/dev/null || true\n" +
        "    sleep 1\n" +
        "    if [ -f /opt/firebird/firebird.conf ]; then\n" +
        "        if grep -q '^AuthServer[[:space:]]*=' /opt/firebird/firebird.conf; then\n" +
        "            sed -i 's/^AuthServer[[:space:]]*=.*/AuthServer = Srp256, Srp, Legacy_Auth/' /opt/firebird/firebird.conf\n" +
        "        else\n" +
        "            printf \"\\nAuthServer = Srp256, Srp, Legacy_Auth\\n\" >> /opt/firebird/firebird.conf\n" +
        "        fi\n" +
        "        if grep -q '^UserManager[[:space:]]*=' /opt/firebird/firebird.conf; then\n" +
        "            sed -i 's/^UserManager[[:space:]]*=.*/UserManager = Srp, Legacy_UserManager/' /opt/firebird/firebird.conf\n" +
        "        else\n" +
        "            printf \"\\nUserManager = Srp, Legacy_UserManager\\n\" >> /opt/firebird/firebird.conf\n" +
        "        fi\n" +
        "    fi\n" +
        "    mkdir -p /tmp/firebird\n" +
        "    chown -R firebird:firebird /opt/firebird /tmp/firebird 2>/dev/null || true\n" +
        "    chmod -R a+rX /opt/firebird/lib 2>/dev/null || true\n" +
        "    if command -v runuser >/dev/null 2>&1 && id firebird >/dev/null 2>&1; then\n" +
        "        runuser -u firebird -- env FIREBIRD=/opt/firebird LD_LIBRARY_PATH=/opt/firebird/lib /opt/firebird/bin/isql -q -user SYSDBA /opt/firebird/security5.fdb <<'EOF_FB_SQL' || true\n" +
        "CREATE USER SYSDBA PASSWORD 'masterkey' USING PLUGIN Srp;\n" +
        "ALTER USER SYSDBA PASSWORD 'masterkey' USING PLUGIN Srp;\n" +
        "COMMIT;\n" +
        "CREATE USER SYSDBA PASSWORD 'masterkey' USING PLUGIN Legacy_UserManager;\n" +
        "ALTER USER SYSDBA PASSWORD 'masterkey' USING PLUGIN Legacy_UserManager;\n" +
        "COMMIT;\n" +
        "QUIT;\n" +
        "EOF_FB_SQL\n" +
        "    elif id firebird >/dev/null 2>&1; then\n" +
        "        su -s /bin/bash firebird -c \"FIREBIRD=/opt/firebird LD_LIBRARY_PATH=/opt/firebird/lib /opt/firebird/bin/isql -q -user SYSDBA /opt/firebird/security5.fdb\" <<'EOF_FB_SQL' || true\n" +
        "CREATE USER SYSDBA PASSWORD 'masterkey' USING PLUGIN Srp;\n" +
        "ALTER USER SYSDBA PASSWORD 'masterkey' USING PLUGIN Srp;\n" +
        "COMMIT;\n" +
        "CREATE USER SYSDBA PASSWORD 'masterkey' USING PLUGIN Legacy_UserManager;\n" +
        "ALTER USER SYSDBA PASSWORD 'masterkey' USING PLUGIN Legacy_UserManager;\n" +
        "COMMIT;\n" +
        "QUIT;\n" +
        "EOF_FB_SQL\n" +
        "    else\n" +
        "        FIREBIRD=/opt/firebird LD_LIBRARY_PATH=/opt/firebird/lib /opt/firebird/bin/isql -q -user SYSDBA /opt/firebird/security5.fdb <<'EOF_FB_SQL' || true\n" +
        "CREATE USER SYSDBA PASSWORD 'masterkey' USING PLUGIN Srp;\n" +
        "ALTER USER SYSDBA PASSWORD 'masterkey' USING PLUGIN Srp;\n" +
        "COMMIT;\n" +
        "CREATE USER SYSDBA PASSWORD 'masterkey' USING PLUGIN Legacy_UserManager;\n" +
        "ALTER USER SYSDBA PASSWORD 'masterkey' USING PLUGIN Legacy_UserManager;\n" +
        "COMMIT;\n" +
        "QUIT;\n" +
        "EOF_FB_SQL\n" +
        "    fi\n" +
        "    if [ -f /opt/firebird/SYSDBA.password ]; then\n" +
        "        printf \"ISC_USER=sysdba\\nISC_PASSWD=masterkey\\n\" > /opt/firebird/SYSDBA.password\n" +
        "        chmod 600 /opt/firebird/SYSDBA.password\n" +
        "    fi\n" +
        "    chown -R firebird:firebird /opt/firebird/security5.fdb /tmp/firebird 2>/dev/null || true\n" +
        "fi\n\n" +
        "# 2-B: Copy OpenAA.FDB and configure permissions for Firebird server\n" +
        "mkdir -p \"$DB_DIR\"\n" +
        "if [ ! -f \"$DB_DIR/OpenAA.FDB\" ] || [ \"$OVERWRITE_DB\" = \"true\" ]; then\n" +
        "    [ -f \"$INSTALL_DIR/OpenAA.FDB\" ] && cp -f \"$INSTALL_DIR/OpenAA.FDB\" \"$DB_DIR/OpenAA.FDB\"\n" +
        "fi\n" +
        "REAL_USER=$(stat -c '%U' \"$HOME_DIR\" 2>/dev/null || echo \"${SUDO_USER:-$(whoami)}\")\n" +
        "if id firebird >/dev/null 2>&1 && [ -n \"$REAL_USER\" ]; then\n" +
        "    usermod -aG \"$REAL_USER\" firebird 2>/dev/null || true\n" +
        "    usermod -aG firebird \"$REAL_USER\" 2>/dev/null || true\n" +
        "fi\n" +
        "chmod a+x \"$HOME_DIR\" 2>/dev/null || true\n" +
        "CUR_PATH=\"$DB_DIR\"\n" +
        "while [ -n \"$CUR_PATH\" ] && [ \"$CUR_PATH\" != \"/\" ] && [ \"$CUR_PATH\" != \".\" ]; do\n" +
        "    chmod a+x \"$CUR_PATH\" 2>/dev/null || true\n" +
        "    CUR_PATH=$(dirname \"$CUR_PATH\")\n" +
        "done\n" +
        "chown -R \"$REAL_USER\":firebird \"$DB_DIR\" 2>/dev/null || chown -R \"$REAL_USER\":\"$REAL_USER\" \"$DB_DIR\" 2>/dev/null || true\n" +
        "chmod -R 777 \"$DB_DIR\" 2>/dev/null || true\n" +
        "[ -f \"$DB_DIR/OpenAA.FDB\" ] && chmod 666 \"$DB_DIR/OpenAA.FDB\" 2>/dev/null || true\n" +
        "systemctl restart firebird.service 2>/dev/null || systemctl restart firebird-superserver.service 2>/dev/null || /opt/firebird/bin/fbguard -daemon -forever 2>/dev/null || true\n\n" +
        "# 2-C: Copy .NEW/.new setting files to SET_DIR, strip .NEW extension, and remove source .NEW files from INSTALL_DIR\n" +
        "mkdir -p \"$SET_DIR\" \"$SET_DIR/.config\"\n" +
        "GLOBAL_DAT_CREATED=false\n" +
        "NEW_COUNT=0\n" +
        "while IFS= read -r -d '' newfile; do\n" +
        "    NEW_COUNT=$((NEW_COUNT + 1))\n" +
        "    filename=$(basename \"$newfile\")\n" +
        "    basename_no_new=\"${filename%.[Nn][Ee][Ww]}\"\n" +
        "    if [ ! \"$newfile\" -ef \"$SET_DIR/$filename\" ]; then\n" +
        "        cp -f \"$newfile\" \"$SET_DIR/$filename\"\n" +
        "    fi\n" +
        "    if [ ! -f \"$SET_DIR/$basename_no_new\" ]; then\n" +
        "        mv -f \"$SET_DIR/$filename\" \"$SET_DIR/$basename_no_new\"\n" +
        "        echo \"Created setting file: $SET_DIR/$basename_no_new\"\n" +
        "        if [ \"${basename_no_new,,}\" = \"global.dat\" ]; then\n" +
        "            GLOBAL_DAT_CREATED=true\n" +
        "        fi\n" +
        "    else\n" +
        "        echo \"Kept existing setting file: $SET_DIR/$basename_no_new\"\n" +
        "        rm -f \"$SET_DIR/$filename\"\n" +
        "    fi\n" +
        "    if [ ! \"$newfile\" -ef \"$SET_DIR/$filename\" ]; then\n" +
        "        rm -f \"$newfile\"\n" +
        "    fi\n" +
        "    chown \"$REAL_USER\":\"$REAL_USER\" \"$SET_DIR/$basename_no_new\" 2>/dev/null || true\n" +
        "    chmod 666 \"$SET_DIR/$basename_no_new\" 2>/dev/null || true\n" +
        "done < <(find \"$INSTALL_DIR\" -maxdepth 1 \\( -type f -o -type l \\) -iname \"*.new\" -print0 2>/dev/null)\n" +
        "echo \"Processed .NEW files count: $NEW_COUNT (GLOBAL_DAT_CREATED=$GLOBAL_DAT_CREATED)\"\n" +
        "chown -R \"$REAL_USER\":\"$REAL_USER\" \"$SET_DIR/.config\" 2>/dev/null || true\n" +
        "if [ ! \"$SET_DIR\" -ef \"$INSTALL_DIR\" ]; then\n" +
        "    chown -R \"$REAL_USER\":\"$REAL_USER\" \"$SET_DIR\" 2>/dev/null || true\n" +
        "    chmod -R 777 \"$SET_DIR\" 2>/dev/null || true\n" +
        "fi\n" +
        "# Pass state to finalize.sh via user-owned file in SET_DIR\n" +
        "STATE_FILE=\"$SET_DIR/.openaa_post_state.env\"\n" +
        "printf \"GLOBAL_DAT_CREATED=%s\\n\" \"$GLOBAL_DAT_CREATED\" > \"$STATE_FILE\"\n" +
        "chown \"$REAL_USER\":\"$REAL_USER\" \"$STATE_FILE\" 2>/dev/null || true\n" +
        "chmod 666 \"$STATE_FILE\" 2>/dev/null || true\n" +
        "echo \"root_setup completed.\"\n";

        var rootShB64 = toUtf8Base64(rootSh);
        var runRootCmd =
            "TMP_SH=$(mktemp /tmp/openaa_root_setup.XXXXXX.sh) && " +
            "printf '%s' '" + rootShB64 + "' | base64 -d > \"$TMP_SH\" && " +
            "/bin/bash \"$TMP_SH\" \"$1\" \"$2\" \"$3\" \"$4\" \"$5\" \"$6\" \"$7\"; " +
            "RC=$?; rm -f \"$TMP_SH\"; exit $RC";

        component.addElevatedOperation(
            "Execute", "/bin/bash", "-c", runRootCmd,
            "root_setup", updateFb, installFb5, targetDir, dbDir, setDir, homeDir, overwriteDB
        );
    }
}

Component.prototype.onInstallationFinished = function() {
    if (!installer.isInstaller()) return;

    var targetDir = normalizePath(installer.value("TargetDir"));
    var homeDir = normalizePath(installer.value("HomeDir"));
    var sep = isWindows() ? "\\" : "/";

    var dbDir = installer.value("OpenAA_DbDir", isWindows() ? "C:\\Data" : (homeDir + "/Data"));
    var overwriteDB = installer.value("OpenAA_OverwriteDB", "false");
    var pageDP = gui.pageByObjectName("DynamicDataPathPage");
    if (pageDP) {
        var dpEdit = pageDP.findChild("dataPathLineEdit");
        var ovCheck = pageDP.findChild("overwriteCheckBox");
        if (dpEdit && dpEdit.text !== "") dbDir = normalizePath(dpEdit.text);
        if (ovCheck) overwriteDB = ovCheck.checked ? "true" : "false";
    }

    var defaultSetDir = homeDir + sep + "OpenAA";
    var setDir = installer.value("OpenAA_SetDir", defaultSetDir);
    var pageWD = gui.pageByObjectName("DynamicWorkingDirPage");
    if (pageWD) {
        var wdEdit = pageWD.findChild("workingDirLineEdit");
        if (wdEdit && wdEdit.text !== "") setDir = normalizePath(wdEdit.text);
    }

    var updateFb = installer.value("OpenAA_UpdateFB", "false");
    var installFb5 = installer.value("OpenAA_InstallFB5", "false");

    if (isWindows()) {
        var psScript = buildWindowsFinalizeScript(targetDir, dbDir, setDir, overwriteDB, homeDir, updateFb, installFb5);
        var psEncoded = toUtf16LeBase64(psScript);
        installer.execute("powershell.exe", ["-NoProfile", "-ExecutionPolicy", "Bypass", "-EncodedCommand", psEncoded]);
    } else {
        var shScript = buildLinuxFinalizeScript();
        var shEncoded = toUtf8Base64(shScript);
        var runFinalizeCmd =
            "TMP_SH=$(mktemp /tmp/openaa_finalize.XXXXXX.sh) && " +
            "printf '%s' '" + shEncoded + "' | base64 -d > \"$TMP_SH\" && " +
            "/bin/bash \"$TMP_SH\" \"$1\" \"$2\" \"$3\" \"$4\" \"$5\" \"$6\" \"$7\"; " +
            "RC=$?; rm -f \"$TMP_SH\"; exit $RC";
        installer.execute("/bin/bash", ["-c", runFinalizeCmd, "openaa_finalize", targetDir, dbDir, setDir, overwriteDB, homeDir, updateFb, installFb5]);
    }
}