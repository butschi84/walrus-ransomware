#pragma once
#include <iostream>
#include <fstream>
#include <bitset>
#include <string>

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
};

