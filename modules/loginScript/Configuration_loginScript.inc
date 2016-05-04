<?php

class Configuration_loginScript
{
	const ISUSINGWEBSITETOOLS = true;
	
	const SESSIONEXPIRETIME = 15;

	const SERVER_HOSTNAME = "mysql";
	const SERVER_USERNAME = "tjmun";
	const SERVER_PASSWORD = "b3r3tt4";
	const SERVER_DATABSE = "tjmun";

	const USERS_TABLE = "techmun_users";
	const USERS_USERID = "userId";
	const USERS_USERNAME = "username";
	const USERS_PASSWORD = "password";
	const USERS_ADMIN = "admin";

	const SESSIONS_TABLE = "techmun_sessions";
	const SESSIONS_SESSIONKEY = "sessionKey";
	const SESSIONS_USERID = "userId";
	const SESSIONS_EXPIRETIME = "expireTime";
}

?>