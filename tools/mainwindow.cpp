#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    serial = new QSerialPort();
    ui->setupUi(this);
    refresh_serial_port();
    setup_custom_plot();

    slider_timer = new QTimer(this);
    slider_timer->setInterval(100);
    connect(slider_timer,SIGNAL(timeout()),this,SLOT(slider_timer_timeout()));

    ui->mode_set_cb->addItem("Torque Control");
    ui->mode_set_cb->addItem("Speed Control");
    ui->mode_set_cb->addItem("Angle Control");

    for (int counter = 0; counter < 4; counter++) {
        torque_slider_change_flag[counter] = false;
        speed_slider_change_flag[counter] = false;
        angle_slider_change_flag[counter] = false;
    }

    ui->custom_plot->setEnabled(false);
    ui->torque_groupbox->setEnabled(false);
    ui->speed_groupbox->setEnabled(false);
    ui->angle_groupbox->setEnabled(false);
    ui->pid_parameter_btn->setEnabled(false);
}

MainWindow::~MainWindow(){
    if (serial->isOpen())
        serial->close();
    delete slider_timer;
    delete serial;
    delete ui;
}

void MainWindow::update_minimum_maximum_value(float value, QLabel *value_widget, QSlider *value_slider,
                                  QTextEdit *maximum_tb, QTextEdit *minimum_tb) {
    int32_t pow_counter = 0, maximum = 0, minimum = 0, error_value = 0, value_step = 0;
    if(value < 1.0 && value > -1.0f) {
        minimum = 0;
        maximum = value * 2;
        value_widget->setText(QString::number(value, 10, 2));
        maximum_tb->setText(QString::number((float)maximum, 10, 2));
        minimum_tb->setText(QString::number((float)minimum, 10, 2));
    } else if(value < 1000.0f && value > -1000.0f) {
        if(value != 0) {
            if(value < 0) {
                value = -1.0 * value;
                for(pow_counter = 1; pow_counter <= 5; pow_counter++)
                    if(value > std::pow(10, pow_counter) && value < std::pow(10, pow_counter + 1))
                        break;
                maximum = ((int32_t)value / std::pow(10, pow_counter)) + 1;
                minimum = ((int32_t)value / std::pow(10, pow_counter)) - 1;
                maximum = std::pow(10, pow_counter) * -1 * maximum;
                minimum = std::pow(10, pow_counter) * -1 * minimum;
            } else {
                for(pow_counter = 1; pow_counter <= 5; pow_counter++)
                    if(value > std::pow(10, pow_counter) && value < std::pow(10, pow_counter + 1))
                        break;
                maximum = ((int32_t)value / std::pow(10, pow_counter)) + 1;
                minimum = ((int32_t)value / std::pow(10, pow_counter)) - 1;
                maximum = std::pow(10, pow_counter) * maximum;
                minimum = std::pow(10, pow_counter) * minimum;
            }
            value_widget->setText(QString::number(value, 10, 2));
            maximum_tb->setText(QString::number((float)maximum, 10, 2));
            minimum_tb->setText(QString::number((float)minimum, 10, 2));
        } else {
            maximum = 1;
            minimum = -1;
            value_widget->setText("0");
            maximum_tb->setText(QString::number((float)maximum, 10, 2));
            minimum_tb->setText(QString::number((float)minimum, 10, 2));
        }
    } else {
        maximum = 1;
        minimum = -1;
        value_widget->setText("0");
        maximum_tb->setText(QString::number((float)maximum, 10, 2));
        minimum_tb->setText(QString::number((float)minimum, 10, 2));
    }
    error_value = maximum - minimum;
    value_step = (uint32_t)((value - minimum) * (10000.0 / (double)error_value));
    value_slider->setValue(value_step);
}

