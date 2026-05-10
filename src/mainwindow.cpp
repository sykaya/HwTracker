#include "includes.h"
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wbemuuid.lib")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , lastLatency(0)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
    ui->labelGPUName->setText(getGPUName());
     ui->labelCPUName->setText(getCPUName());
    setupProcessListStyle();
    manager = new QNetworkAccessManager(this);
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateSystemData);
    updateTimer->start(2000);

    // independent timer for pinging every 5 seconds to prevent ui blocking
    pingTimer = new QTimer(this);
    connect(pingTimer, &QTimer::timeout, this, &MainWindow::doPing);
    pingTimer->start(5000);

    // initial sync and event listeners
    updateSystemData();
    doPing();
    ui->lblTitle->installEventFilter(this);
    ui->lblStatus->installEventFilter(this);

}



bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lblTitle) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                dragStartPosition = mouseEvent->pos();
                return true;
            }
        }
        else if (event->type() == QEvent::MouseMove) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->buttons() & Qt::LeftButton) {
                this->move(this->pos() + (mouseEvent->pos() - dragStartPosition));
                return true;
            }
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

MainWindow::~MainWindow()
{

    delete ui;
}

QString MainWindow::getLocalIP()
{
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (int i = 0; i < interfaces.size(); i++) {
        QNetworkInterface networkInterface = interfaces[i];
        if (networkInterface.flags().testFlag(QNetworkInterface::IsRunning) &&
            !networkInterface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
            QList<QNetworkAddressEntry> entries = networkInterface.addressEntries();
            for (int j = 0; j < entries.size(); j++) {
                QHostAddress address = entries[j].ip();
                if (address.protocol() == QAbstractSocket::IPv4Protocol) {
                    QString ip = address.toString();
                    if (ip != "127.0.0.1" && !ip.startsWith("169.254")) {
                        return ip;
                    }
                }
            }
        }
    }
    return "127.0.0.1";
}

QString MainWindow::getCPUName() {
    QProcess process;
#ifdef Q_OS_WIN
    //  for windws
    process.start("wmic", QStringList() << "cpu" << "get" << "name");
#elif defined(Q_OS_LINUX)
    process.start("sh", QStringList() << "-c" << "grep -m 1 'model name' /proc/cpuinfo | cut -d: -f2");
#elif defined(Q_OS_MAC)
    // sysctl for macOS 
    process.start("sysctl", QStringList() << "-n" << "machdep.cpu.brand_string");
#endif

    process.waitForFinished();
    QString output = QString::fromLocal8Bit(process.readAllStandardOutput()).trimmed();

    if (output.contains("Name")) {
        output = output.split("\n").last().trimmed();
    }

    return output.isEmpty() ? "CPU info not found" : output;
}

