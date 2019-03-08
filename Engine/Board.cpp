#include "Board.h"

Board::Board(float _width, float _height)
	:
	width((_width / BOARD_N_COLS) * BOARD_N_COLS),
	height((_height / BOARD_N_LINS) * BOARD_N_LINS),

	boardX((Graphics::ScreenWidth - width) / 2),
	boardY((Graphics::ScreenHeight - height) / 2),

	cellW(width / BOARD_N_COLS),
	cellH(height / BOARD_N_LINS)
{
	startUpCells();
	setFoodOnBoard();
	setPoisonOnBoard();
}

void Board::drawBoard(Graphics & gfx)
{	
	for (int line = 0; line < BOARD_N_LINS; line++)
	{
		for (int column = 0; column < BOARD_N_COLS; column++)
		{
			const int index = line * BOARD_N_COLS + column;
			if (cells[index].type != CellType::Empty)
				drawCell(gfx, cells[index]);
		}
	}

	drawBorder(gfx);
}


//*****************Snake Controls*****************//
void Board::setSnakeOnBoard(const Snake & snk)
{
	activateCell(CellType::SnkHead, (int)snk.getHead().xCoord, (int)snk.getHead().yCoord, snk.getHead().color);
	for (int i = 0; i <= snk.getSnkLenght(); i++)
	{
		activateCell(snk.body[i]);
	}
	activateCell(snk.getTail());
}
void Board::moveSnake(Snake & snk, float & velocity)
{
	switch (snakeNextCellLocation(snk))
	{
	case CellType::Empty:
		deactivateCell((int)snk.getTail().xCoord, (int)snk.getTail().yCoord);
		snk.move();		
		setSnakeOnBoard(snk);
		break;

	case CellType::Snk:
		break;

	case CellType::SnkHead:		
		snk.move();
		break;		

	case CellType::Food:
		deactivateCell(snk.getTail().xCoord, snk.getTail().yCoord);
		snk.grow();
		snk.move();
		setSnakeOnBoard(snk);
		setFoodOnBoard();		
		break;

	case CellType::Poison:
		deactivateCell(snk.getTail().xCoord, snk.getTail().yCoord);
		snk.move();
		setSnakeOnBoard(snk);
		velocity -= 0.01f;
		break;

	default:
		break;
	}	
}

//*****************Cells Controls*****************//
void Board::startUpCells()
{
	int x, y;
	for (int line = 0; line < BOARD_N_LINS; line++)
	{
		for (int column = 0; column < BOARD_N_COLS; column++)
		{
			CellType type;
			Color cellColor;
			const int index = line * BOARD_N_COLS + column;
			x = boardX + (column * cellW);
			y = boardY + (line * cellH);
			if (line == 0 || column == 0)
			{
				type = CellType::OffBoundarie;
				cellColor = Color(87, 87, 87);
			}			
			else if (line == BOARD_N_LINS - 1 || column == BOARD_N_COLS - 1)
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
	int index = yIndex * BOARD_N_COLS + xIndex;
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
	int index = yIndex * BOARD_N_COLS + xIndex;
	cells[index].type = type;
	cells[index].color = color;
}
void Board::activateCell(const Snake::Segment seg)
{
	int index = int(seg.yCoord) * BOARD_N_COLS + int(seg.xCoord);
	cells[index].type = CellType::Snk;
	cells[index].color = seg.color;
}

void Board::deactivateCell(int xIndex, int yIndex)
{
	const int index = yIndex * BOARD_N_COLS + xIndex;
	cells[index].color = Colors::Black;
	cells[index].type = CellType::Empty;
}

void Board::drawCell(Graphics & gfx, Cell cell) const
{
	const int xPos = cell.xPos + 1;
	const int yPos = cell.yPos + 1;
	const int width = cellW - 1;
	const int height = cellH - 1;

	Color c;
	switch (cell.type)
	{
	case CellType::Food:
		c = Colors::Red;
		break;

	case CellType::Obstacle:
		break;

	case CellType::Poison:
		c = Color(135, 31, 120);
		break;

	case CellType::OffBoundarie:
		c = Color(85, 85, 85);
		break;

	default:
		c = cell.color;
		break;
	}	

	for (int y = yPos; y < yPos + height; y++)
	{
		for (int x = xPos; x < xPos + width; x++) {
			gfx.PutPixel(x, y, c);
		}
	}
}
void Board::drawBorder(Graphics & gfx)
{

	int realWidth = cellW * BOARD_N_COLS;
	int realHeight = cellH * BOARD_N_LINS;
	for (int x = boardX; x < boardX + realWidth; x++)
	{
		gfx.PutPixel(x, boardY, Colors::White);
		gfx.PutPixel(x, boardY + realHeight, Colors::White);
	}

	for (int y = boardY; y < boardY + realHeight; y++)
	{
		gfx.PutPixel(boardX, y, Colors::White);
		gfx.PutPixel(boardX + realWidth, y, Colors::White);
	}
}

void Board::setFoodOnBoard()
{
	int nx = rand() % BOARD_N_COLS;
	int ny = rand() % BOARD_N_LINS;
	int index = ny * BOARD_N_COLS + nx;

	while (cells[index].type != CellType::Empty)
	{
		nx = rand() % BOARD_N_COLS;
		ny = rand() % BOARD_N_LINS;
		index = ny * BOARD_N_COLS + nx;
	}

	activateCell(nx, ny, CellType::Food);
}

void Board::setPoisonOnBoard()
{
	for (int line = 0; line < BOARD_N_LINS; line++)
	{
		for (int column = 0; column < BOARD_N_COLS; column++)
		{			
			const int index = line * BOARD_N_COLS + column;

			if (cells[index].type == CellType::Empty && rand() % 8 == 0)
			{
				activateCell(column, line, CellType::Poison);
			}
		}
	}
}

Board::CellType Board::snakeNextCellLocation(Snake & snk)
{
	const int nextX = snk.getHead().xCoord + snk.getVelocity().x;
	const int nextY = snk.getHead().yCoord + snk.getVelocity().y;	
	const int index = nextY * BOARD_N_COLS + nextX;
	CellType c = cells[index].type;
	return cells[index].type;
}


