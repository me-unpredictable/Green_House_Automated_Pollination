const int fwPin = 6; // forward button connection
const int rvPin =  7; //reverse button connection
const int fw_pin = 9; //motor fw
const int rv_pin = 8; //motor rv
// if pwm stops working then skip rely connection
// relay is 4th layer of protection (optional)
const int pw_pin = 10; //pwm controller power

int buttonState_fw = 0;         // variable for reading the pushbutton status
int buttonState_rv = 0;         // variable for reading the pushbutton status

// controller flag
int _remote = 1; //by default remote is on

//debugging flag
int debug = 0;

//serial communication variables
String receivedCommand = "";
bool dataIn = false;





void setup() {
  // initialize the LED pin as an output:
  pinMode(fwPin, INPUT);
  // initialize the pushbutton pin as an input:
  pinMode(rvPin, INPUT);
  pinMode(rv_pin, OUTPUT);
  pinMode(fw_pin, OUTPUT);
  pinMode(pw_pin, OUTPUT);
  digitalWrite(fw_pin, LOW);
  digitalWrite(pw_pin, HIGH);
  digitalWrite(rv_pin, LOW);

  //begin Serial communication
  Serial.begin(115200);


}

void move_stop_() {
  if (debug) {
    Serial.println("Inside stop function");
  }
  //function to stop the trolley (it's not a brake)
  digitalWrite(fw_pin, LOW);
  digitalWrite(rv_pin, LOW);
  delay(100);
}
void move_fw() {
  if (debug) {
    Serial.println("Inside move forward function");
  }
  //function to move trolley forward
  digitalWrite(rv_pin, LOW);
  digitalWrite(fw_pin, HIGH);
}
void move_rv() {
  if (debug) {
    Serial.println("Inside move backward function");
  }
  //fuction to move trolley backward
  digitalWrite(fw_pin, LOW);
  digitalWrite(rv_pin, HIGH);
}

void disable_remote() {
  if (debug) {
    Serial.println("Inside remote disable function");
  }
  _remote = 0;
}
void enable_remote() {
  if (debug) {
    Serial.println("Inside remote enable function");
  }
  _remote = 1;
}





void demo1() {
  if (debug) {
    Serial.println("Inside demo 1 function");
  }
  //stop the trolley
  move_stop_();
  //disable remote
  disable_remote();
  //---------------------------Demo1----------------------------------
  // Move forward for fix time

  for (int i = 0; i < 70; i++) {
    if (debug) {
      Serial.println("Inside demo 1 mv_fw loop");
    }
    move_fw();
    delay(100);
  }
  // stop the trolley
  move_stop_();
  // Move backward for fix time
  for (int i = 0; i < 70; i++) {
    if (debug) {
      Serial.println("Inside demo 1 mv_bk loop");
    }
    move_rv();
    delay(100);
  }
  // stop the trolley
  move_stop_();
  //enable remote
  enable_remote();
}




void demo2() {
  if (debug) {
    Serial.println("Inside demo 2 function");
  }
  //stop the trolley
  move_stop_();
  //disable remote
  disable_remote();
  //---------------------------Demo2----------------------------------
  // Move forward for fix time then pasue for 2 secs then mv forward
  int j = 0;
  for (int j = 0; j < 10; j++) {
    if (debug) {
      Serial.println("Inside demo 2 mv_fw loop");
    }
    move_fw();
    delay(2000);
    move_stop_();
    delay(2000);
  }
  // stop the trolley
  move_stop_();
  // Move backward for fix time then pasue for 2 secs then mv backward
  int i = 0;
  for (int i = 0; i < 10; i++) {
    if (debug) {
      Serial.println("Inside demo 2 mv_bw loop");
    }
    move_rv();
    delay(2000);
    move_stop_();
    delay(2000);
  }
  // stop the trolley
  move_stop_();
  //enable remote
  enable_remote();
}




void ddemo() {
  if (debug) {
    Serial.println("Inside DummyDemo function");
  }
  //stop the trolley
  move_stop_();
  //disable remote
  disable_remote();
  //---------------------------Dummy Demo------------------------------
  // Move forward for fix time then pasue for 40 secs then mv forward
  for (int i = 0; i < 10; i++) {
    if (debug) {
      Serial.println("Inside ddemo mv_fw loop");
    }
    move_fw();
    delay(2000);
    move_stop_();
    delay(40000);
  }
  // stop the trolley
  move_stop_();
  // Move backward for fix time then pasue for 2 secs then mv backward
  for (int i = 0; i < 10; i++) {
    if (debug) {
      Serial.println("Inside ddemo mv_bw loop");
    }
    move_rv();
    delay(2000);
    move_stop_();
    delay(40000);
  }
  // stop the trolley
  move_stop_();
  //enable remote
  enable_remote();
}




void remote_control() {
  if (debug) {
    Serial.println("Inside remote_control function");
  }
  // read the state of the pushbutton value:
  buttonState_fw = digitalRead(fwPin);
  buttonState_rv = digitalRead(rvPin);
  //Stop the tolley
  move_stop_();
  // Check conditions
  if (buttonState_fw && buttonState_rv == HIGH) {
    if (debug) {
      Serial.println("both buttons are pressed");
    }
    //check if both buttons are pressed
    move_stop_();
  }
  else if (buttonState_fw == HIGH) {
    if (debug) {
      Serial.println("mv_fw button is pressed");
    }
    //check if forward button is pressed
    move_fw();
  } else  if (buttonState_rv == HIGH) {
    if (debug) {
      Serial.println("mv_rv button state");
    }
    //check if reverse button is pressed
    move_rv();
  } else {
    // if received garbage
    move_stop_();
  }

}




void loop() {
  if (debug) {
    Serial.println("Inside main loop");
  }
  if (_remote) {
    if (debug) {
      Serial.println("*Remote is enable!");
    }
    remote_control();
  }
  while (Serial.available())
  {
    if (debug) {
      Serial.println("Inside Serial reading while loop");
    }
    char c = Serial.read(); //read it

    if (c == '[')
    {
      //this is the start of the command string
      receivedCommand = "";
      dataIn = true;
    }
    //otherwise, we are still reading the command string:
    else if (dataIn && c != ']')
    {
      receivedCommand += c;
    }

    else if (dataIn && c == ']')
    {
      if (receivedCommand == "D1")
      {
        if (debug) {
          Serial.println("Running Demo 1");
        }
        demo1();
        if (debug) {
          Serial.println("Demo 1 ended");
        }
      }
      else if (receivedCommand == "D2")
      {
        if (debug) {
          Serial.println("Running Demo 2");
        }
        demo2();
        if (debug) {
          Serial.println("Demo 2 ended");
        }
      }
      else if (receivedCommand == "DD")
      {
        if (debug) {
          Serial.println("Running Dummy Demo");
        }
        ddemo();
        if (debug) {
          Serial.println("Dummy Demo 2 ended");
        }
      }
      else if (receivedCommand == "mv_fw")
      {
        if (debug) {
          Serial.println("Sepcial mv_fw call");
        }
        move_fw();
      }
      else if (receivedCommand == "mv_rv") {
        if (debug) {
          Serial.println("Special mv_rv call");
        }
        move_rv();
      }
      else if (receivedCommand == "stop") {
        if (debug) {
          Serial.println("Special stop call");
        }
        move_dstop_();
      }
    }
    //================================================================
    if (_remote) { //check remote control flag when connected with pc
      if (debug) {
        Serial.println("*Remote is re-enabled!");
      }
      remote_control();
    }
  }
  //Serial.println("Serial over");
  if (_remote) { //check remote control flag when not connected with pc
    remote_control();
  }
}
