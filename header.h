#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

class Food
{
private:
	int cellSize;
	int cellCount;
	int offset;
public:
	Vector2 position;
	Food();
	Food(deque<Vector2> snakeBody);
	void Draw();
	bool ElementInDeque(Vector2 element, deque<Vector2> deque);
	Vector2 GenerateRandomCell();
	Vector2 GenerateRandomPos(deque<Vector2> snakeBody);
};

class Snake
{
private:
	int cellSize;
	int cellCount;
	int offset;
public:
	deque<Vector2> body;
	Vector2 direction;
	bool addSegment;
	Snake();
	void Draw();
	void Update();
	void Reset();
};

class Game {
private:
	int cellSize;
	int cellCount;
public:
	Snake snake;
	Food food;
	int score;
	bool Running;
	Sound eatSound;
	Sound wallSound;
	Game();
	~Game();
	void Draw();
	void Update();
	void CheckCollisionsWithFood();
	void CheckCollisionWithEdges();
	void CheckCollisionWithTail();
	void GameOver();
};

#endif