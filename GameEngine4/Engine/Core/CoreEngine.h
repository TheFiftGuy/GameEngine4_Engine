#ifndef COREENGINE_H
#define COREENGINE_H

#include "GameInterface.h"
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include <memory>


class CoreEngine	{
public:
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	static CoreEngine* GetInstance();

	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning();

	void SetGameInterface(GameInterface* gameInterface_);

private:
	CoreEngine();
	~CoreEngine();
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	Window* window;
	bool isRunning;

	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;
};

#endif // !COREENGINE_H