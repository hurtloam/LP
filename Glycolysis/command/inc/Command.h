/*
 * Command.h
 *
 *  Created on: 9 dec. 2017
 *      Author: peter
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

class Command {
public:
	Command();
	virtual ~Command();
	virtual void execute() = 0;
};

#endif /* INC_COMMAND_H_ */
