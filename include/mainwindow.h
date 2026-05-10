#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QLineEdit>
#include <windows.h>
#include <QDrag>
#include <QApplication>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QElapsedTimer>
#include <QDebug>

#include <QUrl>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
public:
    QString downld= "nil";
    QString upld = "nil";
    void waitMs(int ms);
    QString getLocalIP();
    void updtsysusage();
    void updateGPUUsage();
    QString getGPUName();
    void on_lblTitle_linkActivated(const QString &link);
    int getLatency();
    void setupProcessListStyle();
    void updateSystemData();
    void checkPingResult();
    void updateProcessList();
    QString getMACAdr();
    QString getCPUName();
    void updateNetworkSpeed();
    void doPing();
    void NetworkSpeedTester(QObject *parent = nullptr);
    void startDownload(const QUrl &url);
    void startUpload(const QUrl &url, QIODevice *data);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void onFinished();

    void on_actionExit_triggered();
    void on_actionAbout_triggered();

    void on_btnRefresh_clicked();

    void on_btnNetworkTest_clicked();

private:
    QPoint dragStartPosition;
    QLabel *lblTitle;
    QLabel *lblStatus;
    QTimer *updateTimer;
    QTimer *pingTimer;
    int lastLatency;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QElapsedTimer timer;
    qint64 lastBytes;
    Ui::MainWindow *ui;

};
#endif
