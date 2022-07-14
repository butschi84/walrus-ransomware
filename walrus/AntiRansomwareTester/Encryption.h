#pragma once
#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <sys/stat.h>
#include <filesystem>
namespace fs = std::filesystem;


class Encryption
{
	std::string sourceFileName;
	std::string sourceFileNameEncrypted;
	std::fstream file1; // source file
	std::fstream file2; // destination file

public:
	Encryption(std::string filename1);

	// encrypts the input file
	void Encrypt();

	// decrypts the input file
	void Decrypt();

	// check if file exists
	bool fileExists();

	// copy a file to another location
	bool copyFile(std::string SRC, std::string DEST);

	// check whether a directory exists
	bool directoryExists(std::string path);

	// create a directory
	void createDirectory(std::string path);
};

