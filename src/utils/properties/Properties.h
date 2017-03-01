#ifndef _PROPERTYUTIL_H
#define _PROPERTYUTIL_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "../Common.h"

class Properties
{


public:

    typedef std::map<std::string, std::string> PropertyMapT;
    typedef PropertyMapT::value_type           value_type;
    typedef PropertyMapT::iterator             iterator;

    static Properties* Instance();
    std::string find(const char *key);
    virtual ~Properties(){
        LOG(TRACE) << "Properties delete";
    }
    void print();

private:
    Properties():is("../conf/app.properties"){
        read();
        is.close();
    };
    static Properties* m_pInstance;
    PropertyMapT map;
    std::ifstream is;
    void read();
    //void write( const char *header = NULL);


    static inline char m_hex(int nibble)
    {
        static const char *digits = "0123456789ABCDEF";
        return digits[nibble & 0xf];
    }
};

#endif  // _PROPERTYUTIL_H
