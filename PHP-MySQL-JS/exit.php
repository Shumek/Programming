<?php session_start();
header("Content-type: text/html; charset=utf-8"); 
include_once("bd.php");
?>
<html>
<head>
<title></title>
</head>
<body>
<?php
if (empty($_SESSION['email']) or empty($_SESSION['password'])) {
	exit ("Доступ на эту страницу разрешен только зарегистрированным пользователям.<br><a href='index.php'>Главная страница</a>");
}

unset($_SESSION['password']);
unset($_SESSION['email']); 
exit("<meta http-equiv='Refresh' content='0; URL=index.php'>");
?>
</body>
</html>
