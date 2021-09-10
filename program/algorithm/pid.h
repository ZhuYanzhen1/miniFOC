//
// Created by Lao·Zhu on 2021/9/11.
//

#ifndef MINIFOC_ALGORITHM_PID_H_
#define MINIFOC_ALGORITHM_PID_H_

#define TORQUE_LOOP_CONTROL     1
#define SPEED_LOOP_CONTROL      2
#define ANGLE_LOOP_CONTROL      3

typedef struct {
    float kp;
    float ki;
    float kd;
    float summary;
    float expect;
    float maximum;
    float minimum;
    float sum_maximum;
    float last_error;
} PID_Structure_t;

extern volatile PID_Structure_t speed_pid_handler, angle_pid_handler;
void pid_config(unsigned char mode);
float pid_calculate_result(PID_Structure_t *pid_handler, float collect);

#endif //MINIFOC_ALGORITHM_PID_H_
