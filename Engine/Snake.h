#pragma once

#include "Colors.h"

#define SNAKE_MAX_SIZE 1536

class Snake {
public:
	const enum Direction : char
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		HORIZOLTALLY,
		VERTICALLY
	};
	struct Vector {
		int x;
		int y;
	};
private:
	class Segment{
	public:
		/*********************RULE OF THREE**************************/
		//Constructors
		Segment() = default;
		Segment(const int x_, const int y_, const Color & c_)
			:
			pXcoord(new int(x_)),
			pYcoord(new int(y_)),
			pColor(new Color(c_))
		{}
		Segment(const int x_, const int y_, Color & c_, Segment * pNext_)
			:
			pXcoord(new int(x_)),
			pYcoord(new int(y_)),
			pColor(new Color(c_)),
			pNext(pNext_)
		{}		

		//Copy assignment operator
		Segment& operator=(Segment & rhs)
		{
			//Se o segmento copiado já faz parte de um pilha, ela é esvaziada
			if (pNext != nullptr)
			{
				delete pNext;
				pNext = nullptr;
			}
			//limpa os elementos do segmento
			delete pXcoord;
			delete pYcoord;
			delete pColor;

			pXcoord = nullptr;
			pYcoord = nullptr;
			pColor = nullptr;

			//Copia os elementos do segmento
			pXcoord = new int( *rhs.pXcoord );
			pYcoord = new int( *rhs.pYcoord );
			pColor = new Color( *rhs.pColor );

			//Copia o próximo elemento da pilha
			if (rhs.pNext != nullptr)
			{
				pNext = rhs.pNext;
			}

			return *this;
		}

		//Copy Constructor
		Segment(Segment & src)			
		{
			*this = src;
		}

		//Destructor
		~Segment()
		{		
			delete pXcoord;
			delete pYcoord;
			delete pColor;

			pXcoord = nullptr;
			pYcoord = nullptr;
			pColor = nullptr;

			if (pNext != nullptr)
			{
				delete pNext;
				pNext = nullptr;
			}
		}
		/*********************END RULE OF THREE**************************/

		//Conecta um novo elemento na pilha
		void connect(Segment * pNext_)
		{
			pNext = pNext_;
		}

		//Desconecta Elemento da Pilha
		Segment * desconect()
		{
			Segment * pTemp = pNext;
			pNext = nullptr;
			return pTemp;
		}

		//Retorna o próximo elemento da fila
		Segment * getNext() const
		{
			return pNext;
		}

		//Retorna o número de elementos da fila
		int getSegmentCount()
		{
			int count = 1;
			
			if (pNext != nullptr)
			{
				return pNext->getSegmentCount() + 1;
			}
			else
			{
				return 1;
			}
		}

		//Setter das coordenadas (x e y) do segmento
		void setPosition(const Vector & pos_)
		{
			delete pXcoord;
			delete pYcoord;

			pXcoord = nullptr;
			pYcoord = nullptr;

			pXcoord = new int(pos_.x);
			pYcoord = new int(pos_.y);
		}
		
		//Getter da cor do Segmento
		Color getColor() const
		{
			return *pColor;
		}

		//Getter da posição do Segmento
		Vector getPosition() const
		{
			return { *pXcoord, *pYcoord };
		}
	private:
		int * pXcoord = nullptr;//Coordenada x na tela
		int  * pYcoord = nullptr;//Coordenada y na tela
		Color * pColor = nullptr;//Cor do Seguimento
		Segment * pNext = nullptr;//Ponteiro para o próximo elemento da pilha
	};
	
public:
	Snake(int _startX, int _startY);
	~Snake()
	{
		delete tail;
		tail = nullptr;		
	}

	//Move a Serpente pelo Tabuleiro
	void move();

	//Define a direção que a Serpente ira se mover (up / down / left / right)
	void setDirection(Direction  dir_);

	//Retorna a direção em que a Serpente e está se movendo (up / down / left / right)
	Direction getDirection() const;

	//Retorna o eixo em que a Serpente esta se movendo
	Direction getAxis() const;

	//Retorna o compirmento da Serpente
	int getSnkLenght() const;

	void grow();

	//Inicializa os Segmentos da Serpente
	void InitializeSnake();	
	
	Segment * head = nullptr; //Cabeça da Serpente(primeiro segmento da pilha)
	Segment * tail = nullptr; //fim da Serpente	(Ultimo Segmento da Pilha)
	Segment * getHead() const;	
	Vector getVelocity() const;

private:	
	

	//Cores do corpo da Serpente
	Color bodyColors[5] = {
		{228, 147, 117},
		{210, 136, 87},
		{194, 110, 64},
		{159, 73, 48},
		{152, 57, 27}
	}; //Cores do corpo da Serpente

	Vector velocity = { 0,-1 };
	
	const int startXCoord; //Cordenada X inicial. Posição da cabeça da serpente
	const int startYCoord; //Cordenada Y inicial. Posição da cabeça da serpente
	int segCount = 3; //Tamanho do corpo da Serpente
	
	Direction direction = Direction::UP; //Direção em que a Serpente esta se movendo
	Direction axis = Direction::VERTICALLY;

	//Inicializa os Segmentos do Corpo 
	void InitializeBody(const int xCoord, const int yCoord);
};
