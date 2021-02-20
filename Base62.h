// Name:
// Base62 From Base64
//
// Note: 
// Same function as Base64 but:
// 0~60 : One Character from "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678"
// 61   : Two Character '9A'
// 62   : Two Character '9B'
// 63   : Two Character '9C'
// 
// Data:
// 2018.10.14

#pragma once

#include <string>
#include <map>

class Base62
{
public:
    Base62();
    virtual ~Base62();
    std::string Base62Encode(std::string strSrc);
    std::string Base62Decode(std::string strSrc);

private:
    std::string strCodes =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678";
    char chCodeFlag = '9';
};

