#ifndef _FILE_UTILS_
#define _FILE_UTILS_

#pragma once

#include <string.h>
#include <fstream>

namespace solunar {
   /*
   Redefini no shader.h e shader.cpp
   std::string read_file(const char* filepath)
    {
        FILE* file = fopen(filepath, "rt");
        fseek(file, 0, SEEK_END);
        unsigned long length = ftell(file);
        char* data = new char[length + 1];
        memset(data, 0, length + 1);
        fseek(file, 0, SEEK_SET);
        fread(data, 1, length, file);
        fclose(file);
        
        std::string result(data);
        
        delete[] data;
        return result;
    }*/
}
#endif /* _FILE_UTILS_ */