<?php
// TODO
// Add header

require_once "PhpSerial.php";

$brailleArr = ["a" => [1,0,0,0,0,0], "b" => [1,1,0,0,0,0], "c" => [1,0,0,1,0,0], "d" => [1,0,0,1,1,0], "e" => [1,0,0,0,1,0], "f" => [1,1,0,1,0,0],
                "g" => [1,1,0,1,1,0], "h" => [1,1,0,0,1,0], "i" => [0,1,0,1,0,0], "j" => [0,1,0,1,1,0], "k" => [1,0,1,0,0,0], "l" => [1,1,1,0,0,0],
                "m" => [1,0,1,1,0,0], "n" => [1,0,1,1,1,0], "o" => [1,0,1,0,1,0], "p" => [1,1,1,1,0,0], "q" => [1,1,1,1,1,0], "r" => [1,1,1,0,1,0],
                "s" => [0,1,1,1,0,0], "t" => [0,1,1,1,1,0], "u" => [1,0,1,0,0,1], "v" => [1,1,1,0,0,1], "w" => [0,1,0,1,1,1], "x" => [1,0,1,1,0,1],
                "y" => [1,0,1,1,1,1], "z" => [1,0,1,0,1,1]];
/*
The array is translated according to this schema
1 4
2 5
3 6

Therefore "b" => [1,1,0,0,0,0]
becomes:
1 0
1 0
0 0
*/

//
echo("Bitte geben sie einen Text ein,der nur aus den Buchstaben a-z ohne Sonderzeichen besteht\n");
$input = strtolower(readline());
$input = str_split($input);

foreach($input as &$char){
    $char = $brailleArr[$char];
}

//JSONify the array for ease of transfer
$jsonData = json_encode($input);

//Create connection to Arduino through serial port
//Adjustments might need to be made here (This part was created with help from ChatGPT)
// Create a new instance of PhpSerial
$serial = new PhpSerial();

// Specify the serial port and configure it
$serial->deviceSet("COM3");
$serial->confBaudRate(9600);
$serial->confParity("none");
$serial->confCharacterLength(8);
$serial->confStopBits(1);
$serial->confFlowControl("none");

// Open the serial port
$serial->deviceOpen();

// Write data to the port
$serial->sendMessage($jsonData);

// Close the port
$serial->deviceClose();
echo("Data sent to Arduino.\n");
?>