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
		int neighboursMinesCount = -1;

	public:
		bool HasMine()const;
		void SpawnMine();
		void Draw(const Vec2i& screenPos,bool failed, Graphics& gfx)const;
		void ToggleFlag();
		void Reveal();
		void SetNeighbourMinesCount(int count);
		bool HasNoNeighbourMines()const;

		bool IsFlagged()const;
		bool IsRevealed()const;
		bool IsHidden()const;
	};
public:
	static constexpr int width = 12;
	static constexpr int height = 12;

	Tile field[width * height];

private:
	Tile& TileAt(Vec2i gridPos);
	const Tile& TileAt(Vec2i gridPos)const;
	bool failed = false;
	bool won = false;
	int numberOfMines;
public:
	MineField(int nMines);
	Vec2i ScreenToGrid(const Vec2i& offset, Vec2i& screenPos)const;
	RectI GetRect(Vec2i offset)const;

	void Draw(const Vec2i& offset, Graphics& gfx)const;
	
	void RevealTile(const Vec2i& offset, Vec2i& screenPos);
	void Revealing(Vec2i& gridpos);
	void MarkFlag(const Vec2i& offset, Vec2i& screenPos);

	int MinesCount(const Vec2i& gridPos)const;
	bool HasWon()const;
	bool HasLost()const;

	void Test(int testCases);
};