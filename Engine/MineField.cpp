#include "MineField.h"
#include<assert.h>
#include<random>
#include"SpriteCodex.h"
#include<algorithm>

bool MineField::Tile::IsFlagged() const
{
	return state == State::flagged;
}

bool MineField::Tile::IsRevealed() const
{
	return (state == State::revealed);
}

bool MineField::Tile::IsHidden() const
{
	return state == State::hidden;
}

void MineField::Tile::Reveal()
{
	assert(IsHidden());
	assert(!IsRevealed());

	state = State::revealed;
}

void MineField::Tile::SetNeighbourMinesCount(int count)
{
	assert(neighboursMinesCount == -1);

	neighboursMinesCount = count;
}

bool MineField::Tile::HasNoNeighbourMines() const
{
	return neighboursMinesCount == 0;
}

void MineField::Tile::ToggleFlag()
{
	assert(state != State::revealed);
	if (state == State::hidden)
		state = State::flagged;
	else
		state = State::hidden;
}

bool MineField::Tile::HasMine() const
{
	return hasMine;
}

void MineField::Tile::SpawnMine()
{
	assert(hasMine == false);
	hasMine = true;
}

void MineField::Tile::Draw(const Vec2i & screenPos, bool failed ,Graphics & gfx) const
{
	if (!failed)
	{
		switch (state)
		{
		case State::hidden:
			SpriteCodex::DrawTileButton(screenPos, gfx);
			break;
		case State::flagged:
			SpriteCodex::DrawTileButton(screenPos, gfx);
			SpriteCodex::DrawTileFlag(screenPos, gfx);
			break;
		case State::revealed:
			if (HasMine() == true)
				SpriteCodex::DrawTileBomb(screenPos, gfx);
			else
				SpriteCodex::DrawTileNumber(screenPos, neighboursMinesCount, gfx);
			break;
		}
	}
	else
	{
		switch (state)
		{
		case State::hidden:
			if (!HasMine())
				SpriteCodex::DrawTileButton(screenPos, gfx);
			else
				SpriteCodex::DrawTileBomb(screenPos, gfx);
			break;
		case State::flagged:
			if (!HasMine())
			{
				SpriteCodex::DrawTileFlag(screenPos, gfx);
				SpriteCodex::DrawTileCross(screenPos, gfx);
			}
			else
			{
				SpriteCodex::DrawTileBomb(screenPos, gfx);
				SpriteCodex::DrawTileFlag(screenPos, gfx);
			}
			break;
		case State::revealed:
			if (HasMine() == true)
				SpriteCodex::DrawTileBombRed(screenPos, gfx);
			else
				SpriteCodex::DrawTileNumber(screenPos, neighboursMinesCount, gfx);
			break;
		}
	}
	
}

MineField::Tile & MineField::TileAt(Vec2i gridPos)
{
	return field[gridPos.x + width * gridPos.y];
	// TODO: insert return statement here
}

const MineField::Tile & MineField::TileAt(Vec2i gridPos)const
{
	return field[gridPos.x + width * gridPos.y];
	// TODO: insert return statement here
}

MineField::MineField(int nMines)
{
	assert(nMines > 0 && nMines < width * height);
	numberOfMines = nMines;

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int>xDist(0, width - 1);
	std::uniform_int_distribution<int>yDist(0, height - 1);

	for (int nSpawns = 0; nSpawns < nMines; nSpawns++)
	{
		Vec2i spawnPos;
		do
		{
			spawnPos = Vec2i(xDist(rng), yDist(rng));
		} while (TileAt(spawnPos).HasMine() == true);

		TileAt(spawnPos).SpawnMine();
	}

	Vec2i gridPos;
	for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
	{
		for (gridPos.y = 0; gridPos.y < height; gridPos.y++)
		{
			if (!TileAt(gridPos).HasMine())
				TileAt(gridPos).SetNeighbourMinesCount(MinesCount(gridPos));
		}
	}
}

RectI MineField::GetRect(Vec2i offset) const
{
	return RectI(offset + Vec2i(0, 0), offset + Vec2i(width * SpriteCodex::tileSize, height * SpriteCodex::tileSize));
}

