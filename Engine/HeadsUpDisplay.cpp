#include "HeadsUpDisplay.h"

HeadsUpDisplay::HeadsUpDisplay(int _x, int _y)
	:
	hud_x(_x),
	hud_y(_y)
{}
HeadsUpDisplay::HeadsUpDisplay(const int pxWidth)
	:
	hud_width(pxWidth / tileSize * tileSize),
	hud_x( ( Graphics::ScreenWidth - hud_width ) / 2)
{}

void HeadsUpDisplay::drawHud(Graphics & gfx, const Palette & palette) const
{
	drawStageLabel(gfx);
	drawScoreLabel(gfx);
	drawLivesLabel(gfx);
	drawBorder(gfx, palette);
}

void HeadsUpDisplay::updateScore(const int  sum_)
{
	score += sum_;
}

void HeadsUpDisplay::setScore(const int score_)
{
	score = score_;
}

void HeadsUpDisplay::dropLife()
{
	lives--;
}

int HeadsUpDisplay::getLifes() const
{
	return lives;
}

void HeadsUpDisplay::stageUp()
{
	stage++;
}

void HeadsUpDisplay::setStage(const int stage_)
{
	stage = stage_;
}

void HeadsUpDisplay::resetStage()
{
	stage = 0;
}

int HeadsUpDisplay::getStage()
{
	return stage;
}

void HeadsUpDisplay::setLifes(const int lives_)
{
	lives = lives_;
}

void HeadsUpDisplay::drawStageLabel(Graphics & gfx) const
{
	std::string label = "STAGE ";

	const int labelx = hud_x + tileSize * 2;
	const int labely = tileSize * 2;

	const int stageX = labelx + (CharsCodex::CHAR_SIZE * (int)label.size());
	const int stageY = labely;

	CharsCodex::drawString( label, labelx, labely, gfx, { 255, 255,0 } );
	CharsCodex::drawNumber( stage, stageX, stageY, gfx, { 255, 255, 255 } );	
}

void HeadsUpDisplay::drawScoreLabel(Graphics & gfx) const
{
	std::string label = "SCORE ";

	const int labelx = hud_x + tileSize * 2;
	const int labely = tileSize * 4;

	const int valueX = labelx + (CharsCodex::CHAR_SIZE * (int)label.size());
	const int valueY = labely;

	CharsCodex::drawString(label, labelx, labely, gfx, { 255, 255,0 });
	CharsCodex::drawNumber(score, valueX, valueY, gfx, { 255, 255, 255 });
}

void HeadsUpDisplay::drawLivesLabel(Graphics & gfx) const
{
	std::string label = "LIVES ";

	const int labelx = ( hud_x + hud_width ) - ( tileSize * 5 );
	const int labely = tileSize * 2;

	const int valueX = labelx + 2 * tileSize;
	const int valueY = labely;

	SpriteCodex::live(gfx, labelx, labely);
	CharsCodex::drawString("X", labelx + tileSize, labely, gfx, Colors::White);
	CharsCodex::drawNumber(lives, valueX, valueY, gfx, Colors::White);
}

void HeadsUpDisplay::drawBorder(Graphics & gfx, const Palette & palette) const
{
	for (int x = hud_x; x < hud_x + hud_width; x += tileSize)
	{
		SpriteCodex::Obstacle(gfx, x, 0, palette.base, palette.shadow, palette.highlight);
	}
	for (int y = 0; y < hud_height; y += tileSize)
	{
		SpriteCodex::Obstacle(gfx, hud_x, y, palette.base, palette.shadow, palette.highlight);
		SpriteCodex::Obstacle(gfx, hud_x + hud_width - tileSize, y, palette.base, palette.shadow, palette.highlight);
	}
}
