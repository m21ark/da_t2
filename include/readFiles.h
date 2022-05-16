#ifndef DA_T2_READFILES_H
#define DA_T2_READFILES_H

#include "objs.h"
#include "iostream"
#include "vector"
#include "fstream"
#include "sstream"
#include "../include/readFiles.h"

using namespace std;

vector<FileContents> read_file(const string &path);

ostream &operator<<(ostream &os, const FileContents &l);

istream &operator>>(istream &is, FileContents &l);


#endif //DA_T2_READFILES_H