void MineField::Draw(const Vec2i& offset,Graphics & gfx) const
{
	RectI rect = GetRect(offset);
	gfx.DrawRect(rect, SpriteCodex::baseColor);
	
	Vec2i gridPos =  Vec2i(0, 0);
	for (; gridPos.y < height; gridPos.y++)
	{
		for (gridPos.x = 0; gridPos.x < width ; gridPos.x++)
		{
			TileAt(gridPos).Draw(offset + gridPos * SpriteCodex::tileSize, failed, gfx);
		}
	}
}

Vec2i MineField::ScreenToGrid(const Vec2i & offset, Vec2i & screenPos) const
{
	screenPos -= offset;

	return screenPos / SpriteCodex::tileSize;
}

void MineField::RevealTile(const Vec2i & offset, Vec2i & screenPos)
{
	if (!failed)
	{
		Vec2i gridpos = ScreenToGrid(offset, screenPos);
		MineField::Tile& tile = TileAt(gridpos);
		if (tile.IsHidden() && !tile.IsRevealed())
		{
			Revealing(gridpos);

			if (tile.HasMine())
				failed = true;
		}
	}
}

/*
* basic job, any tile that has been clicked(hidden and flagged) on will call for this too.
* that particular tile will be revealed by line 208.
* now, if the tile is useless(i.e. no neighbourshas mine too)
* it will call those tiles too...
* and hence the recursion solves it all.
*/
void MineField::Revealing(Vec2i & gridpos)
{
	Tile& tile = TileAt(gridpos);
	tile.Reveal();

	if (tile.HasNoNeighbourMines())
	{
		int xStart = std::max<int>(0, gridpos.x - 1);
		int yStart = std::max<int>(0, gridpos.y - 1);
		int xEnd = std::min<int>(width - 1, gridpos.x + 1);
		int yEnd = std::min<int>(height - 1, gridpos.y + 1);
		
		for (Vec2i pos = Vec2i(xStart, yStart); pos.x <= xEnd; pos.x++)
		{
			for (pos.y = yStart; pos.y <= yEnd; pos.y++)
			{
				if (TileAt(pos).IsHidden()) //////very very important because it will give the tile pointing to the grid.....
					Revealing(pos);
			}
		}
	}
}

void MineField::ToggleFlag(const Vec2i & offset, Vec2i & screenPos)
{
	if (!failed)
	{
		MineField::Tile& tile = TileAt(ScreenToGrid(offset, screenPos));
		if (!tile.IsRevealed())
			tile.ToggleFlag();
	}
}

void MineField::Test(int testCases)
{
	assert(testCases > 0 && testCases < height * width);
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int>xDist(0, width - 1);
	std::uniform_int_distribution<int>yDist(0, height - 1);

	Vec2i spawnPos;
	for (int i = 0; i < testCases; i++)
	{
		spawnPos = Vec2i(xDist(rng), yDist(rng));
		if (!TileAt(spawnPos).IsRevealed())
			TileAt(spawnPos).Reveal();
	}
}

int MineField::MinesCount(const Vec2i & gridPos) const
{
	assert(!TileAt(gridPos).HasMine());

	int xStart = std::max<int>(0, gridPos.x - 1);
	int yStart = std::max<int>(0, gridPos.y - 1);
	int xEnd = std::min<int>(width - 1, gridPos.x + 1);
	int yEnd = std::min<int>(height - 1, gridPos.y + 1);
	int count = 0;
	Vec2i spawnPos;
	for (spawnPos.x = xStart; spawnPos.x <= xEnd; spawnPos.x++)
	{
		for (spawnPos.y = yStart; spawnPos.y <= yEnd; spawnPos.y++)
		{
			if (TileAt(spawnPos).HasMine())
				count++;
		}
	}
	return count;
}

bool MineField::HasWon() const
{
	int nMines = 0;
	for (const Tile& tile : field)
	{
		if (tile.IsFlagged())
		{
			nMines++;
			if (!tile.HasMine())
				return false;
		}
	}
	
	if (nMines == numberOfMines)
		return true;
	
	return false;
}

bool MineField::HasLost() const
{
	return failed;
}
