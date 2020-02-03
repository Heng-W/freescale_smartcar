#include "VCAN_Control.h"
#include <math.h>

float g_fGravityAngle = 0;                                              //加速度计转换来的角度
float g_fGyroscopeAngleSpeed  = 0;                                      //陀螺仪转换来的角速度
float g_fCarAngle = 0;                                                  //车身角度

float voltage_gyro = 0;                                                 //定义陀螺仪（选X,Y,Z）
float voltage_gravity = 0;                                              //定义加速度计（选X,Y,Z）
float g_fGyroscopeAngleIntegral = 0;
float g_fAngleControlOut = 0;

float GRAVITY_OFFSET = -530;                                               //加速度计零偏
float GRAVITY_ANGLE_MAX = 3550;                                        //加速度计归一化因子

float GYROSCOPE_OFFSET = -4  ;                                            //陀螺仪零偏移
float GYROSCOPE_ANGLE_RATIO = 16.40;                               //归一化因子

float Car_angle_P = 0.27;                //angle控制参数
float Car_angle_D = 0.036;

float g_fCarSpeed = 0;
float g_fSpeedControlIntegral = 0;
float g_fSpeedControlOutOld = 0;
float g_fSpeedControlOutNew = 0;
float g_fSpeedControlOut = 0;
float g_nSpeedControlPeriod = 0;

float CAR_SPEED_SET = 2;                   // 转/s
float SPEED_CONTROL_P = 0.25;          //speed控制参数
float SPEED_CONTROL_I = 0.02;

float DIR_CONTROL_P = 0.5;
float DIR_CONTROL_D = 0.01;

float g_fLeftVoltageSigma = 0, g_fRightVoltageSigma = 0;
float g_fDirectionControlOutOld = 0, g_fDirectionControlOutNew = 0;
float g_nDirectionControlPeriod = 0;
float g_fDirectionControlOut = 0;
//float Clocks_Gyro = 0;

/*
void Gyro_Offset_Calculate(void)     //陀螺仪三个轴的零点跟随  Cut_Gyro_y为经过处理后的值， Gyro_y为实际的读值，Gyro_y_Offset 为零点
{
  float Cut_Gyro_y;

  //减去偏移值得到的实时值
  Cut_Gyro_y = voltage_gyro - GYROSCOPE_OFFSET;

  //根据实时值，修改零偏置
  if(Cut_Gyro_y>=2)
  {
    GYROSCOPE_OFFSET += 0.001;
  }
  else if(Cut_Gyro_y<=-2)
  {
    GYROSCOPE_OFFSET -= 0.001;
  }
  else
  {
    GYROSCOPE_OFFSET = GYROSCOPE_OFFSET * 0.99 + 0.01 * voltage_gyro;
  }
  //开机2秒进行跟随
  if (Clocks_Gyro <= 400)
  {  Clocks_Gyro++;
    GYROSCOPE_OFFSET = GYROSCOPE_OFFSET * 0.5 + 0.5 * voltage_gyro;
  }

}*/

void Angle_Calculate(void)
{
    float integralDriftError, angle_value;
    Get_Gyro();
    Get_AccData();
    voltage_gyro = mpu_gyro_y;
    voltage_gravity = mpu_acc_z;

    //Gyro_Offset_Calculate();
    angle_value = (voltage_gravity - GRAVITY_OFFSET) / (GRAVITY_ANGLE_MAX - GRAVITY_OFFSET);
    angle_value = limit(angle_value, 1);
    g_fGravityAngle =  asin(angle_value) * 90 / asin(1.0);
    g_fGyroscopeAngleSpeed = (voltage_gyro - GYROSCOPE_OFFSET) / GYROSCOPE_ANGLE_RATIO;
    // 获取角速度，并归一化

    g_fCarAngle = g_fGyroscopeAngleIntegral;      // 车身角度为陀螺仪积分后角度
    integralDriftError = (g_fGravityAngle - g_fCarAngle) / GRAVITY_ADJUST_TIME_CONSTANT;
    // 获取误差，用于矫正陀螺仪的角速度
    g_fGyroscopeAngleIntegral += (g_fGyroscopeAngleSpeed + integralDriftError) * 0.005;  //采样周期5ms,  融合后积分得到真正要用的角度
}


void Angle_Control(void)//PD
{
    float fValue;
    fValue = (CAR_ANGLE_SET - g_fCarAngle) * Car_angle_P + (CAR_ANGLE_SPEED_SET - g_fGyroscopeAngleSpeed) * Car_angle_D;
    g_fAngleControlOut = fValue;
}

void Speed_Control(void)//PI
{
    float fDelta;
    float fP, fI;
    g_fCarSpeed = (leftMotorPulseSigma + rightMotorPulseSigma) * 0.5;    //电极脉冲数平均值
    leftMotorPulseSigma = rightMotorPulseSigma = 0;
    g_fCarSpeed *= CAR_SPEED_CONSTANT;    //进行单位换算，转/s
    fDelta = CAR_SPEED_SET - g_fCarSpeed;
    fP = fDelta * SPEED_CONTROL_P;
    fI = fDelta * SPEED_CONTROL_I;

    g_fSpeedControlIntegral += fI;

    g_fSpeedControlOutOld = g_fSpeedControlOutNew;
    g_fSpeedControlOutNew = fP + g_fSpeedControlIntegral;
}

void SpeedControlOutput(void)
{
    float fValue;
    fValue = g_fSpeedControlOutNew - g_fSpeedControlOutOld;
    g_fSpeedControlOut = fValue * (g_nSpeedControlPeriod + 1) / SPEED_CONTROL_PERIOD + g_fSpeedControlOutOld;
}

void Direction_Control(void)//PD
{
    float fLeftRightAdd, fLeftRightSub;
    float fValue, fDValue, dir_gyro_value;
    int nLeft, nRight;

    nLeft = (int)(g_fLeftVoltageSigma /= 2);
    nRight = (int)(g_fRightVoltageSigma /= 2);  //DIRECTION_CONTROL_COUNT
    g_fLeftVoltageSigma = 0;
    g_fRightVoltageSigma = 0;

    fLeftRightAdd = nLeft + nRight;
    fLeftRightSub = nLeft - nRight;

    g_fDirectionControlOutOld = g_fDirectionControlOutNew;

    if (fLeftRightAdd < LEFT_RIGHT_MINIMUM)
    {
        g_fDirectionControlOutNew = 0;
    }
    else
    {
        fValue = fLeftRightSub * DIR_CONTROL_P / fLeftRightAdd;

        Get_Gyro();
        dir_gyro_value = mpu_gyro_x;
        fDValue = dir_gyro_value - DIRECTION_OFFSET;
        fDValue *= DIR_CONTROL_D;

        fValue += fDValue;
        g_fDirectionControlOutNew = fValue;
    }
}

void DirectionControlOutput(void)
{
    float fValue;
    fValue = g_fDirectionControlOutNew - g_fDirectionControlOutOld;
    g_fDirectionControlOut = fValue * (g_nDirectionControlPeriod + 1) / DIRECTION_CONTROL_PERIOD + g_fDirectionControlOutOld;
}