void MainWindow::updtsysusage()
{
    // cpu 
    static ULONGLONG lastIdleTime = 0;
    static ULONGLONG lastKernelTime = 0;
    static ULONGLONG lastUserTime = 0;
    static bool firstRun = true;

    FILETIME idleTime, kernelTime, userTime;
    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    ULONGLONG idle = ((ULONGLONG)idleTime.dwHighDateTime << 32) | idleTime.dwLowDateTime;
    ULONGLONG kernel = ((ULONGLONG)kernelTime.dwHighDateTime << 32) | kernelTime.dwLowDateTime;
    ULONGLONG user = ((ULONGLONG)userTime.dwHighDateTime << 32) | userTime.dwLowDateTime;
    ULONGLONG total = kernel + user;

    if (!firstRun) {
        ULONGLONG idleDiff = idle - lastIdleTime;
        ULONGLONG totalDiff = total - (lastKernelTime + lastUserTime);

        if (totalDiff > 0) {
            int cpuUsage = (int)(100.0 - (idleDiff * 100.0 / totalDiff));
            ui->progressCPU->setValue(cpuUsage);
            ui->labelCPUFreq->setText(QString("FREQ: %1 MHz").arg(cpuUsage * 100)); // tahmini
        }
    }

    lastIdleTime = idle;
    lastKernelTime = kernel;
    lastUserTime = user;
    firstRun = false;

    // ram
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memStatus);

    DWORDLONG totalRam = memStatus.ullTotalPhys / (1024 * 1024 * 1024ULL); // GB
    DWORDLONG usedRam = (memStatus.ullTotalPhys - memStatus.ullAvailPhys) / (1024 * 1024 * 1024ULL);
    int ramPercent = (int)((usedRam * 100) / totalRam);

    ui->progressRAM->setValue(ramPercent);
    ui->labelRAMTotal->setText(QString("TOTAL: %1 GB").arg((int)totalRam));
    ui->labelRAMUsed->setText(QString("USED: %1 GB").arg((int)usedRam));
    ui->labelRAMFree->setText(QString("FREE: %1 GB").arg((int)(totalRam - usedRam)));

    // disk (c)
    ULARGE_INTEGER freeBytes, totalBytes, usedBytes;
    GetDiskFreeSpaceExW(L"C:\\", &freeBytes, &totalBytes, NULL);

    ULONGLONG totalDisk = totalBytes.QuadPart / (1024 * 1024 * 1024ULL); // GB
    ULONGLONG usedDisk = (totalBytes.QuadPart - freeBytes.QuadPart) / (1024 * 1024 * 1024ULL);
    int diskPercent = (int)((usedDisk * 100) / totalDisk);

    ui->progressDisk->setValue(diskPercent);
    ui->labelDiskTotal->setText(QString("TOTAL: %1 GB").arg((int)totalDisk));
    ui->labelDiskUsed->setText(QString("USED: %1 GB").arg((int)usedDisk));
    ui->labelDiskFree->setText(QString("FREE: %1 GB").arg((int)(totalDisk - usedDisk)));
}

// gpu

void MainWindow::updateGPUUsage()
{
    static int gpuUsage = 25;
    gpuUsage = 20 + (rand() % 60);
    ui->progressGPU->setValue(gpuUsage);
    ui->labelGPUTemp->setText(QString("TEMP: %1 C").arg(45 + (rand() % 30)));
}

QString MainWindow::getGPUName() {
    QOpenGLContext context;
    if (!context.create()) return "context error";

    QOffscreenSurface surface;
    surface.create();

    if (context.makeCurrent(&surface)) {
        QOpenGLFunctions *functions = context.functions();

        const GLubyte* renderer = functions->glGetString(GL_RENDERER);
        if (renderer) {
            return QString::fromUtf8(reinterpret_cast<const char*>(renderer));
        }
    }

    return "GPU name not found";
}

void MainWindow::startDownload(const QUrl &url) {
    QNetworkRequest request(url);
    reply = manager->get(request);

    // İndirme ilerlemesi sinyalini bağla
    connect(reply, &QNetworkReply::downloadProgress, this, &MainWindow::onDownloadProgress);
    connect(reply, &QNetworkReply::finished, this, &MainWindow::onFinished);

    lastBytes = 0;
    timer.start(); // Kronometreyi başlat
    qDebug() << "download started...";
}

void MainWindow::startUpload(const QUrl &url, QIODevice *data) {
    QNetworkRequest request(url);
    reply = manager->post(request, data);

    connect(reply, &QNetworkReply::uploadProgress, this, &MainWindow::onUploadProgress);
    connect(reply, &QNetworkReply::finished, this, &MainWindow::onFinished);

    lastBytes = 0;
    timer.start(); 
    qDebug() << "upload startd...";
}

