#ifndef GAMEUTILS_H
#define GAMEUTILS_H

#include <string>
#include "raylib.h"
#include "RandomApples.h"
#include "Snake.h"

class GameUtils {
private: 
	const int _FPS = 60;
	const int _scroll_speed = 100;
	const int _padding = 50;

	const int _background_squares_length = 900;

	Texture2D _clouds;
	Texture2D _background;

	float _background_x;

	Snake* _snake;
	ApplesInformation* _apples;
public:
	GameUtils();
	~GameUtils();
	void RunGame();
	void LoopBackground();
	void LoadBackground();

	void LoopSnake();
};

#endif
