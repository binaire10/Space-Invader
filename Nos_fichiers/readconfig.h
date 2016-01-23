#pragma once
#include <string>
#include <map>
namespace SpaceInvader
{
char GetValueChar(const std::string &Value, const std::string &File, const char &defaultValue);

std::string GetValueStr(const std::string &Value, const std::string &File, const std::string &defaultValue);

unsigned GetValueInt(const std::string &Value, const std::string &File, const unsigned &defaultValue);

const std::map<std::string, std::string> &LoadFile(const std::string &File, bool reload = false);
}
