#pragma once
#include <string>
#include <functional>
#include "dirent.h"
#include <iostream>

class Discovery
{
	std::string sourceDir;

public:
	Discovery(std::string srcDir);
	void start();

private:
	void readDir(const std::string& path);
};

