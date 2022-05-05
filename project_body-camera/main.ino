int PIR = 4;        // 센서 변수 선언하고 연결한 핀 번호로 초기화
int state = 0;      // 센서 상태 값 저장 변수(0: LOW, 1: HIGH)
int trigpin = 5;
int echopin = 6;


void camera_shot() {

}


long PulseSensor(long standard){
    long duration, distance;

    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);
    duration = pulseIn(echopin, HIGH);
    distance = ((float)(340 * duration) / 1000) / 2;
    
    long detection = distance / standard * 100;       //detection = 거리 비율

    return detection;
}


void setup() {
  pinMode(PIR, INPUT);      // 센서를 입력으로 설정
  Serial.begin(57600);      // 시리얼 통신
  pinMode(echopin, INPUT);
  pinMode(trigpin, OUTPUT);     //초음파 센서
}


void loop() {
    int come = 0;      //사람접근 변수
    

    state = digitalRead(PIR);   // PIR 센서값 입력받음

    if (state == 1 && PulseSensor() >= 80){              // pulsesensor()에 standard 거리 넣어야함.
        Serial.print("ON");       // 시리얼 통신에 센서값 출력
        camera_shot();      //카메라 센서 촬영 시작
    }

    else {                        // 센서 값이 0 이라면
        Serial.print("OFF");      // 시리얼 모니터에 LED 상태 출력
        delay(100);
    }
    delay(100);   // 0.1초 대기(1000ms = 1s)
}

