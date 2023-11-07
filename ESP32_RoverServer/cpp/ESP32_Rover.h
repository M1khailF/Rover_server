#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>

using namespace std;

class ESP32_Rover
{
    public:
        ESP32_Rover(string ip, string port);

        void setMotorValue(float inValue);
        void setAngleValue(float inValue);
        void ARM(bool state);
        void DISARM(bool state);
        bool checkConnect();
    
    private:
        string ipClass;
        string portClass;

        static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
            size_t totalSize = size * nmemb;
            response->append(static_cast<char*>(contents), totalSize);
            return totalSize;
        }

        void urlGet(string name, string value)
        {
            CURL* curl;
            CURLcode res;
            
            curl_global_init(CURL_GLOBAL_DEFAULT);
        
            curl = curl_easy_init();
            if (curl) {
                std::string response;
                string str = "http://" + ipClass + ":" + portClass + "/" + name +"?value=" + value;
                const char * http = str.c_str();
                
                curl_easy_setopt(curl, CURLOPT_URL, http);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
                
                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
            }
            curl_global_cleanup();
        }
};