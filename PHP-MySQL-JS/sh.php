<?php
session_start();
include ("dbc.php");
header("Content-type: text/html; charset=utf-8");
?>
<?php 
$idc=$_COOKIE['idc'];
	$c=0;
	$r=mysql_query ("SELECT * FROM com where idc='$idc' ORDER BY dt DESC"); 
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
</head>
			<table width="90%" <? echo $col; ?> style="margin: 10px 0px;">
			<tr>
				<td colspan="2" style="color: #999999;">Дата опубликования:</td></tr>
				<tr>
				<td colspan="2"><?php echo $row['dt']; ?></td></tr>
			<tr>
				<td colspan="2" style="color: #999999;">Имя:</td></tr>
				
				<tr><td colspan="2"><?php echo $row['name']; ?></td>
				</tr>
			<tr>
				<td  style="color: #999999;">Сообщение:</td>
			</tr>		
			<tr >
				<td>
					<?php echo $row['msg']; ?>
					<br>
				</td>
			</tr>
			<tr>
			<td align="left"><?php
			if 
			($row['email'] != $_SESSION['email']){
			echo '';
			}elseif 
			(empty($row['email'])){
			echo '';
			}else{
			echo "<a href='rep.php?id=$row[id]'>Редактировать</a>";
			}
			?>
			</td>
			<td align="left"><?php
			if 
			($row['email'] != $_SESSION['email']){
			echo '';
			}elseif 
			(empty($row['email']))
			{
			echo '';
			}else{
			echo "<a href='dr.php?id=$row[id]'>Удалить</a>";
			}
			?>
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