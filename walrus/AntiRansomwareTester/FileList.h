#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class FileList
{
	int numFiles = 0;
	std::string fileListName;
	std::vector<std::string> sourceFiles;

public:
	FileList(std::string fileListName);
	void readFileList();
	std::vector<std::string> getSourceFiles();
};

