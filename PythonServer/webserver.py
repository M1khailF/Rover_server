from http.server import HTTPServer, BaseHTTPRequestHandler

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler): 
    def do_GET(self):
        global line
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        line = self.requestline
        
        HtmlFile = open("web.html", 'r', encoding='utf-8')
        html_content = HtmlFile.read()
        
        self.wfile.write(html_content.encode())
    
class Rover_Web():
    def __init__(self, host='0.0.0.0', port=9999) -> None:
        global line
        
        line = ""
        self.host = host
        self.port = port
        self.motorValue = 0.0
        self.angleValue = 0.0
        self.armState = 0

    def run_while_true(self):
        global line
        server_address = ('0.0.0.0', 9999)
        httpd = HTTPServer(server_address, SimpleHTTPRequestHandler)
        while True:
            httpd.handle_request()

            if "/motor" in line:
                line = line.split(" ")
                line = line[1].split("=")
                self.motorValue = float(line[1])

            if "/angle" in line:
                line = line.split(" ")
                line = line[1].split("=")
                self.angleValue = float(line[1])

            if "/armState" in line:
                line = line.split(" ")
                line = line[1].split("=")
                self.armState = int(line[1])
            return [self.motorValue, self.angleValue, self.armState]

if __name__ == "__main__":
    host = '0.0.0.0'
    port = 9999

    server = Rover_Web(host, port)
    while True:
        print(server.run_while_true()) # [motor, angle, armState]