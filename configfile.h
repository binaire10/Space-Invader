#ifndef CONFIGFILE_H
#define CONFIGFILE_H
#include <string>
#include <map>
#include "globaltype.h"
/**
 * @file configfile.h
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
    binaire::uint_t getValueInt(const std::string &Value, const std::string &File, const binaire::uint_t &defaultValue);

    /**
     * @brief getValueChar
     * @param Value
     * @param File
     * @param defaultValue
     * @return
     */
    char getValueChar(const std::string &Value, const std::string &File, const char &defaultValue);
}
#endif // CONFIGFILE_H
