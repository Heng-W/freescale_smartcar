#ifndef _VCAN_Control_H
#define _VCAN_Control_H

#include "include.h"

#define CAR_ANGLE_SET 44
#define CAR_ANGLE_SPEED_SET 0
#define GRAVITY_ADJUST_TIME_CONSTANT  2.0        //加速度计时间补偿系数  

extern float g_fGravityAngle ;                                              //加速度计转换来的角度
extern float g_fGyroscopeAngleSpeed  ;                                      //陀螺仪转换来的角速度
extern float g_fCarAngle ;
extern float GYROSCOPE_ANGLE_RATIO;

extern float voltage_gyro ;                                                 //定义陀螺仪（选X,Y,Z）
extern float voltage_gravity ;                                              //定义加速度计（选X,Y,Z）
extern float g_fGyroscopeAngleIntegral ;
extern float g_fAngleControlOut;


extern float Car_angle_P ;
extern float Car_angle_D ;

/********************************************************************************************************************/
#define ENCODER_CONSTANT  512    //电机转一圈所需的脉冲数 
#define SPEED_CONTROL_PERIOD     100 //速度控制周期，ms 
#define CAR_SPEED_CONSTANT      (1000.0/SPEED_CONTROL_PERIOD/ENCODER_CONSTANT)    // 单位转化比例值 

extern float g_fCarSpeed;
extern float g_fSpeedControlIntegral;
extern float g_fSpeedControlOutOld ;
extern float g_fSpeedControlOutNew;
extern float g_fSpeedControlOut;
extern float g_nSpeedControlPeriod;

extern float CAR_SPEED_SET  ;                   // 转/s
extern float SPEED_CONTROL_P  ;
extern float SPEED_CONTROL_I ;

/********************************************************************************************************************/
#define DIRECTION_CONTROL_PERIOD  10  //方向控制周期，ms 
#define LEFT_RIGHT_MINIMUM       2
#define DIRECTION_OFFSET         -62
extern float DIR_CONTROL_P ;
extern float DIR_CONTROL_D ;

extern float g_fLeftVoltageSigma, g_fRightVoltageSigma;
extern float g_fDirectionControlOutOld, g_fDirectionControlOutNew;
extern float g_nDirectionControlPeriod;
extern float g_fDirectionControlOut;
//extern float Clocks_Gyro ;


void Angle_Calculate(void);
void Angle_Control(void);
void Speed_Control(void);
void SpeedControlOutput(void);
void Direction_Control(void);
void DirectionControlOutput(void);

#endif