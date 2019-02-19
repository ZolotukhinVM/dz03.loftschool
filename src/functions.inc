<?php
function task1()
{
    $xmlText = file_get_contents("./data/data.xml");
    $xml = new SimpleXMLElement($xmlText);
    echo "<h1> Purchase order number: " . $xml->attributes()->PurchaseOrderNumber . "</h1>";
    echo "<h2> Order date: " . $xml->attributes()->OrderDate . "</h2>";
    foreach ($xml->Address as $item) {
        echo "<b>Address (Type: " . $item->attributes()->Type . ")</b><br>";
        echo "Name: " . $item->Name . "<br>";
        echo "Street: " . $item->Street . "<br>";
        echo "City: " . $item->City . "<br>";
        echo "State: " . $item->State . "<br>";
        echo "Zip: " . $item->Zip . "<br>";
        echo "Country: " . $item->Country . "<br><br>";
    }
    echo "<hr>";
    echo "Notes: " . $xml->DeliveryNotes;
    echo "<hr>";
    foreach ($xml->Items->Item as $item) {
        echo "<b> Items (Part number: " . $item->attributes()->PartNumber . ")</b><br>";
        echo "Product name: " . $item->ProductName . "<br>";
        echo "Quantity: " . $item->Quantity . "<br>";
        echo "USPrice: " . $item->USPrice . "<br>";
        if (isset($item->ShipDate)) {
            echo "Ship date: " . $item->ShipDate . "<br><br>";
        } else {
            echo "Comment: " . $item->Comment . "<br><br>";
        }
    }
}

function task2(): string
{
    $arTeam = [
        "Anton" => ["City" => "Moscow", "age" => 30],
        "Viktor" => ["City" => "Tashkent", "age" => 33],
        "Ivan" => ["City" => "Biysk", "age" => 27]
    ];
    $output = json_encode($arTeam);
    file_put_contents("./data/output.json", $output);
    if (rand(0, 1) == 1) {
        $arTeam["Anton"]["age"] = rand(1, 100);
        $arTeam["Viktor"]["age"] = rand(1, 100);
        $arTeam["Ivan"]["age"] = rand(1, 100);
        $output2 = json_encode($arTeam);
        file_put_contents("./data/output2.json", $output2);
    }
    $array1 = json_decode(file_get_contents("./data/output.json"), true);
    $array2 = json_decode(file_get_contents("./data/output2.json"), true);
    $result = "";
    foreach ($array1 as $key => $value) {
        if ($array2[$key]["age"] != $value["age"]) {
            $result .= "Элементы с ключами " . $key . " имеют различия <br>";
        }
    }
    return $result;
}

function task3($fileName = "./data/output.csv"): int
{
    $arNumbers = [];
    for ($i = 1; $i <= 50; $i++) {
        $arNumbers[] = rand(1, 100);
    }
    $arList[] = $arNumbers;
    if (!file_exists($fileName)) {
        $fileOpen = fopen($fileName, 'w');
        foreach ($arList as $fields) {
            fputcsv($fileOpen, $fields, ";");
        }
        fclose($fileOpen);
    }
    $csv = file_get_contents($fileName);
    $arNumbersFile = explode(";", $csv);
    $sum = 0;
    foreach ($arNumbersFile as $value) {
        if ($value % 2 == 0) {
            $sum += $value;
        }
    }
    return $sum;
}

function task4(): string
{
    $json = file_get_contents("https://en.wikipedia.org/w/api.php?action=query&titles=Main%20Page&prop=revisions&rvprop=content&format=json");
    $arr = json_decode($json, true);
    $result = "Title: " . $arr["query"]["pages"]["15580374"]["title"] . "<br>";
    $result .= "Page id: " . $arr["query"]["pages"]["15580374"]["pageid"];
    return $result;
}
