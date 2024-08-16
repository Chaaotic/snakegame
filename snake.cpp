#include "header.h"

Color red = { 180, 0, 0, 255 };
Color darkGreen = { 43, 51, 24, 255 };

// FOOD CLASS DEFINITIONS
Food::Food() {
	cellSize = 30;
	cellCount = 25;
	offset = 75;
	position = { 5,6 };
}

Food::Food(deque<Vector2> snakeBody) {
	cellSize = 30;
	cellCount = 25;
	offset = 75;
	position = { 5,6 };
	position = GenerateRandomPos(snakeBody);
}

void Food::Draw() {
	DrawRectangle(offset+position.x * cellSize, offset +position.y * cellSize, cellSize, cellSize, red);
}

bool Food::ElementInDeque(Vector2 element, deque<Vector2> deque) {
	for (unsigned int i = 0; i < deque.size(); i++) {
		if (Vector2Equals(deque[i], element))
			return true;
	}
	return false;
}

Vector2 Food::GenerateRandomCell() {
	float x = GetRandomValue(0, cellCount - 1);
	float y = GetRandomValue(0, cellCount - 1);
	return Vector2{ x, y };
}

Vector2 Food::GenerateRandomPos(deque<Vector2> snakeBody) {
	Vector2 position = GenerateRandomCell();
	while (ElementInDeque(position, snakeBody)) {
		position = GenerateRandomCell();
	}
	return position;
}

// SNAKE CLASS DEFINITIONS
Snake::Snake() {
	body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
	direction = { 1,0 };
	cellSize = 30;
	cellCount = 25;
	offset = 75;
	addSegment = false;
}

void Snake::Draw() {
	for (unsigned int i = 0; i < body.size(); i++) {
		float x = body[i].x;
		float y = body[i].y;
		Rectangle segment = Rectangle{ offset + x * cellSize, offset + y * cellSize, (float)cellSize, (float)cellSize };
		DrawRectangleRounded(segment, 0.5, 6, darkGreen);
	}
}

void Snake::Update() {
	body.push_front(Vector2Add(body[0], direction));
	if (addSegment == true) {
		addSegment = false;
	}
	else {
		body.pop_back();
	}
}
void Snake::Reset() {
	body = { Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9} };
	direction = { 1, 0 };
}

// GAME CLASS DEFINTIONS
Game::Game() {
	snake = Snake();
	food = Food(snake.body);
	cellSize = 30;
	cellCount = 25;
	score = 0;
	Running = true;
	InitAudioDevice();
	eatSound = LoadSound("food_G1U6tlb.mp3");
	wallSound = LoadSound("spongebob-fail.mp3");
}

Game::~Game() {
	UnloadSound(eatSound);
	UnloadSound(wallSound);
	CloseAudioDevice();
}

void Game::Draw() {
	food.Draw();
	snake.Draw();
}

void Game::Update() {
	if (Running) {
		snake.Update();
		CheckCollisionsWithFood();
		CheckCollisionWithEdges();
		CheckCollisionWithTail();
	}
}

void Game::CheckCollisionsWithFood() {
	if (Vector2Equals(snake.body[0], food.position)) {
		food.position = food.GenerateRandomPos(snake.body);
		snake.addSegment = true;
		score++;
		PlaySound(eatSound);
	}
}

void Game::CheckCollisionWithEdges() {
	if (snake.body[0].x == cellCount || snake.body[0].x == -1) {
		GameOver();
	}
	if (snake.body[0].y == cellCount || snake.body[0].y == -1) {
		GameOver();
	}
}

void Game::CheckCollisionWithTail() {
	deque<Vector2> headlessBody = snake.body;
	headlessBody.pop_front();
	if (food.ElementInDeque(snake.body[0], headlessBody)) {
		GameOver();
	}
}

void Game::GameOver() {
	snake.Reset();
	food.position = food.GenerateRandomPos(snake.body);
	Running = false;
	score = 0;
	PlaySound(wallSound);
}