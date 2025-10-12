//
// Created by 1 on 2025/10/11.
//

#ifndef C8T6_BSP_H
#define C8T6_BSP_H

#pragma once
#include "main.h"
#include "tim.h"

#ifdef __cplusplus
enum class MotorType {
    DC,
    Servo
};

class Motor {
public:
    Motor(TIM_HandleTypeDef* tim,  uint32_t channel,MotorType type);
    void init();
    void setSpeed(float duty);
    void setAngle(float angle);
private:
    TIM_HandleTypeDef* m_tim;
    uint32_t m_channel;
    MotorType m_type;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif
    void Init();
    void Servo_SetAngle(float angle);
    void DC_SetSpeed(float duty);
#ifdef __cplusplus
}
#endif
#endif //C8T6_BSP_H
