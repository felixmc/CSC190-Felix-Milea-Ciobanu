#include "Engine.h"
#include "Core.h"

using Core::Input;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;

bool update(float dt) {
	dt;
	return Input::IsPressed(Input::KEY_ESCAPE);
}

void draw(Core::Graphics& graphics) {
	graphics.SetColor(RGB(255,255,255));
	graphics.DrawString(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 20, "Hello World");
	graphics.DrawLine(10,10,400,300);
}

int main()
{
	Core::Init("Game Demo", SCREEN_WIDTH, SCREEN_HEIGHT);
	Core::RegisterUpdateFn(update);
	Core::RegisterDrawFn(draw);

	Core::GameLoop();

	return 0;
}

