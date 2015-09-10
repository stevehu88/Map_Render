/*
 * base64.h
 *
 *  Created on: Aug 27, 2015
 *      Author: Steve Hu
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);



#endif /* BASE64_H_ */
