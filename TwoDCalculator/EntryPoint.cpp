#include "RenderUI.h"
#include "Engine.h"

int main(int argc, char* argv[])
{
	Engine::Init();

	RenderUI renderUI;

	if( ! renderUI.initialize(argc, argv))
		return -1;
	return renderUI.run();
}