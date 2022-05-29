#include "FileList.h"

FileList::FileList(std::string list) {
    fileListName = list;
}

void FileList::readFileList() {
	std::string line;

	// clear previous result
	sourceFiles.clear();

	std::ifstream reader(fileListName);
	if (reader.is_open()) {
		while (getline(reader, line))
		{
			sourceFiles.push_back(line);
		}
		reader.close();
	}
	else {
		std::cout << "could not open input list" << std::endl;
	}
	
}

std::vector<std::string> FileList::getSourceFiles() {
	return sourceFiles;
}