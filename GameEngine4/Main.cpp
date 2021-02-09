#include "Engine/Core/CoreEngine.h"
#include "Game/Game1.h"


int main(int argc, char* argv[]) {
	CoreEngine::GetInstance()->SetGameInterface(new Game1() );

	if (!CoreEngine::GetInstance()->OnCreate("Game 258 Engine", 800, 600)) {
		std::cout << "Engine failed to initialize" << std::endl;
		return 0;
	}
	CoreEngine::GetInstance()->Run();
	return 0;
}