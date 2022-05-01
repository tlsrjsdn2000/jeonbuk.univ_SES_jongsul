/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'9','10','11','12'},
  {'13','14','15','16'}
};
byte rowPins[ROWS] = {11, 10, 9, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 5, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// 비밀번호
String password = "192711";
// 사용자 입력값 저장
String userInput = "";
int count = 0;

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key){
    Serial.print(key); 
    userInput += key;
    count +=1;


    if(count == 6)
    {
      count =0;
      if (userInput == password)
      { 
        Serial.println();
        Serial.println("Welcome!");
      }
      else
      {
        Serial.println();
        Serial.println("Incorrect password");
      }
      
      userInput = "";
    }  
  }
}
