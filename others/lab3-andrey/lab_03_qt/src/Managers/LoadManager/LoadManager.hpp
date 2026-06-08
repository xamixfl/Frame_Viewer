#ifndef LOADMANAGER_HPP
#define LOADMANAGER_HPP
#include <memory>
#include <string>
#include <type_traits>

#include "../BaseManager.hpp"
#include "LoadId.hpp"
#include "../../BaseObject/BaseObject.hpp"
#include "../../Builders/Directors/Solution/DirectorSolution.hpp"
#include "../../Builders/Readers/Base/BaseReader.hpp"
#include "../../Exceptions/Managers/LoadManagerException.hpp"

class LoadManager final : public BaseManager
{
public:
    LoadManager() : _solution(std::make_shared<DirectorSolution>()) {}
    explicit LoadManager(std::shared_ptr<DirectorSolution> solution) : _solution(std::move(solution)) {}
    ~LoadManager() override = default;

    template <typename TReader>
    requires std::is_base_of_v<BaseReader, TReader> && (!std::is_abstract_v<TReader>)
    std::shared_ptr<BaseObject> load(LoadId id, const std::string& filename)
    {
        try
        {
            std::shared_ptr<BaseReader> reader = std::make_shared<TReader>(filename);
            const auto creator = _solution->create(id);
            if (!creator)
            {
                const time_t cur_time = time(nullptr);
                throw ErrorLoadManager_invalid_loading(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
            }
            const auto director = creator->createDirector(reader);
            return director->create();
        }
        catch (std::bad_alloc&)
        {
            const time_t cur_time = time(nullptr);
            throw ErrorLoadManager_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
        }
        catch (ErrorLoadManager_bad_alloc&) { throw; }
        catch (ErrorLoadManager_invalid_loading&) { throw; }
        catch (ErrorLoadManager_invalid_file&) { throw; }
        catch (...)
        {
            const time_t cur_time = time(nullptr);
            throw ErrorLoadManager_invalid_loading(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
        }
    }

private:
    std::shared_ptr<DirectorSolution> _solution;
};

#endif //LOADMANAGER_HPP
