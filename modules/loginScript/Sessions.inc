<?php

class Sessions //@todo clean up methods
{
	public static function doesSessionExist($sessionKey)
	{
		$sql = sprintf("SELECT * FROM %s WHERE %s='%s'",
			Configuration_loginScript::SESSIONS_TABLE,
			Configuration_loginScript::SESSIONS_SESSIONKEY,
			mysql_real_escape_string($sessionKey)
		);
		$result = MySql::query($sql);
		return mysql_num_rows($result) != 0;
	}

	public static function getExpireTimeFromSessionKey($sessionKey)
	{
		$sql = sprintf("SELECT * FROM %s WHERE %s='%s'",
			Configuration_loginScript::SESSIONS_TABLE,
			Configuration_loginScript::SESSIONS_SESSIONKEY,
			mysql_real_escape_string($sessionKey)
		);
		$result = MySql::query($sql);
		$row = mysql_fetch_array($result);
		return $row[Configuration_loginScript::SESSIONS_EXPIRETIME];
	}

	public static function getUserIdFromSessionKey($sessionKey)
	{
		$sql = sprintf("SELECT * FROM %s WHERE %s='%s'",
			Configuration_loginScript::SESSIONS_TABLE,
			Configuration_loginScript::SESSIONS_SESSIONKEY,
			mysql_real_escape_string($sessionKey)
		);
		$result = MySql::query($sql);
		$row = mysql_fetch_array($result);
		return $row[Configuration_loginScript::SESSIONS_USERID];
	}

	public static function updateExpireTimeFromSessionKey($sessionKey)
	{
		$sql = sprintf("UPDATE %s SET %s='%d' WHERE %s='%s'",
			Configuration_loginScript::SESSIONS_TABLE,
			Configuration_loginScript::SESSIONS_EXPIRETIME,
			time(),
			Configuration_loginScript::SESSIONS_SESSIONKEY,
			mysql_real_escape_string($sessionKey)
		);
		MySql::query($sql);
	}

	public static function addSession($userId)
	{
		do {
			$sessionKey = sha1(rand());
			$sql = sprintf("SELECT * FROM %s WHERE %s='%s'",
				Configuration_loginScript::SESSIONS_TABLE,
				Configuration_loginScript::SESSIONS_SESSIONKEY,
				mysql_real_escape_string($sessionKey)
			);
			$result = MySql::query($sql);
		} while(mysql_num_rows($result) != 0);

		$sql = sprintf("INSERT INTO %s (%s, %s, %s) VALUES ('%s', '%s', '%d')",
			Configuration_loginScript::SESSIONS_TABLE,
			Configuration_loginScript::SESSIONS_SESSIONKEY,
			Configuration_loginScript::SESSIONS_USERID,
			Configuration_loginScript::SESSIONS_EXPIRETIME,
			mysql_real_escape_string($sessionKey),
			mysql_real_escape_string($userId),
			time()
		);
		MySql::query($sql);

		return $sessionKey;
	}
}

?>