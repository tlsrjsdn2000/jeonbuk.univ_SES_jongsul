#include <Keypad.h>
#include <Servo.h>

#define scl_pin 4
#define sdo_pin 5
#define number 4
 
char key[number];                            // 키패드에서 입력받는 번호 저장
char password[number] = {1, 2, 3, 4};      // 비밀번호 설정
int correct = 0;                            // 비밀번호가 맞는 횟수를 세는 변수
int count = 0;                              // 번호를 몇개 입력했는지 세는 변수
 

const byte ROWS = 4;
const byte COLS = 2;

char keys[ROWS][COLS] = {
  {'1','2','3','4'},
  {'5','6','7','8'}
};

byte rowPins[ROWS] = {8,7,6,5};
byte colPins[COLS] = {4,3};

Servo myservo;
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() 
{
    Serial.begin(9600);
    myservo.attach(11);
}

void loop() {
    char key = keypad.getKey();

    if (key)
    {
        Serial.println(key);
        if(key==password[count])
        {
            count++
            correct++
        }

        else (key!=PW[count])
        {
            count++;
            Serial.println("비밀번호가 틀렸습니다. 카메라가 작동됩니다.");
        }

        if (count==4)
        {
            if(correct==4)
              open(); //문 열림
            else
              close(); //문 닫음

            correct=0;
            count=0;  
        }

    
    }
}

void open()
{
    myservo.write(180);
    Serial.println("비밀번호 일치, 문이 열립니다.")
}

void close()
{
    myservo.write(0);
    Serial.println("비밀번호 불일치")
}