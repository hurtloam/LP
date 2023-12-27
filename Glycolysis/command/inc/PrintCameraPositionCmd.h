/*
 * PrintCameraPositionCmd.h
 *
 *  Created on: 9 dec. 2017
 *      Author: peter
 */

#ifndef INC_PRINTCAMERAPOSITIONCMD_H_
#define INC_PRINTCAMERAPOSITIONCMD_H_

#include "../../inc/ViewIf.h"
#include "Command.h"

class PrintCameraPositionCmd : public Command {
public:
	PrintCameraPositionCmd(ViewIf& view);
	virtual ~PrintCameraPositionCmd();
	virtual void execute();
private:
	ViewIf& view;
};



#endif /* INC_PRINTCAMERAPOSITIONCMD_H_ */
