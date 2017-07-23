#include "MineField.h"
#include<assert.h>
#include<random>

bool MineField::Tile::HasMine() const
{
	return hasMine;
}

void MineField::Tile::SpawnMine()
{
	assert(hasMine == false);
	hasMine = true;
}

MineField::Tile & MineField::TileAt(Vec2i gridPos)
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
