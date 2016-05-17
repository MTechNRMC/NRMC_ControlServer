#include "Map.h"
#include <queue>
#include <algorithm>

using std::priority_queue;
using std::reverse;

using namespace NRMC_ACS;

struct NodeComparitor
{
	bool operator() (const MapNode* lhs, const MapNode* rhs) const
	{
		if(lhs->fCost() == rhs->fCost())
			return (lhs->hCost > rhs->hCost);

		return (lhs->fCost() > rhs->fCost());
	}
};

Map::Map(Area& mapArea, double resolution, Area& robotFootPrint, int buffer)
{
	width = mapArea.width/resolution;
	length = mapArea.length/resolution;
	this->resolution = resolution;
	rWidth = std::ceil((robotFootPrint.width/2)/resolution)*2;
	rLength = std::ceil((robotFootPrint.length/2)/resolution)*2;

	int nodeId = 0;
	// build the map
	for(int y=0; y < length; y++)
	{
		MapNode* top = y > 0 ? map[y-1]->neighbors[east].node : 0;	// the node above the current node
		MapNode* prev = new MapNode(0, y, nodeId++);
		map.push_back(prev);

		if(y > 0)
		{
			map[y]->attachNode(*map[y-1], north);
			map[y]->attachNode(*(map[y-1]->neighbors[east].node), northEast);
		}

		for(int x=1; x < width; x++)
		{
			MapNode* newNode = new MapNode(x, y, nodeId++);
			newNode->attachNode(*prev, west);

			if(top != 0)
			{
				newNode->attachNode(*top, north);
				newNode->attachNode(*(top->neighbors[west].node), northWest);

				if(top->neighbors[east].node)
					newNode->attachNode(*(top->neighbors[east].node), northEast);

				top = top->neighbors[east].node;
			}

			prev = newNode;
		}
	}

	configMap(rWidth, rLength, buffer);
}

bool Map::findPath(WorldPos& srcPos, WorldPos& tgtPos, vector<WorldPos>& path)
{
	vector<MapNode*> nodePath;
	MapNode* src = getNodeFromWorld(srcPos);
	MapNode* tgt = getNodeFromWorld(tgtPos);

	if(src == 0 || tgt == 0 || !findPath(*src, *tgt, nodePath))
		return false;

	Pos dirOld{0,0};
	//reverse(nodePath.begin(),nodePath.end());
	for(unsigned int node=nodePath.size()-1; node > 0; node--)
	{
		Pos dirNew{nodePath[node-1]->pos.x-nodePath[node]->pos.x, nodePath[node-1]->pos.y - nodePath[node]->pos.y};
		if(dirNew.x != dirOld.x || dirNew.y != dirOld.y)
			path.push_back(WorldPos{(double)(nodePath[node]->pos.x)*resolution, (double)(nodePath[node]->pos.y)*resolution});
		dirOld.x = dirNew.x;
		dirOld.y = dirNew.y;
	}
	reverse(path.begin(),path.end());
	return true;
}

bool Map::findPath(MapNode& src, MapNode& tgt, vector<MapNode*>& path)
{
	MapNode dummyNode(-1,-1,-1);		// used to force update
	priority_queue<MapNode*, vector<MapNode*>, NodeComparitor> openSet;
	vector<bool> closedSet(width*length, false);
	vector<bool> inOpenSet(width*length, false);

	// check if src or target are in an invalid spot
	if(src.blocked || tgt.blocked)
		return false;

	src.gCost = 0;
	src.calcHCost(tgt);
	openSet.push(&src);
	inOpenSet[src.id] = true;

	while(!openSet.empty())
	{
		MapNode* currNode = openSet.top();
		openSet.pop();
		inOpenSet[currNode->id] = false;
		closedSet[currNode->id] = true;

		if(currNode->id == tgt.id)
		{
			buildPath(src, *currNode, path);
			return true;
		}

		for(int neighbor=0; neighbor<NUMOFNEIGHBORS; neighbor++)
		{
			int newGcost;
			MapNode* neighborNode = currNode->neighbors[neighbor].node;
			if(neighborNode == 0 || neighborNode->blocked || closedSet[neighborNode->id])
				continue;

			newGcost = currNode->neighbors[neighbor].weight + currNode->gCost;
			if(newGcost < neighborNode->gCost || !inOpenSet[neighborNode->id])
			{
				neighborNode->gCost = newGcost;
				neighborNode->calcHCost(tgt);
				neighborNode->parrent = currNode;

				// check if the node needs to be added to the list
				if(!inOpenSet[neighborNode->id])
				{
					openSet.push(neighborNode);
					inOpenSet[neighborNode->id] = true;
				}
				else
				{
					openSet.push(&dummyNode);
					openSet.pop();
				}
			}
		}
	}

	return false;
}

