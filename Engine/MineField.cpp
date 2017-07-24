#include "MineField.h"
#include<assert.h>
#include<random>
#include"SpriteCodex.h"

bool MineField::Tile::HasMine() const
{
	return hasMine;
}

void MineField::Tile::SpawnMine()
{
	assert(hasMine == false);
	hasMine = true;
}

void MineField::Tile::Draw(const Vec2i & screenPos, Graphics & gfx) const
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
			SpriteCodex::DrawTile0(screenPos, gfx);
		break;
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
}

void MineField::Draw(const Vec2i& offset,Graphics & gfx) const
{
	RectI rect = RectI(Vec2i(0, 0),Vec2i(width * SpriteCodex::tileSize, height * SpriteCodex::tileSize));
	gfx.DrawRect(rect, SpriteCodex::baseColor);
	
	Vec2i gridPos =  Vec2i(0, 0);
	for (; gridPos.y < height; gridPos.y++)
	{
		for (gridPos.x = 0; gridPos.x < width ; gridPos.x++)
		{
			TileAt(gridPos).Draw(gridPos * SpriteCodex::tileSize,gfx);
		}
	}
}
