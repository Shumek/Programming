<?php
mysql_connect ("localhost","root","123");
mysql_select_db ("test");
mysql_query("SET NAMES utf8");

$email = $_SESSION['email'];
$password = $_SESSION['password'];
$code1 = $_SESSION['captcha_keystring'];?>