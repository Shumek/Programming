<?php
session_start();
header("Content-type: text/html; charset=utf-8"); 
include_once("bd.php");
	
    if (isset($_POST['submit'])){
		if(empty($_POST['email']))  {
			echo '<br><font color="red">Введите Email!</font>';
		} 
		elseif (!preg_match("/^[a-zA-Z0-9_\.\-]+@([a-zA-Z0-9\-]+\.)+[a-zA-Z]{2,6}$/", $_POST['email'])) {
			echo '<br><font color="red"> E-mail имеет недопустимий формат!</font>';
		}
		elseif(empty($_POST['password'])) {
			echo '<br><font color="red"> Введите пароль!</font>';
		}
		elseif (!preg_match("/\A(\w){6,20}\Z/", $_POST['password'])) {
			echo '<br><font color="red"> Пароль слишком короткий! Пароль должен быть не менее 6 символов! </font>';
		}
		elseif(empty($_POST['password2'])) {
			echo '<br><font color="red"> Введите подтверждение пароля!</font>';
		}
		elseif($_POST['password'] != $_POST['password2']) {
			echo '<br><font color="red"> Введенные пароли не совпадают!</font>';
		
		}
		elseif(empty($_POST['keystring'])) {
			echo '<br><font color="red"> Введите код!</font>';
		}
		elseif(isset($code1) && $code1 != $_POST['keystring']){
		
			echo '<br><font color="red"> Не верный код</font>';
		}

		else{
			$email = $_POST['email'];
			$password = $_POST['password'];
			$mdPassword = md5($password);
			$password2 = $_POST['password2'];
			$ip = $_SERVER['REMOTE_ADDR'];
			$code = $_POST['keystring'];
			
			

			
		
unset($_SESSION['captcha_keystring']);



				$query = ("SELECT id FROM users WHERE email='$email'");
				$sql = mysql_query($query) or die(mysql_error());
				if (mysql_num_rows($sql) > 0){
					echo '<font color="red"> Пользователь с таким e-mail уже зарегистрирован!</font>';
				}
				else{
					$query = "INSERT INTO users (email, password, ip)
							  VALUES ('$email', '$mdPassword', '$ip')";
					$result = mysql_query($query) or die(mysql_error());;
					echo '<font color="green">Вы успешно зарегестрированы!</font><br><a href="index.php">На главную</a>';
					
				}
			}
		}
  
?>
<br>
<a href="registration.php">Назад</a>