# 1 "c:\\Users\\Woo\\jongsul\\jeonbuk.univ_SES_jongsul\\project_body-camera\\main.ino"
int PIR = 4; // 센서 변수 선언하고 연결한 핀 번호로 초기화
int state = 0; // 센서 상태 값 저장 변수(0: LOW, 1: HIGH)
int trigpin = 5;
int echopin = 6;


void camera_shot() {

}


long PulseSensor(long standard){
    long duration, distance;

    digitalWrite(trigpin, 0x1);
    delayMicroseconds(10);
    digitalWrite(trigpin, 0x0);
    duration = pulseIn(echopin, 0x1);
    distance = ((float)(340 * duration) / 1000) / 2;

    long detection = distance / standard * 100; //detection = 거리 비율

    return detection;
}


void setup() {
  pinMode(PIR, 0x00); // 센서를 입력으로 설정
  Serial.begin(57600); // 시리얼 통신
  pinMode(echopin, 0x00);
  pinMode(trigpin, 0x01); //초음파 센서
}


void loop() {
    int come = 0; //사람접근 변수


    state = digitalRead(PIR); // PIR 센서값 입력받음

    if (state == 1 && PulseSensor() <= 80){ // pulsesensor()에 standard 거리 넣어야함.
        Serial.print("ON"); // 시리얼 통신에 센서값 출력
        camera_shot(); //카메라 센서 촬영 시작
    }

    else { // 센서 값이 0 이라면
        Serial.print("OFF"); // 시리얼 모니터에 LED 상태 출력
        delay(100);
    }
    delay(100); // 0.1초 대기(1000ms = 1s)
}
# 1 "c:\\Users\\Woo\\jongsul\\jeonbuk.univ_SES_jongsul\\project_body-camera\\newhtml.ino"
# 2 "c:\\Users\\Woo\\jongsul\\jeonbuk.univ_SES_jongsul\\project_body-camera\\newhtml.ino" 2
# 3 "c:\\Users\\Woo\\jongsul\\jeonbuk.univ_SES_jongsul\\project_body-camera\\newhtml.ino" 2
# 4 "c:\\Users\\Woo\\jongsul\\jeonbuk.univ_SES_jongsul\\project_body-camera\\newhtml.ino" 2
# 5 "c:\\Users\\Woo\\jongsul\\jeonbuk.univ_SES_jongsul\\project_body-camera\\newhtml.ino" 2






const char* ssid = "Cafe_da_ing_2G";
const char* password = "jackpot7777";

ESP8266WebServer server(80);

const int led = 14;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266_2!\r\n");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, 0x01);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/gif", []() {
    static const uint8_t gif[] 
# 71 "c:\\Users\\Woo\\jongsul\\jeonbuk.univ_SES_jongsul\\project_body-camera\\newhtml.ino" 3
                              __attribute__((section( "\".irom.text." "newhtml.ino" "." "71" "." "127" "\""))) 
# 71 "c:\\Users\\Woo\\jongsul\\jeonbuk.univ_SES_jongsul\\project_body-camera\\newhtml.ino"
                                      = {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };
    char gif_colored[sizeof(gif)];
    memcpy_P(gif_colored, gif, sizeof(gif));
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;
    server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
  });

  server.onNotFound(handleNotFound);

  /////////////////////////////////////////////////////////
  // Hook examples

  server.addHook([](const String & method, const String & url, WiFiClient * client, ESP8266WebServer::ContentTypeFunction contentType) {
    (void)method; // GET, PUT, ...
    (void)url; // example: /root/myfile.html
    (void)client; // the webserver tcp client connection
    (void)contentType; // contentType(".html") => "text/html"
    Serial.printf("A useless web hook has passed\n");
    Serial.printf("(this hook is in 0x%08x area (401x=IRAM 402x=FLASH))\n", esp_get_program_counter());
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });

  server.addHook([](const String&, const String & url, WiFiClient*, ESP8266WebServer::ContentTypeFunction) {
    if (url.startsWith("/fail")) {
      Serial.printf("An always failing web hook has been triggered\n");
      return ESP8266WebServer::CLIENT_MUST_STOP;
    }
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });

  server.addHook([](const String&, const String & url, WiFiClient * client, ESP8266WebServer::ContentTypeFunction) {
    if (url.startsWith("/dump")) {
      Serial.printf("The dumper web hook is on the run\n");

      // Here the request is not interpreted, so we cannot for sure
      // swallow the exact amount matching the full request+content,
      // hence the tcp connection cannot be handled anymore by the
      // webserver.

      // we are lucky
      client->sendAll(Serial, 500);
# 133 "c:\\Users\\Woo\\jongsul\\jeonbuk.univ_SES_jongsul\\project_body-camera\\newhtml.ino"
      // Two choices: return MUST STOP and webserver will close it
      //                       (we already have the example with '/fail' hook)
      // or                  IS GIVEN and webserver will forget it
      // trying with IS GIVEN and storing it on a dumb WiFiClient.
      // check the client connection: it should not immediately be closed
      // (make another '/dump' one to close the first)
      Serial.printf("\nTelling server to forget this connection\n");
      static WiFiClient forgetme = *client; // stop previous one if present and transfer client refcounter
      return ESP8266WebServer::CLIENT_IS_GIVEN;
    }
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });

  // Hook examples
  /////////////////////////////////////////////////////////

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
# 1 "c:\\Users\\Woo\\jongsul\\jeonbuk.univ_SES_jongsul\\project_body-camera\\pp.ino"
