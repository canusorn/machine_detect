<?php

/**
 * Database
 *
 * A connection to the database
 */
class Database
{
    /**
     * Get the database connection
     *
     * @return PDO object Connection to the database server
     */
    public function getConn()
    {
        $db_host = "localhost";
        $db_name = "icemachine";
        $db_user = "iotadmin";
        $db_pass = "ZSE@iotb";
        $db_port = 33600;

        $dsn = 'mysql:host=' . $db_host . ';dbname=' . $db_name . ';port=' . $db_port . ';charset=utf8';

        try {

            $db = new PDO($dsn, $db_user, $db_pass);
            $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

            return $db;
        } catch (PDOException $e) {
            echo $e->getMessage();
            exit;
        }
    }
}


class Count
{
    public $countNumber;
    public $sensorid;
    public $time;

    public function create($conn)
    {

        $sql = "INSERT INTO count (sensorid,time)
                VALUES(:sensorid, :time)";

        $stmt = $conn->prepare($sql);

        $stmt->bindValue(':sensorid', $this->sensorid, PDO::PARAM_INT);
        $stmt->bindValue(':time', $this->time, PDO::PARAM_STR);

        return $stmt->execute();
    }
}
