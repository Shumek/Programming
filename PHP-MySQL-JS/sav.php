<?
header("Content-type: text/html; charset=utf-8");
header("Location: gb.php");
require_once "gbook.lib";
$name=trim($name);
$msg=trim($msg);
$id=trim($id);
gbook_init();
if(!$id) echo("Ошибка");
if(!$name || !$msg) echo("Поля <b>Имя</b> и <b>Сообщение</b> должны быть заданы");
// Обновим запись
mysql_query("update com set name='$name', msg='$msg'
 where id=$id");
?>