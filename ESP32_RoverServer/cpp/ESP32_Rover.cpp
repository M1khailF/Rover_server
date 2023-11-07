#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include "ESP32_Rover.h"

using namespace std;

ESP32_Rover::ESP32_Rover(string ip, string port)
{
    ipClass = ip;
    portClass = port;
}

void ESP32_Rover::setMotorValue(float inValue)
{
    string valueStr = to_string(inValue);
    urlGet("motor", valueStr);
}

void ESP32_Rover::setAngleValue(float inValue)
{
    string valueStr = to_string(inValue);
    urlGet("angle", valueStr);
}

void ESP32_Rover::ARM(bool state)
{
    if (state == true){
        urlGet("armState", "1");
    }
    else{
        urlGet("armState", "0");
    }
}

void ESP32_Rover::DISARM(bool state)
{
    if (state == false){
        urlGet("armState", "1");
    }
    else{
        urlGet("armState", "0");
    }
}

bool ESP32_Rover::checkConnect()
{
    CURL* curl;
    CURLcode res;
    
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl) {
        std::string response;
        string str = "http://" + ipClass + ":" + portClass;
        const char * http = str.c_str();
        
        curl_easy_setopt(curl, CURLOPT_URL, http);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << " Failed to perform request: " << curl_easy_strerror(res) << std::endl;
            return false;
        } else {
            return true;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}
