#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#ifndef SPL_01_DIRECTORYREADER_H
#define SPL_01_DIRECTORYREADER_H

class directoryReader {
    std::vector<std::string> Directories(std::vector<std::string> fileNames){
    const std::string directoryPath = "D:\\";
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((directoryPath + "*").c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening directory" << std::endl;
        exit(1);
    }
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            fileNames.push_back(findFileData.cFileName);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);
    FindClose(hFind);
    for (const std::string& fileName : fileNames) {
        std::cout << fileName << std::endl;
    }
    return fileNames;
}
};
#endif //SPL_01_DIRECTORYREADER_H
