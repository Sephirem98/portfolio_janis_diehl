<?php
// TODO
// Translate all outputs
// Add comments

// Author: Janis Diehl
// Created: November 2024
// Purpose: Translating a decision table from a cvs file to usable PHP code
// Problems:

function input(){
    $csvfileArr = glob("Decisiontables/*.csv");

    if($csvfileArr){
        echo("Bitte wählen Sie den Namen der .csv Datei aus, die Sie öffnen möchten.\n");
    
        for($fileNr = 1; $fileNr <= count($csvfileArr); $fileNr++){
            echo("$fileNr. " . str_replace("Decisiontables/", "", $csvfileArr[$fileNr - 1]) . "\n");
        }
        echo("0. Verlassen\n");
        $choice = filter_var(readline(), FILTER_VALIDATE_INT, array('options' => array('default' => 0, 'min_range' => 0, 'max_range' => count($csvfileArr))));
    }else{
        echo("Es befinden sich keine .csv Dateien im Ordner Entscheidungstabellen.\n");
        $choice = 0;
    }

    if($choice){
        return ($csvfileArr[$choice - 1]);
    }else{
        return false;
    }
}

function readCSVfile($file){
    $csvfile = fopen($file, "r");
    //bom = Byte Order Mark
    $bom = fread($csvfile, 3);
    if ($bom !== "\xEF\xBB\xBF") {
        rewind($csvfile); // Reset pointer if no BOM
    }
    for($filerow = 0; ($data[$filerow] = fgetcsv($csvfile, 0, ";"))!==false; $filerow++);
    array_pop($data);
    fclose($csvfile);

    return $data;
}

function validateCSV($dataArr){
    //check if given conditions count equals actual condition count
    if($dataArr[$dataArr[0][0]+1][0] != "StartActions")
        return 1;

    //check if the table has the correct amount of columns
    if(count($dataArr[0]) != (2**$dataArr[0][0])+1)
        return 2;

    for($row = 0; $row < count($dataArr); $row++){
        //check if each row has all values
        for($column = 0; $column < count($dataArr[$row]); $column++){
            if($dataArr[$row][0] != "StartActions" && $dataArr[$row][$column] == ""){
                return 3;
            }
        }

        if($row <= $dataArr[0][0]){
            //check if conditions are variables
            if($dataArr[$row][0][0] != "$" && $row >= 1)
                return 4;

        }elseif($row > $dataArr[0][0]+1){
            //check if actions are functions
            //THIS MIGHT NEED A REWORK TO ACCOUNT FOR PARAMETERS!!!!!!!!
            if(substr($dataArr[$row][0], -2) != "()")
                return 5;
        }
    }
    //check if all functions are unique
    for($column = 1; $column < count($dataArr[0]); $column++){
        $rules[] = "";
        for($row = 1; $row <= $dataArr[0][0]; $row++){
            $rules[$column-1] .= $dataArr[$row][$column];
        }
    }
    if(array_unique($rules) != $rules){
        unset($rules);
        return 6;
    }
    unset($rules);
    return $dataArr;
}

function compileCSVtoPHP($dataArr){
    if(gettype($dataArr = validateCSV($dataArr)) == "array"){
        $output = [];
        for($column = 1; $column < count($dataArr[0]); $column++){
            $output[$column-1] = "if(";
            for($row = 1; $row < count($dataArr); $row++){
                if($row <= (int)$dataArr[0][0]){
                    $output[$column-1] .= ($dataArr[$row][$column] ? "" : "!") . $dataArr[$row][0] . " && ";
                }elseif($row == (int)$dataArr[0][0]+1){
                    $output[$column-1] = substr_replace($output[$column-1], "){\n", -4);
                }else{
                    if($dataArr[$row][$column]){
                        $output[$column-1] .= "    " . $dataArr[$row][0] . ";\n";
                    }
                }
            }
            if(substr_count($output[$column-1], "\n")<=1){
                unset($output[$column-1]);
            }else{
                $output[$column-1] .= "}\n";
            }
        }
        $output = array_values($output);
        return $output;
    }else{
        switch ($dataArr) {
            case '1':
                return "Der Beginn der Aktionen in Spalte A konnte nicht gefunden werden.\n" . 
                        "Dieser sollte mit 'StartActions markiert sein.\n";
                break;

            case '2':
                return "Die Entscheidungstabelle hat nicht die korrekte Anzahl an Spalten.\n" .
                        "Die Tabelle sollte (2^n)+1 Spalten haben, wobei n die Anzahl der Regeln ist.\n";
                break;
                
            case '3':
                return "Eine oder mehrere Zeilen haben fehlende Werte.\n";
                break;

            case '4':
                return "Eine oder mehrere Regeln haben eine falsche Nomenklatur.\n" .
                        "Jede Regel sollte einen Variablennamen beginnend mit '$' haben.\n";
                break;

            case '5':
                return "Eine oder mehrere Aktionen haben eine falsche Nomenklatur.\n" .
                        "Jede Aktion sollte ein Funktionsaufruf sein und mit '()' enden (Parameter werden derzeit nicht unterstützt).\n";
                break;
            
            case '6':
                return "Eine oder mehrere Regeln kommen doppelt vor.\n";
                break;

            default:
                return "Die ausgewählte Datei entspricht nicht dem erwarteten Schema.\n";
                break;
        }
    }
}

if(!is_dir("Decisiontables")){
    mkdir("Decisiontables");
}

if($file = input()){
    $dataArr = readCSVfile($file);
    $output = compileCSVtoPHP($dataArr);
    if(gettype($output) == "string"){
        echo($output);
    }elseif(gettype($output) == "array"){
        foreach($output as $line){
            echo($line);
        }
    }else{
        echo("Error: fehlerhafte Datenübergabe in compileCSVtoPHP().\nBitte kontaktieren sie den Author: janis.diehl@live.de\n");
    }
    
}else{
    echo("Auf Wiedersehen.\n");
}


?>