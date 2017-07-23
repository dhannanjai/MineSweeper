#pragma once
#include "Vec2i.h"

class MineField
{
public:
	class Tile 
	{
	public:
		enum class State
		{
			hidden,
			flagged,
			revealed
		};
	private:
		bool hasMine = false;
		State state = State::hidden;
	
	public:
		bool HasMine()const;
		void SpawnMine();
	};
private:
	static constexpr int width = 10;
	static constexpr int height = 5;

	Tile field[width * height];
public:
	Tile& TileAt(Vec2i gridPos);
	MineField(int nMines);
};