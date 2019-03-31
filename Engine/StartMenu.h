#pragma once

#include "CharsCodex.h"
#include "SpriteCodex.h"
#include "Board.h"
#include  "Mouse.h"

#include <string>
#include <fstream>

class StartMenu
{
private:
	const std::string optionFile = "options.txt";
	const std::string saveFile = "save.txt";

public:
	struct Data
	{
		int stage;
		int score;
		int lives;
		int mapW;
		int mapH;
		float velocity;
		int difficulty;
	};

	enum Menu : char {
		MainMenu,
		LoadMenu,
		OptionMenu
	};

public:
	// ******* Static variables ****** //
	static constexpr int tileSize = 16; //tiles 16px x 16px
	static constexpr int labelHeight = 32; //label is 32px high
	static constexpr int labelWidth = 256; //label is 256px long
	static constexpr int menuSize = ( Graphics::ScreenHeight - ( 6 * tileSize )) / tileSize * tileSize;
	static constexpr int xCoord = ( Graphics::ScreenWidth - menuSize ) / 2;
	static constexpr int yCoord = ( Graphics::ScreenHeight - menuSize ) / 2;
	
	StartMenu();
	~StartMenu()
	{
		delete nGameBt;
		delete lGameBt;
		delete optBt;
		delete bhMinusBt;
		delete bhPlusBt;

		nGameBt = nullptr;
		lGameBt = nullptr;
		optBt = nullptr;
		bhMinusBt = nullptr;
		bhPlusBt = nullptr;
	}
	
	void saveOptions() const;
	void saveGame() const;
	bool loadOptions();
	bool loadGame();	

	bool newGameIsPressed(Mouse::Event event) const;	
	bool loadGameIsPressed(Mouse::Event event) const;	
	bool OptionIsPressed(Mouse::Event event) const;
	bool bhMinusIsPressed(Mouse::Event event) const;
	bool bhPlusIsPressed(Mouse::Event event) const;
	bool bwMinusIsPressed(Mouse::Event event) const;
	bool bwPlusIsPressed(Mouse::Event event) const;
	bool saveOptBtIsPressed(Mouse::Event event) const;
	
	Menu  getMenuInstance() const;
	void setMenuInstance(Menu instance);
	Data getSaveData() const;

	//Define a largura da board em numero de tiles
	void setBoardWidth(const int nTiles_);

	//Define a altura da board em numero de tiles
	void setBoardHeight(const int nTiles_);

	void draw(Graphics & gfx, const Palette & palette, Mouse::Event me)
	{
		draw(gfx, palette, me.GetPosX(), me.GetPosY());
	};
	void draw(Graphics & gfx, const Palette & palette, const int mouseX, const int mouseY);

	

private:
	
	void save(const std::string & filename_) const;
	bool load(const std::string & filename_);

	Menu currentMenu = Menu::MainMenu;
	Data saveDT;	
	
	//MAIN MENU BUTTONS
	const Rect * nGameBt = new Rect(xCoord + ((menuSize - labelWidth) / 2), yCoord + (menuSize - ((3 * labelHeight) + (2 * tileSize))) / 2, labelWidth, labelHeight);
	const Rect * lGameBt = new Rect(nGameBt->getX(), nGameBt->getY() + labelHeight + tileSize, labelWidth, labelHeight);
	const Rect * optBt = new Rect(nGameBt->getX(), nGameBt->getY() + (2 * labelHeight) + (2 * tileSize), labelWidth, labelHeight);
	
	//SUB MENU OPTION BUTTONS;
	//@soXcoord: Coordenada X do Sub Menu Options
	//@soYcoord: Coordenada Y do Sub Menu Options
	//@bhMinusBt: Botão '-' da opção Board Height
	//@bhPlusBt: Botão '+' da opção Board Height
	const int soXcoord = xCoord + ( ( menuSize - (27 * tileSize )) / 2 );
	const int soYcoord = yCoord + ( 2 * tileSize );

	const Rect * bhMinusBt = new Rect( soXcoord + labelWidth + tileSize, soYcoord, labelHeight, labelHeight);
	const Rect * bhPlusBt = new Rect(bhMinusBt->getX() + 8 * tileSize, soYcoord, labelHeight, labelHeight);

	const Rect * bwMinusBt = new Rect( soXcoord + labelWidth + tileSize, soYcoord + 3 * tileSize, labelHeight, labelHeight );
	const Rect * bwPlusBt = new Rect( bwMinusBt->getX() + 8 * tileSize, soYcoord + 3 * tileSize, labelHeight, labelHeight );

	const Rect * saveOptBt = new Rect( nGameBt->getX(), bwPlusBt->getY() + 3 * tileSize, labelWidth, labelHeight );
	
	int yMarker = nGameBt->getY() + (tileSize / 2);
	//MAIN MENU LABELS
	const std::string nGameLabel = "NEW GAME";
	const std::string loadLabel = "LOAD";
	const std::string optionsLabel = "OPTIONS";
	//OPTIONS SUB-MENU
	const std::string mapWLabel = "MAP WIDTH";
	const std::string mapHLabel = "MAP HIGHT";
	const std::string difficultLabel = "DIFFICULTY";
	//DIFFICULT SUB-MENU


	//STRING LABELS
	const std::string stageData = "[STAGE]";
	const std::string scoreData = "[SCORE]";
	const std::string livesData = "[LIVES]";
	const std::string mapWData = "[WIDTH]";
	const std::string mapHData = "[HEIGHT]";
	const std::string velocityData = "[VELOCITY]";
	const std::string difficultyData = "[DIFFICULTY]";


	//Funcões de Desenho desmembradas
	void drawMenuBorder(Graphics & gfx, const Palette & palette);
	void drawBoardHeightOption(Graphics & gfx, const int mx_, const int my_) const;
	void drawBoardWidthOption(Graphics & gfx, const int mx_, const int my_) const;
	void drawSaveOptions(Graphics & gfx, const int mx_, const int my_) const;
};
