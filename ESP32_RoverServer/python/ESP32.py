import requests

class ESP32_Server():
    def __init__(self, ip_adress, port):
        self.IPAdress = ip_adress
        self.Port = port

    def check_connect(self): 
        try:
            req = requests.get(f"http://{self.IPAdress}:{self.Port}", timeout=10)
            return True
        except requests.HTTPError as e:
            print("Checking internet connection failed, status code {0}.".format(e.response.status_code))
        except requests.ConnectionError:
            print("No internet connection available.")
        return False
    
    def setMotorValue(self, value=0.0):
        requests.get(f"http://{self.IPAdress}:{self.Port}/motor?value={value}")

    def setAngleValue(self, value=0.0):
        requests.get(f"http://{self.IPAdress}:{self.Port}/angle?value={value}")
    
    def ARM(self, state=True):
        if state:
            requests.get(f"http://{self.IPAdress}:{self.Port}/armState?value=1")

    def DISARM(self, state=True):
        if state:
            requests.get(f"http://{self.IPAdress}:{self.Port}/armState?value=0")

    def getIp(self):
        return self.IPAdress