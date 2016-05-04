<?php

class Errors
{
	private static $loginCredentialsError = false;
	private static $sessionExpiredError = false;
	private static $userAlreadyExistsError = false;
	private static $notAuthorizedToViewPageError = false;
	private static $mustLoginToViewPageError = false;

	public static function getLoginCredentialsError()
	{
		return self::$loginCredentialsError;
	}

	public static function setLoginCredentialsError($newError)
	{
		self::$loginCredentialsError = $newError;
	}

	public static function getSessionExpiredError()
	{
		return self::$sessionExpiredError;
	}

	public static function setSessionExpiredError($newError)
	{
		self::$sessionExpiredError = $newError;
	}

	public static function getUserAlreadyExistsError()
	{
		return self::$userAlreadyExistsError;
	}

	public static function setUserAlreadyExistsError($newError)
	{
		self::$userAlreadyExistsError = $newError;
	}

	public static function getNotAuthorizedToViewpageError()
	{
		return self::$notAuthorizedToViewPageError;
	}

	public static function setNotAuthorizedToViewPageError($newError)
	{
		self::$notAuthorizedToViewPageError = $newError;
	}

	public static function getMustLoginToViewPageError()
	{
		return self::$mustLoginToViewPageError;
	}

	public static function setMustLoginToViewPageError($newError)
	{
		self::$mustLoginToViewPageError = $newError;
	}
}

?>