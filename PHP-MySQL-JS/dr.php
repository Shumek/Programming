<?php
header("Location: gb.php");
include ("dbconnect.php");
header("Content-type: text/html; charset=utf-8");
$id=trim($id);
if(!$id) error("Незадан идентификатор удаляемого собщения<b>id</b>");
mysql_query("delete from com where id=$id");
?>