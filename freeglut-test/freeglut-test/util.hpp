#pragma once 

#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

string loadFileContent(string path)
{
	ifstream in(path);
	if (!in) {
		cerr << "Fail to load the shader file." << endl;
		return "";
	}
	stringstream ss;
	ss << in.rdbuf();
	in.close();
	return ss.str();
}

#endif // !UTIL_HPP
