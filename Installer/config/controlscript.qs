function Controller() {
    if (installer.isInstaller()) {
        installer.setValue("RemoveTargetDir", "false");
        installer.setMessageBoxAutomaticAnswer("OverwriteTargetDirectory", QMessageBox.Yes);
        installer.setMessageBoxAutomaticAnswer("stopProcessesForUpdates", QMessageBox.Ignore);
    }
}

function isWindows() {
    return (systemInfo.productType === "windows" || systemInfo.kernelType === "winnt");
}

// 既存インストール管理ファイル（components.xml等）をクリアして再インストール可能にする関数
function clearExistingInstallationMetadata(dirPath) {
    if (!installer.isInstaller() || !dirPath || dirPath === "") {
        return;
    }
    var sep = isWindows() ? "\\" : "/";
    var targetDir = isWindows()
        ? dirPath.replace(/\//g, "\\").replace(/\\+$/, "")
        : dirPath.replace(/\\/g, "/").replace(/\/+$/, "");
    var compXml = targetDir + sep + "components.xml";

    if (installer.fileExists(compXml)) {
        var metaFiles = [
            "components.xml",
            "maintenancetool.exe",
            "maintenancetool",
            "maintenancetool.dat",
            "maintenancetool.ini",
            "InstallationLog.txt",
            "network.xml",
            "finalize.ps1",
            "finalize.sh"
        ];
        for (var i = 0; i < metaFiles.length; i++) {
            var filePath = targetDir + sep + metaFiles[i];
            if (installer.fileExists(filePath)) {
                if (isWindows()) {
                    installer.execute("cmd.exe", ["/c", "del", "/f", "/q", filePath]);
                } else {
                    installer.execute("rm", ["-f", filePath]);
                }
            }
        }
    }
}

Controller.prototype.IntroductionPageCallback = function() {
    if (installer.isInstaller()) {
        installer.setValue("RemoveTargetDir", "false");
        clearExistingInstallationMetadata(installer.value("TargetDir"));
    }
    var widget = gui.pageWidgetByObjectName("ComponentSelectionPage");
    if (widget) {
        gui.rejectWithoutClick(buttons.NextButton);
    }
}

Controller.prototype.TargetDirectoryPageCallback = function() {
    if (!installer.isInstaller()) {
        return;
    }
    installer.setValue("RemoveTargetDir", "false");

    var page = gui.pageWidgetByObjectName("TargetDirectoryPage");
    if (page && page.TargetDirectoryLineEdit) {
        clearExistingInstallationMetadata(page.TargetDirectoryLineEdit.text);
        try {
            page.TargetDirectoryLineEdit.textChanged.disconnect(clearExistingInstallationMetadata);
        } catch (e) {}
        page.TargetDirectoryLineEdit.textChanged.connect(clearExistingInstallationMetadata);
    } else {
        clearExistingInstallationMetadata(installer.value("TargetDir"));
    }
}

Controller.prototype.ComponentSelectionPageCallback = function() {
    gui.clickButton(buttons.NextButton);
}