#include "readconfig.h"
#include <string>
#include <map>
#include <fstream>

using namespace std;
/*!
 * \brief Alias mettant en noir la couleur du texte du terminal.
 */
const unsigned KNoir    = 0;
/*!
 * \brief Alias mettant en rouge la couleur du texte du terminal.
 */
const unsigned KRouge   = 1;

/*!
 * \brief Alias mettant en vert la couleur du texte du terminal.

 */
const unsigned KVert    = 2;
/*!
 * \brief Alias mettant en jaune la couleur du texte du terminal.
 */
const unsigned KJaune   = 3;

/*!
 * \brief Alias mettant en bleu la couleur du texte du terminal.
 */
const unsigned KBleu    = 4;

/*!
 * \brief Alias mettant en mangenta la couleur du texte du terminal.
 */
const unsigned KMAgenta = 5;

/*!
 * \brief Alias mettant en cyan la couleur du texte du terminal.
 */
const unsigned KCyan    = 6;

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
            // Clé dans la map
            string  Key;
            // Valeur de la clé
            string  Value;
            // si la ligne est vide on lance une exception (l'exception est attrapée par l'extracteur)
            if(Line.size() == 0)
                throw("can't read File : "+File);
            // on saute jusqu'au premier mot
            while (offset<Line.size() && Line[offset]==' ') ++offset;
            // on extrait le mot
            while (offset<Line.size() && Line[offset]!=' ') Key.push_back(Line[offset++]);
            // on saute jusqu'au :
            while (offset<Line.size() && Line[offset]==' ') ++offset;
            // si il n'est pas trouvé on quitte
            if(offset>=Line.size() || Line[offset++] != ':')
                continue;
            // on saute jusqu'au contenu des variables
            while (offset<Line.size() && Line[offset]==' ') ++offset;
            // on  extrait le 2ème mot
            while (offset<Line.size()) Value.push_back(Line[offset++]);
            // afectation de la valeur;
            TabValue[File][Key] = Value;
        }
        // on retourne la table courante
        return TabValue[File];
    }

    char GetValueChar(const string &Value, const string &File, const char &defaultValue)
    {
        // on essaye de récupérer la valeur attachée à Value
        try
        {
            // On récupère les constante stocker dans File
            const std::map<std::string, std::string> &ArrayVal = LoadFile(File);
            // On récupère la valeur de la clée
            std::map<std::string, std::string>::const_iterator val = ArrayVal.find(Value);
            // si elle n'existe pas ou est invalide on renvoie la valeur par défaut
            if(val == ArrayVal.end() || val->second.size()==0)
                return defaultValue;
            // sinon on retourne la première lettre stockée
            return val->second[0];
        }
        // si le fichier est introuvable ou n'importe quelle erreur on renvoie la valeur par défaut
        catch(...)
        {
            return defaultValue;
        }
    }

    string GetValueStr(const string &Value, const string &File, const string &defaultValue)
    {
        // on essaye de récupérer la valeur attachée à Value
        try
        {
            //  on charge le fichier en mémoire et on le stock
            const std::map<std::string, std::string> &ArrayVal = LoadFile(File);
            // on récupére la valeur attachée à la clée
            std::map<std::string, std::string>::const_iterator val = ArrayVal.find(Value);
            // si elle n'existe pas
            if(val == ArrayVal.end() || val->second.size()==0)
                return defaultValue;
            //sinon on renvoie la valeur attachée à la variable
            return val->second;
        }
        // si le fichier est introuvable ou n'importe quelle erreur on renvoie la valeur par défaut
        catch(...)
        {
            return defaultValue;
        }

    }

    // fonction qui permet de verifier si le nombre est un non signé
    bool isUnsignedValue(const string &ValTest)
    {
        for(const char &Value : ValTest)
            if(!isdigit(Value))
                return false;
        return true;
    }

    // permet de traduire une chaine de caractére en valeur numérique
    unsigned AliasToValueInt(const string &Value)
    {
        // si la valeur est une couleur connue alors on renvois sa valeur numérique
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
        // sinon on ne peut pas géré
        throw(runtime_error("Cannot Find Alias"));
    }

    unsigned GetValueInt(const string &Value, const string &File, const unsigned &defaultValue)
    {
        // on essaye de récupérer la valeur attacher à Value
        try
        {
            //  on charge le fichier en mémoire et on le stock
            const std::map<std::string, std::string> &ArrayVal = LoadFile(File);
            // on récupére la valeur attacher à Value
            std::map<std::string, std::string>::const_iterator val = ArrayVal.find(Value);
            // si elle n'existe pas
            if(val == ArrayVal.end() || val->second.size()==0)
                return defaultValue;
            // si c'est une valeur non signée on l'extrait
            else if(isUnsignedValue(val->second))
                return atoi(val->second.data());
            // sinon on essait de traduire le supposé alias contenu
            return AliasToValueInt(val->second);
        }
        // si le fichier n'existe pas ou l'alias n'est pas traduisible on retourne la valeur par défaut
        catch(...)
        {
            return defaultValue;
        }
    }
}
