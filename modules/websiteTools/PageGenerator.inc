<?php

class PageGenerator
{
	private static $pageTitle;
	private static $showPageTitle;
	private static $isUsingLogin;
	
	private static $addedStyles = array();
	
	public static function beginPage($newPageTitle, $newShowPageTitle = true, $useLogin = Configuration_websiteTools::ISUSINGLOGINSCRIPT)
	{
		self::$isUsingLogin = $useLogin;
		self::$pageTitle = $newPageTitle;
		self::$showPageTitle = $newShowPageTitle;
	}
	
	public static function drawPage()
	{
		Configuration_websiteTools::printPageTop();

		if(self::$showPageTitle) {
			echo self::getHeader(self::$pageTitle);
		}
		
		if(self::$isUsingLogin) {
			if(Errors::getSessionExpiredError() && !Authorization::isAuthorizationOkay(Authorization::getAuthorization(), LoginScript::getPageAuthorization())) {
				Authorization::logout();
				echo self::getPageError("Your session has expired. Please <a href=\"login.php\">login</a> again.");
	
			} else if(Errors::getMustLoginToViewPageError()) {
				echo self::getPageMessage("You must <a href=\"login.php\">login</a> to view this page.");
	
			} else if(Errors::getNotAuthorizedToViewpageError()) {
				echo self::getPageError("You are not authorized to view this page.");
			}
		}
	}
	
	public static function endPage()
	{
		Configuration_websiteTools::printPageBottom();
	}
	
	public static function setShowPageTitle($newShowPageTitle)
	{
		self::$showPageTitle = $newShowPageTitle;
	}
	
	public static function getPageTitle($prefix = false)
	{
		if($prefix) {
			return Configuration_websiteTools::PAGETITLEPREFIX . self::$pageTitle;
		} else {
			return self::$pageTitle;
		}
	}
	
	public static function addStyle($file)
	{
		$path = Configuration_websiteTools::STYLESPATH . "/$file";
		if(!in_array($path, self::$addedStyles)) {
			self::$addedStyles[] = $path;
		}
	}

	public static function addModuleStyle($file)
	{
		$path = Configuration_websiteTools::MODULESTYLESPATH . "/$file";
		if(!in_array($path, self::$addedStyles)) {
			self::$addedStyles[] = $path;
		}
	}

	public static function getAddedStyles()
	{
		$addedHeadHtml = "";
		foreach(self::$addedStyles as $key) {
			$addedHeadHtml .= sprintf("<link href=\"%s\" rel=\"stylesheet\" type=\"text/css\" />\n", $key);
		}
		return $addedHeadHtml;
	}

	public static function getPageError($errorHtml)
	{
		return Configuration_websiteTools::getPageError($errorHtml);
	}

	public static function getPageMessage($messageHtml)
	{
		return Configuration_websiteTools::getPageMessage($messageHtml);
	}

	public static function getHeader($html)
	{
		return Configuration_websiteTools::getHeader($html);
	}

	public static function getSubHeader($html)
	{
		return Configuration_websiteTools::getSubHeader($html);
	}
}

?>