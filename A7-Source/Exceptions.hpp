#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <exception>

#define NOT_FOUND_EXCEPTION_MESSAGE "Not Found\n"
#define BAD_REQUEST_EXCEPTION_MESSAGE "Bad Request\n"
#define PERMISSION_DENIED_EXCEPTION_MESSAGE "Permission Denied\n"
#define EMPTY_EXCEPTION_MESSAGE "Empty\n"
#define NOT_ENOUGH_CREDIT_EXCEPTION_MESSAGE "Not Enough Credit\n"
#define NOT_ENOUGH_ROOM_EXCEPTION_MESSAGE "Not Enough Room\n"
#define NO_RATING_EXCEPTION_MESSAGE "No Rating\n"
#define INSUFFICIENT_RATINGS_EXCEPTION_MESSAGE "Insufficient Ratings\n"

class NotFoundException : public std::exception
{
	public:
		const char* what() const throw();
};

class BadRequestException : public std::exception
{
public:
	const char* what() const throw();
};

class PermissionDeniedException : public std::exception
{
public:
	const char* what() const throw();
};

class EmptyException : public std::exception
{
public:
	const char* what() const throw();
};

class NotEnoughCreditException : public std::exception
{
public:
	const char* what() const throw();
};

class NotEnoughRoomException : public std::exception
{
public:
	const char* what() const throw();
};

class NoRatingException : public std::exception
{
public:
	const char* what() const throw();
};

class InsufficientRatings : public std::exception
{
public:
	const char* what() const throw();
};

#endif 