#include "Snake.h"

Snake::Snake()
{
	InitializeSnake();	
}

void Snake::move(Board & _b)
{
	if (checkCollision())
	{
		deactivateSnake(_b);

		tail.xCoord = body[lastBodyIndex].xCoord;
		tail.yCoord = body[lastBodyIndex].yCoord;
		for (int i = lastBodyIndex; i > 0; i--)
		{
			body[i].xCoord = body[i - 1].xCoord;
			body[i].yCoord = body[i - 1].yCoord;
		}

		body[0].xCoord = head.xCoord;
		body[0].yCoord = head.yCoord;

		head.xCoord += velocity.x;
		head.yCoord += velocity.y;

		activateSnake(_b);
	}
}

void Snake::setDirection(const int dir)
{
	int movingTo = dir;
	switch (movingTo)
	{
	case SNAKE_MOVING_UP:
		velocity = { 0, -1 };
		movDirection = SNAKE_MOVING_UP;
		break;

	case SNAKE_MOVING_DOWN:
		velocity = { 0, 1 };
		movDirection = SNAKE_MOVING_DOWN;
		break;
	
	case SNAKE_MOVING_LEFT:
		velocity = { -1, 0 };
		movDirection = SNAKE_MOVING_LEFT;
		break;

	case SNAKE_MOVING_RIGHT:
		velocity = { 1, 0 };
		movDirection = SNAKE_MOVING_RIGHT;
		break;

	default:
		break;
	}	
}

int Snake::getDirection()
{
	return movDirection;
}

void Snake::setSnakeOnBoard(Board & _b)
{
	activateSnake(_b);
}

void Snake::InitializeSnake()
{
	lastBodyIndex = 0;
	head = { startXCoord, startYCoord, Color{205, 225, 34} };
	InitializeBody(startXCoord, startYCoord + 1);	
	tail = { startXCoord, body[0].yCoord + 1, { 0, 96, 0} };
}

void Snake::InitializeBody(const int _xCoord, const int _yCoord)
{	
	int nx = _xCoord, ny = _yCoord;
	for (int i = 0; i < SNAKE_MAX_SIZE; i++)
	{		
		if (i <= lastBodyIndex) {			
			body[i] = { nx, ny, bodyColors[i % 5] };
			ny++;
		}
		else body[i] = { offBoard, offBoard, bodyColors[i % 5] };
	}
}

void Snake::activateSnake(Board & _b) const
{
	_b.activateCell(head.xCoord, head.yCoord, head.c);
	for (int i = 0; i <= lastBodyIndex; i++)
	{
		_b.activateCell(body[i].xCoord, body[i].yCoord, body[i].c);
	}
	_b.activateCell(tail.xCoord, tail.yCoord, tail.c);
}

void Snake::deactivateSnake(Board & _b) const
{
	_b.deactivateCell(head.xCoord, head.yCoord);
	for (int i = 0; i < lastBodyIndex; i++) {
		_b.deactivateCell(body[i].xCoord, body[i].yCoord);
	}
	_b.deactivateCell(tail.xCoord, tail.yCoord);
}

bool Snake::checkCollision() const
{
	const int nextX = head.xCoord + velocity.x;
	const int nextY = head.yCoord + velocity.y;
	bool collidedWithBody = false;
	for (int i = 0; i < lastBodyIndex; i++)
	{
		if (nextX == body[i].xCoord && nextY == body[i].yCoord)
		{
			collidedWithBody = true;
			break;
		}
	}
	if (!collidedWithBody)
	{
		if (nextX == tail.xCoord && nextY == tail.yCoord)
		{
			collidedWithBody = true;
		}
	}

	return (nextX < BOARD_N_COLS && nextX >= 0) && (nextY < BOARD_N_LINS && nextY >= 0) && !collidedWithBody;
}
