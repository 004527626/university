/*
The MIT License (MIT)

Copyright (c) 2013 Andrew Brinker

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "./Table.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#define MAX_RECORD_LENGTH      120
#define INDEX_LENGTH           10
#define DATE_LENGTH            5
#define END_LENGTH             5
#define TYPE_LENGTH            8
#define PLACE_LENGTH           15
#define REFERENCE_LENGTH       7
#define MAX_DESCRIPTION_LENGTH (MAX_RECORD_LENGTH - INDEX_LENGH \
                                - DATE_LENGTH - END_LENGTH - TYPE_LENGTH \
                                - PLACE_LENGTH - REFERENCE_LENGTH)


Table::Table(std::string new_diskname,
             std::string new_flat_file,
             std::string new_index_file):
             FileSystem(new_diskname),
             flat_file(new_flat_file),
             index_file(new_index_file) {
    FileSystem::newFile(new_flat_file);
    FileSystem::newFile(new_index_file);
}


unsigned int Table::buildTable(std::string input_file) {
    std::string blah = input_file;
    return 0;
}


unsigned int Table::indexSearch(std::string value) {
    std::string blah = value;
    return 0;
}
