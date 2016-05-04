<?php

class LoginScript
{
	private static $isUsingWebsiteTools;
	
	private static $pageAuthorization;

	public static function beginLogin($newPageAuthorization = Authorization::AUTHORIZATION_DEFAULT, $useWebsiteTools = Configuration_loginScript::ISUSINGWEBSITETOOLS)
	{
		self::$isUsingWebsiteTools = $useWebsiteTools;
		self::$pageAuthorization = $newPageAuthorization;
		
		MySql::connect();
		session_start();
		Authorization::authorize();
		
		if(self::$isUsingWebsiteTools && !Authorization::isAuthorizationOkay(Authorization::getAuthorization(), self::$pageAuthorization)) {
			if(self::$pageAuthorization == Authorization::AUTHORIZATION_USER) {
				Errors::setMustLoginToViewPageError(true);
			} else {
				Errors::setNotAuthorizedToViewPageError(true);
			}
			PageGenerator::setShowPageTitle(false);
			PageGenerator::drawPage();
			PageGenerator::endPage();
			exit();
		}
	}
	
	public static function getPageAuthorization()
	{
		return self::$pageAuthorization;
	}
}

?>