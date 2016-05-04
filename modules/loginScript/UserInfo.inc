<?php

class UserInfo
{
	public static function getUsername()
	{
		return Users::getCellFromUserId(self::getUserId(), Configuration_loginScript::USERS_USERNAME);
	}

	public static function getUserId()
	{
		return Sessions::getUserIdFromSessionKey($_SESSION['sessionKey']);
	}

	public static function getAdmin()
	{
		return Users::getCellFromUserId(self::getUserId(), Configuration_loginScript::USERS_ADMIN);
	}

	public static function getHashedPassword()
	{
		return Users::getCellFromUserId(self::getUserId(), Configuration_loginScript::USERS_PASSWORD);
	}

	public static function updateUsername($newUsername)
	{
		Users::updateCellFromUserId(self::getUserId(), Configuration_loginScript::USERS_USERNAME, $newUsername);
	}

	public static function updatePassword($newPassword)
	{
		Users::updateCellFromUserId(self::getUserId(), Configuration_loginScript::USERS_PASSWORD, $newPassword);
	}

	public static function updateAdmin($newAdmin)
	{
		Users::updateCellFromUserId(self::getUserId(), Configuration_loginScript::USERS_ADMIN, $newAdmin);
	}

	public static function checkPassword($password)
	{
		return Users::doUserIdAndPasswordMatch(self::getUserId(), $password);
	}
}

?>