void MainWindow::mdtp_callback_handler(unsigned char pid, const unsigned char *data) {
    uint32_t data1, data2;
    data1 = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    data2 = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
    switch (pid) {
        case 0:
            curve_x.resize(curve_counter + 1);
            curve_angle.resize(curve_counter + 1);
            curve_velocity.resize(curve_counter + 1);
            curve_x[curve_counter] = (curve_counter + 1) * 0.05f;
            curve_angle[curve_counter] = (*((float *)(&data2)));
            curve_velocity[curve_counter] = (*((float *)(&data1)));
            ui->custom_plot->graph(0)->setData(curve_x, curve_velocity);
            ui->custom_plot->graph(1)->setData(curve_x, curve_angle);
            ui->custom_plot->rescaleAxes();
            ui->custom_plot->replot();
            curve_counter = curve_counter + 1;
            break;
        case 1:

            update_minimum_maximum_value((*((float *)(&data2))), ui->slider_current_value,
                                         ui->user_expect_slider, ui->slider_maximum_value, ui->slider_minimum_value);
            break;
        case 2:
            update_minimum_maximum_value((*((float *)(&data1))), ui->speed_kp_value,
                                     ui->speed_kp_slider, ui->speed_kp_maximum, ui->speed_kp_minimum);
            update_minimum_maximum_value((*((float *)(&data2))), ui->speed_ki_value,
                                     ui->speed_ki_slider, ui->speed_ki_maximum, ui->speed_ki_minimum);
            break;
        case 3:
            update_minimum_maximum_value((*((float *)(&data1))), ui->speed_kd_value,
                                     ui->speed_kd_slider, ui->speed_kd_maximum, ui->speed_kd_minimum);
            update_minimum_maximum_value((*((float *)(&data2))), ui->speed_summax_value,
                                     ui->speed_summax_slider, ui->speed_summax_maximum, ui->speed_summax_minimum);
            break;
        case 4:
            update_minimum_maximum_value((*((float *)(&data1))), ui->angle_kp_value,
                                     ui->angle_kp_slider, ui->angle_kp_maximum, ui->angle_kp_minimum);
            update_minimum_maximum_value((*((float *)(&data2))), ui->angle_ki_value,
                                     ui->angle_ki_slider, ui->angle_ki_maximum, ui->angle_ki_minimum);
            break;
        case 5:
            update_minimum_maximum_value((*((float *)(&data1))), ui->angle_kd_value,
                                     ui->angle_kd_slider, ui->angle_kd_maximum, ui->angle_kd_minimum);
            update_minimum_maximum_value((*((float *)(&data2))), ui->angle_summax_value,
                                     ui->angle_summax_slider, ui->angle_summax_maximum, ui->angle_summax_minimum);
            break;
        default:
            break;
    }
}

void MainWindow::on_open_btn_clicked() {
    if(serial->isOpen() == false) {
        if(set_serial_badurate() == false)
            return;
        unsigned char buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        serial->open(QSerialPort::ReadWrite);
        connect(serial,SIGNAL(readyRead()),this,SLOT(serial_received()));
        ui->open_btn->setText("Close");
        ui->serial_port_cb->setEnabled(false);
        ui->serial_baudrate_txt->setEnabled(false);
        ui->calibrate_btn->setEnabled(true);
        ui->start_stop_btn->setEnabled(true);
        ui->mode_set_cb->setEnabled(true);
        slider_timer->start();
        buffer[0] = 0xC3;
        mdtp_data_transmit(0x00, buffer);
        ui->torque_groupbox->setEnabled(true);
        ui->speed_groupbox->setEnabled(true);
        ui->angle_groupbox->setEnabled(true);
        ui->pid_parameter_btn->setEnabled(true);
        ui->custom_plot->setEnabled(true);
    } else {
        serial->close();
        ui->open_btn->setText("Open");
        ui->mode_set_cb->setEnabled(false);
        ui->calibrate_btn->setEnabled(false);
        ui->start_stop_btn->setEnabled(false);
        ui->serial_port_cb->setEnabled(true);
        ui->serial_baudrate_txt->setEnabled(true);
        slider_timer->stop();
        ui->torque_groupbox->setEnabled(false);
        ui->speed_groupbox->setEnabled(false);
        ui->angle_groupbox->setEnabled(false);
        ui->pid_parameter_btn->setEnabled(false);
        ui->custom_plot->setEnabled(false);
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
        ui->user_expect_slider->setEnabled(true);
        ui->slider_maximum_value->setEnabled(true);
        ui->slider_minimum_value->setEnabled(true);
    }else {
        buffer[0] = 0x2D;
        mdtp_data_transmit(0x00, buffer);
        ui->start_stop_btn->setText("Start");

        ui->mode_set_cb->setEnabled(true);
        ui->user_expect_slider->setEnabled(false);
        ui->slider_maximum_value->setEnabled(false);
        ui->slider_minimum_value->setEnabled(false);
    }
}

