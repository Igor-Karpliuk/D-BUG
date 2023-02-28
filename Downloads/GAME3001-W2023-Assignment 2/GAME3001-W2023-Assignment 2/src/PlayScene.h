#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Target.h"
#include "StarShip.h"
#include "Tile.h"
#include "Heuristic.h"
#include "Obstacle.h"
#include <queue>
#include "TileComparator.h"
#include "Label.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene() override;

	// Scene LifeCycle Functions
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void HandleEvents() override;
	virtual void Start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	glm::vec2 m_mousePosition;

	// Game Objects for the Scene
	Target* m_pTarget;
	StarShip* m_pStarShip;

	// Debugging Variables
	bool m_bDebugView;

	// Pathfinding Objects and Functions
	std::vector<Tile*> m_pGrid;
	bool m_isGridEnabled;

	void m_buildGrid();
	bool m_getGridEnabled() const;
	void m_setGridEnabled(bool state);
	void m_computeTileCosts();

	// obstacle list
	std::vector<Obstacle*> m_pObstacles;
	void m_buildObstacles();

	// obstacle utility functions
	void m_removeObstacleAt(int col, int row);
	void m_removeObstacleAt(glm::vec2 grid_position);
	void m_removeAllObstacles();

	// collections, variables for pathfinding
	std::priority_queue<Tile*, std::vector<Tile*>, TileComparator> m_pOpenList; // visited but not expanded list of tiles
	std::list<Tile*> m_pPathList;
	bool m_pathFound = false;

	// pathfinding functions
	void m_findShortestPath();
	void m_buildPathList();
	void m_displayPathList() const;
	void m_resetPathFinding();
	void m_resetSimulation();

	// convenience functions to convert from world space to grid space
	Tile* m_getTile(int col, int row) const;
	Tile* m_getTile(glm::vec2 grid_position) const;

	template <typename T>
	void m_addObjectToGrid(T*& object, int col, int row, TileStatus status);

	template <typename T>
	void m_moveGameObject(T*& object, int col, int row, TileStatus status);

	// heuristic
	Heuristic m_currentHeuristic;

	// Tile Map Variables and Functions
	std::string m_tileMap;
	void m_initializeTileMap();
	void m_buildTileMap();

	// convenience functions to update the Tile Map
	void m_updateTileMap(int col, int row, TileStatus status);
	void m_updateTileMap(glm::vec2 grid_position, TileStatus status);

	// unique variables for ship path movement
	bool toggleFollowPath = false;
	void m_followPath();

	Label* m_pStartLabel{};
};

#endif /* defined (__PLAY_SCENE__) */ 