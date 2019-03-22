#pragma once
#include "SpriteCodex.h"
#include "CharsCodex.h"

class HeadsUpDisplay
{
public:
	HeadsUpDisplay() = default;
	HeadsUpDisplay(int _x, int _y);

	//Desenha o Hud com todas as suas informa��es na tela
	void drawHud(Graphics & gfx);

	//Atualiza a pontua��o
	void setScore( const int score_ );

	//Atualiza o n�vel
	void setStage( const int stage_ );

	//Atualiza as vidas
	void setLives(const int lives_ );
private:
	const int padding = 8;//espa�o entre as infos da Hud
	const int border = 8;// medida da borda
	const int lHeight = CharsCodex::CHAR_SIZE;//Largura da linha da hud

	const int hud_width = 640;//Largura da HUD
	const int hud_height = padding * 2 + border * 2 + lHeight * 2;//Altura da HUD

	int hud_x = (Graphics::ScreenWidth - hud_width) / 2;//Coordenada X da Hud na tela
	int hud_y = padding;//Coordenada Y da Hud na tela

	int stage = 0;
	int score = 0;
	int lives = 12;


	//Fun��es que desenham cada elemento da HUD
	void drawStageLabel(Graphics & gfx);
	void drawScoreLabel(Graphics & gfx);
	void drawLivesLabel(Graphics & gfx);

	//Fun��o que desenha a borda da HUD
	void drawBorder(Graphics & gfx);
};