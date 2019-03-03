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
}

void Board::drawBoard(Graphics & gfx)
{
	for (int i = 0; i < BOARD_N_CELLS; i++)
	{
		if(cells[i].active)	drawCell(gfx, cells[i]);
	}
}

void Board::activateCell(const int xIndex, const int yIndex, Color _c)
{
	cells[yIndex * BOARD_N_COLS + xIndex].active = true;
	setCellColor(xIndex, yIndex, _c);
}

void Board::deactivateCell(int xIndex, int yIndex)
{
	cells[yIndex * BOARD_N_COLS + xIndex].active = false;
	setCellColor(xIndex, yIndex, Colors::White);
}

void Board::startUpCells()
{
	int x, y;
	for (int line = 0; line < BOARD_N_LINS; line++)
	{
		for (int column = 0; column < BOARD_N_COLS; column++)
		{
			const int index = line * BOARD_N_COLS + column;
			x = boardX + (column * cellW);
			y = boardY + (line * cellH);
			cells[index]  = {x, y, false, Colors::White};			
		}
	}
}

void Board::setCellColor(const int _xIndex, const int _yIndex, Color _c)
{
	cells[_yIndex * BOARD_N_COLS + _xIndex].color = _c;
}

void Board::drawCell(Graphics & gfx, Cell cell) const
{
	const int xPos = cell.xPos + 1;
	const int yPos = cell.yPos + 1;
	const int width = cellW - 1;
	const int height = cellH - 1;
	const Color c = cell.color;

	for (int y = yPos; y < yPos + height; y++)
	{
		for (int x = xPos; x < xPos + width; x++) {
			gfx.PutPixel(x, y, c);
		}
	}
}
