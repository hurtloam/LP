/*
 * SDL_base.h
 *
 *  Created on: Nov 30, 2013
 *      Author: peter
 *
 *
 *      Use this function to initialize the SDL library.
 *      This must be called before using any other SDL
 *      function.
 */

#ifndef SDL_base_H_
#define SDL_base_H_
#include <SDL2/SDL.h>
#include "LPConfig.hpp"
#include <pthread.h>

class SDL_base {
public:
	SDL_base();

	/**
	 * \brief Initialize using SDL_Init
	 * \details Initialize the SDL subsystems using SDL_Init. Some OpenGL attributes will be set.
	 *
	 * @param flag e.g. video subsystem
	 */
	SDL_base(Uint32 flag = 0, LPConfig* lpConfig = nullptr);

	/**
	 * \brief
	 * @param title
	 * @param x
	 * @param y
	 * @param flags
	 */
	void createWindow(const char* title, int windowPosx, int windowPosy, GLuint x, GLuint y ,Uint32 flags);

	void destroyWindow(SDL_Window* window);

	/**
	 *  \brief Delete our opengl context.
	 *	Close and destroy the window.
	 *	Clean up initialized subsystems.
	 */
	virtual ~SDL_base();
	SDL_Window* getWindow();
	void setWindow(SDL_Window* window);

	void swapWindow();
	void createOpenGLContext();
	void deleteOpenGLContext();
	SDL_GLContext getMainContext() const;
	SDL_GLContext getThreadContext() const;

	void setMainContext(SDL_GLContext mainContext);

	void setMyMutex(pthread_mutex_t mutex);
	pthread_mutex_t* getMyMutex();

	int testValue = 12345;
	/**
	 * \brief Load a bmp file into a SDL_Texture.
	 * @param File
	 * @param sdlTexture
	 */
//	void OnLoad(const char* File, SDL_Texture *& sdlTexture);

	/**
	 * \brief Make the color transparent.
	 *
	 * @param Surf_Dest
	 * @param R
	 * @param G
	 * @param B
	 * @return
	 */
//	bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);

	/**
	 * \brief Draw the updated surface.
	 *
	 * @param Surf_Dest
	 * @param Surf_Src
	 * @param X
	 * @param Y
	 * @return
	 */
//	bool OnDraw(SDL_Texture* texture,int X, int Y, int W, int H);

	pthread_mutex_t mymutex;
private:
	SDL_Window *window;
	SDL_GLContext mainContext;
	SDL_GLContext threadContext;
	SDL_Renderer *sdlrenderer;
	//	SDL_Texture *sdlTexture;
};

#endif /* SDL_base_H_ */