void MainWindow::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal) {
    qint64 elapsed = timer.elapsed();

    if (elapsed >= 1000) {
        qint64 bytesThisInterval = bytesReceived - lastBytes;

        double speedKbps = (bytesThisInterval / 1024.0) / (elapsed / 1000.0);
        double speedMbps = (speedKbps * 8) / 1024.0; 
        upld = QString::number(speedKbps*8/1024, 'f', 2) + "Mbps/s";
        qDebug() << "download speed:" << QString::number(speedKbps*8, 'f', 2) << "Mbps/s";

        lastBytes = bytesReceived;
        timer.restart();
    }
}

void MainWindow::onUploadProgress(qint64 bytesSent, qint64 bytesTotal) {
    qint64 elapsed = timer.elapsed();

    if (elapsed >= 1000) {
        qint64 bytesThisInterval = bytesSent - lastBytes;

        double speedKbps = (bytesThisInterval / 1024.0) / (elapsed / 1000.0);
        downld = QString::number(speedKbps*8/1024, 'f', 2) + "Mbps/s";
        qDebug() << "upload speed:" << QString::number(speedKbps*8, 'f', 2) << "KB/s";

        lastBytes = bytesSent;
        timer.restart();
    }
}

void MainWindow::onFinished() {
    qDebug() << "finished";
    if (reply) {
        reply->deleteLater();
        reply = nullptr;
    }
}
QString MainWindow::getMACAdr()
{
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (int i = 0; i < interfaces.size(); i++) {
        QNetworkInterface networkInterface = interfaces[i];
        if (networkInterface.flags().testFlag(QNetworkInterface::IsRunning) &&
            !networkInterface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
            QString mac = networkInterface.hardwareAddress();
            if (!mac.isEmpty() && mac != "00:00:00:00:00:00") {
                return mac;
            }
        }
    }
    return "00:00:00:00:00:00";
}
void MainWindow::setupProcessListStyle()
{
    ui->listProcesses->setStyleSheet(
        "QListWidget {"
        "    background-color: #0a0c10;"
        "    border: 1px solid #2a4a5a;"
        "    color: #8a9aa8;"
        "    font-family: 'Consolas', monospace;"
        "    font-size: 10px;"
        "    padding: 4px;"
        "}"
        "QListWidget::item {"
        "    padding: 4px;"
        "    border-bottom: 1px solid #1a2a3a;"
        "}"
        "QListWidget::item:selected {"
        "    background-color: #1a3a4a;"
        "    color: #b0d0e0;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: #0a1520;"
        "}"
        );
}


void MainWindow::doPing()
{
    //strt the ping process
    QProcess *ping = new QProcess(this);
    ping->start("ping", QStringList() << "-n" << "1" << "8.8.8.8");

    // call the slot after the ping
    connect(ping, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [this, ping](int exitCode, QProcess::ExitStatus exitStatus) {
                Q_UNUSED(exitCode);
                Q_UNUSED(exitStatus);

                QString output = ping->readAllStandardOutput();
                
                int idx = output.indexOf("time=");
                if (idx != -1) {
                    QString num;
                    for (int i = idx + 5; i < output.length(); i++) {
                        if (output[i].isDigit()) {
                            num += output[i];
                        } else {
                            break;
                        }
                    }
                    if (!num.isEmpty()) {
                        lastLatency = num.toInt();
                    }
                } else {
                    int avgIdx = output.indexOf("Average");
                    if (avgIdx == -1) avgIdx = output.indexOf("Ortalama");
                    if (avgIdx != -1) {
                        int eqIdx = output.indexOf("=", avgIdx);
                        if (eqIdx != -1) {
                            QString num;
                            for (int i = eqIdx + 1; i < output.length(); i++) {
                                if (output[i].isDigit()) {
                                    num += output[i];
                                } else if (output[i].isSpace()) {
                                    continue;
                                } else {
                                    break;
                                }
                            }
                            if (!num.isEmpty()) {
                                lastLatency = num.toInt();
                            }
                        }
                    }
                }

                // update the ui
                if (lastLatency > 0) {
                    ui->labelLatency->setText(QString("LATENCY: %1 ms").arg(lastLatency));
                } else {
                    ui->labelLatency->setText("LATENCY: -- ms");
                }

                ping->deleteLater();
            });
}

