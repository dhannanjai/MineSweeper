/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include"Graphics.h"
#include "Colors.h"
#include"SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	mineField(7),
	offset(Graphics::GetScreenRect().GetCenter() - Vec2i((MineField::width * SpriteCodex::tileSize) / 2, (MineField::height * SpriteCodex::tileSize) / 2)),
	spayed(L"spayed.wav"),
	won(L"menu_boop.wav")
{
	//mineField.Test(50);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();
		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			Vec2i screenPos = wnd.mouse.GetPos();
			if (mineField.GetRect(offset).Contains(screenPos))
				mineField.RevealTile(offset, screenPos);
		}
		if (e.GetType() == Mouse::Event::Type::RPress)
		{
			Vec2i screenPos = wnd.mouse.GetPos();
			if (mineField.GetRect(offset).Contains(screenPos))
				mineField.MarkFlag(offset, screenPos);
		}
	}

	hasWon = mineField.HasWon();
	hasLost = mineField.HasLost();
}

void Game::ComposeFrame()
{
	mineField.Draw(offset, gfx);
	if (hasWon)
	{
		SpriteCodex::DrawWin(Graphics::GetScreenRect().GetCenter(), gfx);
		
		if (!spayedIsPlayed)
		{
			won.Play();
			wonIsPlayed = true;
		}
	}
	if (hasLost && !spayedIsPlayed)
	{
		spayed.Play();
		spayedIsPlayed = true;
	}
}

