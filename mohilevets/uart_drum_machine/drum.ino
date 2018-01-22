


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(37, OUTPUT); //set bit direction
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  int i=1;
  int h=50;

  
  while (1){

     
    
    if (Serial.available() > 0) {
    h= Serial.parseInt() ;
    }
    digitalWrite(37, HIGH);   // sound on
    delay(h);                       // pause
    digitalWrite(37, LOW);    // sound on
    delay(h);                       // pause
    digitalWrite(37, HIGH);   // sound on
    delay(h);                       // pause
    digitalWrite(37, LOW);    // turn the LED off by making the voltage LOW
    delay(2*h);                       // wait for a second
    
    
  }
}
