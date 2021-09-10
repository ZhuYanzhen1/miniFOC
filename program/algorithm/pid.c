//
// Created by Lao·Zhu on 2021/9/11.
//

#include "pid.h"
#include "fast_math.h"
#include "system.h"

volatile unsigned char pid_angle_control_mode_flag = 0;
volatile PID_Structure_t speed_pid_handler, angle_pid_handler;

void pid_config(unsigned char mode) {
    user_memset((void *) &speed_pid_handler, 0x00, sizeof(PID_Structure_t));
    user_memset((void *) &angle_pid_handler, 0x00, sizeof(PID_Structure_t));

    speed_pid_handler.maximum = 0.6f;
    speed_pid_handler.minimum = -0.6f;
    speed_pid_handler.sum_maximum = 500.0f;

    if (mode == TORQUE_LOOP_CONTROL) {
        user_memset((void *) &speed_pid_handler, 0x00, sizeof(PID_Structure_t));
        speed_pid_handler.maximum = 1.0f;
        speed_pid_handler.minimum = -1.0f;
        speed_pid_handler.kp = 1.0f;
    }
    if (mode == ANGLE_LOOP_CONTROL) {
        angle_pid_handler.maximum = 100.0f;
        angle_pid_handler.minimum = -100.0f;
        pid_angle_control_mode_flag = 1;
    }
}

float pid_calculate_result(PID_Structure_t *pid_handler, float collect) {
    float calculate_result, error = pid_handler->expect - collect;
    pid_handler->summary = pid_handler->summary + error;
    pid_handler->summary = fast_constrain(pid_handler->summary, pid_handler->sum_maximum, -pid_handler->sum_maximum);
    calculate_result = pid_handler->kp * error + pid_handler->ki * pid_handler->summary
        + pid_handler->kd * (error - pid_handler->last_error);
    pid_handler->last_error = error;
    calculate_result = fast_constrain(calculate_result, pid_handler->minimum, pid_handler->maximum);
    return calculate_result;
}
