/*
 * Copyright 2013 Andrew Brinker
 */

#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "./Table.h"

#define BLOCK_SIZE         500
#define FILL_CHAR          '#'
#define MAX_RECORD_LENGTH  120
#define DATE_LENGTH        5
#define END_LENGTH         5
#define TYPE_LENGTH        8
#define PLACE_LENGTH       15
#define REFERENCE_LENGTH   7
#define DESCRIPTION_LENGTH (MAX_RECORD_LENGTH - DATE_LENGTH \
                           - END_LENGTH - TYPE_LENGTH \
                           - PLACE_LENGTH - REFERENCE_LENGTH)
#define INDEX_LENGTH       DATE_LENGTH + END_LENGTH


/*
 * Table()
 *
 * @in: std::string new_diskname
 *   - The name of the virtual disk to be created
 * @in: std::string new_flat_file
 *   - The name of the flat file to be made on the disk
 * @in: std::string new_index_file
 *   - The name of the index file to be made on the disk
 * @return: none
 *
 * Create the two files which will be used by buildTable()
 */
Table::Table(std::string new_diskname,
             std::string new_flat_file,
             std::string new_index_file):
             FileSys(new_diskname),
             flat_file(new_flat_file),
             index_file(new_index_file) {
    FileSys::newFile(new_flat_file);
    FileSys::newFile(new_index_file);
}


/*
 * buildTable()
 *
 * @in: std::string input_file
 *   - The name of the data file being used to construct the table
 * @return: 0
 *
 * Construct a database table using the data from the input file
 */
unsigned int Table::buildTable(std::string input_file) {
    // 1) Read in a number of records that can be contained in a block.
    // 2) Pad that block to the full block size.
    // 3) Add a block to flat_file containing those records
    // 4) Update index_file containing the dates just saved, and the block they
    //    were saved to.
    // 5) Repeat until all records have been saved.
    std::ifstream read_input(input_file);
    while (read_input.good()) {
        std::string records;
        std::vector<std::string> dates;
        for (unsigned int i = 0; i < (BLOCK_SIZE / MAX_RECORD_LENGTH); ++i) {
            std::string record = "";
            getline(read_input, record);
            dates.push_back(record.substr(0, 5));
            records.append(record);
        }
        records = FileSys::block(records)[0];
        FileSys::addBlock(flat_file, records);
        unsigned int current_block = FileSys::getLastBlock(flat_file);
        std::string block = std::to_string(current_block);
        for (unsigned int i = block.length(); i < 5; ++i) {
            block.push_back(' ');
        }
        std::string indices;
        for (unsigned int i = 0; i < dates.size(); ++i) {
            indices.append(dates[i] + " " + block);
        }
        std::cout << "Adding indices to index file" << std::endl;
        std::vector<std::string> index_blocks = FileSys::block(indices);
        for (unsigned int i = 0; i < indices.size(); ++i) {
            std::cout << "Adding " << indices.size()
                      << " records." << std::endl;
            FileSys::addBlock(index_file, index_blocks[i]);
        }
    }
    return 0;
}


/*
 * search()
 *
 * @in: std::string value
 *   - The date being searched for
 * @return:
 *   - 0 if unsuccessful
 *   - 1 is successful
 *
 * Uses indexSearch() for searching the database, and prints the proper record.
 */
unsigned int Table::search(std::string value) {
    unsigned int block = indexSearch(value);
    if (block == 0) {
        return 0;
    }
    std::string block_contents(BLOCK_SIZE, FILL_CHAR);
    FileSys::readBlock(flat_file, block, block_contents);
    for (std::string::const_iterator it = block_contents.cbegin();
         it != block_contents.end();
         ++it) {
        if (*it == '\n' || it == block_contents.cbegin()) {
            if (strncmp(&*(++it), value.c_str(), DATE_LENGTH) == 0) {
                while (*it != '\n') {
                    std::putchar(*it);
                }
                std::putchar('\n');
                return 1;
            }
        }
    }
    return 0;
}


/*
 * indexSearch()
 *
 * @in: std::string value
 *   - The date being searched for
 * @return:
 *   - 0 if unsuccessful
 *   - the block number of the proper record if successful
 *
 * Search the table and return the block number of the desired record.
 */
unsigned int Table::indexSearch(std::string value) {
    int current_block = FileSys::getFirstBlock(index_file);
    std::string block_contents(BLOCK_SIZE, FILL_CHAR);
    do {
        FileSys::readBlock(index_file, current_block, block_contents);
        for (std::string::const_iterator it = block_contents.cbegin();
             it != block_contents.cend();
             it += INDEX_LENGTH) {
            if (strncmp(&*it, value.c_str(), DATE_LENGTH) == 0) {
                return current_block;
            }
        }
    } while (current_block == FileSys::getNextBlock(index_file, current_block));
    return 0;
}
