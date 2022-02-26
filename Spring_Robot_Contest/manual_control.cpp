/**
 * @file manual_control.cpp
 * @brief CAN通信による制御信号を用いてアームを動作させるプログラム
 * @author Akihisa Watanabe
 * @date 2022.02.26
 */
#include <stdio.h>
#include "mbed.h"
#include "EC.h"

CAN can1(p30,p29);
Ticker ticker;

PwmOut arm_down(PA_6); //0.5出力 で動く、０出力で動かない
PwmOut arm_up(PA_5);//0.5出力 で動く、０出力で動かない
DigitalIn pushrack(PC_11,PullUp); //ラックを押し出す
DigitalIn pullrack(PC_10,PullUp); //ラックを引き込む
arm_down.period(50);
arm_up.period(50);

/**
 * @fn
 * @brief アームを上下させる関数
 * @param (option) 0:アームを下げる, 1:アームを上げる
 * @return int 処理が成功した場合は1を，失敗した場合は0を返す．
 */
int arm_up_down(int option){
    switch (option){
        case 0:
            arm_down = 0.5;
            arm_up = 0;
        case 1:
            arm_down = 0;
            arm_up = 0.5;
        default:
            return 0;
    }

    wait(300);
    return 1;
}


/**
 * @fn
 * @brief CAN通信で制御信号を受信してアームを制御する関数
 */
void control(){
    CANMessage msg;
    int staus;
    
    if (can1.read(msg)){
        if(msg.id == 0){
            if (msg.data[0]==2){
                status = arm_up_down(msg.data[1]);
            }
            
        }
    }
}

int main(){
    ticker.attach(&control,0.001)
}