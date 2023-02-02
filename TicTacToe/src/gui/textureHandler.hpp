#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class Texture {
	public:
		
		Texture() {textureHolder = NULL; width = 0; height = 0;} //Constructor

		Texture(string path, SDL_Renderer* renderer) {loadFromFile(path, renderer);} //Constructor that can be used to load directly
		
		~Texture() { free(); } //Destructor

		//Loads image at specified path
		bool loadFromFile(string path, SDL_Renderer* renderer);
		
		//Destructor Code, but I made it a separate function so it can be reused for other functions
		void free() {if(textureHolder != NULL) { SDL_DestroyTexture(textureHolder); textureHolder = NULL; width = 0; height = 0;} }
		
		//Renders texture at given point
		void render(SDL_Renderer* renderer, int x, int y);

		//Renders texture from a specific centre point
		void renderCentred(SDL_Renderer* renderer, int x, int y);

		//Gets image dimensions
		int getWidth() {return width;} 
		int getHeight() {return height;}

		SDL_Texture *getTexture() {return textureHolder;}

	private:
		//The actual hardware texture
		SDL_Texture* textureHolder;

		//Image dimensions
		int width;
		int height;
};

bool Texture::loadFromFile(string path, SDL_Renderer* renderer) {

	free(); //clears pre-existing texture
	
	textureHolder = IMG_LoadTexture(renderer, path.c_str());

	if (textureHolder == NULL) {
		cout << "Texture could not be loaded. Error: " << SDL_GetError() << endl;
	} else SDL_QueryTexture(textureHolder, NULL, NULL, &width, &height);

	//Return success
	return textureHolder != NULL;

}

void Texture::render(SDL_Renderer* renderer, int x, int y) {
	
	SDL_Rect renderQuad = {x, y, width, height}; 
	//Set rendering space and render to screen

	//Render to screen
	SDL_RenderCopy(renderer, textureHolder, NULL, &renderQuad);
}

void Texture::renderCentred(SDL_Renderer* renderer, int x, int y) {
	
	SDL_Rect renderQuad = {(x - (width/2)), (y - (height/2)), width, height}; 
	//Set rendering space and render to screen

	//Render to screen
	SDL_RenderCopy(renderer, textureHolder, NULL, &renderQuad);
}