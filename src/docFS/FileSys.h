/*
 * Copyright 2013 Andrew Brinker
 */

#ifndef SRC_DOCFS_FILESYS_H_
#define SRC_DOCFS_FILESYS_H_

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#include <string>
#include <vector>
#include "./Vdisk.h"


class FileSys : public Vdisk {
 public:
  explicit FileSys(std::string name);
  unsigned int sync();
  unsigned int newFile(std::string file);
  unsigned int removeFile(std::string file);
  unsigned int getFirstBlock(std::string file);
  int getNextBlock(std::string file, unsigned int block_number);
  int addBlock(std::string file, std::string buffer);
  unsigned int deleteBlock(std::string file, unsigned int block_number);
  unsigned int readBlock(std::string file,
                         unsigned int block_number,
                         std::string& buffer);
  unsigned int writeBlock(std::string file,
                          unsigned int block_number,
                          std::string buffer);

 protected:
  std::vector<std::string> block(std::string blocks);

 private:
  unsigned int loadFileSystem();
  unsigned int makeFileSystem();
  unsigned int loadFat(std::string fat_string);
  unsigned int loadRoot(std::string root_string);
  unsigned int fileHasBlock(std::string filename, unsigned int block_number);
  unsigned int prepFileName(std::string& file);
  void strip(std::string& new_string, const char fill);

  std::vector<std::string> root_file_names;     // File names in ROOT
  std::vector<unsigned int> root_first_blocks;  // First blocks in ROOT
  std::vector<unsigned int> fat;                // FAT

  DISALLOW_COPY_AND_ASSIGN(FileSys);
};


#endif  // SRC_DOCFS_FILESYS_H_
