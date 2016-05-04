<?php

function __autoload($className) {
	$modules = array(
		"loginScript",
		"htmlTools",
		"websiteTools"
	);
	foreach($modules as $value) {
		if(file_exists("modules/$value/$className.inc")) {
			require_once "modules/$value/$className.inc";
			return;
		}
	}
	echo "<strong>Error: Class $className not found. (Autoloader)</strong>";
	exit();
}

?>