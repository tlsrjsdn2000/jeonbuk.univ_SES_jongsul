#include <Servo.h>

#define scl_pin 4
#define sdo_pin 5
#define number 4
 
int key[number];                            // 키패드에서 입력받는 번호 저장
int password[number] = {1, 2, 3, 4};      // 비밀번호 설정
int correct = 0;                            // 비밀번호가 맞는 횟수를 세는 변수
int count = 0;                              // 번호를 몇개 입력했는지 세는 변수
 
void setup() {
  Serial.begin(9600);                       // 시리얼 통신 시작 속도는 9600  
  pinMode(scl_pin, OUTPUT);                  // scl_pin 출력으로 설정
  pinMode(sdo_pin, INPUT);                   // sdo_pin 입력으로 설정
}
 
void loop() {  
  int a = getnumber();      // 키 패드에서 숫자 입력 받기
  
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
        
        }
        else{                // 비밀번호가 틀렸을 경우
          correct = 0;        // correct 변수 0으로 초기화
          
          Serial.println("Wrong Password !!! ");    // 비밀번호가 틀렸다고 시리얼 모니터에 출력
          Serial.println();    
          
        }
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


void correct() {
    myservo.write(180);
    Serial.println("open the door");
}

void touch() {
    Serial.println("도어락을 만졌습니다.")
}