#include "TextureHandler.h"

std::unique_ptr<TextureHandler> TextureHandler::textureInstance = nullptr;

std::vector<Texture*> TextureHandler::textures = std::vector<Texture*>();

TextureHandler::TextureHandler()	{
	textures.reserve(10);
}

TextureHandler::~TextureHandler(){
	OnDestroy();
}

TextureHandler* TextureHandler::GetInstance()	{
	if(textureInstance.get() ==nullptr) {
		textureInstance.reset(new TextureHandler);
	}
	return textureInstance.get();
}

void TextureHandler::OnDestroy()	{
	//D I changed .size > 0 to .empty
	if(!textures.empty()) {
		for (auto t : textures) {
			glDeleteTextures(1, &t->textureID);
			delete t;
			t = nullptr;
		}
		textures.clear();
	}
}

void TextureHandler::CreateTexture(const std::string& textureName_, const std::string& textureFilePath_)	{
	
	if (GetTextureData(textureName_)) return; //If Texture already exists, no need to create a new one
	
	Texture* t = new Texture();
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(textureFilePath_.c_str());
	if(surface==nullptr) {
		Debug::Error("Surface for texture " + textureName_ + " failed to be created in ", "TextureHandler.cpp", __LINE__);
		delete t;
		t = nullptr;
		return;
	}

	glGenTextures(1, &t->textureID);
	glBindTexture(GL_TEXTURE_2D, t->textureID);
	int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB; //D int mode = bool condition ? if true : if false;
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //X axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Y axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	t->width = static_cast<float>(surface->w);
	t->height = static_cast<float>(surface->h);
	t->textureName = textureName_;

	textures.push_back(t);

	SDL_FreeSurface(surface);
	surface = nullptr;	
}

const GLuint TextureHandler::GetTexture(const std::string& textureName_)	{
	for(auto t : textures) {
		if(t->textureName == textureName_) {
			return t->textureID;
		}
	}
	return 0;
}

const Texture* TextureHandler::GetTextureData(const std::string textureName_)	{
	for (auto t : textures) {
		if (t->textureName == textureName_) {
			return t;
		}
	}
	return nullptr;
}
