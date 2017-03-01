//
// Created by fred on 06/08/16.
//

#ifndef OPENCV_TUTO_EXCEPTION_H
#define OPENCV_TUTO_EXCEPTION_H

#include <stdexcept>
#include <string>


class BasicException : public std::runtime_error {
public:
    BasicException(const std::string& message)
            : std::runtime_error(message) { };
};


#endif //OPENCV_TUTO_EXCEPTION_H
