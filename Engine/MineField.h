#pragma once
#include "Vec2i.h"
#include"Graphics.h"
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
		void Draw(const Vec2i& screenPos, Graphics& gfx)const;
	};
public:
	static constexpr int width = 10;
	static constexpr int height = 5;

	Tile field[width * height];
public:
	Tile& TileAt(Vec2i gridPos);
	const Tile& TileAt(Vec2i gridPos)const;
	MineField(int nMines);
	void Draw(const Vec2i& offset, Graphics& gfx)const;
};