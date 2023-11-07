from ESP32 import ESP32_Server

if __name__ == "__main__":
    esp = ESP32_Server("192.168.2.1", 9999)
    if esp.check_connect():
        esp.setMotorValue(-0.32)
        esp.setAngleValue(0.32)
        esp.ARM(True)