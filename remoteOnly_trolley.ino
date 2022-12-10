

// constants won't change. They're used here to set pin numbers:
const int fwPin = 6;     // the number of the pushbutton pin
const int rvPin =  7;      // the number of the LED pin

const int fw_pin = 8;
const int rv_pin= 9;
const int pw_pin =10;
// variables will change:
int buttonState_fw = 0;         // variable for reading the pushbutton status
int buttonState_rv = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(fwPin, INPUT);
  // initialize the pushbutton pin as an input:
  pinMode(rvPin, INPUT);
  pinMode(rv_pin, OUTPUT);
  pinMode(fw_pin, OUTPUT);
  pinMode(pw_pin,OUTPUT);
    digitalWrite(fw_pin, LOW);
    digitalWrite(pw_pin,HIGH);
    digitalWrite(rv_pin, LOW);
    //Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState_fw = digitalRead(fwPin);
  
  buttonState_rv = digitalRead(rvPin);
  
  digitalWrite(fw_pin,LOW);
  digitalWrite(rv_pin,LOW);
  if (buttonState_fw && buttonState_rv == HIGH){
    digitalWrite(fw_pin,LOW);
  digitalWrite(rv_pin,LOW);
    
    }
  
  else if(buttonState_fw== HIGH) {
   // turn LED off:
 //  Serial.println("Pin 7 is on");
    digitalWrite(rv_pin, LOW);
    
    digitalWrite(fw_pin, HIGH);
  } else  if(buttonState_rv== HIGH) {
    // turn LED off:
   // Serial.println("Pin 12 is on");
    digitalWrite(fw_pin, LOW);
    
    digitalWrite(rv_pin, HIGH);
  }else{
  
  digitalWrite(fw_pin,LOW);
  digitalWrite(rv_pin,LOW);}
}
