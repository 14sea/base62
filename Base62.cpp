
#include "Base62.h"

Base62::Base62()
{
}


Base62::~Base62()
{
}

std::string Base62::Base62Encode(std::string strSrc)
{
    std::string strDir;
    int nLen = strSrc.length();
    int i = 0;
    int j = 0;
    unsigned char aryChar3[3];
    unsigned char aryChar4[4];

    while (nLen--) 
    {
        aryChar3[i++] = strSrc[j];
        if (i == 3) 
        {
            aryChar4[0] = (aryChar3[0] & 0xfc) >> 2;
            aryChar4[1] = ((aryChar3[0] & 0x03) << 4) + ((aryChar3[1] & 0xf0) >> 4);
            aryChar4[2] = ((aryChar3[1] & 0x0f) << 2) + ((aryChar3[2] & 0xc0) >> 6);
            aryChar4[3] = aryChar3[2] & 0x3f;

            i = 0;
            while (i < 4)
            {
                if (aryChar4[i] < 61)
                {
                    strDir += strCodes[aryChar4[i]];
                }
                else
                {
                    strDir += chCodeFlag;
                    strDir += strCodes[aryChar4[i] - 61];
                }
                i++;
            }
            i = 0;
        }
        j++;
    }

    if (i != 0)
    {
        j = i;
        while (j < 3)
        {
            aryChar3[j] = '\0';
            j++;
        }

        aryChar4[0] = (aryChar3[0] & 0xfc) >> 2;
        aryChar4[1] = ((aryChar3[0] & 0x03) << 4) + ((aryChar3[1] & 0xf0) >> 4);
        aryChar4[2] = ((aryChar3[1] & 0x0f) << 2) + ((aryChar3[2] & 0xc0) >> 6);

        j = 0;
        while (j < i + 1)
        {
            strDir += strCodes[aryChar4[j]];
            j++;
        }

        while (i++ < 3)
        {
            strDir += chCodeFlag;
            strDir += strCodes[3];
        }
    }

    return strDir;
}

std::string Base62::Base62Decode(std::string strSrc)
{
    int i = 0;
    int j = 0;
    int nSrc = 0;
    int nLen = strSrc.size();
    unsigned char aryChar4[4];
    unsigned char aryChar3[3];
    std::string strDir;

    while (nLen-- 
        && !(strSrc[nSrc] == chCodeFlag 
        && strSrc[nSrc + 1] == 'D')) 
    {
        if (strSrc[nSrc] != chCodeFlag)
        {
            aryChar4[i++] = strSrc[nSrc];
        }

        else
        {
            nLen--;
            nSrc++;
            aryChar4[i++] = strSrc[nSrc]+128;
        }

        nSrc++;

        if (i == 4) 
        {
            i = 0;
            while (i < 4)
            {
                if (aryChar4[i] >= 128)
                {
                    aryChar4[i] = strCodes.find(aryChar4[i] - 128);
                    aryChar4[i] += 61;
                }
                else
                {
                    aryChar4[i] = strCodes.find(aryChar4[i]);
                }
                i++;
            }

            aryChar3[0] = (aryChar4[0] << 2) + ((aryChar4[1] & 0x30) >> 4);
            aryChar3[1] = ((aryChar4[1] & 0xf) << 4) + ((aryChar4[2] & 0x3c) >> 2);
            aryChar3[2] = ((aryChar4[2] & 0x3) << 6) + aryChar4[3];

            i = 0;
            while (i < 3)
            {
                strDir += aryChar3[i];
                i++;
            }

            i = 0;
        }
    }

    if (i != 0) 
    {
        j = 0;
        while (j < i)
        {
            if (aryChar4[j] >= 128)
            {
                aryChar4[j] = strCodes.find(aryChar4[j] - 128);
                aryChar4[j] += 61;
            }
            else
            {
                aryChar4[j] = strCodes.find(aryChar4[j]);
            }
            j++;
        }

        aryChar3[0] = (aryChar4[0] << 2) + ((aryChar4[1] & 0x30) >> 4);
        aryChar3[1] = ((aryChar4[1] & 0xf) << 4) + ((aryChar4[2] & 0x3c) >> 2);

        j = 0;
        while (j < i - 1)
        {
            strDir += aryChar3[j];
            j++;
        }
    }

    return strDir;
}