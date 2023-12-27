/*
 * LuaIfLPConfig.h
 *
 *  Created on: Jan 9, 2018
 *      Author: peter
 *
 *      Interface towards Lua
 */

#ifndef LUAIF_LP_CONFIG_H_
#define LUAIF_LP_CONFIG_H_

#include <string>
#include "LPConfig.hpp"

class LuaIfLPConfig {
public:
    LuaIfLPConfig(LPConfig* lpConfig);
    virtual ~LuaIfLPConfig();
    void setConfigFile(std::string configFile);
    void configLP();

    std::string fileName;
    LPConfig* lpConfig;
};

#endif // LUAIF_LP_CONFIG_H_
