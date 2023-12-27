/*
 * LPConfig.hpp
 *
 *  Created on: Sep 24, 2018
 *      Author: peter
 */

#ifndef INC_LPCONFIG_HPP_
#define INC_LPCONFIG_HPP_

#include <string>


class LPConfig
{
  public:
    LPConfig ();
    virtual
    ~LPConfig ();

    std::string title;
    int screenWidth;
    int screenHeight;
    bool multiThreadOn;
    int logPriority;

    int LP_OPEN_GL_CONTEXT_MAJOR_VERSION;
    int LP_OPEN_GL_CONTEXT_MINOR_VERSION;

    int LP_OPEN_GL_DOUBLEBUFFER;
    int LP_OPEN_GL_DEPTH_SIZE;

    int LP_OPEN_GL_MULTISAMPLEBUFFERS;
    int LP_OPEN_GL_MULTISAMPLESAMPLES;

    int LP_OPEN_GL_ACCELERATED_VISUAL;
};

#endif /* INC_LPCONFIG_HPP_ */
