#include "mbed.h"

#define PWM_T 0.1 //PWM周期：100ms
PwmOut PWM_OUT(PB_6); //超音波センサモジュールのTriger端子に入力する信号


InterraptIn GET_PWM(PC_7); //割り込み入力端子の設定．マイコンから出力したPWM信号をD9端子から取り込む．  

Timer ActiveTime; //タイマー計測用変数

unsigned int Count;
unsigned char Flag;
double dist;

void RiseEcho(){
    ActiveTime.start();
}
 
void FallEcho(){
    unsigned long ActiveWidth;
    ActiveTime.stop();
    ActiveWidth = ActiveTime.read_us();
    dist = ActiveWidth * 0.0170; //音速：0.034cm/us
    ActiveTime.reset();
    Flag = 1; //フラグのリセット
}
 
void main(){
    GET_PWM.rise(&RiseEcho);
    GET_PWM.fall(&FallEcho);
    
    PWM_OUT.perido(PWM_T);
    PWM_OUT.write(0.01f);//duty比:1%
    
    Count=0;
    Flag= 0;
    ActiveTime.reset();
    
    while(1){
        if (Flag==1){
            /*ここにモータを動かす処理を書く
            distに計測値(距離)が格納されている．前の値との差分に閾値を設けるのがいいのかな．．．
            */
            
        }
    }
}