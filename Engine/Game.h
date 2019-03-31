/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "FrameTimer.h"
#include "SpriteCodex.h"
#include "CharsCodex.h"
#include "HeadsUpDisplay.h"
#include "StartMenu.h"

class Game
{
	static constexpr int nPalettes = 10; //Número de paletta de cores
	static constexpr Palette palettes[] = {
		//pallet 0:
		{
			{ 0, 84, 84 },//shadow		
			{ 0, 186, 186 },//highlight
			{ 0, 132, 132 }//color
		},

		//pallet 1:
		{
			{ 24, 0, 96 },//shadow
			{ 0, 120, 255 },//highlight
			{ 66, 0, 255 }//color
		},

		//pallet 2:
		{
			{ 0, 96, 96 },//shadow
			{ 0, 196, 196 },//highlight
			{ 0, 148, 148 }//color
		},

		//pallet 3:
		{
			{ 112, 98, 0 },//shadow
			{ 164, 144, 0 },//highlight
			{ 132, 116, 0 }//color
		},

		//pallet 4:
		{
			{ 0, 98, 0 },//shadow
			{ 0, 186, 0 },//highlight
			{ 0, 165, 0 }//color
		},

		//pallet 5:
		{
			{ 0, 66, 33 },//shadow
			{ 255, 198, 66 },//highlight
			{ 132, 132, 0 }//color
		},

		//pallet 6:
		{
			{ 0, 66, 0 },//shadow
			{ 66, 198, 66 },//highlight
			{ 0, 165, 0 }//color
		},

		//pallet 7:
		{
			{ 64, 64, 64 },//shadow
			{ 196, 196, 196 },//highlight
			{ 132, 132, 132 }//color
		},

		//pallet 8:
		{
			{ 0, 64, 148 },//shadow
			{ 0, 198, 255 },//highlight
			{ 99, 165, 255 }//color
		},

		//pallet 9:
		{
			{ 232, 33, 0 },//shadow
			{ 255, 165, 66 },//highlight
			{ 198, 16, 0 }//color
		}
	};
public:
	Game( class MainWindow& wnd );
	~Game()
	{
		delete ft;
		delete startmenu;
		delete board;
		delete hud;
		delete screenArea;

		ft = nullptr;
		startmenu = nullptr;
		board = nullptr;
		hud = nullptr;
		screenArea = nullptr;
	}
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	enum GameStatus : char{
		TitleScreen,
		StartMenu,		
		CountDown,
		GameRunning,
		PauseMenu,
		GameOver
	};
	void updateTittleScreen();
	void composeTittleScreen();

	void updateStartMenu();
	void composeStartMenu();

	void updateCountDown();
	void composeCountDown();

	void updateRunning();
	void composeRunning();

	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void startRound();//começa um novo round do jogo
	void finishRound();//finalina o round do jogo;
	void stageUp();	
	
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	HeadsUpDisplay * hud = nullptr;//Aloca memoria dinamica para hud
	class StartMenu * startmenu = nullptr;//Aloca memoria dinamica para o startmenu
	Board * board = nullptr;//Aloca Memoria Dinamica para Board
	Snake * snake = nullptr;//Aloca Memoria Dinamica para snake

	Keyboard::Event ke;
	Mouse::Event me;

	/****************************** Variaveis e Metodos de controle de Tempo**************************************/
	FrameTimer * ft = new FrameTimer();
	std::chrono::steady_clock::time_point countStartPoint; //@countStartPoint marcador que guarda o momento que a contagem se inicia
	bool isInCountDown = false;//@isInCountDown flag que marca se o jogo está em contagem regressiva;
	int countDownCounter = 0;//@countDownCounter Contador da Contagem Regressiva
	float deltaTime = 0.0f;
	float velocity = 0.0f;
	int keyFrame = 0;	

	int mouseX;
	int mouseY;

	GameStatus gs = GameStatus::TitleScreen;	
	Rect * screenArea = new Rect(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight);

	bool inputConsumed = true;
	
	
	float startVel = velocity;

	int comboCounter = 1;
	
	
	/********************************/
};