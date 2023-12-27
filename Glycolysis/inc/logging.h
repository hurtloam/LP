/*
 * logging.h
 *
 *  Created on: Nov 21, 2018
 *      Author: peter
 */

#ifndef INC_LOGGING_H_
#define INC_LOGGING_H_

#include <SDL2/SDL.h>
#include <time.h>
//#include "../inc/SDL_base.h"
#define STRINGIFY(x) #x
#define LINE_TO_STR(x) STRINGIFY (x)
#define TRACE_DEBUG(fmt, ...)  SDL_LogDebug(SDL_LOG_CATEGORY_CUSTOM, __FILE__ ":" LINE_TO_STR(__LINE__) ", " fmt, ##__VA_ARGS__)
#define TRACE_ERROR(fmt, ...)  SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, __FILE__ ":" LINE_TO_STR(__LINE__) ", " fmt, ##__VA_ARGS__)
#define TRACE_INFO(fmt, ...)  SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, __FILE__ ":" LINE_TO_STR(__LINE__) ", " fmt, ##__VA_ARGS__)
#define TRACE_WARN(fmt, ...)  SDL_LogWarn(SDL_LOG_CATEGORY_CUSTOM, __FILE__ ":" LINE_TO_STR(__LINE__) ", " fmt, ##__VA_ARGS__)

void _my_log_(void *userdata, int category, SDL_LogPriority priority, const char *message);
void setLogging(int *output, int logPriority);

#endif /* INC_LOGGING_H_ */
