#ifndef GAMEUTILS_H
#define GAMEUTILS_H

#include <string>
#include "raylib.h"
//#include "RandomApples.h"
#include "Snake.h"

class GameUtils {
private: 
	const int _FPS = 60;
	int _frame_count;

	const int _scroll_speed = 100;
	const int _padding = 50;

	const int _background_squares_length = 900;

	const int _apple_count = 10;

	Texture2D _clouds;
	Texture2D _background;
	Texture2D _apple_texture;

	float _background_x;
	bool _game_over = false;

	Snake* _snake;
	ApplesInformation* _apples;
public:
	GameUtils();
	~GameUtils();
	void RunGame();
	void LoopBackground();
	void LoadBackground();

	void LoopSnake();
	void PlaceAndUpdateApples();
};

#endif
