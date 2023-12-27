/*
 * InitError.h
 *
 *  Created on: Nov 30, 2013
 *      Author: peter
 */

#ifndef INITERROR_H_
#define INITERROR_H_

#include <exception>
#include <string>

namespace platformBase {

class InitError: public std::exception {

public:
       InitError();
       InitError(const std::string&);
       virtual ~InitError() throw();
       virtual const char* what() const throw();
   private:
       std::string msg;
};

} /* namespace platformBase */

#endif /* INITERROR_H_ */