void MainWindow::on_calibrate_btn_clicked() {
    unsigned char buffer[8] = {0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    mdtp_data_transmit(0x00, buffer);
    ui->calibrate_btn->setEnabled(false);
}

void MainWindow::on_pid_parameter_btn_clicked(){
    unsigned char buffer[8] = {0xD2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    mdtp_data_transmit(0x00, buffer);
}

void MainWindow::on_refresh_btn_clicked(){
    refresh_serial_port();
}

/* slider value changed functions */
void MainWindow::on_torque_kp_slider_valueChanged(int value) {
    float maximum = ui->torque_kp_maximum->toPlainText().toFloat();
    float minimum = ui->torque_kp_minimum->toPlainText().toFloat();
    torque_slider_change_flag[0] = true;
    torque_slider_value[0] = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->torque_kp_value->setText(QString::number(torque_slider_value[0], 10, 2));
}

void MainWindow::on_torque_ki_slider_valueChanged(int value) {
    float maximum = ui->torque_ki_maximum->toPlainText().toFloat();
    float minimum = ui->torque_ki_minimum->toPlainText().toFloat();
    torque_slider_change_flag[1] = true;
    torque_slider_value[1] = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->torque_ki_value->setText(QString::number(torque_slider_value[1], 10, 2));
}

void MainWindow::on_torque_kd_slider_valueChanged(int value) {
    float maximum = ui->torque_kd_maximum->toPlainText().toFloat();
    float minimum = ui->torque_kd_minimum->toPlainText().toFloat();
    torque_slider_change_flag[2] = true;
    torque_slider_value[2] = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->torque_kd_value->setText(QString::number(torque_slider_value[2], 10, 2));
}

void MainWindow::on_torque_summax_slider_valueChanged(int value) {
    float maximum = ui->torque_summax_maximum->toPlainText().toFloat();
    float minimum = ui->torque_summax_minimum->toPlainText().toFloat();
    torque_slider_change_flag[3] = true;
    torque_slider_value[3] = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->torque_summax_value->setText(QString::number(torque_slider_value[3], 10, 2));
}

void MainWindow::on_speed_kp_slider_valueChanged(int value) {
    float maximum = ui->speed_kp_maximum->toPlainText().toFloat();
    float minimum = ui->speed_kp_minimum->toPlainText().toFloat();
    speed_slider_change_flag[0] = true;
    speed_slider_value[0] = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->speed_kp_value->setText(QString::number(speed_slider_value[0], 10, 2));
}

void MainWindow::on_speed_ki_slider_valueChanged(int value) {
    float maximum = ui->speed_ki_maximum->toPlainText().toFloat();
    float minimum = ui->speed_ki_minimum->toPlainText().toFloat();
    speed_slider_change_flag[1] = true;
    speed_slider_value[1] = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->speed_ki_value->setText(QString::number(speed_slider_value[1], 10, 2));
}

void MainWindow::on_speed_kd_slider_valueChanged(int value) {
    float maximum = ui->speed_kd_maximum->toPlainText().toFloat();
    float minimum = ui->speed_kd_minimum->toPlainText().toFloat();
    speed_slider_change_flag[2] = true;
    speed_slider_value[2] = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->speed_kd_value->setText(QString::number(speed_slider_value[2], 10, 2));
}

void MainWindow::on_speed_summax_slider_valueChanged(int value) {
    float maximum = ui->speed_summax_maximum->toPlainText().toFloat();
    float minimum = ui->speed_summax_minimum->toPlainText().toFloat();
    speed_slider_change_flag[3] = true;
    speed_slider_value[3] = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->speed_summax_value->setText(QString::number(speed_slider_value[3], 10, 2));
}


void MainWindow::on_angle_kp_slider_valueChanged(int value) {
    float maximum = ui->angle_kp_maximum->toPlainText().toFloat();
    float minimum = ui->angle_kp_minimum->toPlainText().toFloat();
    angle_slider_change_flag[0] = true;
    angle_slider_value[0] = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->angle_kp_value->setText(QString::number(angle_slider_value[0], 10, 2));
}

void MainWindow::on_angle_ki_slider_valueChanged(int value) {
    float maximum = ui->angle_ki_maximum->toPlainText().toFloat();
    float minimum = ui->angle_ki_minimum->toPlainText().toFloat();
    angle_slider_change_flag[1] = true;
    angle_slider_value[1] = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->angle_ki_value->setText(QString::number(angle_slider_value[1], 10, 2));
}

void MainWindow::on_angle_kd_slider_valueChanged(int value) {
    float maximum = ui->angle_kd_maximum->toPlainText().toFloat();
    float minimum = ui->angle_kd_minimum->toPlainText().toFloat();
    angle_slider_change_flag[2] = true;
    angle_slider_value[2] = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->angle_kd_value->setText(QString::number(angle_slider_value[2], 10, 2));
}

void MainWindow::on_angle_summax_slider_valueChanged(int value) {
    float maximum = ui->angle_summax_maximum->toPlainText().toFloat();
    float minimum = ui->angle_summax_minimum->toPlainText().toFloat();
    angle_slider_change_flag[3] = true;
    angle_slider_value[3] = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->angle_summax_value->setText(QString::number(angle_slider_value[3], 10, 2));
}

void MainWindow::on_user_expect_slider_valueChanged(int value) {
    float maximum = ui->slider_maximum_value->toPlainText().toFloat();
    float minimum = ui->slider_minimum_value->toPlainText().toFloat();
    expect_slider_change_flag = true;
    expect_slider_value = (maximum - minimum) * (value / 10000.0f) + minimum;
    ui->slider_current_value->setText(QString::number(expect_slider_value, 10, 2));
}

/* some functions related to timer interrupt */

void MainWindow::slider_timer_timeout() {
    unsigned char buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned int uintp32 = 0x00000000UL;
    if(expect_slider_change_flag == true){
        buffer[0] = 0x3C;
        uintp32 = (*((unsigned int *) (&expect_slider_value)));
        expect_slider_change_flag = false;
        goto mdtp_sendpackage;
    }

    for (int counter = 0; counter < 4; counter++) {
        if(torque_slider_change_flag[counter] != false) {
            buffer[0] = ((4 + counter) << 4) | ((~(4 + counter)) & 0x0f);
            uintp32 = (*((unsigned int *) (&torque_slider_value[counter])));
            torque_slider_change_flag[counter] = false;
            goto mdtp_sendpackage;
        }
    }

    for (int counter = 0; counter < 4; counter++) {
        if(speed_slider_change_flag[counter] != false) {
            buffer[0] = ((4 + counter) << 4) | ((~(4 + counter)) & 0x0f);
            uintp32 = (*((unsigned int *) (&speed_slider_value[counter])));
            speed_slider_change_flag[counter] = false;
            goto mdtp_sendpackage;
        }
    }

    for (int counter = 0; counter < 4; counter++) {
        if(angle_slider_change_flag[counter] != false) {
            buffer[0] = ((8 + counter) << 4) | ((~(8 + counter)) & 0x0f);
            uintp32 = (*((unsigned int *) (&angle_slider_value[counter])));
            angle_slider_change_flag[counter] = false;
            goto mdtp_sendpackage;
        }
    }

mdtp_sendpackage:
    if(buffer[0] != 0x00) {
        buffer[4] = (unsigned char) ((uintp32 >> 24UL) & 0x000000ffUL);
        buffer[5] = (unsigned char) ((uintp32 >> 16UL) & 0x000000ffUL);
        buffer[6] = (unsigned char) ((uintp32 >> 8UL) & 0x000000ffUL);
        buffer[7] = (unsigned char) (uintp32 & 0x000000ffUL);
        mdtp_data_transmit(0x00, buffer);
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
    if(ui->serial_port_cb->currentText() == NULL || ui->serial_baudrate_txt->toPlainText() == NULL) {
        QMessageBox::information(NULL, "Error", "Please select port number and baudrate first!");
        return false;
    }

    serial->setPortName(ui->serial_port_cb->currentText());
    serial->setBaudRate(ui->serial_baudrate_txt->toPlainText().toInt());
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    return true;
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
