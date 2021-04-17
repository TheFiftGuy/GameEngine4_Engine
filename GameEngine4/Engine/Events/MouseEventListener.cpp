#include "MouseEventListener.h"
#include "../Core/CoreEngine.h"

CoreEngine* MouseEventListener::engineInstance = nullptr;
glm::ivec2 MouseEventListener::mouse = glm::ivec2();
glm::ivec2 MouseEventListener::prevMouse = glm::ivec2();
bool MouseEventListener::firstUpdate = true;


MouseEventListener::~MouseEventListener()	{
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(CoreEngine* engine_)	{
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e_)	{
	if(e_.type == SDL_MOUSEBUTTONDOWN) {
		UpdateMousePosition();
		NotifyOfMousePressed(e_.button.button);
	}
	else if(e_.type == SDL_MOUSEBUTTONUP) {
		UpdateMousePosition();
		NotifyOfMouseReleased(e_.button.button);
	}
	else if(e_.type == SDL_MOUSEMOTION) {
		UpdateMousePosition();
		NotifyOfMouseMove();
	}
	else if(e_.type == SDL_MOUSEWHEEL) {
		UpdateMousePosition();
		NotifyOfMouseScroll(e_.wheel.y);
	}
}

void MouseEventListener::NotifyOfMousePressed(int buttonType_)	{
	if(engineInstance) {
		engineInstance->NotifyOfMousePressed(mouse, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseReleased(int buttonType_)	{
	if (engineInstance) {
		engineInstance->NotifyOfMouseReleased(mouse, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseMove()	{
	if (engineInstance) {
		engineInstance->NotifyOfMouseMove(mouse);
	}
}

void MouseEventListener::NotifyOfMouseScroll(int y_)	{
	if (engineInstance) {
		engineInstance->NotifyOfMouseScroll(y_);
	}
}

glm::ivec2 MouseEventListener::GetPreviousMousePosition()	{
	return prevMouse;
}

glm::ivec2 MouseEventListener::GetMousePosition()	{
	return mouse;
}

glm::ivec2 MouseEventListener::GetMouseOffset()	{
	return glm::ivec2(mouse.x - prevMouse.x, prevMouse.y - mouse.y);
}

void MouseEventListener::UpdateMousePosition()	{
	int tmpX, tmpY;
	SDL_GetMouseState(&tmpX, &tmpY);
	tmpY = static_cast<int>(engineInstance->GetScreenHeight()) - tmpY;
	if(firstUpdate) {
		prevMouse.x = mouse.x = tmpX;
		prevMouse.y = mouse.y = tmpY;
		firstUpdate = false;
	}
	else {
		prevMouse.x = mouse.x;
		prevMouse.y = mouse.y;
		mouse.x = tmpX;
		mouse.y = tmpY;
	}
}
