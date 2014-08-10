<?php
session_start();
include_once('bd.php');
header("Content-type: text/html; charset=utf-8");
?>
<html>
	<head>
		<title>Востановление пароля</title>
		<meta http-equiv=Content-Type content="text/html; charset=windows-1251">
	</head>
	<body>
	<?php
if (isset($_POST['submit'])){     
	$email = $_POST['email'];
	
	if (empty($email)){
		echo "Введите e-mail!";
	}
   else{
		$resultat = mysql_query("SELECT * FROM users WHERE email = '$email'");
		$array = mysql_fetch_array($resultat);
		if (empty($array)){
			echo 'Ошибка! Такого пользователя не существует';
		}
		elseif (mysql_num_rows($resultat) > 0){
			$chars="qazxswedcvfrtgbnhyujmkiolp1234567890QAZXSWEDCVFRTGBNHYUJMKIOLP"; 
			$max=10; 
			$size=StrLen($chars)-1; 
			$password=null; 
			
			while($max--){
			$password.=$chars[rand(0,$size)]; 
			}
			$newmdPassword = md5($password); 
			$title = 'Востановления пароля пользователю '.$email.' для сайта Site.ru!';
			$headers  = "Content-type: text/plain; charset=windows-1251\r\n";
			$headers .= "Админестрация сайта Site.ru";
			$letter = 	'Вы запросили восстановление пароля для аккаунта '.$email.' на сайте Site.ru \r\nВаш новый пароль: '.$password;

			
			if (mail($email, $title, $letter, $headers)) {
			   mysql_query("UPDATE users SET password = '$newmdPassword' WHERE email = '$email'  AND users.email = '$email'");
			   echo 'Новый пароль отправлен на ваш e-mail!<br><a href="index.php">Главная страница</a>';
			}
		}		
	}
}
mysql_close();
?>
	<table border="0">
	<tr >
		<td width="100%" colspan="3">
		<img align="middle-right"  width="1920" src="123.jpg">
		</td>
	</tr>
	<tr>
		<td width="100px" rowspan="2" ></td>
		
<table align="center">
 
      <form method="POST">
      <tr>
	  <br><br><br>
      <td>E-mail:</td>
      <td><input type="text" size="20" name="email"></td>
      </tr>
      <tr>
       <td></td>
      <td colspan="2"><input type="submit" value="Восстановить пароль" name="submit" ></td>
      </tr>
	 <tr>
     <td><a href="index.php">Главная</a></td>
	 </tr>
      </form>
</table>
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
 