#pragma once

#include "Map/MapCoordinate.h"

#include <vector>


class Tile;
class TileMap;


/**
 * GraphWalker does a basic depth-first connection check
 *			on a TileMap given a starting point.
 */
class GraphWalker
{
public:
	GraphWalker(const MapCoordinate&, TileMap&, std::vector<Tile*>&);
	~GraphWalker() = default;

private:
	GraphWalker() = delete;
	GraphWalker(GraphWalker&) = delete;
	GraphWalker& operator=(const GraphWalker&) = delete;

private:
	void walkGraph(const MapCoordinate& position, TileMap& tileMap, std::vector<Tile*>& tileList);

private:
	TileMap& mTileMap;
	std::vector<Tile*>& mTileList;

	MapCoordinate mPosition{};
};
