#pragma once

#include "Colors.h"

#define SNAKE_MAX_SIZE 1536
#define SNAKE_MOVING_UP 0
#define SNAKE_MOVING_DOWN 1
#define SNAKE_MOVING_LEFT 2
#define SNAKE_MOVING_RIGHT 3

class Snake {
public:
	struct Segment{
		int xCoord;
		int yCoord;
		Color color;
	};

	struct Vector {
		int x;
		int y;
	};

	Segment body[SNAKE_MAX_SIZE]; //Array contendo o corpo da Serpente

public:
	Snake(int _startX, int _startY);

	//Move a Serpente pelo Tabuleiro
	void move();

	//Define a dire��o que a Serpente ira se mover (up / down / left / right)
	void setDirection(const int dir);

	//Retorna a dire��o em que a Serpente e est� se movendo (up / down / left / right)
	int getDirection() const;

	//Retorna o compirmento da Serpente
	int getSnkLenght() const;

	void grow();

	//Inicializa os Segmentos da Serpente
	void InitializeSnake();	
	
	Segment getHead() const;
	Segment getTail() const;
	Vector getVelocity() const;

private:	
	Segment head; //Cabe�a da Serpente	
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
	
	const int startXCoord; //Cordenada X inicial. Posi��o da cabe�a da serpente
	const int startYCoord; //Cordenada Y inicial. Posi��o da cabe�a da serpente
	int lastBodyIndex; //Tamanho do corpo da Serpente
	int movDirection = SNAKE_MOVING_UP; //Dire��o em que a Serpente esta se movendo
	const int offBoard = -10; //posi��o dos segmentos n�o fazem parte da Serpente	

	//Inicializa os Segmentos do Corpo 
	void InitializeBody(const int xCoord, const int yCoord);
};
