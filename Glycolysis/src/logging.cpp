/*
 * logging.cpp
 *
 *  Created on: Nov 21, 2018
 *      Author: peter
 */

#include <SDL2/SDL.h>
#include <time.h>
#include "../inc/logging.h"
#include <string>

void _my_log_(void *userdata, int category, SDL_LogPriority priority, const char *message)
{
	FILE *fdLogOutput;
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	std::string dateStr(asctime(timeinfo));
	dateStr[dateStr.size()-1] = ' ';

	switch (priority) {
	  case SDL_LOG_PRIORITY_VERBOSE: {
	    printf("[%s]:VERBOSE: msg = %s\n", dateStr.c_str(), message);
	    break;
	  }
	case SDL_LOG_PRIORITY_DEBUG: {
		printf("[%s]:DEBUG: msg = %s\n", dateStr.c_str(), message);
		break;
	}
	case SDL_LOG_PRIORITY_INFO: {
		printf("[%s]:INFO: msg = %s\n", dateStr.c_str(), message);
		break;
	}
  case SDL_LOG_PRIORITY_WARN: {
    printf("[%s]:WARNING: msg = %s\n", dateStr.c_str(), message);
    break;
  }
	case SDL_LOG_PRIORITY_ERROR: {
		printf("[%s]:ERROR: msg = %s\n", dateStr.c_str(), message);
		break;
	}
	default: {
		printf("[%s]:ERROR: Log Priority Level not found.");
		printf("[%s]:UNKOWN: msg = %s\n", dateStr.c_str(), message);
	}
	};


//	if (*((int*)userdata) == 1) {
//		printf("[%s]:LOGLEVEL %d: msg = %s\n", dateStr.c_str(), priority, message);
//	} else if (*((int*)userdata) == 2) {
//		fprintf(fdLogOutput, "[%s]:LOGLEVEL %d: msg = %s\n", dateStr.c_str(), priority, message);
//	} else if (*((int*)userdata) == 3) {
//		/* Don't print any log*/
//	}
}

void setLogging(int *output, int logPriority)
{
//  SDL_LogSetPriority(SDL_LOG_CATEGORY_CUSTOM, SDL_LOG_PRIORITY_VERBOSE);
//  SDL_LogSetPriority(SDL_LOG_CATEGORY_CUSTOM, (SDL_LogPriority)logPriority);
//	  SDL_LogSetPriority(SDL_LOG_CATEGORY_CUSTOM,SDL_LOG_PRIORITY_INFO);
	  SDL_LogSetOutputFunction(&_my_log_, output);
}


