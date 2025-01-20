<?php
// TODO
// Add comments
// Add header

$subnetArr = [];

$file = fopen("IP_file.txt", "r") or die("Unable to open origin file!");
$iplist = fread($file, filesize("IP_file.txt"));
fclose($file);

$ipArr = explode("\n", $iplist);
array_pop($ipArr);

if($ipArr){
    foreach ($ipArr as &$ip) {
        $ip = explode("/", $ip);
        $ip[2] = str_replace("\r", "", $ip[2]);
    }
    unset($ip);
    
    for($i = 0; $i < count($ipArr); $i++){
        $dd_mask = -1 << (32 - $ipArr[$i][1]);
        $network_address = ip2long($ipArr[$i][0]) & $dd_mask;
        $network_address = long2ip($network_address);
        $tempArr[0] = $ipArr[$i][2];
        $tempArr[1] = $ipArr[$i][0];
        $subnetArr[$network_address][] = $tempArr;
    }
}else{
    die("The opened file was empty!");
}

$file = fopen("Subnets.txt", "w") or die("Unable to open end file!");

foreach($subnetArr as $key => $subnet){
    fwrite($file, $key . ":\n");
    foreach($subnet as $subnetPos){
        fwrite($file, $subnetPos[0] . ": " . $subnetPos[1] . "\n");
    }
    fwrite($file, "\n");
}

fclose($file);