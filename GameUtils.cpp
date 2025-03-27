#include "GameUtils.h"
#include "TaskUtils.h"
#include <algorithm>
#include <utility>
#include <iostream>

GameUtils::GameUtils() {
	InitWindow(0, 0, "");
	//InitWindow(200, 200, "");
	ToggleFullscreen();
	SetTargetFPS(_FPS);
	//HideCursor();

	_clouds = LoadTexture(TaskUtils::_clouds_path);
	_background = LoadTexture(TaskUtils::_bc_path);

	_snake = new Snake((GetScreenWidth() - _background_squares_length) / 2, (GetScreenHeight() - _background_squares_length) / 2, _background_squares_length, _FPS);
	_apples = new ApplesInformation(_apple_count);

	_background_x = 0.0f;
	_frame_count = _FPS / _snake->_speed;
}

GameUtils::~GameUtils() {
	UnloadTexture(_clouds);
	UnloadTexture(_background);

	delete _snake;
	delete _apples;

	CloseWindow();
}

void GameUtils::RunGame() {
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		LoopBackground();
		LoadBackground();

		LoopSnake();

		EndDrawing();
		_frame_count++;
	}
}

void GameUtils::LoopBackground() {
	_background_x -= _scroll_speed * GetFrameTime();

	if (_background_x <= -_clouds.width)
		_background_x = 0;

	for (int i = 0; _background_x + i * _clouds.width < GetScreenWidth(); i++) {
		DrawTexture(_clouds, _background_x + i * _clouds.width, 0, WHITE);
		DrawTexture(_clouds, _background_x + i * _clouds.width, _clouds.width, WHITE);
	}
}

void GameUtils::LoadBackground() {
	Rectangle square{ (GetScreenWidth() / 2) - _padding - (_background.width * 2), (GetScreenHeight() / 2) - _padding - (_background.height * 2), (_background.width * 4) + (_padding * 2), (_background.height * 4) + (_padding * 2)};
	DrawRectangleRounded(square, 0.1f, 10, DARKGREEN);

	int xStart = GetScreenWidth() / 2 - (_background.width * 2.0f);
	int yStart = GetScreenHeight() / 2 - (_background.height * 2.0f);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			DrawTexture(_background, xStart + i * _background.width, yStart + j * _background.height, WHITE);
		}
	}
}

void GameUtils::LoopSnake() {
	_snake->_temp_accseleration = _snake->DistributeAccseleration();

	std::cout << _snake->_accseleration.first << ' ' << _snake->_accseleration.second << std::endl;

	if (_snake->AccselerationZero() || _frame_count == _FPS / _snake->_speed) {
		_snake->_accseleration = _snake->_temp_accseleration;
		_frame_count = 0;
	}

	_snake->Pop_Back();
	_snake->Push_Front(_snake->IncramentedPair());
	

	std::for_each(_snake->Begin(), _snake->End(), [&](const std::pair<int,int>& pair) {
		DrawRectangle(pair.first, pair.second, _snake->GetSquaresLength(), _snake->GetSquaresLength(), RED);
	});
}

void GameUtils::PlaceAndUpdateApples() {

}