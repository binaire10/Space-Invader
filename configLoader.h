#pragma once
#include <string>
#include <map>
#include "mytype.h"
/**
 * @file configLoader.h
 * \brief Here some alias and struct to work with flux
 * @author (binaire) Alexandre Wery
 */

namespace binaire
{
    /**
     * @brief loadFile
     * @param File
     * @param reload
     * @return
     */
    const std::map<std::string, std::string> &loadFile(const std::string &File, bool reload = false);

    /**
     * @brief getValueStr
     * @param Value
     * @param File
     * @param defaultValue
     * @return
     */
    std::string getValueStr(const std::string &Value, const std::string &File, const std::string &defaultValue);

    /**
     * @brief getValueInt
     * @param Value
     * @param File
     * @param defaultValue
     * @return
     */
    uint_t getValueInt(const std::string &Value, const std::string &File, const uint_t &defaultValue);

    /**
     * @brief getValueChar
     * @param Value
     * @param File
     * @param defaultValue
     * @return
     */
    char getValueChar(const std::string &Value, const std::string &File, const char &defaultValue);
}
