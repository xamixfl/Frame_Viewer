#include "CompositeLoader.hpp"

#include <filesystem>

#include "../../../../Exceptions/Moderator/ModeratorException.hpp"
#include "../../../../Exceptions/Reader/ReaderException.hpp"
#include "../../../Readers/ArchiveReaders/BaseArchiveReader.hpp"
#include "../../../Readers/ArchiveReaders/targz/TARGZReader.hpp"
#include "../../../Readers/LPReaders/txt/TXTLPReader.hpp"
#include "../../../Readers/LPReaders/csv/CSVLPReader.hpp"
#include "../../../Readers/LPReaders/bin/BINLPReader.hpp"
#include "../../../Readers/PTUReader/cmr/CMRPTUReader.hpp"
#include "../../../Readers/PTUReader/csv/CSVPTUReader.hpp"
#include "../../../Readers/PTUReader/bin/BINPTUReader.hpp"

namespace
{
std::shared_ptr<BaseObject> loadEntry(LoadManager& mgr, const std::string& name)
{
    const auto ext = std::filesystem::path(name).extension().string();

    if (ext == ".txt") return mgr.load<TXTLPReader>(LoadId::Figure, name);
    if (ext == ".csv") return mgr.load<CSVLPReader>(LoadId::Figure, name);
    if (ext == ".bin") return mgr.load<BINLPReader>(LoadId::Figure, name);

    if (ext == ".cmr")    return mgr.load<CMRPTUReader>(LoadId::Camera, name);
    if (ext == ".csvcmr") return mgr.load<CSVPTUReader>(LoadId::Camera, name);
    if (ext == ".bincmr") return mgr.load<BINPTUReader>(LoadId::Camera, name);

    return nullptr;
}
}

std::shared_ptr<BaseObject> CompositeLoader::load(const std::string& filename) const
{
    try
    {
        std::shared_ptr<BaseObject> result = std::make_shared<CompositeObject>();
        for (std::shared_ptr<BaseArchiveReader> reader = std::make_shared<TARGZReader>(filename);
             !reader->isEnd();
             reader->next())
        {
            const std::string name = reader->current();
            if (auto child = loadEntry(*_loader, name))
                result->addChild(child);
        }
        return result;
    }
    catch (std::bad_alloc&)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorModerator_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
    catch (...)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorReader_invalid_archive(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}
