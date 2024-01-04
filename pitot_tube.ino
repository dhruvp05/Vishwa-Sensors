int Voutplus = 14;
int Voutminus = 15;
float millivolt_out;
float pressure_kPa;
float speed;
int digital_value;
int a;
int b;

void setup() {
  pinMode(Voutplus,INPUT);
  pinMode(Voutminus,INPUT);
  Serial.begin(9600);
}

void loop() {
  a = analogRead(Voutplus);
  b = analogRead(Voutminus);
  digital_value = abs(b-a);
  millivolt_out = ((digital_value/1023)*3.3)*1000;
  pressure_kPa = (2*millivolt_out - 40)/7;
  speed = sqrt((2*pressure_kPa*1000)/1.193);
  Serial.println(digital_value);
}
