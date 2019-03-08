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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	board( 640, (640 * BOARD_N_LINS) / BOARD_N_COLS),
	snake(BOARD_N_COLS/2, BOARD_N_LINS / 2)
{	
	snake.InitializeSnake();
	board.setSnakeOnBoard(snake);
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
	deltaTime += ft.measureTimeSpan();
	int movingTo = snake.getDirection();
	
	if (wnd.kbd.KeyIsPressed('W'))
	{
		if (movingTo == SNAKE_MOVING_LEFT || movingTo == SNAKE_MOVING_RIGHT)
		{
			snake.setDirection(SNAKE_MOVING_UP);
			coolOff = false;
		}		
	}

	else if (wnd.kbd.KeyIsPressed('S'))
	{
		if (movingTo == SNAKE_MOVING_LEFT || movingTo == SNAKE_MOVING_RIGHT)
		{
			snake.setDirection(SNAKE_MOVING_DOWN);
			coolOff = false;
		}
	}

	else if (wnd.kbd.KeyIsPressed('A'))
	{
		if (movingTo == SNAKE_MOVING_UP || movingTo == SNAKE_MOVING_DOWN)
		{
			snake.setDirection(SNAKE_MOVING_LEFT);
			coolOff = false;
		}
	}

	else if (wnd.kbd.KeyIsPressed('D'))
	{
		if (movingTo == SNAKE_MOVING_UP || movingTo == SNAKE_MOVING_DOWN)
		{
			snake.setDirection(SNAKE_MOVING_RIGHT);
			coolOff = false;
		}
	}	

	if (deltaTime >= velocity) {		
		deltaTime -= velocity;
		coolOff = true;	
		board.moveSnake(snake, velocity);
	}

	
}

void Game::ComposeFrame()
{
	board.drawBoard(gfx);
}
