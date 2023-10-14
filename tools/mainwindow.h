#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTextEdit>
#include <QSlider>

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
    void on_start_stop_btn_clicked();
    void on_calibrate_btn_clicked();

    /* slider value changed callback functions */
    void on_user_expect_slider_valueChanged(int value);
    void on_speed_kp_slider_valueChanged(int value);
    void on_speed_ki_slider_valueChanged(int value);
    void on_speed_kd_slider_valueChanged(int value);
    void on_speed_summax_slider_valueChanged(int value);
    void on_angle_kp_slider_valueChanged(int value);
    void on_angle_ki_slider_valueChanged(int value);
    void on_angle_kd_slider_valueChanged(int value);
    void on_angle_summax_slider_valueChanged(int value);
    void on_pid_parameter_btn_clicked();

    void on_torque_kp_slider_valueChanged(int value);

    void on_torque_ki_slider_valueChanged(int value);

    void on_torque_kd_slider_valueChanged(int value);

    void on_torque_summax_slider_valueChanged(int value);

public slots:
    void serial_received();
    void slider_timer_timeout();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;

    /* slider value changed variables */
    bool expect_slider_change_flag = false;
    bool torque_slider_change_flag[4];
    bool speed_slider_change_flag[4];
    bool angle_slider_change_flag[4];

    float expect_slider_value = 0;
    float torque_slider_value[4];
    float speed_slider_value[4];
    float angle_slider_value[4];
    QTimer *slider_timer;

    /* chart & curve value variables */
    uint64_t curve_counter = 0;
    QVector<double> curve_velocity, curve_angle, curve_x;

    /* serial configure functions */
    void refresh_serial_port();
    bool set_serial_badurate();
    void update_minimum_maximum_value(float value, QLabel *value_widget, QSlider *value_slider,
                                      QTextEdit *maximum_tb, QTextEdit *minimum_tb);

    /* chart & curve configure function */
    void setup_custom_plot();

    /* mdtp related functions */
    void mdtp_receive_handler(unsigned char data);
    void mdtp_data_transmit(unsigned char pid, const unsigned char *data);
    void mdtp_callback_handler(unsigned char pid, const unsigned char *data);
};
#endif // MAINWINDOW_H
