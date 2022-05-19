#include "WiFi.h"
#include "esp_camera.h"
#include "esp_timer.h"
#include "img_converters.h"
#include "Arduino.h"
#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems
#include "driver/rtc_io.h"
#include <ESPAsyncWebServer.h>
#include <StringArray.h>
#include <SPIFFS.h>
#include <FS.h>

#include <Keypad.h>
#include <Servo.h>

#define scl_pin 4
#define sdo_pin 5
#define number 4 // 키패드 핀 설정 //

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22 // 카메라 핀 설정 //
 
int key[number];                            // 키패드에서 입력받는 번호 저장
int password[number] = {1, 2, 3, 4};      // 비밀번호 설정
int correct = 0;                            // 비밀번호가 맞는 횟수를 세는 변수
int count = 0;    // 번호를 몇개 입력했는지 세는 변수

const char* ssid = "303"; // 와이파이 아이디
const char* password = "20001119"; //와이파이 비번

AsyncWebServer server(80); 
boolean takeNewPhoto = false;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { text-align:center; }
    .vert { margin-bottom: 10%; }
    .hori{ margin-bottom: 0%; }
  </style>
</head>
<body>
  <div id="container">
    <h2>Jongsul project</h2>
    <p>This is test ver of SES Door ESP camera.</p>
    <p>
      <button onclick="rotatePhoto();">ROTATE</button>
      //<button onclick="capturePhoto()">CAPTURE PHOTO</button>
      <button onclick="location.reload();">REFRESH PAGE</button>
    </p>
  </div>
  <div><img src="saved-photo" id="photo" width="70%"></div>
</body>
<script>
  var deg = 0;
  function capturePhoto() {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', "/capture", true);
    xhr.send();
  }
  function rotatePhoto() {
    var img = document.getElementById("photo");
    deg += 90;
    if(isOdd(deg/90)){ document.getElementById("container").className = "vert"; }
    else{ document.getElementById("container").className = "hori"; }
    img.style.transform = "rotate(" + deg + "deg)";
  }
  function isOdd(n) { return Math.abs(n % 2) == 1; }
</script>
</html>)rawliteral";


Servo myservo;

// Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);                       // 시리얼 통신 시작 속도는 9600  
  pinMode(scl_pin, OUTPUT);                  // scl_pin 출력으로 설정
  pinMode(sdo_pin, INPUT);               // sdo_pin 입력으로 설정
  myservo.attach(11);                    // 11번을 서보모터 핀으로 지정 
}
 
void loop() {  
  int a = getnumber();      // 키 패드에서 숫자 입력 받기

    if key{
      capturePhoto();
    }
  
  
    if (a != 0){            // 키패드에서 입력 받는 숫자가 0이 아닐 때
      key[count] = a;       // key변수에 입력 받는 숫자 저장
      Serial.print("PUSH :  ");   
      Serial.println(key[count]);  // 입력 받은 숫자 출력
      count ++;             // 비밀번호를 몇 개 입력했는지 세어줌
      delay(500);           // 한번에 여러 개의 숫자가 막 입력되지 않도록 delay 설정
 
      if(count == number){    // 입력한 숫자의 개수가 비밀번호 개수와 같을 경우
        
        for(int j=0; j<number; j++){    // 입력한 숫자와 비밀번호의 숫자 비교
          if(password[j] == key[j])
          correct++;                    // 입력한 숫자와 비밀번호의 숫자를 비교하여 숫자가 맞으면 correct변수를 1씩 추가해줌
        }
              
        if(correct == number){         // correct변수가 설정한 비밀번호의 개수와 같을 경우. (비밀번호가 맞을경우)
          correct = 0;                 // correct 변수 0으로 초기화
          
          
          Serial.println("Correct Password !!! ");    // 비밀번호가 맞았다고 시리얼 모니터에 출력
          Serial.println();    

          open();  
        
        }
        else{                // 비밀번호가 틀렸을 경우
          correct = 0;        // correct 변수 0으로 초기화
          
          
          Serial.println("Wrong Password !!! ");    // 비밀번호가 틀렸다고 시리얼 모니터에 출력
          Serial.println(); 

          close();   
          
        }

 /*       if(count==4)
        {
          if(correct==4)
            open();
          else
            close();
        }*/
        count = 0;          // 비밀번호를 몇 개를 썼는지 세주는 변수 0으로 초기화
      }        
   }    
}
 
byte getnumber(void){   
  byte count;
  byte num = 0;
  for(count = 1; count <= 8; count++)  {   // 번호를 1~16까지 비교해줌
    digitalWrite(scl_pin, LOW);             // 동기용 클럭 신호 low(Serial Clock)
    if (digitalRead(sdo_pin) == 0)          // 입력 받는 수와 1~16까지 비교하는 숫자가 맞을경우
      num = count;                          // num에 count를 대입해줌
    digitalWrite(scl_pin, HIGH);            // 동기용 클럭 신호 high(Serial Clock)
  }    
  return num;                               // num반환
}

void open()
{
    myservo.write(180);
    Serial.println("password match, open the door");
}

void close()
{
    myservo.write(0);
    Serial.println("password mismatch, run the camera");

    void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    ESP.restart();
  }
  else {
    delay(500);
    Serial.println("SPIFFS mounted successfully");
  }

  // Print ESP32 Local IP Address
  Serial.print("IP Address: http://");
  Serial.println(WiFi.localIP());

  // Turn-off the 'brownout detector'
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  // OV2640 camera module
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    ESP.restart();
  }

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });

  server.on("/capture", HTTP_GET, [](AsyncWebServerRequest * request) {
    takeNewPhoto = true;
    request->send_P(200, "text/plain", "Taking Photo");
  });

  server.on("/saved-photo", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, FILE_PHOTO, "image/jpg", false);
  });

  // Start server
  server.begin();

}

void loop() {
  if (takeNewPhoto) {
    capturePhotoSaveSpiffs();
    takeNewPhoto = false;
  }
  delay(1);
}

// Check if photo capture was successful
bool checkPhoto( fs::FS &fs ) {
  File f_pic = fs.open( FILE_PHOTO );
  unsigned int pic_sz = f_pic.size();
  return ( pic_sz > 100 );
}

// Capture Photo and Save it to SPIFFS
void capturePhotoSaveSpiffs( void ) {
  camera_fb_t * fb = NULL; // pointer
  bool ok = 0; // Boolean indicating if the picture has been taken correctly

  do {
    // Take a photo with the camera
    Serial.println("Taking a photo...");

    fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      return;
    }

    // Photo file name
    Serial.printf("Picture file name: %s\n", FILE_PHOTO);
    File file = SPIFFS.open(FILE_PHOTO, FILE_WRITE);

    // Insert the data in the photo file
    if (!file) {
      Serial.println("Failed to open file in writing mode");
    }
    else {
      file.write(fb->buf, fb->len); // payload (image), payload length
      Serial.print("The picture has been saved in ");
      Serial.print(FILE_PHOTO);
      Serial.print(" - Size: ");
      Serial.print(file.size());
      Serial.println(" bytes");
    }
    // Close the file
    file.close();
    esp_camera_fb_return(fb);

    // check if file has been correctly saved in SPIFFS
    ok = checkPhoto(SPIFFS);
  } while ( !ok );
}
}
