#pragma once

#include "Board.h"

#define SNAKE_MAX_SIZE BOARD_N_CELLS
#define SNAKE_MOVING_UP 0
#define SNAKE_MOVING_DOWN 1
#define SNAKE_MOVING_LEFT 2
#define SNAKE_MOVING_RIGHT 3


class Snake {
	struct Segment{
		int xCoord;
		int yCoord;
		Color c;
	};

	struct Vector {
		int x;
		int y;
	};

public:
	Snake();

	//Move a Serpente pelo Tabuleiro
	void move(Board & _b);

	//Define a direção que a Serpente ira se mover (up / down / left / right)
	void setDirection(const int dir);

	//Retorna a direção em que a Serpente e está se movendo (up / down / left / right)
	int getDirection();

	//Coloca a serpente posicionada dentro do Tabuleiro
	void setSnakeOnBoard(Board & _b);

private:
	Segment head; //Cabeça da Serpente
	Segment body[SNAKE_MAX_SIZE]; //Array contendo o corpo da Serpente
	Segment tail; // Rabo da Serpente

	//Cores do corpo da Serpente
	Color bodyColors[5] = {
		{228, 147, 117},
		{210, 136, 87},
		{194, 110, 64},
		{159, 73, 48},
		{152, 57, 27}
	}; //Cores do corpo da Serpente

	Vector velocity = { 0,-1 };
	
	const int startXCoord = (BOARD_N_COLS / 2); //Cordenada X inicial. Posição da cabeça da serpente
	const int startYCoord = (BOARD_N_LINS / 2); //Cordenada Y inicial. Posição da cabeça da serpente
	int lastBodyIndex; //Tamanho do corpo da Serpente
	int movDirection = SNAKE_MOVING_UP; //Direção em que a Serpente esta se movendo
	const int offBoard = -10; //posição dos segmentos não fazem parte da Serpente


	//Inicializa os Segmentos da Serpente
	void InitializeSnake();

	//Inicializa os Segmentos do Corpo 
	void InitializeBody(const int xCoord, const int yCoord);

	//Ativa a serpente no tabuleiro para ser desenhada.
	void activateSnake(Board & _b) const;

	//Desativa a serpente no tabuleiro para ser desenhada.
	void deactivateSnake(Board & _b) const;

	//Verifica colisão com paredes ou corpo;
	bool checkCollision() const;
};
