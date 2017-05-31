<?php
$dbhost = "localhost";
$dbuser = "root";
$dbpassword = "";
$dbdatabase = "go4shop";
$config_basedir = "http://localhost/site1/go4shop/";
$config_sitename = "Go4Shop";
$db = mysql_connect($dbhost, $dbuser, $dbpassword) or die(mysql_error());
mysql_select_db($dbdatabase, $db) or die(mysql_error());
?>
