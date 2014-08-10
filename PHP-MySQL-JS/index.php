<?php
session_start();
header("Content-type: text/html; charset=utf-8");
include_once("bd.php");

?>
<html>
	<head>
		<title>Вход</title>
	</head>
	<body>
	<table border="0">
	<tr >
		<td width="100%" colspan="3">
		<img align="middle-right"  width="1920"  src="123.jpg">
		</td>
	</tr>
	<tr>
		<td width="300px" rowspan="2"></td>
		<td>
		<table align="center">
		<tr>
		<td>
		<br><br><br>
		<p>Дорогие посетители!
На этом сайте Вы можете прочитать про хамское отношение к клиентам и людям в различных уголках России в магазинах, фирмах и т.д.
Мы считаем, что "хамло" - надо учить. А чем их можно научить? Только рублем и презрительным отношением! И тем, что другие не пойдут туда, где с людьми обошлись "не по человечески".

Если Вы хотите поделиться своей историей - милости просим, но это можно сделать после краткой регистрации (придумать логин и пароль). В дальнейшем, Вы сможете редактировать свои записи, удалять и вводить новые.
Просим воздержаться от оскорблений, вранья и неточных сведений. Такие записи будут удаляться модераторами сайта. Лучше пишите с юмором.
При размещении информации - просим вводить примерно в таком ключе:</p>
		
	<p>-	дата события и примерное время</p>
	<p>-	точное место события </p>
	<p>-	объективное описание события и его участников</p> 
		</td>
	</tr>
	<tr>
		<td><?php
if(empty($email) and empty($password)){
print <<<HERE
<table>
Вход:
<br>
<br>
 <form action="login.php" method="POST">
      <tr>
      <td>Email:</td>
      <td><input type="text" name="email" ></td>
      </tr>
	  
      <tr>
      <td>Пароль:</td>
      <td><input type="password" name="password" ></td>
      </tr>
	  
	  <tr>
      <td colspan="2"><input type="submit" value="OK" name="submit" ></td>
      </tr>
      </form>
      </table>
<a href="registration.php">Регистрация</a>
<a href="password.php">Забыл парорль</a>
HERE;
}
else{
echo "Вы не правильно вели логин или пароль";
}
?>
</td>
	</tr>
</table>
</td>
		<td width="300px"  rowspan="2"></td>
	</tr>	
	<tr>
		<td >
		<?php 
	$c=0;
	$r=mysql_query ("SELECT * FROM mes ORDER BY dt DESC"); 
	while ($row=mysql_fetch_array($r))
	{
		if ($c%2)
			$col="bgcolor='#f9f9f9'";
		else
			$col="bgcolor='#f0f0f0'";
			
			?>
			<table width="100%" <? echo $col; ?> style="margin: 10px 0px;">
			<tr>
				<td ><?php echo $row['city']; ?>, <?php echo $row['dt']; ?>, Оценка хамла: <?php echo $row['rad'];?></td>
			</tr>
			<tr>
				<td><?php echo $row['msg']; ?><br></td></tr>
			<tr>
			<td align="left">
			</td>
			<td align="left">
			</td>
			<td align="left">
		</td>
			</tr>
			
			</table>
			<?php
		$c++;
	}
	
	if ($c==0)
		echo "Сообщений нет<br>";
	

?>
</td>
		
	</tr>
	<tr>
		<td colspan="3" height="50px"></td>
	</tr>	
	</table>
	</body>
</html>
