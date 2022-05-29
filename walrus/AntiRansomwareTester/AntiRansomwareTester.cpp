// AntiRansomwareTester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Encryption.h"
#include "FileList.h"

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "Ransomware Test Software " << "\n";
        std::cout << "========================" << "\n";
        std::cout << "- will encrypt a specified list of files" << "\n";
        std::cout << "- use at your own risk: this utility is open source of course. Have a look and compile it yourself." << "\n";
        std::cout << "- use with test files. see if your cyber security defense system reacts to the actions." << "\n";
        std::cout << "" << "\n";
        std::cout << "usage: " << "\n";
        std::cout << "ransomwaretester.exe /encrypt filelist.txt" << "\n";
        std::cout << "ransomwaretester.exe /decrypt filelist.txt" << "\n";
    } else {
        // read file list
        std::cout << "trying to read input file: " << argv[2] << "\n";
        FileList inputFiles((std::string)argv[2]);
        inputFiles.readFileList();
        std::vector<std::string> sourceFiles = inputFiles.getSourceFiles();
        std::string operation = argv[1];
        if (operation == "/encrypt") {
            std::cout << "starting encryption of files..." << "\n";
            for (std::size_t i = 0; i < sourceFiles.size(); ++i) {
                Encryption gamma(sourceFiles[i]);
                std::cout << "encrypt: " << sourceFiles[i] << "\n";
                gamma.Encrypt();
            }
        } else if (operation == "/decrypt") {
            std::cout << "starting decryption of files..." << "\n";
            for (std::size_t i = 0; i < sourceFiles.size(); ++i) {
                Encryption gamma(sourceFiles[i]);
                std::cout << "decrypt: " << sourceFiles[i] << "\n";
                gamma.Decrypt();
            }
        } else {
            std::cout << "unknown argument: '" << argv[1] << "'\n";
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
