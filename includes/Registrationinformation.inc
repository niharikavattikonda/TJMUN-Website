<?php

class RegistrationInformation
{
	const TABLE = "techmun_registrationinformation";
	const USERID = "userId";
	public static function getAllRows()
	{
		$sql = sprintf("SELECT * FROM %s ORDER BY school",
			self::TABLE
		);
		$result = MySql::query($sql);
		while($row = mysql_fetch_assoc($result)) {
			$allRows[] = $row;
		}
		return $allRows;
	}
	
	public static function getRowFromUserId($userId)
	{
		$sql = sprintf("SELECT * FROM %s WHERE %s='%s'",
			self::TABLE,
			self::USERID,
			mysql_real_escape_string($userId)
		);
		$result = MySql::query($sql);
		$row = mysql_fetch_assoc($result);
		return $row;
	}
	
	public static function getCellFromUserId($userId, $field)
	{
		$sql = sprintf("SELECT * FROM %s WHERE %s='%s'",
			self::TABLE,
			self::USERID,
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
			self::TABLE
		);
		$result =  MySql::query($sql);
		while($row = mysql_fetch_assoc($result)) {
			$fieldValues[] = $row[$fieldName];
		}
		return $fieldValues;
	}
}

?>