#pragma once
#include <string>
#include <map>
namespace SpaceInvader
{
    /**
     * @brief GetValueChar
     * Fonction qui permet de récupérer un charactére à partire d'un fichier yaml
     * @param Value
     * Nom de La variable contenant la valeur à extraire
     * @param File
     * Nom du ficher yaml contenant les imformation suposer
     * @param defaultValue
     * Valeur par-défaut en cas d'échec de lecture
     * @return
     * valeur contenue dans la variable
     */
    char GetValueChar(const std::string &Value, const std::string &File, const char &defaultValue);

    /**
     * @brief GetValueStr
     * Fonction qui récupere le contenue d'une variable dans un fichier yaml
     * @param Value
     * Nom de la variable
     * @param File
     * Nom du Fichier YAML
     * @param defaultValue
     * Valeur par-défaut en cas d'inexistance de la variable
     * @return
     * Valeur de la variable
     */
    std::string GetValueStr(const std::string &Value, const std::string &File, const std::string &defaultValue);

    /**
     * @brief GetValueInt
     * Fonction qui permet de recuperé une valeur numérique non signé à partir d'un fichier yaml
     * @param Value
     * nom de la variable
     * @param File
     * nom du fichier de configuration
     * @param defaultValue
     * Valeur par-défaut en cas d'echec d'extraction
     */
    unsigned GetValueInt(const std::string &Value, const std::string &File, const unsigned &defaultValue);

    /**
     * @brief LoadFile
     * Fonction de lecture partiel de fichier yaml
     * @param File
     * Fichier au format yaml à lire
     * @param reload
     * Les donnée déjàt en mémoire seron rechargé si vrai
     * @return
     * Renvoie les donnés de configuration
     */
    const std::map<std::string, std::string> &LoadFile(const std::string &File, bool reload = false);
}
