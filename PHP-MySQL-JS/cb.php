<?php
session_start();
header("Content-type: text/html; charset=utf-8");
header ("Cache-control: no-cache");	
include ("dbc.php");
$idc=trim($id);
setcookie("idc", $idc, time() + 3600*24); 
?>
<html>
<head>
<link rel="stylesheet" href="css/ui-lightness/jquery-ui-1.10.1.custom.css" />
  <script src="js/jquery-1.9.1.js"></script>
  <script src="js/jquery-ui-1.10.1.custom.js"></script>
  <link rel="stylesheet" href="/resources/demos/style.css" />
  <title>Форум</title>
</head>
<body>
		<?php
if (empty ($_SESSION['email'])){
 die("Попытка взлома!");
}
echo ("<h2>Привет, ". $_SESSION["email"]."</h2>");
echo ("<a href=\"exit.php\">[Выйти]</a>");
?>
		<h1 align="center">Коментари</h1>

<div id="messages">	</div>
<br>
<script>
</script>
<form id="myForm">
<table>
	<tr>
		<td width="160">
			Имя:
		</td>
		<td>
			<input id="name" name="name" style="width: 200px;">
		</td>
	</tr>
	<tr>
	<tr>
		<td width="160" valign="top">
			Сообщение:
		</td>
		<td>
			<textarea id="msg" name="msg" style="width: 300px;"></textarea>
		</td>
	</tr>		
	<tr>
		<td width="160">
			&nbsp;
		</td>
		<td>
			<input type=hidden name=idc id="idc" value=<?=$idc?>>
			<input id="btn" type="submit" value="Отправить сообщение">
			<a href="gb.php">На главную</a>
		</td>
	</tr>
</table>
</form>

<script>
	function splash()
	{
		if (document.myForm.name.value  =='')
			{
				alert ("Заполните строку Город!");
				return false;	
			}
			
		if (document.myForm.msg.value  =='')
			{
				alert ("Заполните текст сообщения!");
				return false;	
			}
		
		return true;   
	}

	function show_messages()
	{
		$.ajax({
			url: "sh.php",
			cache: false,
			success: function(html){
				$("#messages").html(html);
			}
		});
	}
		
	$(document).ready(function(){

		show_messages();
		
		$("#myForm").submit(function(){
		
			var name = $("#name").val();
			var msg  = $("#msg").val();
			var idc = $("#idc").val();
			if (name =='')
			{
				alert ("Заполните строку Город!");
				return false;
			}
			if (msg =='')
			{
				alert ("Заполните текст сообщения!");
				return false;
			}

			$.ajax({
				type: "POST",
				url: "act.php",
				data: "name="+name+"&msg="+msg+"&idc="+idc+"&action=add",
				success: function(msg){
					show_messages();
			   }
			});
			
			
			return false;
		});
		
	});
	

</script>	

	</body>


</html>