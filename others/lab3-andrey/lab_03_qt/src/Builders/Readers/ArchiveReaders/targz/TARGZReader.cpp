//
// Created by nuelex on 27/05/25.
//

#include <archive.h>
#include <archive_entry.h>
#include "TARGZReader.hpp"

#include "../../../../Exceptions/Reader/ReaderException.hpp"

TARGZReader::TARGZReader(const std::string& path)
{
    try
    {
        bool flag = targzExtract(path);
        if (!flag)
        {
            const time_t cur_time = time(nullptr);
            throw ErrorReader_invalid_archive(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
        }

        _iter = std::filesystem::directory_iterator("./" + _dir);
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorReader_invalid_archive(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}

bool TARGZReader::targzExtract(const std::string& path) const
{
    struct archive* a = archive_read_new();
    struct archive* ext = archive_write_disk_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM);

    system(("mkdir -p " + _dir).c_str());

    if (archive_read_open_filename(a, path.c_str(), 10240) != ARCHIVE_OK)
    {
        return false;
    }

    struct archive_entry* entry;
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK)
    {
        std::string full_path = std::string{"./" + _dir} + "/" + archive_entry_pathname(entry);;
        archive_entry_set_pathname(entry, full_path.c_str());

        if (archive_write_header(ext, entry) != ARCHIVE_OK)
        {
            continue;
        }

        if (archive_entry_size(entry) > 0)
        {
            const void* buff;
            size_t size;
            la_int64_t offset;
            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK)
            {
                archive_write_data_block(ext, buff, size, offset);
            }
        }
        archive_write_finish_entry(ext);
    }

    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);

    return true;
}

TARGZReader::~TARGZReader()
{
    std::filesystem::remove_all(_dir);
}



