#include "Window.h"

Window::Window() /*: window(nullptr), context(nullptr)*/	{ // this line happens before anything else in the constructor
	window = nullptr;
	context = nullptr; // Other way to do it

}

Window::~Window()	{
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)	{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Debug::FatalError("Failed to init SDL", "Window.cpp", __LINE__);
		return false;
	}
	this->width = width_;
	this->height = height_;

	SetPreAttributes();

	window = SDL_CreateWindow(name_.c_str(), //c._str()  turns the string "name_" from a string to a const char*
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL); //one line of thing(stuff,stuff,....)

	if (window == nullptr) {
		Debug::FatalError("Failed to create Window", "Window.cpp", __LINE__);
		
		return false;
	}

	context = SDL_GL_CreateContext(window);
	SetPostAttributes();

	//GLEW is the library we use for OpenGL calls/API
	GLenum error = glewInit();
	if (error != GLEW_OK) { // if GLenum is NOT = OK, then its an error
		Debug::FatalError("Failed to init GLEW", "Window.cpp", __LINE__);
		return false;
	}
	glEnable(GL_DEPTH_TEST);

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl; //You said this is not for DEBUG yet
	return true;

}

//Cleaning up and destroying the window
void Window::OnDestroy()	{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window); //cant call delete to delete the pointer as its a special SDL pointer
	window = nullptr;

}

int Window::GetWidth() const	{
	return width;
}

int Window::GetHeight() const	{
	return height;
}

SDL_Window* Window::GetWindow() const	{
	return window;
}

void Window::SetPreAttributes()	{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //gets rid of deprecated fuctions
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); //sets version to 4.5
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5); // ^
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE; //set before initilazing GLEW

}

void Window::SetPostAttributes()	{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}
