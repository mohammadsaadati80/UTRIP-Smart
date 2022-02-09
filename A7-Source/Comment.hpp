#ifndef __COMMENT_H__
#define __COMMENT_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

#define SPACE ' '
#define COLON ':'

class Comment
{
public:
	Comment(std::string username, std::string comment);
	void show_comment();

private:
	std::string username;
	std::string comment;

};

#endif