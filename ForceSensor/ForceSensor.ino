float cf = 19.5; // caliberation factor

int ffs1 = A0; // FlexiForce sensor is connected analog pin A0 of arduino or mega. 

int ffsdata = 0; 
float vout; 
void setup()
{
  Serial.begin(9600); 
  pinMode(ffs1, INPUT); 
  
}

void loop()
{
 

 ffsdata = analogRead(ffs1);
vout = (ffsdata * 5.0) / 1023.0; 
vout = vout * cf ; 
//Serial.print("Flexi Force sensor: "); 
Serial.print(vout,3); 
Serial.println(""); 
delay(100); 
  
}
