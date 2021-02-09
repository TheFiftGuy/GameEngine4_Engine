#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine()	{
	window = nullptr;
	isRunning = false;
	fps = 60;
	gameInterface = nullptr;
	currentSceneNum = 0;
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
	Debug::OnCreate();
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {  //both calls OnCreate & checks return value
		Debug::FatalError("Window failed to initialize", "CoreEngine.cpp", __LINE__);
		OnDestroy();
		return isRunning = false; //sets + returns false
	}

	if (gameInterface) {
		if (!gameInterface->OnCreate() ) {
			Debug::FatalError("Game failed to initialize", "CoreEngine.cpp", __LINE__);
			OnDestroy();
			return isRunning = false;
		}
	}

	// /*for Testing*/ Debug::Info("Everything Worked", "CoreEngine.cpp", __LINE__); // message , fileName (or __FILE__), line
	timer.Start();
	return isRunning = true;
}

void CoreEngine::Run()	{
	while (isRunning) {
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime()	);
		Render();
		SDL_Delay(timer.GetSleepTime(fps) );
	}

	if (!isRunning) {
		OnDestroy();
	}
}

void CoreEngine::Exit()	{
	isRunning = false;
}

bool CoreEngine::GetIsRunning() const	{
	return isRunning;
}

int CoreEngine::GetCurrentScene() const	{
	return currentSceneNum;
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_)	{
	gameInterface = gameInterface_;

}

void CoreEngine::SetCurrentScene(int sceneNum_)	{
	currentSceneNum = sceneNum_;
}

void CoreEngine::Update(const float deltaTime_)	{
	
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
		std::cout << deltaTime_ << std::endl; //to test the timer for marking - not DEBUG worthy
	}

}

void CoreEngine::Render()	{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (gameInterface) {
		gameInterface->Render();
	}
	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy()	{
	delete gameInterface;
	gameInterface = nullptr;

	delete window;
	window = nullptr;

	SDL_Quit();
	exit(0);
}
