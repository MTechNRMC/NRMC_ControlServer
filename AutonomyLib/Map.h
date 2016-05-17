/*
 * Map.h
 *
 *  Created on: May 13, 2016
 *      Author: pttn40
 */

#ifndef MAP_H_
#define MAP_H_
#include "MapNode.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

namespace NRMC_ACS
{
	struct WorldPos
	{
		double x, y;
	};
	struct Area
	{
		double width, length;
	};

	class Map
	{
	protected:
		int width, length, rWidth, rLength;
		double resolution;

		vector<MapNode*> map;
	public:
		Map(Area& mapArea, double resolution, Area& robotFootPrint, int buffer = 0);
		virtual ~Map();
		bool findPath(WorldPos& srcPos, WorldPos& tgtPos, vector<WorldPos>& path);
		bool findPath(MapNode& src, MapNode& tgt, vector<MapNode*>& path);
		MapNode* getNodeFromWorld(WorldPos& pos);
		virtual string displayMap();
		string displayPath(WorldPos& srcPos, WorldPos& tgtPos);
		string displayWayPoints(WorldPos& srcPos, WorldPos& tgtPos);
	private:
		void destroyMap(MapNode* node);
		void configMap(int robotWidth, int robotLength, int buffer);
		void buildPath(MapNode& src, MapNode& curr, vector<MapNode*>& path);
	};
}

#endif /* MAP_H_ */
