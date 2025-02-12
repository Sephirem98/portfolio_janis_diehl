#include <ArduinoJson.h>

// Author: Janis Diehl
// Created: December 2024
// Purpose: Display braille letters on a 3x2 LED Matrix
// Usage: As soon as the serial monitor displays the connection confirmation,
// the user can input a 2D array of bits. Each second dimension array is made up of 6 bits.
// Example:[[1,1,0,0,1,0], [0,1,0,0,1,1]]
// The six digits represent each position of a braille letter like this:
// 0  3
// 1  6
// 2  5
// and are put out through the following pin numbers:
// 2  5
// 3  6
// 4  7

const int ledPins[] = {2, 3, 4, 5, 6, 7};
int** ledState;
size_t numRows = 0;

void setup(){
  Serial.begin(9600);
  while(!Serial){
    // Wait for connection
  }
  Serial.println("\nConnection established\nWaiting for input\n");
  while(!Serial.available()){
    // Wait for input
  }
  ledState = processInput();

  for(int i = 0; i < 6; i++){
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop(){
  // Iterate through ledState and output each Braille char one by one
  showBrailleText(ledState);

  hold(3000);
  
  resetLEDs();
}

bool hold(int time){
  // Alternative for delay to not miss any input
  for(int i = 0; i < time; i++){
    if(Serial.available()){
      ledState = processInput();
      return true;
    }
    delay(1);
  }
  return false;
}

int** processInput(){
  // Receive Data from Serial (Later from PHP Script)
  // and turn that into a JSON Document
  DynamicJsonDocument doc = readFromSerial();

  // Turn JSON Document into a 2D array
  ledState = translateJSONtoArr(doc);

  return ledState;
}

DynamicJsonDocument readFromSerial(){
  // Read from Serial input until closing brackets of 2D array are found
  String jsonData = Serial.readStringUntil("]]");
  flush();

  // Dynamically allocate memory
  DynamicJsonDocument doc(jsonData.length() * 2);

  DeserializationError error = deserializeJson(doc, jsonData);
  if(error){
    Serial.println("Json could not be read correctly\n");
  }

  // Optional debug output
  debugCheckJSON(doc);
  
  return doc;
}

void flush(){
  while(Serial.available()){
    Serial.read();
  }
}

void debugCheckJSON(DynamicJsonDocument doc){
  // Print all bits of the array
  for(JsonArray row : doc.as<JsonArray>()){
    for(int bit : row){
      Serial.print(bit);
      Serial.print(" ");
    }
    Serial.print(" ");
  }
  Serial.print("\n");
}

int** translateJSONtoArr(DynamicJsonDocument doc){
  JsonArray outerArr = doc.as<JsonArray>();

  // Dynamically allocate memory for the 2D array
  numRows = outerArr.size();
  int** ledState = new int*[numRows];

  size_t rowIndex = 0;

  // Iterates through the JsonArray to create the second dimension arrays
  // and set their values
  for(JsonArray row : outerArr){
    ledState[rowIndex] = new int[6];

    size_t colIndex = 0;

    for(int value : row){
      ledState[rowIndex][colIndex++] = value;
    }
    rowIndex++;
  }
  return ledState;
}

void resetLEDs(){
  for(int ledPos = 0; ledPos < 6; ledPos++){
    digitalWrite(ledPins[ledPos], LOW);
  }
}

void showBrailleText(int** ledState){
  //Iterate through each Bit of a Braille Char
  for(int character = 0; character < numRows; character++){
    showBrailleChar(ledState[character]);
    if(hold(1000)){
      return;
    }
  }
}

void showBrailleChar(int ledStateChar[6]){
	for(int ledPos = 0; ledPos < 6; ledPos++){
    digitalWrite(ledPins[ledPos], ledStateChar[ledPos]);
  }
}