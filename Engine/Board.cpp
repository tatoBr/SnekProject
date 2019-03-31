#include "Board.h"

Board::Board(const int tileSize)	
{
	const int pxHeight = (Graphics::ScreenHeight - (2 * (Graphics::ScreenHeight / 6)));

	height = ( pxHeight / tileSize )* tileSize;
	width = height;

	boardY = ( Graphics::ScreenHeight / 6 );
	boardX = (( Graphics::ScreenWidth - width ) / 2 );

	nHorTiles = width / tileSize;
	nVerTiles = height / tileSize;

	cells = new Cell[nHorTiles * nVerTiles];
}
Board::Board(int _nCols, int _nLines)
	:	
	nHorTiles(( _nCols > maxColumns ) ? maxColumns : (( _nCols < minColumns ) ? minColumns : _nCols )),
	nVerTiles(( _nLines > maxLines ) ? maxLines : (( _nLines < minLines ) ? minLines : _nLines )),
	
	width( nHorTiles * tileSize ),
	height( nVerTiles * tileSize),

	boardX((Graphics::ScreenWidth - width) / 2),
	boardY(tileSize * 6),

	cells(new Cell[nHorTiles * nVerTiles])
{}

void Board::startUpBoard(const Snake& snk, const int nObst_, const int nPoison_)
{	
	startUpCells();
	setSnakeOnBoard(snk);	
	setObstaclesOnBoard(nObst_);
	setPoisonOnBoard(nPoison_);
	setFoodOnBoard();
}

void Board::drawBoard(Graphics & gfx, const Palette & palette, const int keyFrame) const
{	
	for (int line = 0; line < nVerTiles; line++)
	{
		for (int column = 0; column < nHorTiles; column++)
		{
			const int index = line * nHorTiles + column;
			
				drawCell(gfx, cells[index], palette, keyFrame);
		}
	}

	//drawBorder(gfx);
}


//*****************Snake Controls*****************//
void Board::setSnakeOnBoard(const Snake & snk)
{	
	for (auto * currentSeg = snk.tail; currentSeg != nullptr; currentSeg = currentSeg->getNext())
	{
		const Snake::Vector v = currentSeg->getPosition();
		const Color c = currentSeg->getColor();
		activateCell(CellType::Snk, v.x, v.y, c);
	}
}
void Board::eraseSnkFromBoard(const Snake & snk)
{	
	for (auto * currentSeg = snk.tail; currentSeg != nullptr; currentSeg = currentSeg->getNext())
	{
		deactivateCell(currentSeg->getPosition().x, currentSeg->getPosition().y);
	}
	
}
Board::CellType Board::moveSnake( Snake & snk )
{
	CellType ct = snakeNextCellLocation(snk);
	switch (ct)
	{
	case CellType::Empty:
		deactivateCell(snk.tail->getPosition().x, snk.tail->getPosition().y);
		snk.move();		
		setSnakeOnBoard(snk);		
		break;

	case CellType::Snk:		
		break;

	case CellType::SnkHead:		
		snk.move();		
		break;		

	case CellType::Food:
		//deactivateCell(snk.tail->getPosition().x, snk.tail->getPosition().y);
		snk.grow();
		snk.move();
		setSnakeOnBoard(snk);
		setFoodOnBoard();		
		break;

	case CellType::Poison:
		deactivateCell(snk.tail->getPosition().x, snk.tail->getPosition().y);
		snk.move();
		setSnakeOnBoard(snk);				
		break;

	case CellType::Obstacle:		
		break;

	default:		
		break;
	}
	
	return ct;
}

Snake::Vector Board::getCenter()
{
	return {nHorTiles / 2, nVerTiles / 2 };
}

int Board::getWidth() const
{
	return width;
}


//*****************Cells Controls*****************//
void Board::startUpCells()
{
	int x, y;
	for (int line = 0; line < nVerTiles; line++)
	{
		for (int column = 0; column < nHorTiles; column++)
		{
			CellType type;
			Color cellColor;
			const int index = line * nHorTiles + column;
			x = boardX + (column * tileSize);
			y = boardY + (line * tileSize);
			if (line == 0 || column == 0)
			{
				type = CellType::OffBoundarie;
				cellColor = Color(87, 87, 87);
			}			
			else if (line == nVerTiles - 1 || column == nHorTiles - 1)
			{
				type = CellType::OffBoundarie;
				cellColor = Color(87, 87, 87);
			}
			else
			{
				type = CellType::Empty;
				cellColor = Colors::Blue;
			}
			cells[index]  = {type, x, y, cellColor};			
		}
	}
}
void Board::activateCell(const int xIndex, const int yIndex, CellType type)
{
	int index = yIndex * nHorTiles + xIndex;
	cells[index].type = type;

	Color c;
	switch (type)
	{
	case CellType::Food:
		c = Colors::Red;
		break;
	case CellType::Obstacle:
		c = Colors::Gray;
		break;
	case CellType::Poison:
		c = Color(135, 31, 120);
		break;
	default:
		c = Colors::Black;
		break;
	}

	cells[index].color = c;
}
void Board::activateCell(const CellType type, const int xIndex, const int yIndex, const Color color)
{
	int index = yIndex * nHorTiles + xIndex;
	cells[index].type = type;
	cells[index].color = color;
}

