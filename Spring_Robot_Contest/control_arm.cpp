#include "mbed.h"

#define PWM_T 0.1 //PWM周期：100ms
PwmOut PWM_TRIGER(PB_6); //超音波センサモジュールのTriger端子に入力する信号


InterruptIn GET_PWM(PC_7); //割り込み入力端子の設定．マイコンから出力したPWM信号をD9端子から取り込む．  

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
 
int main(){
    GET_PWM.rise(&RiseEcho);
    GET_PWM.fall(&FallEcho);
    
    PWM_TRIGER.period(PWM_T);
    PWM_TRIGER.write(0.01f);//duty比:1%
    
    Count=0;
    Flag= 0;
    int threshold=100;
    ActiveTime.reset();
    
    while(1){
        if (Flag==1){
            if (dist > threshold){
            /*ここにモータを動かす処理を書く
            distに計測値(距離)が格納されている．前の値との差分に閾値を設けるのがいいのかな．．．
            */        
            }
        }
    }
}