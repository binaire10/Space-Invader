#include "configLoader.h"
#include <map>
#include <iostream>
#include <fstream>
#include "mytype.h"

using namespace std;


namespace binaire
{
    const map<string, string> &loadFile(const string &File, bool reload)
    {
        static map<string, map<string, string> > TabValue;
        if(!reload)
        {
            map<string, map<string, string> >::iterator value;
            if((value = TabValue.find(File)) !=TabValue.end())
                return value->second;
        }

        ifstream file(File);
        string Line;
        while (getline(file,Line))
        {
            uint_t offset(0);
            string  Key;
            string  Value;
            if(Line.size() == 0)
                throw("can't read File : "+File);
            while (offset<Line.size() && Line[offset]==' ') ++offset;
            while (offset<Line.size() && Line[offset]!=' ') Key.push_back(Line[offset++]);
            while (offset<Line.size() && Line[offset]==' ') ++offset;
            if(offset>=Line.size() || Line[offset++] != ':')
                continue;
            while (offset<Line.size() && Line[offset]==' ') ++offset;
            while (offset<Line.size()) Value.push_back(Line[offset++]);
            TabValue[File][Key] = Value;
        }
        return TabValue[File];
    }

    char getValueChar(const string &Value, const string &File, const char &defaultValue)
    {
        try
        {
            const std::map<std::string, std::string> &ArrayVal = loadFile(File);
            std::map<std::string, std::string>::const_iterator val = ArrayVal.find(Value);
            if(val == ArrayVal.end())
                return defaultValue;
            return val->second[0];
        }
        catch(...)
        {
            return defaultValue;
        }
    }

    string getValueStr(const string &Value, const string &File, const string &defaultValue)
    {
        try
        {
            const std::map<std::string, std::string> &ArrayVal = loadFile(File);
            std::map<std::string, std::string>::const_iterator val = ArrayVal.find(Value);
            if(val == ArrayVal.end())
                return defaultValue;
            return val->second;
        }
        catch(...)
        {
            return defaultValue;
        }

    }

    uint_t getValueInt(const string &Value, const string &File, const uint_t &defaultValue)
    {
        try
        {
            const std::map<std::string, std::string> &ArrayVal = loadFile(File);
            std::map<std::string, std::string>::const_iterator val = ArrayVal.find(Value);
            if(val == ArrayVal.end())
                return defaultValue;
            return abs(atoi(val->second.data()));
        }
        catch(...)
        {
            return defaultValue;
        }
    }
}
