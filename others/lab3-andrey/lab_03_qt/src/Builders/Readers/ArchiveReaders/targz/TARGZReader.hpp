//
// Created by nuelex on 27/05/25.
//

#ifndef TARGZREADER_HPP
#define TARGZREADER_HPP
#include <filesystem>
#include <iostream>

#include "../BaseArchiveReader.hpp"


class TARGZReader : public BaseArchiveReader
{
public:
    TARGZReader() = delete;
    TARGZReader(const std::string &path);

    ~TARGZReader() override;

    void next() override
    {
        ++_iter;
    }
    std::string current() const override
    {
        const auto value = *_iter;
        const auto& full_path = value.path();

        return full_path.string();
    }
    bool isEnd() const override
    {
        return _iter == end(_iter);
    }

private:
    std::string _dir{"test"};
    std::filesystem::directory_iterator _iter;

    bool targzExtract(const std::string &path) const;
};



#endif //TARGZREADER_HPP
