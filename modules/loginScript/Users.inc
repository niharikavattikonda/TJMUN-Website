<?php

class Users
{
	public static function doesUserExist($username)
	{
		$sql = sprintf("SELECT * FROM %s WHERE %s='%s'",
			Configuration_loginScript::USERS_TABLE,
			Configuration_loginScript::USERS_USERNAME,
			mysql_real_escape_string($username)
		);
		$result = MySql::query($sql);
		return mysql_num_rows($result) != 0;
	}

	public static function doUsernameAndPasswordMatch($username, $password)
	{
		$sql = sprintf("SELECT * FROM %s WHERE %s='%s'",
			Configuration_loginScript::USERS_TABLE,
			Configuration_loginScript::USERS_USERNAME,
			mysql_real_escape_string($username)
		);
		$result = MySql::query($sql);
		$row = mysql_fetch_assoc($result);

		if(mysql_num_rows($result) == 0) {
			return false;
		} else if($row[Configuration_loginScript::USERS_PASSWORD] == sha1($password)) {
			return true;
		} else {
			return false;
		}
	}
	
	public static function doUserIdAndPasswordMatch($userId, $password)
	{
		$sql = sprintf("SELECT * FROM %s WHERE %s='%s'",
			Configuration_loginScript::USERS_TABLE,
			Configuration_loginScript::USERS_USERID,
			mysql_real_escape_string($userId)
		);
		$result = MySql::query($sql);
		$row = mysql_fetch_assoc($result);

		if(mysql_num_rows($result) == 0) {
			return false;
		} else if($row[Configuration_loginScript::USERS_PASSWORD] == sha1($password)) {
			return true;
		} else {
			return false;
		}
	}

	public static function insertUser($username, $password, $admin)
	{
		do {
			$userId = sha1(rand());
			$sql = sprintf("SELECT * FROM %s WHERE %s='%s'",
				Configuration_loginScript::USERS_TABLE,
				Configuration_loginScript::USERS_USERID,
				mysql_real_escape_string($userId)
			);
			$result = MySql::query($sql);
		} while(mysql_num_rows($result) != 0);

		$sql = sprintf("INSERT INTO %s (%s, %s, %s, %s) VALUES ('%s', '%s', '%s', '%s')",
			Configuration_loginScript::USERS_TABLE,
			Configuration_loginScript::USERS_USERID,
			Configuration_loginScript::USERS_USERNAME,
			Configuration_loginScript::USERS_PASSWORD,
			Configuration_loginScript::USERS_ADMIN,
			mysql_real_escape_string($userId),
			mysql_real_escape_string($username),
			mysql_real_escape_string(sha1($password)),
			mysql_real_escape_string($admin)
		);
		MySql::query($sql);

		return $userId;
	}
	
	public static function getCellFromUserId($userId, $field)
	{
		$sql = sprintf("SELECT * FROM %s WHERE %s='%s'",
			Configuration_loginScript::USERS_TABLE,
			Configuration_loginScript::USERS_USERID,
			mysql_real_escape_string($userId)
		);
		$result = MySql::query($sql);
		$row = mysql_fetch_assoc($result);
		
		return $row[$field];
	}
	
	public static function getFieldArray($fieldName)
	{
		$sql = sprintf("SELECT %s FROM %s",
			mysql_real_escape_string($fieldName),
			Configuration_loginScript::USERS_TABLE
		);
		$result =  MySql::query($sql);
		while($row = mysql_fetch_assoc($result)) {
			$fieldValues[] = $row[$fieldName];
		}
		return $fieldValues;
	}
	
	public static function getRowFromUserId($userId)
	{
		$sql = sprintf("SELECT * FROM %s WHERE %s='%s'",
			Configuration_loginScript::USERS_TABLE,
			Configuration_loginScript::USERS_USERID,
			mysql_real_escape_string($userId)
		);
		$result = MySql::query($sql);
		$row = mysql_fetch_assoc($result);
		return $row;
	}
	
	public static function getAllRows()
	{
		$sql = sprintf("SELECT * FROM %s",
			Configuration_loginScript::USERS_TABLE
		);
		$result = MySql::query($sql);
		while($row = mysql_fetch_assoc($result)) {
			$allRows[] = $row;
		}
		return $allRows;
	}
	
	public static function getUserIdFromUsername($username)
	{
		$sql = sprintf("SELECT * FROM %s WHERE %s='%s'",
			Configuration_loginScript::USERS_TABLE,
			Configuration_loginScript::USERS_USERNAME,
			mysql_real_escape_string($username)
		);
		$result = MySql::query($sql);
		$row = mysql_fetch_assoc($result);
		return $row[Configuration_loginScript::USERS_USERID];
	}

	public static function updateCellFromUserId($userId, $fieldName, $newValue)
	{
		$sql = sprintf("UPDATE %s SET %s='%s' WHERE %s='%s'",
			Configuration_loginScript::USERS_TABLE,
			mysql_real_escape_string($fieldName),
			mysql_real_escape_string($newValue),
			Configuration_loginScript::USERS_USERID,
			mysql_real_escape_string($userId)
		);
	}
}

?>