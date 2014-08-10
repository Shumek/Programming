<?php
session_start();
header("Content-type: text/html; charset=utf-8");
?>
<html>
	<head>
		<title>Редактирование</title>
		<script type="text/javascript">
src="kcaptcha/index.php"; 
function reload(){
        document.captcha.src='kcaptcha/index.php';
        document.captcha.src=src+'?rand='+Math.random();
}
</script>
	</head>
	<body>
	<table>
	<tr >
		<td  width="100%" colspan="3">
		<img align="middle-right"  width="1920"  src="123.jpg">
		</td>
	</tr>
	<tr>
		<td width="600" rowspan="2" ></td>
		<td width='600px'>
		<table align="center">
		<form action="verification.php" method="POST">
      <tr>
      <td>Email<font color="red">*</font>:</td>
      <td><input type="text" size="20" name="email"></td>
      </tr>
      <tr>
      <td>Пароль<font color="red">*</font>:</td>
      <td><input type="password" size="20" maxlength="20" name="password"></td>
	  <td><h4>Пароль должен быть не менее 6 символов!</h4></td>
      </tr>
      <tr>
      <td>Подтверждения пароля<font color="red">*</font>:</td>
      <td><input type="password" size="20" maxlength="20" name="password2"></td>
      </tr>
      <tr>
	<td>Введите код<font color="red">*</font>:</td>
	<td><input type="text" name="keystring"></td>
      </tr>
      <tr>
	<td>
	<a href="javascript:void(0)"  onclick="reload()">
	<img src="kcaptcha/index.php" name="captcha"></td>
	</a>
      </tr>
      <tr>
      <td colspan="2"><input type="submit" value="Зарегистроваться..." name="submit" ></td>
      </tr>
     <br>
      </form>
	  </table>
<font face="Verdana" size="4">Поля со значком <font color="red">*</font> должны быть обязательно заполнены!</font> 
<br><a href='index.php'>На главную</a>
		
		
		
		
		
		</td>
	</tr>
</table></td>
		<td width="100px"  rowspan="2">
		</td>
	</tr>	
	<tr>
	</tr>
	<tr>
		<td height="50px"></td>
	</tr>	

	</body>
</html>