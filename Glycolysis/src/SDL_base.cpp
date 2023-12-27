/*
 * SDL_base.cpp
 *
 *  Created on: Nov 30, 2013
 *      Author: peter
 */

#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include "../inc/SDL_base.h"
#include "../inc/InitError.h"
#include <iostream>

SDL_base::SDL_base(Uint32 flags, LPConfig* lpConfig){
	// Initialize the SDL subsystems using SDL_Init
    if (SDL_Init(flags) != 0)
        throw platformBase::InitError();

    /* Request opengl 3.1 context.
     * SDL doesn't have the ability to choose which profile at this time of writing,
     * but it should default to the core profile */

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, lpConfig->LP_OPEN_GL_CONTEXT_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, lpConfig->LP_OPEN_GL_CONTEXT_MINOR_VERSION);

//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
//    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
//
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, lpConfig->LP_OPEN_GL_DOUBLEBUFFER);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, lpConfig->LP_OPEN_GL_DEPTH_SIZE);

//    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);


//    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
//    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
//    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
//    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
//
//    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
//
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, lpConfig->LP_OPEN_GL_MULTISAMPLEBUFFERS);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, lpConfig->LP_OPEN_GL_MULTISAMPLESAMPLES);

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, lpConfig->LP_OPEN_GL_ACCELERATED_VISUAL);

    // to 1 and SDL_GL_MULTISAMPLESAMPLES to a value greater than 0,
//    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
//    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

//    glHint(GL_POLYGON_SMOOTH, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);

    glEnable(GL_MULTISAMPLE);

    testValue = 54321;
}

SDL_base::~SDL_base() {

	/* Delete our opengl context */
	SDL_GL_DeleteContext(mainContext);

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up initialized subsystems
    SDL_Quit();
}

/**
 * SDL_base::createWindow
 * Create a window for OpenGL usage. Throws an exception InitError if something
 * goes wrong.
 */
void SDL_base::createWindow(const char* title, int windowPosx, int windowPosy, GLuint x, GLuint y ,Uint32 flags) {
  std::cout << "Before SDL_CreateWindow" << std::endl;
	window = SDL_CreateWindow(
        title,			// window title
        windowPosx, // initial x position
        windowPosy, // initial y position
        x,          // width, in pixels
        y,          // height, in pixels
        flags       // flags - see below
    );

  std::cout << "after SDL_CreateWindow" << std::endl;
    // Check that the window was successfully made
    if (window == NULL) {
        // In the event that the window could not be made...
    	throw platformBase::InitError();
    }
}

/**
 * SDL_base::destroyWindow
 * Use this function to destroy a window.
 *
 */
void SDL_base::destroyWindow(SDL_Window* window) {
  SDL_DestroyWindow(window);
}

SDL_Window* SDL_base::getWindow() {
	return window;
}

void SDL_base::setWindow(SDL_Window* window) {
	this->window = window;
}

/**
 *  Swap our back buffer to the front
 *
 */
void SDL_base::swapWindow() {
	SDL_GL_SwapWindow(window);
}

/**
 *  Create our opengl context and attach it to our window
 */
void SDL_base::createOpenGLContext() {
	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
	this->threadContext = SDL_GL_CreateContext(window);
	this->mainContext = SDL_GL_CreateContext(window);
	if (this->mainContext == NULL)
	{
	  printf("LP - SDL_base: Error in createOpenGLContext method:\n");
	  throw platformBase::InitError();
	}
}

/**
 *  Delete our opengl context.
 *
 */
void SDL_base::deleteOpenGLContext() {
  SDL_GL_DeleteContext(this->mainContext);
}


SDL_GLContext SDL_base::getMainContext() const {
	return mainContext;
}

SDL_GLContext SDL_base::getThreadContext() const {
	return threadContext;
}

void SDL_base::setMainContext(SDL_GLContext mainContext) {
	this->mainContext = mainContext;
}
