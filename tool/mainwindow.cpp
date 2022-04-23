#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <thread>
#include <QMessageBox>
#include <QSettings>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), mDumpType(DUMPTYPE::KERNEL), mStop(false),
      mRunning(false)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{
    if (mRunning) {
        QMessageBox::information(this, "Tips", "You are running now!");
        return;
    }
    mRunning = true;
    mStop = false;

    //https://docs.microsoft.com/en-us/troubleshoot/windows-server/performance/memory-dump-file-options
    if (ui->radioButton_Auto->isChecked()) {
        mDumpType = DUMPTYPE::AUTO;
    } else if (ui->radioButton_Complete->isChecked()) {
        mDumpType = DUMPTYPE::COMPLETE;
    } else if (ui->radioButton_Kernel->isChecked()) {
        mDumpType = DUMPTYPE::KERNEL;
    } else if (ui->radioButton_Small->isChecked()) {
        mDumpType = DUMPTYPE::SMALL;
    }

    std::thread t1([&] {
        while (!mStop) {
            //HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\CrashControl
            QSettings qRegQ("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\CrashControl",
                            QSettings::NativeFormat);
            qRegQ.setValue("AlwaysKeepMemoryDump", (int) 0);
            qRegQ.setValue("CrashDumpEnabled", (int) mDumpType);
            //20ms
            QThread::msleep(20);
        }
        mRunning = false;
    });
    t1.detach();

    QMessageBox::information(this, "Tips", "Start new running!");
}

void MainWindow::on_pushButton_stop_clicked()
{
    mStop = true;
    QMessageBox::information(this, "Tips", "Stop running!");
}
