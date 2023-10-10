//
// Created by devel on 07/10/2023.
//

#ifndef Z_WAR_RESOURCESMANAGER_HPP
#define Z_WAR_RESOURCESMANAGER_HPP

#include "raylib.h"
#include "yaml-cpp/yaml.h"
#include "../pattern/observer/ClassicObservable.hpp"
#include <vector>
#include <string>
#include <thread>

using namespace Game::Pattern::Observer;

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
        float basicNormalFontSize;

        /**
         * taille large de la police pour texte normal
         */
        float basicLargerFontSize;

        /**
         * taille normal de la police pour texte spécial
         */
        float specialNormalFontSize;

        /**
         * taille large de la police pour texte spécial
         */
        float specialLargerFontSize;

        /**
         * version de l'application
         */
        int currentVersion;

        /**
         * fps du jeux
         */
        int fps;

        /**
         * chemin du dossier contenant les ressources
         */
        std::string resourcesDirPath;

        /**
         * chemin de l'icone de l'application
         */
        std::string appIconPath;

        /**
         * nom de l'application
         */
        std::string appName;

        /**
         * liste des créateurs
         */
        std::vector<YAML::Node> creators;

        bool isLoaded;

        GameGlobalResource() : isLoaded{false} {}
    }GameGlobalResource;

    /**
     * données du joueur
     */
    typedef struct{
        /*
         * nom du joueur
         */
        std::string name;

        /**
         * prénom du joueur
         */
        std::string fname;

        /**
         * date de naissance du joueur
         */
        std::string birth;

        /**
         * date du premier lancement du jeux par le joueur
         */
        std::string joinDate;

        /**
         * si c'est le premier lancement du jeux (données joueur non configurés)
         */
        bool isConfigured;
    }PlayerConfigDatas;

    typedef struct{
        /**
         * son général du jeux
         */
        float generalSongPercent;

        /*
         *  son dans une partie
         */
        float gameSongPercent;

        /**
         * son des coups dans une partie
         */
        float hitSongPercent;

        /**
         * son des actions sur le jeux (click souris hover ...)
         */
        float generalActionSongPercent;
    }SongConfigDatas;

    /**
     * ressources requises du jeux
     */
    typedef struct GameRequiredResource{
        /**
         * configuration du joueur
         */
        PlayerConfigDatas* playerConfig;
        SongConfigDatas* songConfig;

        explicit GameRequiredResource(PlayerConfigDatas* playerConfig,SongConfigDatas* songConfig) : playerConfig{playerConfig},songConfig{songConfig} {}
    }GameRequiredResource;

    /**
     * gestionnaire de ressources, passerelle avec les librairies utilisés
     */
    class ResourcesManager : public ClassicObservable {

        public:
            typedef enum{
                /**
                 * fin de chargement des ressources requises au jeux
                 * données transmises: booléen donnant l'état de réussite de l'action
                 */
                END_OF_LOADING_APP_RESSOURCES
            }ResourcesManagerObservableEvents;
        public:
            explicit ResourcesManager();

            /**
             * charge les ressources à partir du fichier @APP_CONFIG_FILE_PATH
             * @return bool si le chargement a réussi
             */
            bool loadGlobalResources() noexcept;

            /**
             * charge les ressources requises pour le jeux
             * renvoie l'évenement END_OF_LOADING_APP_RESSOURCES
             * met à jour le status de getSuccessfullyLoadRequiredResources()
             * @attention fonction non bloquante
             */
            void loadRequiredResources() noexcept;

            /**
             *
             * @return si les ressources requises ont bien été chargés
             */
            bool getSuccessfullyLoadRequiredResources() noexcept;

            /**
             * @attention à la modification des données
             * @return les données requises du jeux
             */
            GameRequiredResource* getGameRequiredResources() noexcept;

            /**
             * @attention à la modification des données
             * @return les données préliminaires du jeux
             */
            GameGlobalResource* getGameGlobalResources() noexcept;

        private:
            /**
             * charge les données requises pour l'application
             * @attention lancement interne par thread
             * @param fromThread à partir du thread
             */
            void loadRequiredResources(bool fromThread) noexcept;

        public:
            /**
             * chemin du fichier app.yaml de configuration (par rapport à l'executable final)
             */
            static const char* APP_CONFIG_FILE_PATH;

            /**
             * chemin du dossier des polices d'écriture à partir du dossier des ressources
             */
            static const char* FONTS_DIR_PATH;

            /**
             * chemin du dossier des configurations à partir du dossier des ressources
             */
            static const char* CONFIG_DIR_PATH;

        private:
            /**
             * ressources globales et préliminaires du jeux
             */
            GameGlobalResource* gameGlobalResources;

            /**
             * thread de chargement des ressources requises du jeux
             */
            std::thread* requiredResourcesLoadingThread;

            /**
             * ressources requises du jeux
             */
            GameRequiredResource* gameRequiredResources;
    };

}

#endif //Z_WAR_RESOURCESMANAGER_HPP
