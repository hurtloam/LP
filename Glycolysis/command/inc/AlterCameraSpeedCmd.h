/*
 * AlterCameraSpeed.h
 *
 *  Created on: 9 dec. 2017
 *      Author: peter
 */

#ifndef INC_ALTERCAMERASPEEDCMD_H_
#define INC_ALTERCAMERASPEEDCMD_H_

#include "../../inc/ViewIf.h"
#include "Command.h"

class AlterCameraSpeedCmd : public Command {
public:
	AlterCameraSpeedCmd(ViewIf& view);
	virtual ~AlterCameraSpeedCmd();
	virtual void execute();
private:
	ViewIf& view;
};



#endif /* INC_ALTERCAMERASPEEDCMD_H_ */
