//
// Created by 1 on 2025/10/11.
//

#include "bsp.h"
#include "stm32f1xx_hal_tim.h"
#include "main.h"
Motor::Motor(TIM_HandleTypeDef* tim,uint32_t channel,MotorType type)
:m_tim(tim),m_channel(channel),m_type(type){}