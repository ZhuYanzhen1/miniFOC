#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    serial = new QSerialPort();
    ui->setupUi(this);
    refresh_serial_port();
    setup_custom_plot();
    slider_timer = new QTimer(this);
    slider_timer->setInterval(50);
    connect(slider_timer,SIGNAL(timeout()),this,SLOT(slider_timer_timeout()));
    ui->slider_minimum_value->setText("-1.0");
    ui->slider_maximum_value->setText("1.0");
    ui->serial_baudrate_txt->setText("115200");
    ui->mode_set_cb->addItem("Torque Control");
    ui->mode_set_cb->addItem("Speed Control");
    ui->mode_set_cb->addItem("Angle Control");
    ui->mode_set_cb->setEditText("Torque Control");
}

MainWindow::~MainWindow(){
    if (serial->isOpen())
        serial->close();
    delete slider_timer;
    delete serial;
    delete ui;
}

void MainWindow::mdtp_callback_handler(unsigned char pid, const unsigned char *data){
    if(pid == 0){
        uint32_t velocity = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
        uint32_t angle = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
        curve_x.resize(curve_counter + 1);
        curve_angle.resize(curve_counter + 1);
        curve_velocity.resize(curve_counter + 1);
        curve_x[curve_counter] = (curve_counter + 1) * 0.05f;
        curve_angle[curve_counter] = (*((float *)(&angle)));
        curve_velocity[curve_counter] = (*((float *)(&velocity)));
        ui->custom_plot->graph(0)->setData(curve_x, curve_velocity);
        ui->custom_plot->graph(1)->setData(curve_x, curve_angle);
        ui->custom_plot->rescaleAxes();
        ui->custom_plot->replot();
        curve_counter = curve_counter + 1;
    }
}

void MainWindow::on_user_expect_slider_valueChanged(int value){
    float maximum = ui->slider_maximum_value->toPlainText().toFloat();
    float minimum = ui->slider_minimum_value->toPlainText().toFloat();
    slider_change_flag = true;
    slider_value = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->slider_current_value->setText(QString::number(slider_value));
}

void MainWindow::on_open_btn_clicked(){
    if(serial->isOpen() == false){
        if(set_serial_badurate() == true){
            serial->open(QSerialPort::ReadWrite);
            ui->open_btn->setText("Close");
            ui->serial_port_cb->setEnabled(false);
            ui->serial_baudrate_txt->setEnabled(false);
            ui->calibrate_btn->setEnabled(true);
            ui->start_stop_btn->setEnabled(true);
            ui->mode_set_cb->setEnabled(true);
            ui->user_expect_slider->setEnabled(true);
            ui->slider_maximum_value->setEnabled(true);
            ui->slider_minimum_value->setEnabled(true);
            slider_timer->start();
            connect(serial,SIGNAL(readyRead()),this,SLOT(serial_received()));
        }
    }else {
        serial->close();
        ui->open_btn->setText("Open");
        ui->mode_set_cb->setEnabled(false);
        ui->calibrate_btn->setEnabled(false);
        ui->start_stop_btn->setEnabled(false);
        ui->user_expect_slider->setEnabled(false);
        ui->slider_maximum_value->setEnabled(false);
        ui->slider_minimum_value->setEnabled(false);
        ui->serial_port_cb->setEnabled(true);
        ui->serial_baudrate_txt->setEnabled(true);
        slider_timer->stop();
    }
}

void MainWindow::on_start_stop_btn_clicked(){
    unsigned char buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    if(ui->start_stop_btn->text() == "Start") {
        ui->start_stop_btn->setText("Stop");
        buffer[0] = 0x1E;
        if (ui->mode_set_cb->currentText() == "Torque Control")
                buffer[1] = 0x01;
        if (ui->mode_set_cb->currentText() == "Speed Control")
                buffer[1] = 0x02;
        if (ui->mode_set_cb->currentText() == "Angle Control")
                buffer[1] = 0x03;
        mdtp_data_transmit(0x00, buffer);
        ui->mode_set_cb->setEnabled(false);
    }else {
        buffer[0] = 0x2D;
        mdtp_data_transmit(0x00, buffer);
        ui->start_stop_btn->setText("Start");
        ui->mode_set_cb->setEnabled(true);
    }
}

void MainWindow::on_calibrate_btn_clicked(){
    unsigned char buffer[8] = {0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    mdtp_data_transmit(0x00, buffer);
    ui->calibrate_btn->setEnabled(false);
}

void MainWindow::on_refresh_btn_clicked(){
    refresh_serial_port();
}

/* some functions related to timer interrupt */

void MainWindow::slider_timer_timeout(){
    if(slider_change_flag == true){
        unsigned char buffer[8] = {0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        unsigned int uintp32 = (*((unsigned int *) (&slider_value)));
        buffer[4] = (unsigned char) ((uintp32 >> 24UL) & 0x000000ffUL);
        buffer[5] = (unsigned char) ((uintp32 >> 16UL) & 0x000000ffUL);
        buffer[6] = (unsigned char) ((uintp32 >> 8UL) & 0x000000ffUL);
        buffer[7] = (unsigned char) (uintp32 & 0x000000ffUL);
        mdtp_data_transmit(0x00, buffer);
        slider_change_flag = false;
    }
}

/* some functions related to plot initialize and refresh */

void MainWindow::setup_custom_plot(){
    QPen pen;
    pen.setColor(Qt::blue);
    ui->custom_plot->legend->setVisible(true);
    ui->custom_plot->addGraph();
    ui->custom_plot->graph(0)->setPen(pen);
    ui->custom_plot->graph(0)->setName("Speed");

    pen.setColor(Qt::red);
    ui->custom_plot->addGraph();
    ui->custom_plot->graph(1)->setPen(pen);
    ui->custom_plot->graph(1)->setName("Angle");

    ui->custom_plot->xAxis->setLabel("t(s)");
    ui->custom_plot->yAxis->setLabel("y(rad/s rad)");

    ui->custom_plot->xAxis->setRange(0,1);
    ui->custom_plot->yAxis->setRange(0,1);

    connect(ui->custom_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->custom_plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->custom_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->custom_plot->yAxis2, SLOT(setRange(QCPRange)));

    ui->custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

/* some functions related to serial port control */

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

void MainWindow::serial_received(){
    QByteArray info = serial->readAll();
    char *buffer = info.data();
    for (int counter = 0; counter < info.length(); counter++)
        mdtp_receive_handler(buffer[counter]);
}
