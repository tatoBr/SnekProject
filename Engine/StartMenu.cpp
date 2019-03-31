#include "StartMenu.h"

StartMenu::StartMenu()
{	
	if (loadOptions()) {
		saveDT = {
			1, //Stage
			0, //Score
			3, //Lives
			18, //Map Width in tiles
			16, //Map Height in tiles
			0.3f, // velocity}
			0 //Difficulty
		};
	}
}

void StartMenu::saveOptions() const
{
	save(optionFile);
}
void StartMenu::saveGame() const
{
	save( saveFile );
}

bool StartMenu::loadOptions()
{
	return load( optionFile );
}
bool StartMenu::loadGame()
{
	return load(saveFile);
}

bool StartMenu::newGameIsPressed(Mouse::Event event) const
{
	return (event.LeftIsPressed()) && (nGameBt->containsPoint(event.GetPosX(), event.GetPosY()));
}
bool StartMenu::loadGameIsPressed(Mouse::Event event) const
{
	return (event.LeftIsPressed()) && (lGameBt->containsPoint(event.GetPosX(), event.GetPosY()));
}
bool StartMenu::OptionIsPressed(Mouse::Event event) const
{
	return (event.LeftIsPressed()) && (optBt->containsPoint(event.GetPosX(), event.GetPosY()));
}
bool StartMenu::bhMinusIsPressed(Mouse::Event event) const
{
	return (event.LeftIsPressed()) && (bhMinusBt->containsPoint(event.GetPosX(), event.GetPosY()));
}
bool StartMenu::bhPlusIsPressed(Mouse::Event event) const
{
	return (event.LeftIsPressed()) && (bhPlusBt->containsPoint(event.GetPosX(), event.GetPosY()));
}
bool StartMenu::bwMinusIsPressed(Mouse::Event event) const
{
	return (event.LeftIsPressed()) && (bwMinusBt->containsPoint(event.GetPosX(), event.GetPosY()));
}
bool StartMenu::bwPlusIsPressed(Mouse::Event event) const
{
	return (event.LeftIsPressed()) && (bwPlusBt->containsPoint(event.GetPosX(), event.GetPosY()));
}
bool StartMenu::saveOptBtIsPressed(Mouse::Event event) const
{
	return  (event.LeftIsPressed()) && (saveOptBt->containsPoint(event.GetPosX(), event.GetPosY()));
}

StartMenu::Menu StartMenu::getMenuInstance() const
{
	return currentMenu;
}
void StartMenu::setMenuInstance(Menu instance)
{
	currentMenu = instance;
}


StartMenu::Data StartMenu::getSaveData() const
{
	return saveDT;
}

void StartMenu::setBoardWidth(const int nTiles_)
{
	
	saveDT.mapW = ( nTiles_ < Board::minColumns ) ? Board::minColumns : ( nTiles_ > Board::maxColumns ) ? Board::maxColumns : nTiles_ ;
}
void StartMenu::setBoardHeight(const int nTiles_)
{
	saveDT.mapH = ( nTiles_ < Board::minLines ) ? Board::minLines : ( nTiles_ > Board::maxLines ) ? Board::maxLines : nTiles_;
}



void StartMenu::draw( Graphics & gfx, const Palette & palette, const int mouseX_, const int mouseY_ )
{
	//Desenha a Borda do Menu	
	drawMenuBorder(gfx, palette);
	const int xMarker = nGameBt->getX() - 2 * tileSize;

	switch (currentMenu)
	{
	case StartMenu::MainMenu:
		//Desenha as labels dos botões
		SpriteCodex::labelNewGame(gfx, nGameBt->getX(), nGameBt->getY());
		SpriteCodex::labelLoadGame(gfx, lGameBt->getX(), lGameBt->getY());
		SpriteCodex::labelOptions(gfx, optBt->getX(), optBt->getY());

		//Define a coordenada y do marcados de menu
		if (nGameBt->containsPoint(mouseX_, mouseY_))
		{
			yMarker = nGameBt->getY() + (tileSize / 2);
		}
		else if (lGameBt->containsPoint(mouseX_, mouseY_))
		{
			yMarker = lGameBt->getY() + (tileSize / 2);
		}
		else if (optBt->containsPoint(mouseX_, mouseY_))
		{
			yMarker = optBt->getY() + (tileSize / 2);
		}
		//Desenha o marcador de menu
		SpriteCodex::live(gfx, xMarker, yMarker);
		break;

	case StartMenu::LoadMenu:
		break;

	case StartMenu::OptionMenu:
		drawBoardHeightOption( gfx, mouseX_, mouseY_ );
		drawBoardWidthOption( gfx, mouseX_, mouseY_ );
		drawSaveOptions(gfx, mouseX_, mouseY_);
		break;

	default:
		break;
	}	
}

