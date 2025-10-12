//
// Created by 1 on 2025/10/11.
//

#include "bsp.h"

Motor::Motor(TIM_HandleTypeDef* tim,uint32_t channel,MotorType type)
:m_tim(tim),m_channel(channel),m_type(type){}

void Motor::init()
{
    HAL_TIM_PWM_Start(m_tim, m_channel);
}

void Motor::setSpeed(float duty) {
    if (m_type!=MotorType::DC) {
        return;
    }
    if (duty<0.0f) {
        duty=0.0f;
    }
    if (duty>1.0f) {
        duty=1.0f;
    }

    auto compare =static_cast<uint32_t>(m_tim->Init.Period*duty);
    __HAL_TIM_SET_COMPARE(m_tim,m_channel,compare);
}

void Motor::setAngle(float angle) {
    if (m_type!=MotorType::Servo) {
        return;
    }
    if (angle<-90) {
        angle=-90;
    }
    if (angle>90) {
        angle=90;
    }
    auto pulse = 1500 + static_cast<uint16_t>(angle/180.0f*2000.0f);
    __HAL_TIM_SET_COMPARE(m_tim,m_channel,pulse);
}

extern "C" {
    static Motor Servo(&htim2,TIM_CHANNEL_2,MotorType::Servo);
    static Motor DC(&htim2,TIM_CHANNEL_2,MotorType::DC);

    void BSP_Init() {
        Servo.init();
        DC.init();
    }
    void Servo_SetAngle(float angle) {
        Servo.setAngle(angle);
    }
    void DC_SetSpeed(float duty) {
        Servo.setSpeed(duty);
    }
}