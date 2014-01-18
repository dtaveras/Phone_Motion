
int incomingByte = 0;
int led = 9;
void setup()                    // run once, when the sketch starts
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  pinMode(led, OUTPUT);
}

void loop()                       // run over and over again
{
  //Serial.println("Hello world!");  // prints hello with ending line break
  //delay(1000);
  /*for(int load = 0; load < 256; load++)
  {
    //analogWrite(led, load);
    //delay(100);
  }*/
  if(Serial.available() > 0) {
    incomingByte = Serial.read();
    analogWrite(led, 255);
    Serial.print("I received: ");
    if(incomingByte == 'A'){
      Serial.write("got A");
    }
    Serial.write(incomingByte);
  }
}
