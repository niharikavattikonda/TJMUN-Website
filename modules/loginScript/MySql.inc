<?php

class MySql
{
	public static function connect()
	{
		if($_SERVER['HTTP_HOST'] == "localhost") {
			$host = "localhost";
		} else {
			$host = Configuration_loginScript::SERVER_HOSTNAME;
		}
		
		mysql_connect($host, Configuration_loginScript::SERVER_USERNAME, Configuration_loginScript::SERVER_PASSWORD) or die(mysql_error());
		mysql_select_db(Configuration_loginScript::SERVER_DATABSE) or die(mysql_error());
	}

	public static function query($sql)
	{
		$result = mysql_query($sql) or die(mysql_error());
		return $result;
	}
}

?>