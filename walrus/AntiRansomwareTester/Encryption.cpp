#include "Encryption.h"

Encryption::Encryption(std::string filename)
{
    sourceFileName = filename;
    sourceFileNameEncrypted = filename + ".enc";
}

// copy in binary mode
bool Encryption::copyFile(std::string SRC, std::string DEST)
{
    std::ifstream src(SRC, std::ios::binary);
    std::ofstream dest(DEST, std::ios::binary);
    dest << src.rdbuf();
    return src && dest;
}

bool Encryption::directoryExists(std::string path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

void Encryption::createDirectory(std::string path) {
    fs::create_directory(path);
}

void Encryption::Decrypt()
{
    char currentByte;
    bool currentBit;
    int index = 0;

    // make sure tmp dir exists
    if (!directoryExists("c:\\tmp")) createDirectory("c:\\tmp");

    // copy to tmp
    if (!copyFile(sourceFileNameEncrypted, "c:\\tmp\\walrus_in.tmp")) {
        printf("could not copy source file");
        return;
    }

    // open input file
    file2.open("c:\\tmp\\walrus_in.tmp", std::ios::in | std::ios::out | std::ios::binary);

    // check if source file exists
    if (!file2.is_open()) {
        printf("encrypted file %s could not be loaded\n", sourceFileName.c_str());
        return;
    }

    // open output file
    file1.open("c:\\tmp\\walrus_out.tmp", std::ios::out | std::ios::binary);

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

    // copy output file to destination
    copyFile("c:\\tmp\\walrus_out.tmp", sourceFileName);

    //delete the encrypted file
    std::remove(sourceFileNameEncrypted.c_str());
    std::remove("c:\\tmp\\walrus_out.tmp");
    std::remove("c:\\tmp\\walrus_in.tmp");
}

void Encryption::Encrypt()
{
    char currentByte;
    bool currentBit;
    int index = 0;

    // make sure tmp dir exists
    if (!directoryExists("c:\\tmp")) createDirectory("c:\\tmp");

    // copy to tmp
    if (!copyFile(sourceFileName, "c:\\tmp\\walrus_in.tmp")) {
        printf("could not copy source file");
        return;
    }

    // open input file
    file1.open("c:\\tmp\\walrus_in.tmp", std::ios::in | std::ios::out | std::ios::binary);

    // check if source file exists
    if (!file1.is_open()) {
        printf("source file %s could not be loaded\n", sourceFileName.c_str());
        return;
    }

    // open output file
    file2.open("c:\\tmp\\walrus_out.tmp", std::ios::out | std::ios::binary);

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

    // copy output file to destination
    copyFile("c:\\tmp\\walrus_out.tmp", sourceFileNameEncrypted);

    //delete the unencrypted file
    std::remove(sourceFileName.c_str());
    std::remove("c:\\tmp\\walrus_out.tmp");
    std::remove("c:\\tmp\\walrus_in.tmp");
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