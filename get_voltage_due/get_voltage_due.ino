// For the Arduino DUE
// NOTE - can use double instead of float to increase the precision/ num of d.p beyond 6 if needed

// Read output voltage from the AD8317 
#define v_max 3.3   // due uses 3.3V reference, only ref thats supported
#define v_min 0
#define v_out_pin A2 // e.g v_out connected to A2 on the due

void setup() {
    analogReadResolution(12);     // use max (12-bit) ADC resolution
    Serial.begin(9600); // set baud rate
}
void loop() {
  // To return a value from 0 -> 2^12-1 (4095)
  float adc_reading = analogRead(v_out_pin);     // e.g v_out connected to A0
  
  float v_range = v_max - v_min; 
  float v_out = (adc_reading/4095.000000) * v_range;
  
  Serial.print(v_out, 6);
  Serial.print("\n");
  delay (100);
}
