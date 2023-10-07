//
// Created by devel on 07/10/2023.
//

#ifndef Z_WAR_RESOURCESLOADER_HPP
#define Z_WAR_RESOURCESLOADER_HPP

#include "raylib.h"

namespace Game::Resource {
    /**
     * conteneur des ressources globales du jeux
     */
    typedef struct GameGlobalResource{
        /**
         * police d'écriture pour texte normal
         */
        Font basicTextFont;

        /**
         * police d'écriture pour texte spécial
         */
        Font specialTextFont;

        /**
         * taille normal de la police pour texte normal
         */
        int basicNormalFontSize;

        /**
         * taille large de la police pour texte normal
         */
        int basicLargerFontSize;

        /**
         * taille normal de la police pour texte spécial
         */
        int specialNormalFontSize;

        /**
         * taille large de la police pour texte spécial
         */
        int specialLargerFontSize;

        /**
         * nom de l'application
         */
        const char* appName;

        bool isLoaded;
    }GameGlobalResource;

    /**
     * chargeur de ressources, passerelle avec la librairie utilisé
     */
    class ResourcesLoader {
        public:
            /**
             * charge les ressources à partir du fichier @APP_CONFIG_FILE_PATH
             * @return les données chargées ou nullptr si echec
             */
            static GameGlobalResource* loadGlobalResources() noexcept;

        public:
            /**
             * chemin du fichier app.yaml de configuration (par rapport à l'executable final)
             */
            const char* APP_CONFIG_FILE_PATH = "./app.yaml";
    };

}

#endif //Z_WAR_RESOURCESLOADER_HPP
