<?php
session_start();
include ("dbconnect.php");
header("Content-type: text/html; charset=utf-8");
?>
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
<head>
	<link rel="stylesheet" type="text/css" href="style.css">
    <script type="text/javascript" src="script.js"></script>
	<meta http-equiv=Content-Type content="text/html; charset=utf-8">
</head>
			<table  width="100%" <? echo $col; ?> style="margin: 10px 0px;">
			<tr>
				<td ><?php echo $row['city']; ?>, <?php echo $row['dt']; ?>, Оценка хамла: <?php echo $row['rad'];?></td>
			</tr>
			<tr>
				<td><?php echo $row['msg']; ?><br></td></tr>
			<tr>
			<td><?php
			if 
			($row['email'] != $_SESSION['email']){
			echo '';
			}elseif 
			(empty($row['email'])){
			echo '';
			}else{
			echo "<a href='replay.php?id=$row[id]'>Редактировать</a>";
			}
			?>
			
			<?php
			if 
			($row['email'] != $_SESSION['email']){
			echo '';
			}elseif 
			(empty($row['email']))
			{
			echo '';
			}else{
			echo "<a href='drop.php?id=$row[id]'>Удалить</a>";
			}
			?>
			<?php
			if (empty($_SESSION['email'])){
			echo '';
			}else{
			echo "<a href='cb.php?id=$row[id]'>Коментарии</a>";
	        }
			?>
		</td>
			</tr>
			
			</table>
			<?php
		$c++;
	}
	if ($c==0)
		echo "Сообщений нет<br>";
	

?>