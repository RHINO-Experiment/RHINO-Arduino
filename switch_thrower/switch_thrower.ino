
  // Switching Code 

  //========================================================================================================


  // Definitions ------------------------------------------------------------------------------------------

  #define tw1_A 39    // A and B for the first two way switch
  #define tw1_B 41

  #define tw2_A 43    // A and B for the second two way switch
  #define tw2_B 45

  #define ew_A 47     // A, B and C for the eight way switch
  #define ew_B 49
  #define ew_C 51

  // Classes -------------------------------------------------------------------------------------------------

  class EightWaySwitch {
  
    public:

      EightWaySwitch(int pinA, int pinB, int pinC);
      void setSwitchState(int z);     // set switch state
      
    private:
      int _pinA, _pinB, _pinC;        // store the pins used by the switch object

  };

  EightWaySwitch::EightWaySwitch(int pinA, int pinB, int pinC){   // constructor
    _pinA = pinA;
    _pinB = pinB;
    _pinC = pinC;

    pinMode(_pinA, OUTPUT);
    pinMode(_pinB, OUTPUT);
    pinMode(_pinC, OUTPUT);
  }

  void EightWaySwitch::setSwitchState(int z) {    // this switch statement implements the HMC523 truth table


      switch(z) {

        case 1:     // RF 1
        digitalWrite(_pinA, LOW);
        digitalWrite(_pinB, LOW);
        digitalWrite(_pinC, LOW);
        Serial.print("EWS State: 1 \n");
        break; 

        case 2:      // RF 2
        digitalWrite(_pinA, HIGH);
        digitalWrite(_pinB, LOW);
        digitalWrite(_pinC, LOW);
        Serial.print("EWS State: 2 \n");
        break;

        case 3: // RF 3
        digitalWrite(_pinA, LOW);
        digitalWrite(_pinB, HIGH);
        digitalWrite(_pinC, LOW);
        Serial.print("EWS State: 3 \n");
        break;

        case 4: // RF 4
        digitalWrite(_pinA, HIGH);
        digitalWrite(_pinB, HIGH);
        digitalWrite(_pinC, LOW);
        Serial.print("EWS State: 4 \n");
        break;

        case 5: // RF 5
        digitalWrite(_pinA, LOW);
        digitalWrite(_pinB, LOW);
        digitalWrite(_pinC, HIGH);
        Serial.print("EWS State: 5 \n");
        break;

        case 6:   // RF 6
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

        default:
        Serial.print("EWS State: Invalid \n");
        break;
      }

  }

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

  void TwoWaySwitch::setSwitchState(int y) {
    
    switch (y){

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

      default:
      Serial.print("TWS State: Invalid \n");
      break;

    }
  }

  // Objects --------------------------------------------------------------------------------------------------

  TwoWaySwitch tw1(tw1_A,tw1_B);
  TwoWaySwitch tw2(tw2_A,tw2_B);
  EightWaySwitch ew1(ew_A, ew_B, ew_C);

  // Setup -------------------------------------------------------------------------------------------------

  void setup() {        // serial starts
                        
    Serial.begin(115200); // 9600. /115200
    Serial.println("Initialising Switch Thrower");
    Serial.print("\n");

  }

  // Main ---------------------------------------------------------------------------------------------------

  void loop() {

    // taking user input - storing as serialInput
    String serialInput = ""; //empty string to store user input
    if (Serial.available() > 0) {           // if data recieved from serial
      serialInput = Serial.readStringUntil('\n');

    if (serialInput.length() < 6) {
     Serial.println("Invalid input length");
     return; 
    }   

//read data until newline, store as serial input
      Serial.print("Input: ");                      //print this
      Serial.print(serialInput);
      Serial.print("\n");

    // serialIn is going to be of form txtyez, need to seperate

    String tws1 = serialInput.substring(0,2); // tws1 is the first two way switch
    String tws2 = serialInput.substring(2,4); //tws2 is second two way switch
    String ews = serialInput.substring(4,6); // ews is eight way switch

    // convert the number in each substring into an integer and pass it to the relevant objects

    int x = tws1[1] - '0';  
    int y = tws2[1] - '0';      // converts between ascii numerical value to actual integer numerical value
    int z = ews[1] - '0';  

    Serial.print(x);
    Serial.print(y);
    Serial.print(z);
    Serial.print("\n");

    tw1.setSwitchState(x);
    tw2.setSwitchState(y);    //set switch state for the switches 
    ew1.setSwitchState(z);

    }
  }
