//
// Created by Lao·Zhu on 2021/9/11.
//

#include "pid.h"
#include "fast_math.h"
#include "system.h"

unsigned char pid_parameter_available_flag = 0;
volatile unsigned char pid_control_mode_flag = 0;
volatile PID_Structure_t speed_pid_handler, angle_pid_handler;

void pid_config(unsigned char mode) {
    user_memset((void *) &speed_pid_handler, 0x00, sizeof(PID_Structure_t));
    user_memset((void *) &angle_pid_handler, 0x00, sizeof(PID_Structure_t));

    pid_control_mode_flag = mode;

    speed_pid_handler.maximum = 1.0f;
    speed_pid_handler.minimum = -1.0f;

    angle_pid_handler.maximum = 100.0f;
    angle_pid_handler.minimum = -100.0f;
}

float pid_calculate_result(PID_Structure_t *pid_handler, float collect) {
    float current_result, error = pid_handler->expect - collect;
    pid_handler->summary = pid_handler->summary + error;
    pid_handler->summary = fast_constrain(pid_handler->summary, pid_handler->sum_maximum, -pid_handler->sum_maximum);
    current_result = pid_handler->kp * error + pid_handler->ki * pid_handler->summary
        + pid_handler->kd * (error - pid_handler->last_error);
    pid_handler->last_error = error;
    current_result = fast_constrain(current_result, pid_handler->minimum, pid_handler->maximum);
    return current_result;
}
