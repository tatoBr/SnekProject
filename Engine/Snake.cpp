#include "Snake.h"

Snake::Snake(int _startX, int _startY)
	:
	startXCoord(_startX),
	startYCoord(_startY)
{
	InitializeSnake();
}

/*************Public Functions***************/
void Snake::InitializeSnake()
{		
	if (tail != nullptr)
	{
		delete tail;
		tail = nullptr;
	}
	setDirection( Direction::UP );	
	InitializeBody(startXCoord, startYCoord);	
}

void Snake::move()
{
	Segment * currentSeg = tail;
	while (currentSeg->getNext() != nullptr)
	{
		Vector v = currentSeg->getNext()->getPosition();
		currentSeg->setPosition({ v.x, v.y });
		currentSeg = currentSeg->getNext();
	}

	Vector pos = head->getPosition();

	head->setPosition({ pos.x + velocity.x, pos.y + velocity.y });
}

void Snake::setDirection(Direction  dir_)
{	
	direction = dir_;
	switch (direction)
	{
	case Direction::UP:
		velocity = { 0, -1 };
		axis = Direction::VERTICALLY;
		break;

	case Direction::DOWN:
		velocity = { 0, 1 };
		axis = Direction::VERTICALLY;
		break;
	
	case Direction::LEFT:
		velocity = { -1, 0 };	
		axis = Direction::HORIZOLTALLY;
		break;

	case Direction::RIGHT:
		velocity = { 1, 0 };
		axis = Direction::HORIZOLTALLY;
		break;

	default:
		break;
	}	
}
Snake::Direction Snake::getDirection() const 
{
	return direction;
}
Snake::Direction Snake::getAxis() const
{
	return axis;
}
int Snake::getSnkLenght() const
{
	return tail->getSegmentCount();
}
void Snake::grow()
{
	Vector nsCoords = tail->getPosition();//@nsCoords coordenadas do novo segmento	

	auto * nt = new Segment(nsCoords.x, nsCoords.y, bodyColors[tail->getSegmentCount() % 5]);
	nt->connect(tail);
	tail = nt;
}

Snake::Segment * Snake::getHead() const
{	
	return head;
}

Snake::Vector Snake::getVelocity() const
{
	return velocity;
}

/*************Private Functions***************/
void Snake::InitializeBody(const int _xCoord, const int _yCoord)
{
	tail = new Segment(_xCoord, _yCoord, bodyColors[0]);
	head = tail;	
	for (int i = 1; i < segCount; i++)
	{
		head->connect(new Segment(_xCoord, _yCoord - i, bodyColors[i % 5]));
		head = head->getNext();
	}
}




