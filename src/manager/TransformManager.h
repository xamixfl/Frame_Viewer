#ifndef TRANSFORMMANAGER_H
#define TRANSFORMMANAGER_H

#include <cstddef>
#include <string>
#include <vector>

#include "manager/BaseManager.h"

class BaseObject;
class Transform;
class SceneManager;
class HistoryManager;

class TransformManager final : public BaseManager {
public:
    void move(BaseObject& obj, const Transform& t);
    void rotate(BaseObject& obj, const Transform& t);
    void scale(BaseObject& obj, const Transform& t);

    void moveGroup(SceneManager& sceneMgr, HistoryManager& historyMgr,
                   const std::vector<size_t>& ids, const Transform& t, const std::string& opName);
    void rotateGroup(SceneManager& sceneMgr, HistoryManager& historyMgr,
                     const std::vector<size_t>& ids, const Transform& t, const std::string& opName);
    void scaleGroup(SceneManager& sceneMgr, HistoryManager& historyMgr,
                    const std::vector<size_t>& ids, const Transform& t, const std::string& opName);
};

#endif
