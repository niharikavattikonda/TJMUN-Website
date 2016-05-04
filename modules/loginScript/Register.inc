<?php

class Register
{
	public static function addUser($username, $password, $admin)
	{
		if(Users::doesUserExist($username)) {
			Errors::setUserAlreadyExistsError(true);
			return false;
		} else {
			return Users::insertUser($username, $password, $admin);
		}
	}
}

?>