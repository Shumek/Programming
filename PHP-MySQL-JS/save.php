<?
header("Content-type: text/html; charset=utf-8");
header("Location: gb.php");
require_once "gbook.lib";
$city=trim($city);
$msg=trim($msg);
$rad=trim($rad);
$id=trim($id);
gbook_init();
if(!$id) echo("Ошибка");
if(!$city || !$msg) echo("Поля <b>Город</b> и <b>Сообщение</b> должны быть заданы");
// Обновим запись
mysql_query("update mes set city='$city', msg='$msg',
  rad='$rad' where id=$id");
?>