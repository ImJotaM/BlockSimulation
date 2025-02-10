#include <raylib.h>

#define DELTA_TIME(FPS) (float)(1.0 / (float) FPS)
#define BLOCK_SIZE 80.0

void RandomizeColor(Color* color) {

	color->r = GetRandomValue(0, 255);
	color->g = GetRandomValue(0, 255);
	color->b = GetRandomValue(0, 255);

}

int main() {

	const char* Window_title = "BlockSimulation";

	SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_BORDERLESS_WINDOWED_MODE | FLAG_VSYNC_HINT);
	InitWindow(0, 0, Window_title);

	int fps = GetMonitorRefreshRate(GetCurrentMonitor());
	int Window_width = GetMonitorWidth(GetCurrentMonitor());
	int Window_height = GetMonitorHeight(GetCurrentMonitor());

	Rectangle rect = {
		.x = 0.0,
		.y = 0.0,
		.width = BLOCK_SIZE,
		.height = BLOCK_SIZE,
	};

	float velocity_x = 600;
	float velocity_y = 600;

	float lastFrameTime = (float) GetTime();
	float currentFrameTime;
	float accumulator = 0.0;

	Color color = RED;

	while (!WindowShouldClose()) {

		currentFrameTime = (float) GetTime();
		float dt = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		accumulator += dt;

		while (accumulator >= DELTA_TIME(fps)) {

			rect.x += (velocity_x * DELTA_TIME(fps));
			rect.y += (velocity_y * DELTA_TIME(fps));

			if (rect.x + BLOCK_SIZE > Window_width || rect.x < 0) {
				velocity_x *= -1;
				RandomizeColor(&color);
			}

			if (rect.y + BLOCK_SIZE > Window_height || rect.y < 0) {
				velocity_y *= -1;
				RandomizeColor(&color);
			}

			accumulator -= DELTA_TIME(fps);

		}

		BeginDrawing();

		ClearBackground(BLACK);

		DrawText(TextFormat("FPS: %d", GetFPS()), 0, 0, 16, WHITE);
		DrawRectangleRec(rect, color);

		EndDrawing();

	}

	CloseWindow();

	return 0;
}