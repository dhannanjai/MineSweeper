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

		bool IsRevealed()const;
		void Reveal();
	};
public:
	static constexpr int width = 12;
	static constexpr int height = 12;

	Tile field[width * height];

private:
	Tile& TileAt(Vec2i gridPos);
	const Tile& TileAt(Vec2i gridPos)const;
	
public:
	MineField(int nMines);
	void Draw(const Vec2i& offset, Graphics& gfx)const;
	Vec2i ScreenToGrid(const Vec2i& offset, Vec2i& screenPos)const;
	void RevealTile(const Vec2i& offset, Vec2i& screenPos);

	void Test(int testCases);
};