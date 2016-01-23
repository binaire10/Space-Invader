#include "readconfig.h"
#include <string>
#include <map>
#include <fstream>
#include "MyConst.h"

using namespace std;
namespace SpaceInvader
{
    const map<string, string> &LoadFile(const string &File, bool reload)
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
            // Position dans la ligne
            unsigned offset(0);
            // Clée dans la map
            string  Key;
            // Valeur de la clé
            string  Value;
            // si la ligne est vide on lance une exception (l'exception est attraper par l'extracteur)
            if(Line.size() == 0)
                throw("can't read File : "+File);
            // on saute jusqu'au premier mots
            while (offset<Line.size() && Line[offset]==' ') ++offset;
            // on extrait le mots
            while (offset<Line.size() && Line[offset]!=' ') Key.push_back(Line[offset++]);
            // on saute jusqu'au :
            while (offset<Line.size() && Line[offset]==' ') ++offset;
            // si il n'est pas trouver on quite
            if(offset>=Line.size() || Line[offset++] != ':')
                continue;
            // on saute jusqu'au contenue des variable
            while (offset<Line.size() && Line[offset]==' ') ++offset;
            // on  extrait le 2éme mots
            while (offset<Line.size()) Value.push_back(Line[offset++]);
            // avectation de la valeur;
            TabValue[File][Key] = Value;
        }
        // on retourne la table courante
        return TabValue[File];
    }

    char GetValueChar(const string &Value, const string &File, const char &defaultValue)
    {
        try
        {
            const std::map<std::string, std::string> &ArrayVal = LoadFile(File);
            std::map<std::string, std::string>::const_iterator val = ArrayVal.find(Value);
            if(val == ArrayVal.end() || val->second.size()==0)
                return defaultValue;
            return val->second[0];
        }
        catch(...)
        {
            return defaultValue;
        }
    }

    string GetValueStr(const string &Value, const string &File, const string &defaultValue)
    {
        try
        {
            const std::map<std::string, std::string> &ArrayVal = LoadFile(File);
            std::map<std::string, std::string>::const_iterator val = ArrayVal.find(Value);
            if(val == ArrayVal.end() || val->second.size()==0)
                return defaultValue;
            return val->second;
        }
        catch(...)
        {
            return defaultValue;
        }

    }

    bool isUnsignedValue(const string &ValTest)
    {
        for(const char &Value : ValTest)
            if(!isdigit(Value))
                return false;
        return true;
    }

    unsigned AliasToValueInt(const string &Value)
    {
        if("KJaune" == Value)
            return KJaune;
        if("KNoir" == Value)
            return KNoir;
        if("KRouge" == Value)
            return KRouge;
        if("KVert" == Value)
            return KVert;
        if("KBleu" == Value)
            return KBleu;
        if("KMAgenta" == Value)
            return KMAgenta;
        if("KCyan" == Value)
            return KCyan;
        throw(runtime_error("Cannot Find Alias"));
    }

    unsigned GetValueInt(const string &Value, const string &File, const unsigned &defaultValue)
    {
        try
        {
            const std::map<std::string, std::string> &ArrayVal = LoadFile(File);
            std::map<std::string, std::string>::const_iterator val = ArrayVal.find(Value);
            if(val == ArrayVal.end() || val->second.size()==0)
                return defaultValue;
            else if(isUnsignedValue(val->second))
                return atoi(val->second.data());
            return AliasToValueInt(val->second);
        }
        catch(...)
        {
            return defaultValue;
        }
    }

    unsigned getType(const string &Value)
    {
        try
        {
            if(Value.size()==0 || !isUnsignedValue(Value))
                return 0;
            else if(Value.size()==1)
                return 1;
            else if(isUnsignedValue(Value))
                return 2;
            return 0;
        }
        catch(...)
        {
            return 0;
        }
    }
}