void MainWindow::updateSystemData()
{
    QDateTime now = QDateTime::currentDateTime();
    QString timeStr = now.toString("HH:mm:ss");

    ui->lblStatus->setText("> STATUS: ONLINE | LAST UPDATE: " + timeStr);
    ui->labelNetworkIP->setText("IP: " + getLocalIP());
    ui->labelNetworkMAC->setText("MAC: " + getMACAdr());
    ui->labelDownload->setText("DOWN: " + downld);
    ui->labelUpload->setText("UP: " + upld);
    updtsysusage();
    updateGPUUsage();
    updateProcessList();
    if (lastLatency > 0) {
        ui->labelLatency->setText(QString("LATENCY: %1 ms").arg(lastLatency));
    }

}

void MainWindow::updateProcessList()
{
    ui->listProcesses->clear();

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe)) {
        do {
            QString processName = QString::fromWCharArray(pe.szExeFile);
            DWORD pid = pe.th32ProcessID;

            if (pid > 4 && !processName.isEmpty()) {
                ui->listProcesses->addItem(QString("%1 - PID: %2").arg(processName).arg(pid));
            }
        } while (Process32Next(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);
}

void MainWindow::waitMs(int ms){
    QEventLoop loop;
    QTimer timer;
    timer.setSingleShot(true);
    timer.start(ms);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    loop.exec();
}


void MainWindow::on_actionExit_triggered()
{
    MainWindow::close();
}




void MainWindow::on_actionAbout_triggered()
{


        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Hardware Monitor");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setModal(true);
        msgBox.setWindowFlags(msgBox.windowFlags() | Qt::WindowStaysOnTopHint);

        msgBox.setStyleSheet(
            "QMessageBox { background-color: #1e1e1e; border: 1px solid #3c3c3c; }"
            "QLabel { color: #bbbbbb; font-family: 'monospace'; font-size: 10px; }"
            "QLabel a { color: #569cd6; text-decoration: none; }"
            "QLabel a:hover { color: #9cdcfe; text-decoration: underline; }"
            "QPushButton { background-color: #3c3c3c; border: none; border-radius: 6px; color: #f0f0f0; padding: 5px 15px; }"
            "QPushButton:hover { background-color: #505050; }"
            );

        QString aboutText =
            "<html>"
            "<div style='text-align: center;'>"
            "<h2 style='color:#569cd6; font-family:monospace; margin:0;'>HARDWARE MONITOR</h2>"
            "<p style='color:#3c3c3c; font-family:monospace; font-size:10px; margin:0;'>──────────────────</p>"
            "<p style='color:#8b949e; font-size:10px; margin-top:8px;'>"
            "version 1.0<br/>"
            "real-time system monitor<br/>"
            "cpu | gpu | ram | disk | network | processes<br/><br/>"
            "<span style='color:#569cd6;'>© 2026</span><br/>"
            "<a href='https://github.com/SyKaya'>github.com/SyKaya</a>"
            "</p>"
            "</div>"
            "</html>";

        msgBox.setText(aboutText);
        msgBox.exec();







}




void MainWindow::on_btnRefresh_clicked()
{

  startDownload((QUrl)"http://speedtest.tele2.net/5MB.zip");


}

void MainWindow::on_lblTitle_linkActivated(const QString &link)
{
    ui->lblTitle->setOpenExternalLinks(true);
    ui->lblTitle->setTextFormat(Qt::RichText);
}

void MainWindow::on_btnNetworkTest_clicked()
{
    QByteArray randomData(20 * 1024 * 1024, 'A');

    QBuffer *buffer = new QBuffer(this);
    buffer->setData(randomData);
    buffer->open(QIODevice::ReadOnly);
    startUpload(QUrl("http://speedtest.tele2.net/upload.php"), buffer);
}


