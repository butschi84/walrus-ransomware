#include "Encryption.h"

Encryption::Encryption(std::string filename)
{
    sourceFileName = filename;
    sourceFileNameEncrypted = filename + ".enc";
}

void Encryption::Decrypt()
{
    char currentByte;
    bool currentBit;
    int index = 0;

    // open input file
    file2.open(sourceFileNameEncrypted, std::ios::in | std::ios::out | std::ios::binary);

    // check if source file exists
    if (!file2.is_open()) {
        printf("encrypted file %s could not be loaded\n", sourceFileName.c_str());
        return;
    }

    // open output file
    file1.open(sourceFileName, std::ios::out | std::ios::binary);

    // sets the pointers to the beginning of the file
    file2.seekg(0, std::ios::beg);
    file1.seekp(0, std::ios::beg);

    // reads the first value
    file2.read(&currentByte, 1);
    while (file2.good())
    {
        // loop for four bits
        for (int c = 0; c < 4; c++)
        {
            // shifts the byte over
            char lastBit = ((currentByte & 1) * 128);
            char result = (currentByte >> 1);
            // clear bit 7
            result &= ~(1 << 7);
            // move last bit to front
            currentByte = result | lastBit;
        }

        // writes the character
        file1.write(&currentByte, 1);

        // increments the pointer
        file2.seekg(++index);
        file1.seekp(index);

        // reads the next value
        file2.read(&currentByte, 1);
    }

    file1.close();
    file2.close();

    //delete the encrypted file
    std::remove(sourceFileNameEncrypted.c_str());
}

void Encryption::Encrypt()
{
    char currentByte;
    bool currentBit;
    int index = 0;

    // open input file
    file1.open(sourceFileName, std::ios::in | std::ios::out | std::ios::binary);

    // check if source file exists
    if(!file1.is_open()) {
        printf("source file %s could not be loaded\n", sourceFileName.c_str());
        return;
    }

    // open output file
    file2.open(sourceFileNameEncrypted, std::ios::out | std::ios::binary);

    // sets the pointers to the beginning of the file
    file1.seekg(0, std::ios::beg);
    file2.seekp(0, std::ios::beg);

    // reads the first value
    file1.read(&currentByte, 1);
    while (file1.good())
    {
        // loop for four bits
        for (int c = 0; c < 4; c++)
        {
            // finds out if the first bit is a one
            currentBit = static_cast<bool> ((unsigned char)currentByte / 128);

            // shifts the byte over
            currentByte <<= 1;

            // if the first bit was a one then we add it to the end
            if (currentBit)
            {
                currentByte += 1;
            }
        }

        // writes the character
        file2.write(&currentByte, 1);

        // increments the pointer
        file1.seekg(++index);
        file2.seekp(index);

        // reads the next value
        file1.read(&currentByte, 1);
    }

    file1.close();
    file2.close();

    //delete the unencrypted file
    std::remove(sourceFileName.c_str());
}

bool Encryption::fileExists() {
    FILE* file;
    errno_t err;

    if ((err = fopen_s(&file, sourceFileName.c_str(), "r")) != 0) {
        // file could not be opened
        return false;
    }
    else {
        // file could be opened
        fclose(file);
        return true;
    }
}