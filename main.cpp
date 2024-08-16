#include "header.h"

Color green = { 15, 204, 96, 255 };
Color DarkGreen = { 43, 51, 24, 255 };

bool eventTriggered(double n, double& lastUpdateTime);

int main()
{
	double lut = 0;
	int cellSize = 30, cellCount = 25, Offset = 75;

	Game game = Game();

	cout << "Starting the game..." << endl;
	InitWindow(2*Offset + 750, 2*Offset + 750, "Retro Snake");
	SetTargetFPS(60);

	while (WindowShouldClose() == false) {
		BeginDrawing();

		// Controls the speed of the snake, make the abs val of the decimal closer to 0 to make it faster and vice-versa
		if (eventTriggered(0.2,lut)) {
			game.Update();
		}

		// Key input conditionals
		if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
			game.snake.direction = { 0, -1 };
			game.Running = true;
		}
		else if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
			game.snake.direction = { 0, 1 };
			game.Running = true;
		}
		else if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
			game.snake.direction = { -1, 0 };
			game.Running = true;
		}
		else if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
			game.snake.direction = { 1, 0 };
			game.Running = true;
		}


		// Drawing
		ClearBackground(green);
		DrawRectangleLinesEx(Rectangle{ (float)Offset - 5, (float)Offset - 5, (float)cellSize * cellCount + 10, (float)cellSize * cellCount + 10 }, 5, DarkGreen);
		DrawText("Retro Snake", Offset - 5, 20, 40, DarkGreen);
		DrawText(TextFormat("%i", game.score), Offset - 5, Offset + cellSize * cellCount + 10, 40, DarkGreen);
		game.Draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

bool eventTriggered(double n, double & lastUpdateTime) {
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= n) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

