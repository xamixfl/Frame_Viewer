#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <memory>
#include "base_manager.h"
#include "base_drawer.h"

class DrawManager: public BaseManager
{
public:
	DrawManager() = default;
	~DrawManager() override = default;

	void drawScene();
	void setDrawer(std::shared_ptr<BaseDrawer> drawer_);
private:
	std::shared_ptr<BaseDrawer> drawer;
};


#endif //DRAW_MANAGER_H
