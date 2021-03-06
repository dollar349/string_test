#include <stdio.h>
#include <stdarg.h>
#include <math.h>

typedef enum {
    COOL_ALARM_HIGH_HEAD_PRESSURE1,
    COOL_ALARM_HIGH_HEAD_PRESSURE2,
    COOL_ALARM_LOSS_AIRFLOW,
    COOL_ALARM_STANDBY_GLYCOOL_PUMP_ON,
    COOL_ALARM_WATER_UNDER_FLOOR,           //5
    COOL_ALARM_CLOGGED_FILTERS,
    COOL_ALARM_HIGH_TEMP,
    COOL_ALARM_LOW_TEMP,
    COOL_ALARM_HIGH_HUMD,
    COOL_ALARM_LOW_HUMD,                    //10
    COOL_ALARM_HUMD_OVERFLOW,
    COOL_ALARM_HUMD_FAILED,
    COOL_ALARM_COMP1_MOTOR_PROTECT,
    COOL_ALARM_COMP2_MOTOR_PROTECT,
    COOL_ALARM_MAIN_FAN_OVERLOAD,           //15
    COOL_ALARM_MANUAL_OVERRIDE,
    COOL_ALARM_SMOKE,
    COOL_ALARM_LOW_CHILL_WATER_FLOW,
    COOL_ALARM_STANDBY_UNIT_ON,
    COOL_ALARM_LOW_SUCTION_PRESSURE,        //20
    COOL_ALARM_SHORT_CYCLE,
    COOL_ALARM_LOSS_OF_POWER,
    COOL_ALARM_INVERTER_BYPASS,
    COOL_ALARM_STANDBY_FAN,
    COOL_ALARM_LOSS_EMERGENCY_POWER,        //25
    COOL_ALARM_LOCAL_ALARM1,
    COOL_ALARM_LOCAL_ALARM2,
    COOL_ALARM_LOCAL_ALARM3,
    COOL_ALARM_LOCAL_ALARM4,
    MAX_COOL_ALARM
} COOL_ALARM_e;

typedef struct{
    COOL_ALARM_e AlarmMap;
    char AlarmCode;
}CoolerAlarm;

CoolerAlarm g_mm2_alarm[1]={
    {
     COOL_ALARM_HIGH_HEAD_PRESSURE1,0x03
    }
};
int main(int argc, char* argv[])
{
   // int in_size =_INTSIZEOF(int);
    //printf("int_size=%d\n",in_size);
  printf("test = %d %d\n",g_mm2_alarm[0].AlarmMap, g_mm2_alarm[0].AlarmCode);
}
