#include "IOManager.h"
#include <fstream>

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
    std::ifstream file(filePath, std::ios::binary);

    if (file.fail()){
        perror(filePath.c_str());
        return false;
    }

    // Seek to the end of file
    file.seekg(0, std::ios::end);

    // Get Filesize
    int fileSize = file.tellg();
    // Return to start of file
    file.seekg(0, std::ios::beg);

    //Remove header of file from variable if existing. Reduces file size.
    fileSize -= file.tellg();

    buffer.resize(fileSize);

    file.read((char *)&(buffer[0]), fileSize);

    file.close();

    return true;
}
