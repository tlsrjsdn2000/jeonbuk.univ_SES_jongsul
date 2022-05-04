int LED = 3;        // LED 변수 선언하고 연결한 핀 번호로 초기화
int PIR = 4;        // 센서 변수 선언하고 연결한 핀 번호로 초기화
int state = 0;      // 센서 상태 값 저장 변수(0: LOW, 1: HIGH)
 

void setup() {
  pinMode(LED, OUTPUT);     // LED를 출력으로 설정
  pinMode(PIR, INPUT);      // 센서를 입력으로 설정
  Serial.begin(57600);      // 시리얼 통신, 속도는 9600
}
 
void loop() {
  state = digitalRead(PIR);   // PIR 센서값 입력받음
  digitalWrite(LED, LOW);       // 초기 LED값을 0FF로 설정해주기
  
  if (state == 1){              // 센서 값이 1 이라면
    Serial.print("ON");       // 시리얼 통신에 센서값 출력
    camera_start();         //카메라 작동    
  }
  
  else {                        // 센서 값이 0 이라면
    Serial.print("OFF");      // 시리얼 모니터에 LED 상태 출력
    delay(100);
  }
  delay(100);   // 0.1초 대기(1000ms = 1s)
}

void camera_start() {

}