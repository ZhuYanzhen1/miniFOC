#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

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
    void on_refresh_btn_clicked();

    void on_open_btn_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort serial;
    void refresh_serial_port();
    bool set_serial_badurate();
};
#endif // MAINWINDOW_H