/***************************** PRIVATE FUNCTIONS ***********************************/
void StartMenu::save(const std::string & filename_) const
{
	std::ofstream outf(filename_);
	outf << stageData << '\n' << saveDT.stage << '\n';
	outf << scoreData << '\n' << saveDT.score << '\n';
	outf << livesData << '\n' << saveDT.lives << '\n';
	outf << mapWData << '\n' << saveDT.mapW << '\n';
	outf << mapHData << '\n' << saveDT.mapH << '\n';
	outf << velocityData << '\n' << saveDT.velocity << '\n';
	outf << difficultyData << '\n' << saveDT.difficulty << '\n';

	outf.close();
}
bool StartMenu::load(const std::string & filename_)
{
	std::ifstream inf(filename_);
	if (inf)
	{
		for (std::string line; std::getline(inf, line); )
		{
			if (line == stageData)
				inf >> saveDT.stage;

			else if (line == scoreData)
				inf >> saveDT.score;

			else if (line == livesData)
				inf >> saveDT.lives;

			else if (line == mapWData)
				inf >> saveDT.mapW;

			else if (line == mapHData)
				inf >> saveDT.mapH;

			else if (line == velocityData)
				inf >> saveDT.velocity;

			else if (line == difficultyData)
				inf >> saveDT.difficulty;
		}
	}

	return inf.good();
}

void StartMenu::drawMenuBorder(Graphics & gfx, const Palette & palette)
{
	for (int x = xCoord; x < xCoord + menuSize; x += tileSize)
	{
		SpriteCodex::Obstacle(gfx, x, yCoord, palette);
		SpriteCodex::Obstacle(gfx, x, yCoord + menuSize - tileSize, palette);
	}
	for (int y = yCoord + tileSize; y < yCoord + menuSize - tileSize; y += tileSize)
	{
		SpriteCodex::Obstacle(gfx, xCoord, y, palette);
		SpriteCodex::Obstacle(gfx, xCoord + menuSize - tileSize, y, palette);
	}
}
void StartMenu::drawBoardHeightOption(Graphics & gfx, const int mx_, const int my_) const
{
	SpriteCodex::labelBoardH(gfx, soXcoord, soYcoord);
	if (bhMinusBt->containsPoint(mx_, my_))
	{
		SpriteCodex::labelMinus(gfx, bhMinusBt->getX(), bhMinusBt->getY());
	}
	else
	{
		SpriteCodex::labelMinusGray(gfx, bhMinusBt->getX(), bhMinusBt->getY());
	}

	CharsCodex::drawNumber(saveDT.mapH, bhMinusBt->getX() + 2 * tileSize, bhMinusBt->getY(), gfx, Colors::Yellow);
	if (bhPlusBt->containsPoint(mx_, my_))
	{
		SpriteCodex::labelPlus(gfx, bhPlusBt->getX(), bhPlusBt->getY());
	}
	else
	{
		SpriteCodex::labelPlusGray(gfx, bhPlusBt->getX(), bhPlusBt->getY());
	}
}
void StartMenu::drawBoardWidthOption(Graphics & gfx, const int mx_, const int my_) const
{
	SpriteCodex::labelBoardW(gfx, soXcoord, soYcoord + 3 * tileSize);
	if (bwMinusBt->containsPoint(mx_, my_))
	{
		SpriteCodex::labelMinus(gfx, bwMinusBt->getX(), bwMinusBt->getY());
	}
	else
	{
		SpriteCodex::labelMinusGray(gfx, bwMinusBt->getX(), bwMinusBt->getY());
	}

	CharsCodex::drawNumber(saveDT.mapW, bwMinusBt->getX() + 2 * tileSize, bwMinusBt->getY(), gfx, Colors::Yellow);
	if (bwPlusBt->containsPoint(mx_, my_))
	{
		SpriteCodex::labelPlus(gfx, bwPlusBt->getX(), bwPlusBt->getY());
	}
	else
	{
		SpriteCodex::labelPlusGray(gfx, bwPlusBt->getX(), bwPlusBt->getY());
	}
}
void StartMenu::drawSaveOptions(Graphics & gfx, const int mx_, const int my_) const
{
	if (saveOptBt->containsPoint(mx_, my_))
	{
		SpriteCodex::labelSave(gfx, saveOptBt->getX(), saveOptBt->getY());
	}
	else
	{
		SpriteCodex::labelSaveGrey(gfx, saveOptBt->getX(), saveOptBt->getY());
	}
}
