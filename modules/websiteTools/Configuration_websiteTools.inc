<?php

class Configuration_websiteTools
{
	const ISUSINGLOGINSCRIPT = true;
	
	const PAGETITLEPREFIX = "TechMUN | ";

	const STYLESPATH = "styles";
	const MODULESTYLESPATH = "moduleStyles";

	public static function printPageTop()
	{
		//require('PageTopContent.inc');
	}

	public static function printPageBottom()
	{
		//require('PageBottomContent.inc');
	}

	public static function getPageError($errorHtml)
	{
		return sprintf("<div class=\"errtext\">%s</div>", $errorHtml);
	}

	public static function getPageMessage($messageHtml)
	{
		return sprintf("<div class=\"messagetext\">%s</div>", $messageHtml);
	}

	public static function getHeader($html)
	{
		return sprintf("<div class=\"header\">%s</div>", $html);
	}

	public static function getSubHeader($html)
	{
		return sprintf("<div class=\"subHeader\">%s</div>", $html);
	}
}

?>
