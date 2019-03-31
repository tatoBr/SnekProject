#pragma once

#include "SpriteCodex.h"
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
	//Constructor, desctructor.
	Board() = default;
	Board(const int tileSize);
	Board(int _tileWidth, int _tileHeight);
	~Board()
	{
		delete[] cells;
		cells = nullptr;
	}

	// Variaveis estáticas 
	static constexpr int nPalettes = 9; //total de variações de paleta de cores
	static constexpr int tileSize = 16; //tamanho dos tiles = 16px x 16px
	static constexpr int maxColumns = Graphics::ScreenWidth / tileSize; //maximo de colunas permitida
	static constexpr int maxLines = Graphics::ScreenHeight / tileSize - 6; //máximo de linhas permitida
	static constexpr int minColumns = 18; 
	static constexpr int minLines = 16;
	//Inicializa o Tabuleiro
	void startUpBoard(const Snake& snk, const int nObst_, const int nPoison_);

	//Desenha as celulas ativas do Tabuleiro. 	
	void drawBoard(Graphics & gfx, const Palette & palette, const int keyFrame) const;		

	//*****************Snake Controls*****************//
	void setSnakeOnBoard(const Snake & snk);
	void eraseSnkFromBoard(const Snake & snk);
	CellType moveSnake( Snake & snk );

	Snake::Vector getCenter();
	int getWidth() const;
	
private:	
	int nHorTiles; // numero de tiles na horinzontal
	int nVerTiles; // numero de tiles na vertical

	int width;//Largura do Tabuleiro
	int height;//Altura do Tabuleiro
	
	int boardX;//Coordenada x do Tabuleiro dentro da janela de jogo
	int boardY;//Coordenada y do Tabuleiro dentro da janela de jogo
	
	int cellH;//Altura das Celulas que formam o tabuleiro
	

	Snake::Vector poisons[BOARD_N_CELLS];
	Cell * cells;//array contendo todas as celulas que formam o tabuleiro
	
	//*****************Cells Controls*****************//
	void startUpCells();//Inicializa as celulas do tabuleiro. 

	//Ativa uma celula do tabuleiro.	
	void activateCell(const int xIndex, const int yIndex, CellType type);
	void activateCell(const CellType type, const int xIndex, const int yIndex, const Color color);
	//void activateCell(const Snake::Segment seg);

	//Desativa uma celula do tabuleiro.
	void deactivateCell(const int xIndex, const int yIndex);	
	
	//Desenha uma Celula do tabuleiro
	void drawCell(Graphics & gfx, Cell cell, const Palette & palette, const int keyFrame) const;	
	void drawFood(const int keyFrame, Graphics & gfx, const int x, const int y) const;
	void drawPoison(const int KeyFrame, Graphics & gfx, const int x, const int y)const;
	
	//Posiciona os elemento do jogo dentro da board
	void setFoodOnBoard();
	void setObstaclesOnBoard(const int nObst_);
	void setPoisonOnBoard(const int nPoison_);

	//retorna o tipo de celula diretamente a frente da snake
	CellType snakeNextCellLocation(Snake & snk);	
};
