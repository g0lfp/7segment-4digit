/*
 * 4 DIGIT 7 SEGMENT DISPLAY WITH MULTIPLEXING.
 * by G0LFP
 * 
 * The bit pattern for the numbers, and the pin configurations are stored in arrays. 
 * I looked at several examples on the web, some of them looked quite laborious, with separate funtions
 * for each digit.  
 */



char digit[] {0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
// Where lsb is segment 'a' and msb is dp.

int pin[] {2,3,4,5,6,7,8,9};  // {a,b,c,d,e,f,g,dp}
int common[] {A0,A1,A2,A3}; // To save confusion, the running order is Units,Tens,Hundreds,Thousands

int segment,pos,i,j,k,l,n;
int tempDigit;
String number,m;
long start;

void setup() 
{
 
  // Set all the segment/common pins to outputs 
  for (segment=0; segment<8; segment++)
  {
    pinMode(pin[segment], OUTPUT);
    digitalWrite(pin[segment], HIGH);
  }
 for (pos=0; pos<4; pos++)
  {
    pinMode(common[pos], OUTPUT);
    digitalWrite(common[pos], HIGH);
  }
  Serial.begin(9600); // for debugging..  
  start = millis();   //  the initial timer datum
}

void loop() 
{

  // 3 second refresh, make a new random. 0-9999, then reset the timer.
  if  (start+3000 < millis()) 
    {
      l=random(9999);
      start = millis();
      number = String(l); // convert to string to 'chop up'
    }
  
  
  // Loop through the digits. 
  for (k=0;k<number.length();k++)
  {
   n= number.length()-k-1;        //find the length (n is number of digits used) and leave the unused digits blank
   digitalWrite(common[n],LOW); 
  
    m = number[k];
    i = m.toInt();
 
 
  // loop the bits
  
  tempDigit = digit[i];
  for (segment=0;segment<8;segment++)
  {    
    if (tempDigit & 1)
    {
      digitalWrite(pin[segment],HIGH);
    }
    else
    {
      digitalWrite(pin[segment],LOW);
    }
    tempDigit = tempDigit >> 1;    
  }
    
  delay(3);       // short delay, leave the digit on long enough to stop ghosting
  digitalWrite(common[n],HIGH);
  delay(3);       // but not too long as to cause the display to flicker.
 }
  
}
