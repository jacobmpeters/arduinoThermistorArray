/// Set up temp/hum sht11 sensor
//#include <SHT1x.h>
//// Specify data and clock connections and instantiate SHT1x object
//#define dataPin  10
//#define clockPin 11
//SHT1x sht1x(dataPin, clockPin);
////////////////////////////////

// define truth table for mux
int addressTable[][3] = {
  {LOW , LOW , LOW },
  {HIGH, LOW , LOW},
  {LOW , HIGH, LOW },
  {HIGH , HIGH, LOW},
  {LOW, LOW , HIGH },
  {HIGH, LOW , HIGH},
  {LOW, HIGH, HIGH },
  {HIGH, HIGH, HIGH}
};

// define board select table
int boardSelect[] = {3, 4, 5, 6};

// define pin select table
int pinSelect[] = {0, 1, 2, 3};

void setup() {
  pinMode(A0, INPUT); pinMode(A1, INPUT); pinMode(A2, INPUT); pinMode(A3, INPUT); // set pin modes
  //pinMode(0, OUTPUT); pinMode(1, OUTPUT); pinMode(2, OUTPUT);
  pinMode(3, OUTPUT); pinMode(4, OUTPUT); pinMode(5, OUTPUT); pinMode(6, OUTPUT);
  pinMode(7, OUTPUT); pinMode(8, OUTPUT); pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
//  ///sht11 stuff
//  float temp_c; 
//  float humidity; 
//    // Read values from the sensor
//  temp_c = sht1x.readTemperatureC();
//  humidity = sht1x.readHumidity();
//  ////

  String current_data_string = ""; //predefine current_data_string (which will be redefined each iteration with data)
  String running_data_string = ""; //predefine running_data_string (which will be used to concatenate a list of data
                                   //for entire loop)

  // set all board select pins to LOW (disabled) initially
  for (int i = 0; i <= 3; i++) {
    digitalWrite(boardSelect[i], LOW);
  }

  delay(5);

  // loop through boards and enable them one at a time
  for (int thisBoard = 0; thisBoard <= 3; thisBoard++) {
    digitalWrite(boardSelect[thisBoard], HIGH); //enable board
    delay(5);
    // loop through thermistors
    for (int thisPin = 0; thisPin <= 7; thisPin++) {

      // select MUX input pin
      digitalWrite(7, addressTable[thisPin][0]); // select channel using address table
      digitalWrite(8, addressTable[thisPin][1]);
      digitalWrite(9, addressTable[thisPin][2]);

      // read MUX output and store it in string
      current_data_string = String(analogRead(pinSelect[thisBoard]));

      // check if the list (running_data_string) has a value yet.. if not, do not add comma
      if (running_data_string.length() < 2) {
        running_data_string = String(running_data_string + current_data_string);
      }
      else { // if the list has data already, add a comma between old data and new data
        running_data_string = String(running_data_string + "," + current_data_string);
      }

      delay(5);

    }

    //disable current board
    digitalWrite(boardSelect[thisBoard], LOW);

  }
  running_data_string = String("thermistorMUX_B," + running_data_string);
  Serial.println(running_data_string);
//  Serial.print(',');
//  Serial.print(temp_c);
//  Serial.print(',');
//  Serial.println(humidity);
  delay(50);

}



