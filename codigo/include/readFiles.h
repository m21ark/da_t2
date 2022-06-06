#ifndef DA_T2_READFILES_H
#define DA_T2_READFILES_H

#include "objs.h"
#include "iostream"
#include "vector"
#include "fstream"
#include "sstream"
#include "../include/readFiles.h"

using namespace std;

/**
 * Reads data files and returns its line contents in a vector
 * @param path path to file's location
 * @return file lines organized in a vector
 */
vector<FileContents> read_file(const string &path);

/**
 * Overload for the FileContents struct
 * @param os ostream to be used
 * @param l struct to be used
 * @return changed ostream
 */
ostream &operator<<(ostream &os, const FileContents &l);

/**
 * Overload for the FileContents struct
 * @param is istream to be used
 * @param l struct to be used and changed
 * @return changed istream
 */
istream &operator>>(istream &is, FileContents &l);


#endif //DA_T2_READFILES_H
