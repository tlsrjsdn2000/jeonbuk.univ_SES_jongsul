int LED = 3;        // LED 변수 선언하고 연결한 핀 번호로 초기화
int PIR = 4;        // 센서 변수 선언하고 연결한 핀 번호로 초기화
int state = 0;      // 센서 상태 값 저장 변수(0: LOW, 1: HIGH)
int trigpin = 5;
int echopin = 6;


void setup() {
  pinMode(LED, OUTPUT);     // LED를 출력으로 설정
  pinMode(PIR, INPUT);      // 센서를 입력으로 설정
  Serial.begin(57600);      // 시리얼 통신
  pinMode(echopin, INPUT);
  pinMode(trigpin, OUTPUT);     //초음파 센서
}


void loop() {
    int come = 0;      //사람접근 변수
    
    PulseSensor();      //기준거리 넣어줘야함


    state = digitalRead(PIR);   // PIR 센서값 입력받음

    if (state == 1){              // 센서 값이 1 이라면
        Serial.print("ON");       // 시리얼 통신에 센서값 출력

    }

    else {                        // 센서 값이 0 이라면
        Serial.print("OFF");      // 시리얼 모니터에 LED 상태 출력
        delay(100);
    }
    if (come == 1){

    }
    delay(100);   // 0.1초 대기(1000ms = 1s)
}


void camera_start() {

}


long PulseSensor(long standard){
    long duration, distance;

    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = ((float)(340 * duration) / 1000) / 2;
    
    long detection = (standard - distance) / 100;       //detection = 거리 비율
    
    return detection;
}

