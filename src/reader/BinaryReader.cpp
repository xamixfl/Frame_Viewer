#include "reader/BinaryReader.h"
#include "exception/Exceptions.h"

BinaryReader::~BinaryReader() {
    if (_stream.is_open()) {
        _stream.close();
    }
}

void BinaryReader::open(const std::string& filename) {
    if (_stream.is_open()) {
        _stream.close();
    }

    _filename = filename;
    _stream.open(_filename, std::ios::binary);
    if (!_stream.is_open()) {
        throw FileOpenError(_filename.c_str(), __FILE__, "BinaryReader", __FUNCTION__);
    }
}

void BinaryReader::close() noexcept {
    if (_stream.is_open()) {
        _stream.close();
    }
}

double BinaryReader::read() {
    if (!_stream.is_open()) {
        throw FileNotOpenError(__FILE__, "BinaryReader", __FUNCTION__);
    }

    double value = 0.0;
    _stream.read(reinterpret_cast<char*>(&value), sizeof(double));
    if (_stream.fail() && !_stream.eof()) {
        throw FileReadError(__FILE__, "BinaryReader", __FUNCTION__);
    }
    return value;
}

bool BinaryReader::isOpen() const noexcept {
    return _stream.is_open();
}

bool BinaryReader::eof() const noexcept {
    return _stream.eof();
}
