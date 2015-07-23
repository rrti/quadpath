#ifndef I_PATH_MANAGER_H
#define I_PATH_MANAGER_H

#include <boost/cstdint.hpp>

#include "PFSTypes.hpp"
#include "System/type2.h"
#include "System/float3.h"

struct MoveDef;
class CSolidObject;

class IPathManager {
public:
	static IPathManager* GetInstance(unsigned int type);
	static void FreeInstance(IPathManager* pm);

	virtual ~IPathManager() {}

	virtual unsigned int GetPathFinderType() const = 0;
	virtual boost::uint32_t GetPathCheckSum() const { return 0; }

	virtual boost::int64_t Finalize() { return 0; }

	/**
	 * returns if a path was changed after RequestPath returned its pathID
	 * this can happen eg. if a PathManager reacts to TerrainChange events
	 * (by re-requesting affected paths without changing their ID's)
	 */
	virtual bool PathUpdated(unsigned int pathID) { return false; }

	virtual void Update() {}
	virtual void UpdatePath(const CSolidObject* owner, unsigned int pathID) {}
	virtual void DeletePath(unsigned int pathID) {}

	virtual float3 NextWayPoint(
		const CSolidObject* owner,
		unsigned int pathID,
		unsigned int numRetries,
		float3 callerPos,
		float radius,
		bool synced
	) { return ZeroVector; }

	virtual void GetPathWayPoints(
		unsigned int pathID,
		std::vector<float3>& points,
		std::vector<int>& starts
	) const {}

	virtual unsigned int RequestPath(
		CSolidObject* caller,
		const MoveDef* moveDef,
		const float3& startPos,
		const float3& goalPos,
		float goalRadius,
		bool synced
	) { return 0; }

	virtual void TerrainChange(unsigned int x1, unsigned int z1, unsigned int x2, unsigned int z2, unsigned int type) {}

	virtual int2 GetNumQueuedUpdates() const { return (int2(0, 0)); }
};

extern IPathManager* pathManager;

#endif

