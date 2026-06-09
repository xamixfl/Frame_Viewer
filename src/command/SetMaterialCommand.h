#ifndef SETMATERIALCOMMAND_H
#define SETMATERIALCOMMAND_H

#include "command/BaseCommand.h"
#include "data/Material.h"
#include <vector>
#include <cstddef>

class SceneManager;
class HistoryManager;

class SetMaterialCommand final : public BaseCommand {
public:
    SetMaterialCommand(SceneManager& sceneMgr, HistoryManager& historyMgr, 
                       std::vector<size_t>&& ids, const Material& material);
    
    ~SetMaterialCommand() override = default;

    void execute() override;
    [[nodiscard]] std::string name() const override;

private:
    SceneManager& _sceneMgr;
    HistoryManager& _historyMgr;
    std::vector<size_t> _ids;
    Material _material;
};

#endif // SETMATERIALCOMMAND_H
