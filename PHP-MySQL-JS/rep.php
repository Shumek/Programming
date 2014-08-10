<? session_start();
include ("dbconnect.php");
header("Content-type: text/html; charset=utf-8");
$id=trim($id);
require_once "gbook.lib";
gbook_init();
if(!$id) error("Не задан идентификатор редактируемого сообщения<b>id</b>");
$r=mysql_query("select id, name, msg from com where id=$id") OR DIE(mysql_error());
if(mysql_num_rows($r)==0) echo("Сообщения с id=$id нет в гостевой таблице");
$f=mysql_fetch_array($r);
$id=($f['id']);
$name=($f['name']);
$msg=($f['msg']);

?>

<html>
	<head>
		<title>Редактирование</title>
		<meta http-equiv=Content-Type content="text/html; charset=windows-1251">
	</head>
	<body>
	<table border="1">
	<tr >
		<td height="700px" width="100%" colspan="3">
		<img align="middle-right"  width="1920" height="100%" src="123.jpg">
		</td>
	</tr>
	<tr>
		<td width="100px" rowspan="2" ></td>
<td rowspan="2" width='600px'>
<?php
if (empty ($_SESSION['email'])){
 die("Попытка взлома!");
}
echo ("<h2>Привет, ". $_SESSION["email"]."</h2>");
echo ("<a href=\"exit.php\">Выйти</a>");
?>
<h3 align=center>Редактирование сообщения</h3>
<form action=sav.php method=post>
<table align=center><a href="cb.php">Назад</a><tr><td>
<table>
<tr>

<th>Имя:</th>
<td><input class=e name=name value='<?=$name?>'></td></tr>
<tr>
<b>Сообщение:</b><br>
<textarea cols=40 rows=10 name=msg><?=$msg?></textarea><br>
</table>
<input type=hidden name=id value=<?=$id?>>
</tr>
<center><input type=submit value='Сохранить'></center>
</form>
		</td>
	</tr>
</table></td>
		<td width="100px"  rowspan="2">
		</td>
	</tr>	
	<tr>
	</tr>
	<tr>
		<td colspan="3" height="50px"></td>
	</tr>
	</body>
	</html>
