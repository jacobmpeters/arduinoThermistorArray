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

  for (int i = 0; i <= 3; i++) {// set all board select pins to LOW (disabled) initially
    digitalWrite(boardSelect[i], LOW);
  }

  delay(5);

  for (int thisBoard = 0; thisBoard <= 3; thisBoard++) { //loop through boards
    digitalWrite(boardSelect[thisBoard], HIGH); //enable board
    delay(5);
    for (int thisPin = 0; thisPin <= 7; thisPin++) { // loop through thermistors
      // select MUX input pin
      digitalWrite(7, addressTable[thisPin][0]); // select channel using address table
      digitalWrite(8, addressTable[thisPin][1]);
      digitalWrite(9, addressTable[thisPin][2]);
      // read MUX output
      Serial.print(analogRead(pinSelect[thisBoard])); // read/print data
      Serial.print(',');
      delay(5);
    }
    digitalWrite(boardSelect[thisBoard], LOW); // disable current board
  }
  float time = millis();
  Serial.print(time);
  Serial.print('\n'); // print carriage return
  delay(500);
}



