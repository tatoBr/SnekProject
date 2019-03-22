#pragma once

#include "Colors.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "Snake.h"

#define BOARD_N_COLS 48 //Numero de Colunas do Tabuleiro
#define BOARD_N_LINS 32 //Numero de Linhas do Tabuleiro
#define	BOARD_N_CELLS (BOARD_N_COLS * BOARD_N_LINS) //Numero de Celulas que formam o Tabuleiro

class Board {
public:
	enum CellType : char {
		Empty,
		Snk,
		SnkHead,
		Food,
		Poison,
		Obstacle,
		OffBoundarie
	};

	struct Cell {
		CellType type;
		int xPos;
		int yPos;		
		Color color;
	};

public:
	Board() = default;
	Board(float _width, float _height);

	//Desenha as celulas ativas do Tabuleiro. 
	//Apenas Celulas ativas são desenhadas pelo metodo 'drawBoard'
	void drawBoard(Graphics & gfx);		

	//*****************Snake Controls*****************//
	void setSnakeOnBoard(const Snake & snk);
	bool moveSnake(Snake & snk, float & velocity);
	
private:	

	int width;//Largura do Tabuleiro
	int height;//Altura do Tabuleiro
	
	int boardX;//Coordenada x do Tabuleiro dentro da janela de jogo
	int boardY;//Coordenada y do Tabuleiro dentro da janela de jogo

	int cellW;//Largura das Celulas que formam o tabuleiro
	int cellH;//Altura das Celulas que formam o tabuleiro

	int foodX;
	int foodY;

	Snake::Vector poisons[BOARD_N_CELLS];
	Cell cells[BOARD_N_CELLS];//array contendo todas as celulas que formam o tabuleiro

	//*****************Cells Controls*****************//
	void startUpCells();//Inicia as celulas do tabuleiro. 

	//Ativa uma celula do tabuleiro.	
	void activateCell(const int xIndex, const int yIndex, CellType type);
	void activateCell(const CellType type, const int xIndex, const int yIndex, const Color color);
	void activateCell(const Snake::Segment seg);

	//Desativa uma celula do tabuleiro.
	void deactivateCell(const int xIndex, const int yIndex);	
	
	void drawCell(Graphics & gfx, Cell cell) const;

	void drawBorder(Graphics & gfx);
	
	void setFoodOnBoard();
	void setPoisonOnBoard();
	CellType snakeNextCellLocation(Snake & snk);
};
