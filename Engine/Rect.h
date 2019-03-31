#pragma once

class Rect
{
public:
	Rect() = delete;
	Rect(int x_, int y_, int width_, int height_)
		:
		xCoord(x_),
		yCoord(y_),
		width(width_),
		height(height_)
	{
		left = xCoord;
		right = xCoord + width;
		top = yCoord;
		bottom = yCoord + height;
	}

	bool containsPoint(const int x_, const int y_) const
	{
		return (( x_ >= left ) && ( x_ <= right )) && (( y_ >= top) && (y_ <= bottom ));
	}

	int getX() const
	{
		return xCoord;
	}
	int getY() const
	{
		return yCoord;
	}
	int getCenterX() const
	{
		return xCoord + width / 2;
	}
	int getCenterY() const
	{
		return yCoord + height / 2;
	}
private:
	int xCoord;
	int yCoord;
	int width;
	int height;

	int left; 
	int right;
	int top;
	int bottom;
};
