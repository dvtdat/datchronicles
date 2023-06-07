#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <iostream>

class Utils
{
public:
    static unsigned int split(const std::string &txt, std::vector<std::string> &str, char ch)
    {
        int pos = txt.find(ch);
        int initialPos = 0;
        str.clear();
        while (pos != std::string::npos)
        {
            str.push_back(txt.substr(initialPos, pos - initialPos + 1));
            initialPos = pos + 1;
            pos = txt.find(ch, initialPos);
        }
        str.push_back(txt.substr(initialPos, std::min<int>(pos, txt.size() - (initialPos + 1))));

        return str.size();
    }
};

#endif // UTILS_H