Map::~Map()
{
	for(int y=0; y < length; y++)
	{
		destroyMap(map[y]);
	}
}

string Map::displayMap()
{
	string mapString = "";

	for(int y = 0; y<length; y++)
	{
		MapNode* currNode = map[y];
		while(currNode)
		{
			if(currNode->blocked)
				mapString += "X";
			else
				mapString += "0";
			currNode = currNode->neighbors[east].node;
		}
		mapString += "\n";
	}

	return mapString;
}

string Map::displayPath(WorldPos& srcPos, WorldPos& tgtPos)
{
	string mapString = "";
	vector<MapNode*> nodePath;
	MapNode* src = getNodeFromWorld(srcPos);
	MapNode* tgt = getNodeFromWorld(tgtPos);

	if(src == 0 || tgt == 0 || !findPath(*src, *tgt, nodePath))
		return mapString;

	for(int y = 0; y<length; y++)
	{
		MapNode* currNode = map[y];
		while(currNode)
		{
			bool inPath = false;
			for(unsigned int pos=0; pos<nodePath.size(); pos++)
			{
				if(currNode->id == nodePath[pos]->id)
				{
					inPath = true;
					break;
				}
			}
			if(inPath)
				mapString += "!";
			else if(currNode->blocked)
				mapString += "X";
			else
				mapString += "0";

			currNode = currNode->neighbors[east].node;
		}
		mapString += "\n";
	}

	return mapString;
}

string Map::displayWayPoints(WorldPos& srcPos, WorldPos& tgtPos)
{
	string mapString = "";
	MapNode* startNode = getNodeFromWorld(srcPos);
	vector<WorldPos> wayPoints;

	findPath(srcPos, tgtPos, wayPoints);

	for(int y = 0; y<length; y++)
	{
		MapNode* currNode = map[y];
		while(currNode)
		{
			bool isWayPoint = false;
			for(unsigned int pos=0; pos<wayPoints.size(); pos++)
			{
				MapNode* node = getNodeFromWorld(wayPoints[pos]);
				if(currNode->id == node->id)
				{
					isWayPoint = true;
					break;
				}
			}
			if(isWayPoint)
				mapString += "*";
			else if(currNode->id == startNode->id)
				mapString += "S";
			else if(currNode->blocked)
				mapString += "X";
			else
				mapString += "0";

			currNode = currNode->neighbors[east].node;
		}
		mapString += "\n";
	}

	return mapString;
}

void Map::destroyMap(MapNode* node)
{
	if(node == 0)
		return;

	destroyMap(node->neighbors[east].node);
	delete node;
	node = 0;
}

void Map::configMap(int robotWidth, int robotLength, int buffer)
{
	// first buffer the north and south
	MapNode* currNNode = map[0];
	MapNode* currSNode = map[map.size()-1];
	while(currNNode && currSNode)
	{
		MapNode* tmpNNode = currNNode;
		MapNode* tmpSNode = currSNode;
		for(int i=0; i<(robotLength/2)+buffer && tmpNNode && tmpSNode; i++)
		{
			tmpNNode->blocked = true;
			tmpSNode->blocked = true;
			tmpNNode = tmpNNode->neighbors[south].node;
			tmpSNode = tmpSNode->neighbors[north].node;
		}
		currNNode = currNNode->neighbors[east].node;
		currSNode = currSNode->neighbors[east].node;
	}

	// set the east and west
	for(int y=0; y<length; y++)
	{
		MapNode* leftNode = map[y];
		MapNode* rightNode = map[y];

		// get the right or west most node
		while(rightNode && rightNode->neighbors[east].node)
			rightNode = rightNode->neighbors[east].node;

		for(int i=0; i<(robotWidth/2)+buffer && leftNode && rightNode; i++)
		{
			leftNode->blocked = true;
			rightNode->blocked = true;
			leftNode = leftNode->neighbors[east].node;
			rightNode = rightNode->neighbors[west].node;
		}
	}
}

MapNode* Map::getNodeFromWorld(WorldPos& pos)
{
	int x = pos.x/resolution;
	int y = pos.y/resolution;

	// check the pos
	if(pos.x < 0 || pos.y < 0 || x >= width || y >= length)
		return 0;	// pos out of bounds

	MapNode* currNode = map[y];
	for(int i=1; i<x && currNode; i++)
		currNode = currNode->neighbors[east].node;

	return currNode;
}

void Map::buildPath(MapNode& src, MapNode& curr, vector<MapNode*>& path)
{
	if(curr.id == src.id || curr.parrent == 0)
	{
		path.push_back(&curr);
		return;
	}
	buildPath(src, *curr.parrent, path);

	path.push_back(&curr);
	return;
}
