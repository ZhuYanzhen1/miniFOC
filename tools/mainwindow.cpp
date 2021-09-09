#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    serial = new QSerialPort();
    ui->setupUi(this);
    refresh_serial_port();
    ui->serial_baudrate_txt->setText("115200");
}

MainWindow::~MainWindow(){
    if (serial->isOpen())
        serial->close();
    delete serial;
    delete ui;
}

bool MainWindow::set_serial_badurate(){
    if(ui->serial_port_cb->currentText() == NULL || ui->serial_baudrate_txt->toPlainText() == NULL){
        QMessageBox::information(NULL, "Error", "Please select port number and baudrate first!");
        return false;
    } else{
        serial->setPortName(ui->serial_port_cb->currentText());
        serial->setBaudRate(ui->serial_baudrate_txt->toPlainText().toInt());
        serial->setDataBits(QSerialPort::Data8);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        return true;
    }
}

void MainWindow::refresh_serial_port(){
    QList<QSerialPortInfo> serialPortinfo = QSerialPortInfo::availablePorts();
    int count = serialPortinfo.count();
    ui->serial_port_cb->clear();
    for(int i = 0; i < count; i++)
        ui->serial_port_cb->addItem(serialPortinfo.at(i).portName());
}

void MainWindow::mdtp_callback_handler(unsigned char pid, const unsigned char *data){
    qDebug() << "pack:" << pid << "  data:" << data[0] << data[1] << data[2] << data[3]
                 << data[4] << data[5] << data[6] << data[7];
}

void MainWindow::serial_received(){
    QByteArray info = serial->readAll();
    char *buffer = info.data();
    for (int counter = 0; counter < info.length(); counter++)
        mdtp_receive_handler(buffer[counter]);
}

void MainWindow::on_open_btn_clicked(){
    if(serial->isOpen() == false){
        if(set_serial_badurate() == true){
            serial->open(QSerialPort::ReadWrite);
            ui->open_btn->setText("Close");
            ui->serial_port_cb->setEnabled(false);
            ui->serial_baudrate_txt->setEnabled(false);
            connect(serial,SIGNAL(readyRead()),this,SLOT(serial_received()));
        }
    }
    else{
        serial->close();
        ui->open_btn->setText("Open");
        ui->serial_port_cb->setEnabled(true);
        ui->serial_baudrate_txt->setEnabled(true);
    }
}

void MainWindow::on_refresh_btn_clicked(){
    refresh_serial_port();
}
