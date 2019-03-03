#pragma once

#include "Colors.h"
#include "Graphics.h"

#define BOARD_N_COLS 32 //Numero de Colunas do Tabuleiro
#define BOARD_N_LINS 24 //Numero de Linhas do Tabuleiro
#define	BOARD_N_CELLS (BOARD_N_COLS * BOARD_N_LINS) //Numero de Celulas que formam o Tabuleiro

class Board {
	struct Cell {
		int xPos;
		int yPos;
		bool active;
		Color color;
	};

public:
	Board() = default;
	Board(float _width, float _height);

	//Desenha as celulas ativas do Tabuleiro
	void drawBoard(Graphics & gfx);	

	//Ativa uma celula do tabuleiro. Apenas Celulas ativas são desenhadas pelo metodo 'drawBoard'
	void activateCell(const int xIndex, const int yIndex, Color _c);

	//Desativa uma celula do tabuleiro. Apenas Celulas ativas são desenhadas pelo metodo 'drawBoard'
	void deactivateCell(const int xIndex, const int yIndex);  
	
private:	

	int width;//Largura do Tabuleiro
	int height;//Altura do Tabuleiro
	
	int boardX;//Coordenada x do Tabuleiro dentro da janela de jogo
	int boardY;//Coordenada y do Tabuleiro dentro da janela de jogo

	int cellW;//Largura das Celulas que formam o tabuleiro
	int cellH;//Altura das Celulas que formam o tabuleiro

	Cell cells[BOARD_N_CELLS];//array contendo todas as celulas que formam o tabuleiro
	
	void startUpCells();//Inicia as celulas do tabuleiro. 
	void setCellColor(const int _xIndex, const int _yIndex, Color _c);//Muda a cor da celula do tabuleiro
	void drawCell(Graphics & gfx, Cell cell) const;//Desenha uma celula do tabuleiro
};
