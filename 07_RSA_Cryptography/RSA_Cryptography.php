<?php
//TODO
//Redo the entire thing

// Author: Janis Diehl
// Created:
// Purpose: A proof of concept to encode a message via RSA encryption.
// Problems: Due to my not-very-optimized approach to this project, it takes quite a while to calculate everything if you're using higher primes.
// For this reason i have limited the primes to 1000 and below.
// Secondly, this version of the code can only encript numbers and probably only up to a certain size.
// In a future version this entire thing will be redone so the user can choose between key generation, encryption and decryption.
// At that point the program will be able to handle alphanumeric input and hopefully will be able to handle larger primes
// without taking so long.


//gcd function copied from bigkm1@gmail.com on https://www.php.net/manual/en/function.gmp-gcd.php
//Returns the greatest common divisor of the two parameters
function gcd($a,$b) {
    return ($a % $b) ? gcd($b,$a % $b) : $b;
}

//Generates the first part of the public key
//using the formula gcd(fn, e) = 1 where 1 < e < fn
//calculates each possible value for e and chooses a random one
function generateEncKey($fn){
    $index = 0;
    for($eTemp = 2; $eTemp < $fn; $eTemp++){
        if(gcd($fn, $eTemp) == 1){
            $eIndex[$index] = $eTemp;
            $index++;
        }
    }
    $e = $eIndex[random_int(0, sizeof($eIndex)-1)];
    
    return $e;
}

//Generates the first part of the private key
//using the formula (e * d) mod fn = 1
//calculates each possible value for e and chooses a random one
function generateDecKey($e, $fn){
    $index = 0;
    for($dTemp = 1; $dTemp < $fn; $dTemp++){
        if(($e*$dTemp) % $fn == 1){
            $dIndex[$index] = $dTemp;
            $index++;
        }
    }
    $d = $dIndex[random_int(0, sizeof($dIndex)-1)];
    
    return $d;
}

//Encodes or decodes a given message m
//using the formula: mv = (m ^ key1) mod n
//key1 uses e for encoding or d for decoding 
function cryption($m, $key1, $n){
    $mTemp = $m;
    for($i = 0; $i < $key1-1; $i++){
        $mTemp = $mTemp * $m % $n;
    }
    return $mTemp;
}

//Function slightly adapted from https://www.geeksforgeeks.org/php-program-to-print-prime-number-from-1-to-n/
function isPrime($number){
    if($number % 2 == 0 || $number % 3 == 0){
        return false;
    }

    for($div = 5, $step = 2; $div * $div <= $number; $div += $step, $step = 6 - $step){
        if($number % $div == 0){
            return false;
        }
    }
    
    return true;
}


//Generates all primes within the given range and returns a random one.
//The larger the prime, the more secure the encryption will be
//To stay within the range of an integer, the largest possible prime is 46337 (<46340).
function primeGenerator($range, $max){
    $index = 0;
    for($i = $max - $range; $i <= $max; $i++){
        if(isPrime($i)){
            $primeIndex[$index] = $i;
            $index++;
        }
    }
    $prime = $primeIndex[random_int(0, sizeof($primeIndex)-1)];
    
    return $prime;
}

//Main

//$max = 46340;
$max = 1000;

$range = readline("Please enter the range in which the primes will be generated (min 100/max $max): ");

if($range < 100){
    $range = 100;
}elseif ($range > $max) {
    $range = $max;
}

echo "The primes will be generated between " . ($max - $range) . " and " . $max . "\n";

do{
    $p = primeGenerator($range, $max);
    $q = primeGenerator($range, $max);
}while($p==$q);

echo "-Primes generated-\n\n";
var_dump($p);
var_dump($q);
$n = $p * $q;
$fn = ($p - 1) * ($q - 1);

echo "-Generating Public Key-\n";
//echo "-Please be patient as this may take a while-\n";
$pubKey = [generateEncKey($fn), $n];
echo "Public Key: {" . $pubKey[0] . ", " . $pubKey[1] . "}\n";

echo "-Generating Private Key-\n";
//echo "-Please be patient as this may take a while-\n";
$privKey = [generateDecKey($pubKey[0], $fn), $n];
echo "Private Key: {" . $privKey[0] . ", " . $privKey[1] . "}\n";

$input = readline("Message: ");
echo "Encoded: " . cryption($input, $pubKey[0], $pubKey[1]) . "\n";

$decode = readline("Encrypted Message: ");
echo "Decoded: " . cryption($decode, $privKey[0], $privKey[1]) . "\n";
?>
