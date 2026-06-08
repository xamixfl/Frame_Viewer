//
// Created by nuelex on 27/05/25.
//

#ifndef BASEARCHIVEREADER_HPP
#define BASEARCHIVEREADER_HPP
#include <string>


class BaseArchiveReader
{
public:
    BaseArchiveReader() = default;
    virtual ~BaseArchiveReader() = default;

    virtual void next() = 0;
    virtual std::string current() const = 0;
    virtual bool isEnd() const = 0;
};

#endif //BASEARCHIVEREADER_HPP
