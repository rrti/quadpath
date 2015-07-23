#include "IPathManager.hpp"
#include "HAPFS/PathManager.hpp"
#include "QTPFS/PathManager.hpp"
#include "System/Log/ILog.hpp"

IPathManager* pathManager = NULL;

IPathManager* IPathManager::GetInstance(unsigned int type) {
	if (pathManager == NULL) {
		const char* fmtStr = "[IPathManager::GetInstance] using %s path-manager";
		const char* typeStr = "";

		switch (type) {
			case PFS_TYPE_HAPFS: { typeStr = "HAPFS"; pathManager = new HAPFS::PathManager(); } break;
			case PFS_TYPE_QTPFS: { typeStr = "QTPFS"; pathManager = new QTPFS::PathManager(); } break;
		}

		LOG(fmtStr, typeStr);
	}

	return pathManager;
}

void IPathManager::FreeInstance(IPathManager* pm) {
	assert(pm == pathManager);
	delete pm;
	pathManager = NULL;
}

