#include "HeadsUpDisplay.h"

HeadsUpDisplay::HeadsUpDisplay(int _x, int _y)
	:
	hud_x(_x),
	hud_y(_y)
{}

void HeadsUpDisplay::drawHud(Graphics & gfx)
{
	drawStageLabel(gfx);
	drawScoreLabel(gfx);
	drawLivesLabel(gfx);
	drawBorder(gfx);
}

void HeadsUpDisplay::setScore(const int score_)
{
	score = score_;
}

void HeadsUpDisplay::setStage(const int stage_)
{
	stage = stage_;
}

void HeadsUpDisplay::setLives(const int lives_)
{
	lives = lives_;
}

void HeadsUpDisplay::drawStageLabel(Graphics & gfx)
{
	std::string label = "STAGE ";

	const int labelx = hud_x + border + padding;
	const int labely = hud_y + border + padding;

	const int stageX = labelx + (CharsCodex::CHAR_SIZE * label.size());
	const int stageY = labely;

	CharsCodex::drawString( label, labelx, labely, gfx, { 255, 255,0 } );
	CharsCodex::drawNumber( stage, stageX, stageY, gfx, { 255, 255, 255 } );	
}

void HeadsUpDisplay::drawScoreLabel(Graphics & gfx)
{
	std::string label = "SCORE ";

	const int labelx = hud_x + border + padding;
	const int labely = hud_y + border + padding + lHeight + padding;

	const int valueX = labelx + (CharsCodex::CHAR_SIZE * label.size());
	const int valueY = labely;

	CharsCodex::drawString(label, labelx, labely, gfx, { 255, 255,0 });
	CharsCodex::drawNumber(score, valueX, valueY, gfx, { 255, 255, 255 });
}

void HeadsUpDisplay::drawLivesLabel(Graphics & gfx)
{
	std::string label = "LIVES ";

	const int labelx = ( ( hud_x + hud_width ) - padding - CharsCodex::CHAR_SIZE ) - ( label.size() * CharsCodex::CHAR_SIZE ) - ( 9 * CharsCodex::CHAR_SIZE );
	const int labely = hud_y + border + padding;

	const int valueX = labelx + (CharsCodex::CHAR_SIZE * label.size());
	const int valueY = labely;

	CharsCodex::drawString(label, labelx, labely, gfx, { 255, 255,0 });
	for (int i = 0; i < lives; i++)
	{
		int x = valueX + (i * CharsCodex::CHAR_SIZE);

		if (i >= 8)
		{
			SpriteCodex::drawTileHeartPlus(gfx, x, valueY);
			break;
		}
		else {
			SpriteCodex::drawTileHeart(gfx, x, valueY);
		}
	}
	
	
}

void HeadsUpDisplay::drawBorder(Graphics & gfx)
{
	const int npx = hud_width / padding - 2; //n de quadrados que formam a borda na horizontal
	const int npy = hud_height / padding;//n de quadrados que formam a borda na vertical

	for (int y = 0; y < npy; y++)
	{
		const int xi = hud_x;
		const int xii = ( hud_x + hud_width ) -  padding * 3 ;
		const int cy = hud_y +  ( y * padding );
		gfx.drawSquare(xi + 1 , cy + 1, padding - 1, { 128, 128, 128 } );
		gfx.drawSquare(xii + 1, cy + 1, padding - 1, { 128, 128, 128 });
	}

	for (int x = 0; x < npx; x++)
	{
		const int yi = hud_y;
		const int yii = hud_y + hud_height;
		const int cx = hud_x +  ( x * padding );

		gfx.drawSquare(cx + 1, yi + 1, padding - 1, { 128, 128, 128 });
		gfx.drawSquare(cx + 1, yii + 1, padding - 1, { 128, 128, 128 });
	}


}
