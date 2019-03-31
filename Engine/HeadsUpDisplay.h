#pragma once
#include "SpriteCodex.h"
#include "CharsCodex.h"

class HeadsUpDisplay
{
public:
	HeadsUpDisplay() = default;
	HeadsUpDisplay(int _x, int _y);
	HeadsUpDisplay(const int pxWidth);

	//Desenha o Hud com todas as suas informações na tela
	void drawHud(Graphics & gfx, const Palette & palette) const;

	//Soma um valor a pontuação
	void updateScore( const int sum_ );

	//Define o valor da pontuação
	void setScore(const int score_);

	void dropLife();
	int getLifes() const;

	void stageUp();
	void setStage(const int stage_);
	void resetStage();
	int getStage();

	//Atualiza as vidas
	void setLifes(const int lifes_ );
private:
	const int tileSize = 16;
	const int padding = 8;//espaço entre as infos da Hud
	const int border = 8;// medida da borda
	const int lHeight = CharsCodex::CHAR_SIZE;//Largura da linha da hud

	int hud_width;//Largura da HUD
	const int hud_height = tileSize * 6;

	int hud_x = (Graphics::ScreenWidth - hud_width) / 2;//Coordenada X da Hud na tela
	int hud_y = padding;//Coordenada Y da Hud na tela

	int stage = 1;
	int score = 0;
	int lives = 3;


	//Funções que desenham cada elemento da HUD
	void drawStageLabel(Graphics & gfx) const;
	void drawScoreLabel(Graphics & gfx) const;
	void drawLivesLabel(Graphics & gfx) const;	

	//Função que desenha a borda da HUD
	void drawBorder(Graphics & gfx, const Palette & palette ) const;
};