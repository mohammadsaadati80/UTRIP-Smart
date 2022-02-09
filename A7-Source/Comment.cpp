#include "Comment.hpp"
using namespace std;

Comment::Comment(string username, string comment)
{
	this->username = username;
	this->comment = comment;
}

void Comment::show_comment()
{
	cout << username << COLON << SPACE << comment << endl;
}