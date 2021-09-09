#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refresh_serial_port();
    ui->serial_baudrate_txt->setText("115200");
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::set_serial_badurate(){
    if(ui->serial_port_cb->currentText() == NULL || ui->serial_baudrate_txt->toPlainText() == NULL)
    {
        QMessageBox::information(NULL, "Error", "Please select port number and baudrate first!");
        return false;
    }
    else
    {
        serial.setPortName(ui->serial_port_cb->currentText());
        serial.setBaudRate(ui->serial_baudrate_txt->toPlainText().toInt());
        return true;
    }
}

void MainWindow::refresh_serial_port()
{
    QList<QSerialPortInfo> serialPortinfo = QSerialPortInfo::availablePorts();
    int count = serialPortinfo.count();
    ui->serial_port_cb->clear();
    for(int i = 0; i < count; i++)
        ui->serial_port_cb->addItem(serialPortinfo.at(i).portName());
}

void MainWindow::on_open_btn_clicked()
{
    if(serial.isOpen() == false){
        if(set_serial_badurate() == true)
            serial.open(QSerialPort::ReadWrite);
        ui->open_btn->setText("Close");
    }
    else{
        serial.close();
        ui->open_btn->setText("Open");
    }
}

void MainWindow::on_refresh_btn_clicked()
{
    refresh_serial_port();
}
