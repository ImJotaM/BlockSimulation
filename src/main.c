#include <raylib.h>

void RandomizeColor(Color* color) {

	color->r = GetRandomValue(0, 255);
	color->g = GetRandomValue(0, 255);
	color->b = GetRandomValue(0, 255);

}

Color GetRandomColor() {

	Color color;

	color.r = GetRandomValue(0, 255);
	color.g = GetRandomValue(0, 255);
	color.b = GetRandomValue(0, 255);

	return color;
}

typedef struct {

	Rectangle rect;

	float velocity_x;
	float velocity_y;

	Color color;

} Block;

void InitBlock(Block* block, int window_width, int window_height) {

	float size = (float)GetRandomValue(50, 80);
	float posx = (float)GetRandomValue(0, (int)(window_width - size));
	float posy = (float)GetRandomValue(0, (int)(window_height - size));

	float velocity_x = (float)GetRandomValue(300, 800);
	float velocity_y = (float)GetRandomValue(300, 800);

	*(block) = (Block){
		.rect = { posx, posy, size, size },
		.velocity_x = velocity_x,
		.velocity_y = velocity_y,
		.color = GetRandomColor(),
	};

}

void UpdateBlock(Block* block, int window_width, int window_height, float dt) {

	block->rect.x += (block->velocity_x * dt);
	block->rect.y += (block->velocity_y * dt);

	if (block->rect.x + block->rect.width > window_width || block->rect.x < 0) {
		block->velocity_x *= -1;
		RandomizeColor(&block->color);
	}

	if (block->rect.y + block->rect.height > window_height || block->rect.y < 0) {
		block->velocity_y *= -1;
		RandomizeColor(&block->color);
	}

}

void RenderBlock(Block* block) {
	DrawRectangleRec(block->rect, block->color);
}

int main() {

	const char* Window_title = "BlockSimulation";

	SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT);
	InitWindow(0, 0, Window_title);

	int fps = GetMonitorRefreshRate(GetCurrentMonitor());
	int window_width = GetMonitorWidth(GetCurrentMonitor());
	int window_height = GetMonitorHeight(GetCurrentMonitor());

	SetTargetFPS(fps);

	int block_lenght = 1;
	Block* blocks = (Block*)MemAlloc(block_lenght * sizeof(Block));
	if (!blocks) {
		TraceLog(LOG_ERROR, "Failed to allocate memory for blocks");
		CloseWindow();
		return -1;
	}

	for (size_t i = 0; i < block_lenght; ++i) {
		InitBlock(&blocks[i], window_width, window_height);
	}

	while (!WindowShouldClose()) {

		if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_EQUAL)) {
			
			block_lenght++;
			blocks = (Block*)MemRealloc(blocks, block_lenght * sizeof(Block));
			InitBlock(&blocks[block_lenght - 1], window_width, window_height);

		}

		float dt = GetFrameTime();

		for (size_t i = 0; i < block_lenght; ++i) {
			UpdateBlock(&blocks[i], window_width, window_height, dt);
		}

		BeginDrawing();

		ClearBackground(BLACK);

		DrawText(TextFormat("FPS: %d", GetFPS()), 0, 0, 16, WHITE);

		for (size_t i = 0; i < block_lenght; ++i) {
			RenderBlock(&blocks[i]);
		}

		EndDrawing();

	}

	MemFree(blocks);

	CloseWindow();

	return 0;
}