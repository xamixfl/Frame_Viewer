#ifndef LOAD_MANAGER_H
#define LOAD_MANAGER_H

#include <memory>
#include "base_manager.h"
#include "base_object.h"
#include "data_source_solution.h"
#include "director_solution.h"

#define LIST_MODEL_DIRECTOR_ID 1
#define MATRIX_MODEL_DIRECTOR_ID 2

#define TXT_DATA_SOURCE_ID 1
#define CSV_DATA_SOURCE_ID 2


class LoadManager: public BaseManager
{
public:
	LoadManager();
	~LoadManager() override = default;

	std::shared_ptr<BaseObject> loadModelFromFile(const std::string &filename, size_t directorID, size_t dataSourceID);
	std::shared_ptr<BaseObject> loadModelFromFile(const std::string &filename);

private:
	std::shared_ptr<CarcassModelDirectorSolution> directorSolution;
	std::shared_ptr<DataSourceSolution> dataSourceSolution;

	void registerFileExtension(const std::string &extension,
							   size_t dataSourceId,
							   size_t directorId);
	std::map<std::string, std::pair<size_t, size_t>> extensionMap;
	[[nodiscard]] static std::string getFileExtension(const std::string &filePath) ;
};


#endif //LOAD_MANAGER_H
