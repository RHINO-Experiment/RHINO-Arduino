// CODE FOR TEMPERATURE SENSOR(s) AND ALL SWITCHES

#include <SPI.h>
#include <Adafruit_MAX31865.h>


// ----------------- PINS & MACROS--------------------------------------------

  // temp sensors
  #define CS_1 37 // for thermo1
  #define CS_2 36 // for thermo2
  #define SDI 34  //shared
  #define SDO 32
  #define CLK 30

  // switches
  #define tw1_A 52      // 1st two-way switch
  #define tw1_B 53

  #define tw2_A 51    // 2nd two-way switch
  #define tw2_B 50

  #define ew_A 48
  #define ew_B 49       // Eight way switch
  #define ew_C 46

#define RREF 4300.0
#define RNOMINAL  1000.0

// -------------- EIGHT WAY SWITCH CLASS -----------------------------------------------

  class EightWaySwitch {

    public: 

      EightWaySwitch(int pinA, int pinB, int pinC);
      void setSwitchState(int z);

    private:
      int _pinA, _pinB, _pinC;

  };

  EightWaySwitch::EightWaySwitch(int pinA, int pinB, int pinC){

    _pinA = pinA;
    _pinB = pinB;
    _pinC = pinC;
    
    pinMode(_pinA, OUTPUT);
    pinMode(_pinB, OUTPUT);
    pinMode(_pinC, OUTPUT);

  }

  void EightWaySwitch::setSwitchState(int z) {

      switch(z) {     // rf com to ...
    
        case 1:        // rf 1
        digitalWrite(_pinA,LOW);
        digitalWrite(_pinB,LOW);
        digitalWrite(_pinC, LOW);
        Serial.print("EWS State: 1 \n");
        break;

        case 2:       //rf 2 etc.
        digitalWrite(_pinA, HIGH);
        digitalWrite(_pinB, LOW);
        digitalWrite(_pinC, LOW);
        Serial.print("EWS State: 2 \n");
        break;

        case 3: 
        digitalWrite(_pinA, LOW);
        digitalWrite(_pinB, HIGH);
        digitalWrite(_pinC, LOW);
        Serial.print("EWS State: 3 \n");
        break;

        case 4: 
        digitalWrite(_pinA, HIGH);
        digitalWrite(_pinB, HIGH);
        digitalWrite(_pinC, LOW);
        Serial.print("EWS State: 4 \n");
        break;

        case 5: 
        digitalWrite(_pinA, LOW);
        digitalWrite(_pinB, LOW);
        digitalWrite(_pinC, HIGH);
        Serial.print("EWS State: 5 \n");
        break;

        case 6: 
        digitalWrite(_pinA, HIGH);
        digitalWrite(_pinB, LOW);
        digitalWrite(_pinC, HIGH);
        Serial.print("EWS State: 6 \n");
        break;

        case 7: 
        digitalWrite(_pinA, LOW);
        digitalWrite(_pinB, HIGH);
        digitalWrite(_pinC, HIGH);
        Serial.print("EWS State: 7 \n");
        break;

        case 8: 
        digitalWrite(_pinA, HIGH);
        digitalWrite(_pinB, HIGH);
        digitalWrite(_pinC, HIGH);
        Serial.print("EWS State: 8 \n");
        break;

      }

  }


// ------------- TWO WAY SWITCH CLASS ----------------------------------

  class TwoWaySwitch {

    public:

      TwoWaySwitch(int pinA, int pinB);
      void setSwitchState(int y);

    private:
      int _pinA, _pinB;
    
  };

  TwoWaySwitch::TwoWaySwitch(int pinA, int pinB){
    _pinA = pinA;
    _pinB = pinB;

    pinMode(_pinA, OUTPUT);
    pinMode(_pinB, OUTPUT);

  }

  void TwoWaySwitch::setSwitchState(int y){

    switch(y){

      case 1: 
        digitalWrite(_pinA, LOW);
        digitalWrite(_pinB, HIGH);
        Serial.print("TWS State: 1 \n");
      break;

      case 2: 
        digitalWrite(_pinA, HIGH);
        digitalWrite(_pinB, LOW);
        Serial.print("TWS State: 2 \n");
      break;

    }

  }


// --------------- THERMO FUNCTION TO READ TEMP -----------------------------

  float read_temperature(Adafruit_MAX31865 thermo){
      
      uint16_t rtd = thermo.readRTD();
      float ratio = rtd;
      ratio /= 32768;
      float temperature = thermo.temperature(RNOMINAL, RREF);

      // Check and print any faults
      uint8_t fault = thermo.readFault();
      if (fault) {
        Serial.print("Fault 0x"); Serial.println(fault, HEX);
        if (fault & MAX31865_FAULT_HIGHTHRESH) {
          Serial.println("Thermo: RTD High Threshold"); 
        }
        if (fault & MAX31865_FAULT_LOWTHRESH) {
          Serial.println("Thermo: RTD Low Threshold"); 
        }
        if (fault & MAX31865_FAULT_REFINLOW) {
          Serial.println("Thermo: REFIN- > 0.85 x Bias"); 
        }
        if (fault & MAX31865_FAULT_REFINHIGH) {
          Serial.println("Thermo: REFIN- < 0.85 x Bias - FORCE- open"); 
        }
        if (fault & MAX31865_FAULT_RTDINLOW) {
          Serial.println("Thermo: RTDIN- < 0.85 x Bias - FORCE- open"); 
        }
        if (fault & MAX31865_FAULT_OVUV) {
          Serial.println("Thermo: Under/Over voltage"); 
        }
        thermo.clearFault();
      }
      return temperature;
  } 


// ---------------------- SETUP ----------------------------------------

  // Initialise temp sensors
  // Use software SPI: CS, SDI, SDO, CLK
  Adafruit_MAX31865 thermo1 = Adafruit_MAX31865(CS_1, SDI, SDO, CLK);   
  Adafruit_MAX31865 thermo2 = Adafruit_MAX31865(CS_2, SDI, SDO, CLK);  

  // Initialise switches
  TwoWaySwitch tw1(tw1_A, tw1_B);
  TwoWaySwitch tw2(tw2_A, tw2_B);
  EightWaySwitch ew1(ew_A, ew_B, ew_C);

  void setup(){

      // Initialise temperature sensors
      thermo1.begin(MAX31865_3WIRE);
      thermo2.begin(MAX31865_3WIRE);

      // start serial
      Serial.begin(9600);
  }


// ---------------------- MAIN -----------------------------------------

void loop() {

  // Read temperature
  float temperature1; // temperature of first sensor
  float temperature2; // temperature of second sensor

  temperature1 = read_temperature(thermo1);
  temperature2 = read_temperature(thermo2);

  // Output temp
  Serial.print("T1:");
  Serial.print(temperature1, 3);
  // Output temp
  Serial.print(",T2:");
  Serial.print(temperature2, 3);
  Serial.print("\n");

    String serialInput = "";
  if (Serial.available() > 0) {

    serialInput = Serial.readStringUntil('\n');    

  int x = -1, y = -1, z = -1;

  sscanf(serialInput.c_str(), "t%d" "t%d" "e%d", &x, &y, &z); 

  tw1.setSwitchState(x);
  tw2.setSwitchState(y);
  ew1.setSwitchState(z);


  }

  delay(100); // May need to tweak - limit loop speed 

}