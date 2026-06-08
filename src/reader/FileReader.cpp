#include "reader/FileReader.h"
#include "exception/Exceptions.h"

FileReader::~FileReader() {
    if (_stream.is_open()) {
        _stream.close();
    }
}

void FileReader::open(const std::string& filename) {
    if (_stream.is_open()) {
        _stream.close();
    }

    _filename = filename;
    _stream.open(_filename);
    if (!_stream.is_open()) {
        throw FileOpenError(_filename.c_str(), __FILE__, "FileReader", __FUNCTION__);
    }
}

void FileReader::close() noexcept {
    if (_stream.is_open()) {
        _stream.close();
    }
}

double FileReader::read() {
    if (!_stream.is_open()) {
        throw FileNotOpenError(__FILE__, "FileReader", __FUNCTION__);
    }

    double value;
    _stream >> value;
    if (_stream.fail() && !_stream.eof()) {
        throw FileReadError(__FILE__, "FileReader", __FUNCTION__);
    }
    return value;
}

bool FileReader::isOpen() const noexcept {
    return _stream.is_open();
}

bool FileReader::eof() const noexcept {
    return _stream.eof();
}
