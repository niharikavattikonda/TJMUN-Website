<?php

class Authorization
{
	const AUTHORIZATION_DEFAULT = 0;
	const AUTHORIZATION_USER = 1;
	const AUTHORIZATION_ADMIN = 2;

	private static $authorization;

	public static function authorize()
	{
		if(isset($_SESSION['sessionKey'])) { //if a session key is stored...
			if(!Sessions::doesSessionExist($_SESSION['sessionKey'])) { //if the session key cannot be matched to one in the table...
				self::$authorization = self::AUTHORIZATION_DEFAULT;
				Authorization::logout();

			} else if(time() > Sessions::getExpireTimeFromSessionKey($_SESSION['sessionKey']) + (Configuration_loginScript::SESSIONEXPIRETIME * 60)) { //if the session has expired...
				Errors::setSessionExpiredError(true);
				self::$authorization = self::AUTHORIZATION_DEFAULT;

			} else { //otherwise, the user is logged in...
				Sessions::updateExpireTimeFromSessionKey($_SESSION['sessionKey']);
				if(Users::getCellFromUserId(Sessions::getUserIdFromSessionKey($_SESSION['sessionKey']), Configuration_loginScript::USERS_ADMIN) == "y") { //if the user is an admin...
					self::$authorization = self::AUTHORIZATION_ADMIN;
				} else { //otherwise, the user is a normal user (non-admin)...
					self::$authorization = self::AUTHORIZATION_USER;
				}
			}
		} else { //otherwise, no session key was found...
			self::$authorization = self::AUTHORIZATION_DEFAULT;
		}
	}

	public static function getAuthorization()
	{
		return self::$authorization;
	}

	public static function setAuthorization($newAuthorization)
	{
		self::$authorization = $newAuthorization;
	}

	public static function logout()
	{
		session_destroy();
		self::$authorization = self::AUTHORIZATION_DEFAULT;
	}

	public static function login($username, $password)
	{
		if(Users::doUsernameAndPasswordMatch($username, $password)) {
			$userId = Users::getUserIdFromUsername($username);
			$_SESSION['sessionKey'] = Sessions::addSession($userId);
			$isAdmin = Users::getCellFromUserId($userId, Configuration_loginScript::USERS_ADMIN);
			if($isAdmin == "y") {
				self::$authorization = self::AUTHORIZATION_ADMIN;
			} else {
				self::$authorization = self::AUTHORIZATION_USER;
			}
			return true;
		} else {
			Errors::setLoginCredentialsError(true);
			return false;
		}
	}

	public static function isAuthorizationOkay($currentAuthorization, $targetAuthorization)
	{
		return $currentAuthorization >= $targetAuthorization;
	}

	public static function isAdmin()
	{
		return self::isAuthorizationOkay(self::$authorization, self::AUTHORIZATION_ADMIN);
	}

	public static function isUser()
	{
		return self::isAuthorizationOkay(self::$authorization, self::AUTHORIZATION_USER);
	}
}

?>