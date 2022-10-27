<?php

require "includes.php";

date_default_timezone_set('Asia/Bangkok');
$dateTime = new DateTime();

$db = new Database();
$conn = $db->getConn();

$count = new Count();
$count->time = $dateTime->format('Y-m-d H:i:s');
$count->create($conn);
