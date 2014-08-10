<?php
session_start();
	include ("dbconnect.php");
	
	$city=$_REQUEST['city'];
	$msg=$_REQUEST['msg'];
	$action=$_REQUEST['action'];
	$rad=$_REQUEST['rad'];
	$email = $_SESSION['email'];
	
	if ($action=="add")
	{
		$sql="INSERT INTO mes(city, dt, msg, rad, email) VALUES ('$city', NOW(), '$msg', '$rad', '$email')";
		$r=mysql_query ($sql);
	}
	
	if ($action=="delete")
	{
		$sql="DELETE FROM mes";
		$r=mysql_query($sql);
	}
	
	header("Location: gb.php");
?>