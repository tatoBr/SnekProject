#include "Snake.h"

Snake::Snake(int _startX, int _startY)
	:
	startXCoord(_startX),
	startYCoord(_startY)
{

}

/*************Public Functions***************/
void Snake::InitializeSnake()
{
	lastBodyIndex = 0;	
	setDirection( Direction::UP );
	head = { startXCoord, startYCoord, Color{ 205, 225, 34 } };
	InitializeBody(startXCoord, startYCoord + 1);
	tail = { startXCoord, body[lastBodyIndex].yCoord + 1,{ 0, 96, 0 } };
}

void Snake::move()
{
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
}

void Snake::setDirection(Direction  dir_)
{	
	direction = dir_;
	switch (direction)
	{
	case Direction::UP:
		velocity = { 0, -1 };		
		break;

	case Direction::DOWN:
		velocity = { 0, 1 };		
		break;
	
	case Direction::LEFT:
		velocity = { -1, 0 };		
		break;

	case Direction::RIGHT:
		velocity = { 1, 0 };		
		break;

	default:
		break;
	}	
}
Snake::Direction Snake::getDirection() const 
{
	return direction;
}
int Snake::getSnkLenght() const
{
	return lastBodyIndex;
}
void Snake::grow()
{
	lastBodyIndex++;
}

Snake::Segment Snake::getHead() const
{
	return head;
}
Snake::Segment Snake::getTail() const
{
	return tail;
}
Snake::Vector Snake::getVelocity() const
{
	return velocity;
}


/*************Private Functions***************/
void Snake::InitializeBody(const int _xCoord, const int _yCoord)
{	
	int nx = _xCoord, ny = _yCoord;
	for (int i = 0; i < SNAKE_MAX_SIZE; i++)
	{		
		if (i <= lastBodyIndex) {			
			body[i] = { nx, ny, bodyColors[i % 5] };
			ny += 1;
		}
		else body[i] = { offBoard, offBoard, bodyColors[i % 5] };
	}
}




