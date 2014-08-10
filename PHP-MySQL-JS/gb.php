<?php
session_start();
header("Content-type: text/html; charset=utf-8");
header ("Cache-control: no-cache");	
include ("dbconnect.php");
?>
<html>
<head>
<link rel="stylesheet" href="css/ui-lightness/jquery-ui-1.10.1.custom.css" />
  <script src="js/jquery-1.9.1.js"></script>
  <script src="js/jquery-ui-1.10.1.custom.js"></script>
  <link rel="stylesheet" href="/resources/demos/style.css" />
  <script>
  $(function() {
    $( "#dialog" ).dialog({
      autoOpen: false,
      show: {
        effect: "blind",
        duration: 1000
      },
      hide: {
        effect: "explode",
        duration: 2000
      }
    });
 
    $( "#opener" ).click(function() {
      $( "#dialog" ).dialog( "open" );
    });
  });
  </script>
  <title>Форум</title>
  <meta http-equiv=Content-Type content="text/html; charset=utf-8">
</head>

<body>
	<table border="0">
	<tr >
		<td width="100%" colspan="3">
		<img align="middle-right"  width="1920"  src="123.jpg">
		</td>
	</tr>
	<tr>
		<td width="300px" rowspan="2" align="top"></td>
		<td>
		<BR><BR><BR>
		<?php
if (empty ($_SESSION['email'])){
 die("Не верный Логин или Пароль");
}
echo ("<h2>Привет, ". $_SESSION["email"]."</h2>");
echo ("<a href=\"exit.php\">[Выйти]</a>");
?>
		<h1 align="center">Форум</h1>

<div id="messages">	</div>
<br>
<script>
</script>
<div id="dialog" title="Новое сообщение" class="bs1">
<form id="myForm">
<table border="0" width="100%" height="100%">
	<tr>
		<td width="160">
			Город:
		</td>
		<td>
			<input id="city" name="city" style="width: 200px;">
		</td>
	</tr>
	<tr>
		<td width="100">
			Оценка хамла:
		</td>
		<td>
	<input type="radio" name="rad" value="1" id="rad">1
	<input type="radio" name="rad" value="2" id="rad">2
	<input type="radio" name="rad" value="3" id="rad">3
	<input type="radio" name="rad" value="4" id="rad">4
	<input type="radio" name="rad" value="5" id="rad">5
				</td>
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
			<input id="btn" type="submit" value="Отправить сообщение">
		</td>
	</tr>
</table>
</form>
</div>
<button id="opener">Добавить сообщение</button>
<script>


	function splash()
	{
		if (document.myForm.city.value  =='')
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
			url: "show.php",
			cache: false,
			success: function(html){
				$("#messages").html(html);
			}
		});
	}
		
	$(document).ready(function(){

		show_messages();
		
		$("#myForm").submit(function(){
		
			var name = $("#city").val();
			var msg  = $("#msg").val();
			var rad = $("#rad").val();
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
				url: "action.php",
				data: "city="+name+"&msg="+msg+"&rad="+rad+"&action=add",
				success: function(msg){
					show_messages();
			   }
			});
			
			return false;
		});
		
	});
	

</script>	


		</td>
</td>
		<td width="300px"  rowspan="2">
		</td>
	</tr>	
	<tr>
		
	</tr>
	<tr>
		<td colspan="3" height="50px"></td>
	</tr>	
	</table>
	</body>


</html>