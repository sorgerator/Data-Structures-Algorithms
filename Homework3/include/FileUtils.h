//
// Created by aldin on 26/05/2025.
//

#ifndef FILEUTILS_H
#define FILEUTILS_H
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "Entry.h"

namespace FileUtils {
    Entry* read_file(const std::string& file_path, int len);
    void write_to_file(const Entry* entries, const std::string& file_path, int len);
}

#endif //FILEUTILS_H
