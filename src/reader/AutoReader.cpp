#include "reader/AutoReader.h"
#include "reader/BinaryReader.h"
#include "reader/FileReader.h"
#include "exception/Exceptions.h"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <string>

namespace {

std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(static_cast<int>(c)));
    });
    return s;
}

} 

std::unique_ptr<BaseReader> AutoReader::_selectReader(const std::string& filename) {
    const std::string ext = toLower(std::filesystem::path(filename).extension().string());

    if (ext == ".bin") {
        return std::make_unique<BinaryReader>();
    }
    return std::make_unique<FileReader>();
}

void AutoReader::open(const std::string& filename) {
    _impl = _selectReader(filename);
    _impl->open(filename);
}

void AutoReader::close() noexcept {
    if (_impl) {
        _impl->close();
    }
}

double AutoReader::read() {
    if (!_impl) {
        throw FileNotOpenError(__FILE__, "AutoReader", __FUNCTION__);
    }
    return _impl->read();
}

bool AutoReader::isOpen() const noexcept {
    return _impl && _impl->isOpen();
}

bool AutoReader::eof() const noexcept {
    return _impl && _impl->eof();
}
