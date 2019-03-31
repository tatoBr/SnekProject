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

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	startmenu(new class StartMenu())
{
	wnd.kbd.DisableAutorepeat();
}

void Game::Go()
{
	ke = wnd.kbd.ReadKey();//Keyboard event retirado da fila de eventos para ser usado durante este frame
	me = wnd.mouse.Read();//Mouse event retirado da fila de eventos para ser usado durante este frame
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::updateTittleScreen()
{
	using namespace std::chrono;
	
	if (!isInCountDown) {
		if (( ke.IsPress() && ke.GetCode() == VK_RETURN ) || me.LeftIsPressed() )
		{
			countStartPoint = steady_clock::now();
			isInCountDown = true;
		}
	}
	else if(isInCountDown)
	{
		seconds secs(2);//contador com 3 segundos
		steady_clock::time_point ct = steady_clock::now();//novo timePoint inicializado
		duration<float> dur = ct - countStartPoint;
		countDownCounter = int(secs.count() - dur.count());
		
		if (countDownCounter <= 0)
		{			
			gs = GameStatus::StartMenu;
			isInCountDown = false;
		}
	}
}
void Game::composeTittleScreen()
{
	SpriteCodex::drawTitle(gfx, screenArea->getCenterX(), screenArea->getCenterY());
}

void Game::updateStartMenu()
{	
	switch (startmenu->getMenuInstance())
	{
		case StartMenu::Menu::MainMenu:
			//Volta para a tela inicial se a tecla ESC for pressionada;
			if (ke.IsRelease() && ke.GetCode() == VK_ESCAPE)
			{
				gs = GameStatus::TitleScreen;
			}

			//Começa um novo Jogo se o botão 'NEW GAME' for clicado
			if (startmenu->newGameIsPressed(me))
			{
				startRound();
				gs = GameStatus::CountDown;
			}

			//Carrega um jogo salvo em arquivo e inicia
			else if (startmenu->loadGameIsPressed(me))
			{
				startmenu->loadGame();
				startRound();
				gs = GameStatus::CountDown;
			}

			//Vai para o submenu Options se o botão 'OPTIONS' for clicado
			else if (startmenu->OptionIsPressed(me))
			{
				startmenu->setMenuInstance(StartMenu::Menu::OptionMenu);
			}
			break;

		case StartMenu::Menu::OptionMenu:
			//Volta para o menuprincipal se a telcla esc for pressionada
			if (ke.IsRelease() && ke.GetCode() == VK_ESCAPE)
			{
				startmenu->setMenuInstance(StartMenu::Menu::MainMenu);
			}

			//subtrai 1 da altura da Board se o botão '@bhMinusBt' for clicado
			else if (startmenu->bhMinusIsPressed(me))
			{
				const int h = startmenu->getSaveData().mapH - 1;
				startmenu->setBoardHeight(h);
			}
			//soma 1 na altura da Board se o botão '@bhPlusBt' for clicado
			else if (startmenu->bhPlusIsPressed(me))
			{
				const int h = startmenu->getSaveData().mapH + 1;
				startmenu->setBoardHeight(h);
			}

			//subtrai 1 da largura da Board se o botão '@bwMinusBt' for clicado
			else if (startmenu->bwMinusIsPressed(me))
			{
				const int w = startmenu->getSaveData().mapW - 1;
				startmenu->setBoardWidth(w);
			}
			//soma 1 da largura da Board se o botão '@bwPlusBt' for clicado
			else if (startmenu->bwPlusIsPressed(me))
			{
				const int w = startmenu->getSaveData().mapW + 1;
				startmenu->setBoardWidth(w);
			}

			//Salva as definições de opções
			else if (startmenu->saveOptBtIsPressed(me))
			{
				startmenu->saveOptions();
			}

			break;
	default:
		break;
	}	
}
void Game::composeStartMenu()
{
	startmenu->draw( gfx, palettes[0], wnd.mouse.GetPosX(), wnd.mouse.GetPosY());
}

void Game::updateCountDown()
{
	using namespace std::chrono;

	if (!isInCountDown)
	{
		mouseX = screenArea->getCenterX() - 24;
		mouseY = screenArea->getCenterY() - 24;
		countStartPoint = steady_clock::now();
		isInCountDown = true;
	}

	seconds sec(4);//total de segundo do contador;
	steady_clock::time_point ct = steady_clock::now();// momento do frame atual
	duration<float> timeLapse = ct - countStartPoint;// duração entre o ponto inicial e o frameatual
	countDownCounter = int(sec.count() - timeLapse.count());

	if (countDownCounter < 0)
	{
		isInCountDown = false;
		gs = GameStatus::GameRunning;
		ft->measureTimeSpan();
		deltaTime = 0.0f;
	}
}
void Game::composeCountDown()
{	
	hud->drawHud( gfx, palettes[hud->getStage() % nPalettes] );
	board->drawBoard( gfx, palettes[hud->getStage() % nPalettes], keyFrame );
	if (countDownCounter > 0)
	{
		const int x = screenArea->getCenterX() - 24;
		const int y = screenArea->getCenterY() - 24;
		CharsCodex::m64_48x48_Number(countDownCounter, gfx, x, y);
	}
	else
	{
		CharsCodex::drawString("GO", screenArea->getCenterX(), screenArea->getCenterY(), gfx, Colors::Red);
	}
}

void Game::updateRunning()
{
	deltaTime += ft->measureTimeSpan();	

	switch (ke.GetCode())
	{
	case 'W':
		if ( inputConsumed && snake->getAxis() == Snake::Direction::HORIZOLTALLY )
		{
			snake->setDirection(Snake::Direction::UP);
			inputConsumed = false;
		}
		break;
	case 'S':
		if ( inputConsumed && snake->getAxis() == Snake::Direction::HORIZOLTALLY )
		{
			snake->setDirection(Snake::Direction::DOWN);
			inputConsumed = false;
		}
		break;
	case 'A':
		if ( inputConsumed && snake->getAxis() == Snake::Direction::VERTICALLY )
		{
			snake->setDirection(Snake::Direction::LEFT);
			inputConsumed = false;
		}
		break;
	case 'D':
		if ( inputConsumed && snake->getAxis() == Snake::Direction::VERTICALLY )
		{
			snake->setDirection(Snake::Direction::RIGHT);
			inputConsumed = false;
		}
		break;

	case VK_RETURN:
		gs = GameStatus::PauseMenu;
		break;

	default:
		break;
	}

	if (deltaTime >= velocity)
	{
		keyFrame = (keyFrame < 4) ? keyFrame + 1 : 1;
		deltaTime -= velocity;
		inputConsumed = true;

		switch ( board->moveSnake(*snake) )
		{
		case Board::CellType::Food:
			hud->updateScore(50 * comboCounter);
			comboCounter++;

			if (snake->getSnkLenght() > 8)
			{
				stageUp();
			}
			break;

		case Board::CellType::Poison:
			velocity -= velocity / 10;
			comboCounter = 1;
			break;

		case Board::CellType::OffBoundarie:
		case Board::CellType::Obstacle:
		case Board::CellType::Snk:
			velocity = startVel;
			hud->dropLife();

			if (hud->getLifes() <= 0)
			{
				gs = GameStatus::GameOver;
			}
			else
			{				
				board->eraseSnkFromBoard(*snake);
				snake->InitializeSnake();
				board->setSnakeOnBoard(*snake);
				gs = GameStatus::CountDown;
			}
			break;

		default:
			break;
		}
	}
}
void Game::composeRunning()
{
	hud->drawHud(gfx, palettes[hud->getStage() % nPalettes]);
	board->drawBoard(gfx, palettes[hud->getStage() % nPalettes], keyFrame);
}

void Game::UpdateModel()
{	
	switch (gs)
	{
	case Game::TitleScreen:
		updateTittleScreen();	
		break;

	case Game::StartMenu:
		updateStartMenu();	
		break;

	case Game::CountDown:
		updateCountDown();		
		break;

	case Game::GameRunning:
		updateRunning();
		break;

	case Game::PauseMenu:
		//updatePauseMenu();	
		break;

	case Game::GameOver:
		break;
	
	default:
		break;
	}
}
void Game::ComposeFrame()
{	
	switch (gs)
	{
	case Game::TitleScreen:		
		composeTittleScreen();
		break;
	case Game::StartMenu:		
		composeStartMenu();
		break;

	case Game::CountDown:		
		composeCountDown();
		break;

	case Game::GameRunning:
		composeRunning();
		break;

	case Game::PauseMenu:		
		//composePauseMenu();
		break;

	
	default:
		break;
	}
}

void Game::startRound()
{
	board = new Board(startmenu->getSaveData().mapW, startmenu->getSaveData().mapH);//Cria uma nova Istancia de Board
	hud = new HeadsUpDisplay(board->getWidth());//Cria uma nova Istancia de HUD
	snake = new Snake(board->getCenter().x, board->getCenter().y);//Cria uma nova Istancia de Snake

	hud->setStage(startmenu->getSaveData().stage);
	hud->setScore(startmenu->getSaveData().score);
	hud->setLifes(startmenu->getSaveData().lives);	

	velocity = startmenu->getSaveData().velocity;
	startVel = velocity;

	const int obst = 8 + (2 * hud->getStage());
	const int pois = 8 + (8 * hud->getStage());
	board->startUpBoard(*snake, obst, pois); //prepara a snake dentro da board
}
void Game::finishRound()
{
	gs = GameStatus::StartMenu;

	delete hud;
	delete board;
	delete snake;

	hud = nullptr;
	board = nullptr;
	snake = nullptr;
}

void Game::stageUp()
{
	gs = GameStatus::CountDown;
	wnd.kbd.Flush();
	hud->stageUp();
	const int obst = 8 + (2 * hud->getStage());
	const int pois = 8 + (8 * hud->getStage());
	snake->InitializeSnake();
	board->startUpBoard(*snake, obst, pois); //prepara a snake dentro da board	
}


