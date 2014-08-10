<?php
	session_start();
	include ("dbc.php");
	
	$name=$_REQUEST['name'];
	$msg=$_REQUEST['msg'];
	$action=$_REQUEST['action'];
	$rad=$_REQUEST['rad'];
	$email = $_SESSION['email'];
	$idc=$_POST['idc'];
	
	if ($action=="add")
	{
		$sql="INSERT INTO com (name, dt, msg, email, idc) VALUES ('$name', NOW(), '$msg', '$email', '$idc')";
		$r=mysql_query ($sql);
	}
	
	if ($action=="delete")
	{
		$sql="DELETE FROM com";
		$r=mysql_query($sql);
	}

	header("Location: gb.php");
?>