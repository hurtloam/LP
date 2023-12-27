/*
 * AlterCameraSpeed.h
 *
 *  Created on: 9 dec. 2017
 *      Author: peter
 */

#ifndef INC_ALTERGRIDCMD_H_
#define INC_ALTERGRIDCMD_H_

#include "../../stage/inc/StageIf.h"
#include "Command.h"

class AlterGridCmd : public Command {
public:
	AlterGridCmd(StageIf& stage);
	virtual ~AlterGridCmd();
	virtual void execute();
private:
	StageIf& stage;
};



#endif /* INC_ALTERGRIDCMD_H_ */
