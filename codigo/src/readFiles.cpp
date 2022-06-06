#include "../include/readFiles.h"

vector<FileContents> read_file(const string &path) {

    vector<FileContents> rows;
    fstream file(path, ios::in);

    if (!file) {
        cerr << "file " << path << " not found!\n";
        return {};
    }

    FileContents fileObj{};
    string aux;

    getline(file, aux);
    while (getline(file, aux)) {
        stringstream ss(aux);
        ss >> fileObj;
        rows.push_back(fileObj);
    }

    file.close();
    return rows;
}

ostream &operator<<(ostream &os, const FileContents &l) {
    os << l.pred << " " << l.dest << " " << l.capacity << " " << l.duration;
    return os;
}

istream &operator>>(istream &is, FileContents &l) {
    is >> l.pred >> l.dest >> l.capacity >> l.duration;
    return is;
}
