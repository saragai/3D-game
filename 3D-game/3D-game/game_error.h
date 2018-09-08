/*
game_error.h

(c) 2018 Saragai Takanori
*/

#pragma once

#include <exception>
#include <string>

#define FATAL_ERROR -1
#define WARNING 1

class GameError : public std::exception
{
private:
	int errorCode;
	std::string message;

public:
	GameError() throw() :
		errorCode(FATAL_ERROR),
		message("Undefined Error in Game.") {}

	GameError(const GameError& e) throw() :
		std::exception(e),
		errorCode(e.errorCode),
		message(e.message) {}

	GameError(int code, const std::string &s) throw() :
		errorCode(code),
		message(s) {}

	GameError& operator= (const GameError& gameError) throw()
	{
		std::exception::operator=(gameError);
		this->errorCode = gameError.errorCode;
		this->message = gameError.message;
	}

	virtual ~GameError() throw() {};

	virtual const char* what() const throw()
	{
		return this->getMessage();
	}

	const char* getMessage() const throw()
	{
		return message.c_str();
	}

	int getErrorCode() const throw()
	{
		return errorCode;
	}
};