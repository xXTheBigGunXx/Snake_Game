#include "GameUtils.h"
#include "TaskUtils.h"
#include <algorithm>
#include <utility>

GameUtils::GameUtils() {
	InitWindow(0, 0, "");
	ToggleFullscreen();
	SetTargetFPS(_FPS);

	_clouds = LoadTexture(TaskUtils::_clouds_path);
	_background = LoadTexture(TaskUtils::_bc_path);
	_apple_texture = LoadTexture(TaskUtils::_apple_path);
	_snakes_head_texture = LoadTexture(TaskUtils::_snake_head_path);

	_snake = new Snake((GetScreenWidth() - _background_squares_length) / 2, (GetScreenHeight() - _background_squares_length) / 2, _background_squares_length, _FPS);
	_apples = new ApplesInformation(_apple_count, _background_squares_length);

	_background_x = 0.0f;
	_frame_count = _FPS / _snake->_speed;
}

GameUtils::~GameUtils() {
	UnloadTexture(_clouds);
	UnloadTexture(_background);
	UnloadTexture(_apple_texture);
	UnloadTexture(_snakes_head_texture);

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

		if (start_of_a_game == true) {
			Rectangle button = { GetScreenWidth()/2 - 300, GetScreenHeight()/2 - 75, 600, 150};
			DrawRectangleRec(button, LIGHTGRAY);
			DrawText(mess.c_str(), GetScreenWidth() / 2 - (mess.length() * 13), GetScreenHeight() / 2 - 25, 50, DARKGRAY);

			if (CheckCollisionPointRec(GetMousePosition(), button)) {
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					start_of_a_game = false;
					_game_over = false;
				}
			}
		}
		else {

			PlaceAndUpdateApples();
			LoopSnake();

			if (_snake->OutOfBounds(_background_squares_length) || _snake->HitItself()) {
				DrawText("Game Over!", GetScreenWidth() / 2 - 250, GetScreenHeight() / 2 - 25, 100, BLACK);
				mess = "Restart the game!";
				_game_over = true;
				start_of_a_game = true;

				_snake = new Snake((GetScreenWidth() - _background_squares_length) / 2, (GetScreenHeight() - _background_squares_length) / 2, _background_squares_length, _FPS);
				_apples = new ApplesInformation(_apple_count, _background_squares_length);

				_snakes_head_texture = LoadTexture(TaskUtils::_snake_head_path);
			}
		}

		EndDrawing();
		_frame_count++;
	}
}

void GameUtils::LoopBackground() {
	if(_game_over == false)
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
	if(_game_over == false){
		auto temp = _snake->DistributeAccseleration();
		bool changes_dirrection = false;

		if (temp.first != _snake->_temp_accseleration.first || temp.second != _snake->_temp_accseleration.second) {
			changes_dirrection = true;
			if (changes_dirrection == true) {
				if (temp == std::make_pair(1, 0)) {
					if (_snake->_temp_accseleration == std::make_pair(0, -1))
						_snakes_head_texture = RotateTexture90(_snakes_head_texture, true);
					else
						_snakes_head_texture = RotateTexture90(_snakes_head_texture, false);
				}
				else if (temp == std::make_pair(-1, 0)) {
					if (_snake->_temp_accseleration == std::make_pair(0, -1))
						_snakes_head_texture = RotateTexture90(_snakes_head_texture, false);
					else
						_snakes_head_texture = RotateTexture90(_snakes_head_texture, true);
				}
				else if (temp == std::make_pair(0, 1)) {
					if (_snake->_temp_accseleration == std::make_pair(1, 0))
						_snakes_head_texture = RotateTexture90(_snakes_head_texture, true);
					else
						_snakes_head_texture = RotateTexture90(_snakes_head_texture, false);
				}
				else if (temp == std::make_pair(0, -1)) {
					if (_snake->_temp_accseleration == std::make_pair(-1, 0))
						_snakes_head_texture = RotateTexture90(_snakes_head_texture, true);
					else
						_snakes_head_texture = RotateTexture90(_snakes_head_texture, false);
				}
			}
			_snake->_temp_accseleration = temp;
		}

		if (_snake->AccselerationZero() || _frame_count % (_FPS / _snake->_speed) == 0) {
			_snake->_accseleration = _snake->_temp_accseleration;
			_frame_count = 0;
		}
		if (!_snake->AccselerationZero()) {
			_snake->Pop_Back();
			_snake->Push_Front(_snake->IncramentedPair());
		}
	}
	
	int count = 0;

	std::for_each(_snake->_snakes_body.rbegin(), _snake->_snakes_body.rend(), [&](const std::pair<int, int>& pair) {

		if (pair == *_snake->Begin())
			DrawTexture(_snakes_head_texture, pair.first + _snake->_accseleration.first * 10, pair.second + _snake->_accseleration.second * 10, WHITE);
		else {
			DrawCircle(pair.first + 30, pair.second + 30, 30.0f, Color{ 88, 156,65, 200});
			if (count % 5 == 0) {
				auto temp = Vector2();
				temp.x = pair.first + 30;
				temp.y = pair.second + 30;
				DrawRing(temp, 25, 30, 0, 360, 10, Color{100, 200,73,255});
			}
			count++;
		}
	});
}

void GameUtils::PlaceAndUpdateApples() {
	int index = _snake->HeadHitApple(_apples);

	if (index != -1) {
		_apples->_index--;

		std::pair<int, int> temp;
		for (size_t i = 0; i < _frame_count; i++) {
			auto idk = std::prev(_snake->_snakes_body.end());
			temp = *idk;
			_snake->_snakes_body.push_back(std::make_pair(temp.first, temp.second));
		}

		_apples->_coordinates.erase(_apples->_coordinates.begin() + index);
	}
	_apples->GenerateNApples();

	for (size_t i = 0; i < _apples->_coordinates.size(); i++) {
		DrawTexture( _apple_texture, _snake->_x_offset + _apples->_coordinates[i].first, _snake->_y_offset + _apples->_coordinates[i].second, WHITE);
	}
}

Texture2D GameUtils::RotateTexture90(Texture2D texture, bool clock_wise) {
	Image image = LoadImageFromTexture(texture);

	if (clock_wise) {
		ImageRotateCW(&image);
	}
	else {
		ImageRotateCCW(&image);
	}
	Texture2D rotatedTexture = LoadTextureFromImage(image);
	UnloadImage(image);

	return rotatedTexture;
}