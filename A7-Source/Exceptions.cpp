#include "Exceptions.hpp"
using namespace std;

const char* NotFoundException::what() const throw()
{
	return NOT_FOUND_EXCEPTION_MESSAGE;
}

const char* BadRequestException::what() const throw()
{
	return BAD_REQUEST_EXCEPTION_MESSAGE;
}

const char* PermissionDeniedException::what() const throw()
{
	return PERMISSION_DENIED_EXCEPTION_MESSAGE;
}

const char* EmptyException::what() const throw()
{
	return EMPTY_EXCEPTION_MESSAGE;
}

const char* NotEnoughCreditException::what() const throw()
{
	return NOT_ENOUGH_CREDIT_EXCEPTION_MESSAGE;
}

const char* NotEnoughRoomException::what() const throw()
{
	return NOT_ENOUGH_ROOM_EXCEPTION_MESSAGE;
}

const char* NoRatingException::what() const throw()
{
	return NO_RATING_EXCEPTION_MESSAGE;
}

const char* InsufficientRatings::what() const throw()
{
	return INSUFFICIENT_RATINGS_EXCEPTION_MESSAGE;
}