#include "ESP32_Rover.h"

int main(){
    ESP32_Rover esp("192.168.2.1", "9999");
    if (esp.checkConnect()){
        esp.setMotorValue(0.41);
        esp.setAngleValue(0.42);
        esp.DISARM(true);    
    }
    return 0;
}