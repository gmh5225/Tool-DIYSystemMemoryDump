#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

public:
    enum DUMPTYPE { AUTO = 7, KERNEL = 2, SMALL = 3, COMPLETE = 1 };

public:
    DUMPTYPE mDumpType;
    bool mStop;
    bool mRunning;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