void Board::deactivateCell(int xIndex, int yIndex)
{
	const int index = yIndex * nHorTiles + xIndex;
	cells[index].color = Colors::Black;
	cells[index].type = CellType::Empty;
}

void Board::drawCell(Graphics & gfx, Cell cell, const Palette & palette, const int keyFrame) const
{
	
	const int xPos = cell.xPos;
	const int yPos = cell.yPos;
	const int width = tileSize - 1;
	const int height = tileSize - 1;	
	SpriteCodex::empty(gfx, xPos, yPos, palette.base, palette.shadow, palette.highlight);

	switch (cell.type)
	{
	case CellType::Food:
		drawFood(keyFrame, gfx, xPos, yPos);
		break;

	case CellType::Obstacle:
	case CellType::OffBoundarie:
		SpriteCodex::Obstacle(gfx, xPos, yPos, palette.base, palette.shadow, palette.highlight);
		break;

	case CellType::Poison:
		drawPoison(keyFrame, gfx, xPos, yPos);
		break;		
	
	default:		
		break;
	}	

	if (cell.type != CellType::Poison &&
		cell.type != CellType::Obstacle &&
		cell.type != CellType::OffBoundarie &&
		cell.type != CellType::Food &&
		cell.type != CellType::Empty)
	{
		for (int y = yPos; y < yPos + height; y++)
		{
			for (int x = xPos; x < xPos + width; x++) {
				gfx.PutPixel(x, y, cell.color);
			}
		}
	}
}

void Board::drawFood(const int keyFrame, Graphics & gfx, const int x, const int y) const
{
	switch (keyFrame)
	{
	case 1:
		SpriteCodex::fruitLeft(gfx, x, y);
		break;
	case 2:
		SpriteCodex::fruitMiddle(gfx, x, y);
		break;
	case 3:
		SpriteCodex::fruitRight(gfx, x, y);
		break;
	default:
		SpriteCodex::fruitMiddle(gfx, x, y);
		break;
	}
}
void Board::drawPoison(const int KeyFrame, Graphics & gfx, const int x, const int y) const
{
	if (KeyFrame % 2 == 0)
	{
		SpriteCodex::poisonUp(gfx, x, y);
	}
	else
	{
		SpriteCodex::poisonDown(gfx, x, y);
	}
}

void Board::setFoodOnBoard()
{
	int nx = rand() % nHorTiles;
	int ny = rand() % nVerTiles;
	int index = ny * nHorTiles + nx;
	int sIndex;
	bool emptySurround = false;
	
	while ( !( cells[index].type == CellType::Empty && emptySurround ))
	{
		nx = rand() % nHorTiles;
		ny = rand() % nVerTiles;
		emptySurround = true;
		for (int y = ny - 1; y <= ny + 1; y++)
		{
			for (int x = nx - 1; x <= nx + 1; x++)
			{
				sIndex = y * nHorTiles + x;
				emptySurround = ( cells[sIndex].type == CellType::Empty ) && emptySurround;
			}
		}
		index = ny * nHorTiles + nx;
	}

	activateCell(nx, ny, CellType::Food);
}
void Board::setObstaclesOnBoard(const int nObst_)
{
	for (int i = 0; i < nObst_; i++)
	{
		int nx = rand() % nHorTiles;//Gera uma coord x aleatória para posicionar o obstáculo
		int ny = rand() % nVerTiles;//Gera uma coord y aleatória para posicionar o obstáculo
		int index = ny * nHorTiles + nx; //indice no array de celulas referente as coordenadas geradas


		while (cells[index].type != CellType::Empty) // checa se a celula nas coords geradas esta vazia
		{
			nx = rand() % nHorTiles;
			ny = rand() % nVerTiles;
			index = ny * nHorTiles + nx;
		}
		activateCell(nx, ny, CellType::Obstacle); //ativa a celula na coord gerada
	}	
}
void Board::setPoisonOnBoard(const int nPoison_)
{
	for (int i = 0; i < nPoison_; i++)
	{
		int nx = rand() % nHorTiles;//Gera uma coord x aleatória para posicionar o obstáculo
		int ny = rand() % nVerTiles;//Gera uma coord y aleatória para posicionar o obstáculo
		int index = ny * nHorTiles + nx; //indice no array de celulas referente as coordenadas geradas

		while (cells[index].type != CellType::Empty) // checa se a celula nas coords geradas esta vazia
		{
			nx = rand() % nHorTiles;
			ny = rand() % nVerTiles;
			index = ny * nHorTiles + nx;
		}
		activateCell(nx, ny, CellType::Poison); //ativa a celula na coord gerada
	}
}

Board::CellType Board::snakeNextCellLocation(Snake & snk)
{	
	const int nextX = snk.getHead()->getPosition().x + snk.getVelocity().x;
	const int nextY = snk.getHead()->getPosition().y + snk.getVelocity().y;
	const int index = nextY * nHorTiles + nextX;
	CellType c = cells[index].type;
	return cells[index].type;
}


