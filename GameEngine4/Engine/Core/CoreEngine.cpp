#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine()	{
	window = nullptr;
	isRunning = false;
}

CoreEngine::~CoreEngine()	{

}

CoreEngine* CoreEngine::GetInstance()	{
	if (engineInstance.get() == nullptr) {//makes a new CoreEngine if there is none
		engineInstance.reset(new CoreEngine); 
	}
	return engineInstance.get();

}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)	{
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {  //both calls OnCreate & checks return value
		std::cout << "Window failed to initialize" << std::endl;
		OnDestroy();
		return isRunning = false; //sets + returns false
	}

	return isRunning = true;
}

void CoreEngine::Run()	{
	while (isRunning) {
		Update(0.016f);
		Render();
	}

	if (!isRunning) {
		OnDestroy();
	}
}

bool CoreEngine::GetIsRunning()	{
	return isRunning;
}

void CoreEngine::Update(const float deltaTime_)	{

}

void CoreEngine::Render()	{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//CALL GAME RENDER HERE (none for now)

	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy()	{
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}
