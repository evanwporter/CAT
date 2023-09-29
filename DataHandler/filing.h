#ifndef FILING_H
#define FILING_H

#include <iostream>
#include <string>
#include <windows.h> 


std::string DirName(const std::string& fname)
{
     size_t pos = fname.find_last_of("\\/");
     return (std::string::npos == pos)
         ? ""
         : fname.substr(0, pos);
}

static std::string GetExePath() {
    char buffer[MAX_PATH]; 
    GetModuleFileName(NULL, buffer, MAX_PATH); 

    return DirName(std::string(buffer));
}

#endif