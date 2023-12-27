-- Configuration file for the LearningPlatform application
-- Created 24/9 -18
--

-- Title -----------------------------------------------
-- ----------------------------------------------------------
title = "BioMolCraft"

-- Resolution -----------------------------------------------
-- ----------------------------------------------------------
Screens = {
    width1024 = 1024,
    height768 = 768,
    width1680 = 1680,
    height1050 = 1050,
    width1920 = 1920,
    height1080 = 1080,
}

screenWidth = Screens["width1920"]
screenHeight = Screens["height1080"]

-- Multi threading  -----------------------------------------
-- ----------------------------------------------------------
--    If multiThreadOn = true, then splash screen will be 
--    activated.
multiThreadOn = true


-- Log Priority ---------------------------------------------
-- ----------------------------------------------------------
LogPriority = {
    SDL_LOG_PRIORITY_VERBOSE = 1,
    SDL_LOG_PRIORITY_DEBUG = 2,
    SDL_LOG_PRIORITY_INFO = 3,
    SDL_LOG_PRIORITY_WARN = 4,
    SDL_LOG_PRIORITY_ERROR = 5,
    SDL_LOG_PRIORITY_CRITICAL = 6,
}

logPriority = LogPriority["SDL_LOG_PRIORITY_ERROR"]

-- SDL GL Attributes ----------------------------------------
-- ----------------------------------------------------------
LP_OPEN_GL_CONTEXT_MAJOR_VERSION = 4
LP_OPEN_GL_CONTEXT_MINOR_VERSION = 2

--    LP_OPEN_GL_CONTEXT_MAJOR_VERSION = 3
--    LP_OPEN_GL_CONTEXT_MINOR_VERSION = 1

--    LP_OPEN_GL_STENCIL_SIZE = 8
--

-- Turn on double buffering with a 24bit Z buffer.
-- You may need to change this to 16 or 32 for your system
LP_OPEN_GL_DOUBLEBUFFER = 1
LP_OPEN_GL_DEPTH_SIZE = 24

--    LP_OPEN_GL_BUFFER_SIZE = 32


--    LP_OPEN_GL_RED_SIZE = 8
--    LP_OPEN_GL_GREEN_SIZE = 8
--    LP_OPEN_GL_BLUE_SIZE = 8
--    LP_OPEN_GL_ALPHA_SIZE = 8
--
--    LP_OPEN_GL_DEPTH_SIZE = 32
--
-- MULTISAMPLEBUFFERS to 1 and SDL_GL_MULTISAMPLESAMPLES 
-- to a value greater than 0,
LP_OPEN_GL_MULTISAMPLEBUFFERS = 1
LP_OPEN_GL_MULTISAMPLESAMPLES = 4

LP_OPEN_GL_ACCELERATED_VISUAL = 1
