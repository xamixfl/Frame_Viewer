#ifndef AUTOREADER_H
#define AUTOREADER_H

#include <memory>
#include <string>

#include "reader/BaseReader.h"

class AutoReader final : public BaseReader {
public:
    AutoReader() = default;
    ~AutoReader() override = default;

    void open(const std::string& filename) override;
    void close() noexcept override;

    double read() override;

    [[nodiscard]] bool isOpen() const noexcept override;
    [[nodiscard]] bool eof() const noexcept override;

private:
    std::unique_ptr<BaseReader> _impl;

    [[nodiscard]] static std::unique_ptr<BaseReader> _selectReader(const std::string& filename);
};

#endif // AUTOREADER_H
