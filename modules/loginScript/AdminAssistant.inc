<?php

class AdminAssistant //@todo finish!
{
	public function getUsernames()
	{
		return Users::getFieldArray(Configuration_loginScript::USERS_USERNAME);
	}

	public function getUsernamesWithUserIds()
	{
		$rows = Users::getAllRows();
		
		foreach($rows as $value) {
			$users[$value[Configuration_loginScript::USERS_USERID]] = $value[Configuration_loginScript::USERS_USERNAME];
		}
		return $users;
	}
}

?>