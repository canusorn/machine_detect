<?php

require "includes.php";

date_default_timezone_set('Asia/Bangkok');
$dateTime = new DateTime();

$db = new Database();
$conn = $db->getConn();

$count = new Count();
if(isset($_REQUEST['id'])){
    $count->sensorid = $_REQUEST['id'];
}

$count->time = $dateTime->format('Y-m-d H:i:s');

$count->create($conn);
