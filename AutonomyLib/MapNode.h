/*
 * MapNode.h
 *
 *  Created on: May 13, 2016
 *      Author: pttn40
 */

#ifndef MAPNODE_H_
#define MAPNODE_H_

#define NUMOFNEIGHBORS 8

#include <climits>
#include <cmath>

namespace NRMC_ACS
{
	enum Direction
	{
		north,
		northEast,
		east,
		southEast,
		south,
		southWest,
		west,
		northWest
	};
	struct Pos
	{
		int x, y;
	};

	struct MapNode;
	struct Edge
	{
		MapNode* node;
		int weight;
	};

	struct MapNode
	{
	public:
		int id;
		Pos pos;
		int gCost;
		int hCost;
		bool blocked;
		Edge neighbors[NUMOFNEIGHBORS];
		MapNode* parrent;
		MapNode(int x, int y, int nodeId)
		{
			id = nodeId;
			nodeId++;
			pos.x = x;
			pos.y = y;
			gCost = INT_MAX;
			hCost = INT_MAX;
			blocked = false;
			parrent = 0;

			for(int i=0; i<NUMOFNEIGHBORS; i++)
			{
				neighbors[i].node = 0;
				neighbors[i].weight = (i%2 == 0) ? 10 : 14;
			}
		}
		int fCost() const
		{
			return gCost+hCost;
		}
		void calcHCost(MapNode& target)
		{
			int xDist = std::abs(pos.x - target.pos.x);
			int yDist = std::abs(pos.y - target.pos.y);

			if(xDist > yDist)
				hCost = 14*yDist+10*xDist;
			else
				hCost = 14*xDist+10*yDist;
		}
		void attachNode(MapNode& node, Direction direction)
		{
			int connectBackIndex = (direction+4)%8;
			neighbors[direction].node = &node;
			node.neighbors[connectBackIndex].node = this;
		}
		void removeNode(Direction direction)
		{
			int connectBackIndex = (direction+4)%8;

			// check if node attached
			if(neighbors[direction].node==0)
				return;

			neighbors[direction].node->neighbors[connectBackIndex].node = 0;
			neighbors[direction].node = 0;
		}
	};
}
#endif /* MAPNODE_H_ */
