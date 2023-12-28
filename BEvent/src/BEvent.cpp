/*
 * BEvent.cpp
 *
 *  Created on: Dec 12, 2013
 *      Author: peter
 */

#include <SDL2/SDL.h>
#include "../inc/BEvent.h"

BEvent::BEvent() {
	// TODO Auto-generated constructor stub

}

BEvent::~BEvent() {
	// TODO Auto-generated destructor stub
}

void BEvent::OnEvent(SDL_Event* Event) {
    switch(Event->type) {
        case SDL_KEYDOWN: {
            OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod);
            break;
        }
        case SDL_KEYUP: {
            OnKeyUp(Event->key.keysym.sym, Event->key.keysym.mod);
            break;
        }
        case SDL_MOUSEMOTION: {
            OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;
        }
        case SDL_MOUSEWHEEL:
        	OnMouseWheel(Event->wheel.y);
        	break;
        case SDL_MOUSEBUTTONDOWN: {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonDown(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONUP: {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonUp(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }
        case SDL_TEXTINPUT: {
          OnTextInput(Event->text.text);
          break;
        }
        case SDL_JOYAXISMOTION: {
            OnJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
            break;
        }
        case SDL_JOYBALLMOTION: {
            OnJoyBall(Event->jball.which,Event->jball.ball,Event->jball.xrel,Event->jball.yrel);
            break;
        }
        case SDL_JOYHATMOTION: {
            OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
            break;
        }
        case SDL_JOYBUTTONDOWN: {
            OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
            break;
        }
        case SDL_JOYBUTTONUP: {
            OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
            break;
        }
        case SDL_QUIT: {
            OnExit();
            break;
        }
        case SDL_SYSWMEVENT: {
            //Ignore
            break;
        }

//        case SDL_VIDEORESIZE: {
//            OnResize(Event->resize.w,Event->resize.h);
//            break;
//        }
//
//        case SDL_VIDEOEXPOSE: {
//            OnExpose();
//            break;
//        }

        default: {
            OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
            break;
        }
    }
}

void BEvent::OnEvent() {

}
void BEvent::OnInputFocus() {
    //Pure virtual, do nothing
}

void BEvent::OnInputBlur() {
    //Pure virtual, do nothing
}

void BEvent::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
    //Pure virtual, do nothing
}

void BEvent::OnKeyUp(SDL_Keycode sym, Uint16 mod) {
    //Pure virtual, do nothing
}

void BEvent::OnMouseFocus() {
    //Pure virtual, do nothing
}

void BEvent::OnMouseBlur() {
    //Pure virtual, do nothing
}

void BEvent::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {
    //Pure virtual, do nothing
}

void BEvent::OnMouseWheel(Sint32 y) {
    //Pure virtual, do nothing
}

void BEvent::OnLButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void BEvent::OnLButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void BEvent::OnRButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void BEvent::OnRButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void BEvent::OnMButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void BEvent::OnTextInput(char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]) {

}

void BEvent::OnMButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void BEvent::OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value) {
    //Pure virtual, do nothing
}

void BEvent::OnJoyButtonDown(Uint8 which,Uint8 button) {
    //Pure virtual, do nothing
}

void BEvent::OnJoyButtonUp(Uint8 which,Uint8 button) {
    //Pure virtual, do nothing
}

void BEvent::OnJoyHat(Uint8 which,Uint8 hat,Uint8 value) {
    //Pure virtual, do nothing
}

void BEvent::OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) {
    //Pure virtual, do nothing
}

void BEvent::OnMinimize() {
    //Pure virtual, do nothing
}

void BEvent::OnRestore() {
    //Pure virtual, do nothing
}

void BEvent::OnResize(int w,int h) {
    //Pure virtual, do nothing
}

void BEvent::OnExpose() {
    //Pure virtual, do nothing
}

void BEvent::OnExit() {
    //Pure virtual, do nothing
}

void BEvent::OnUser(Uint8 type, int code, void* data1, void* data2) {
    //Pure virtual, do nothing
}
