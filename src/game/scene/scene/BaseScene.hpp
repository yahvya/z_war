//
// Created by devel on 07/10/2023.
//

#ifndef Z_WAR_BASESCENE_HPP
#define Z_WAR_BASESCENE_HPP

#include "../../pattern/observer/ClassicObservable.hpp"
#include "../../pattern/observer/ClassicObserver.hpp"
#include "../../core/Game.hpp"
#include <mutex>


using namespace Game::Pattern::Observer;

namespace Game::Scene::Scene{

    /**
     * interface de scène de jeux
     * initialisé en mode (entrain de dessiner par défaut pour mutex)
     */
    class BaseScene : public ClassicObserver,public ClassicObservable {
        public:
            explicit BaseScene(Game::Core::Game* linkedGame);

            /**
             * dessine la scène
             * @param countOfRetry nombre de tentatives si echec de dessin
             * @return si le dessin réussi
             */
            virtual bool draw(int countOfRetry) noexcept = 0;

            /**
             * configure la fenêtre pour la scène (taille,titre,fps)
             * @return si la configuration réussie
             */
            virtual bool configWindow() noexcept;

            /**
             * stoppe le dessin en mettant à jour le booléen de status
             * thread safe
             * @return self
             */
            virtual BaseScene* stopDrawing() noexcept;

            /**
             * centre le fenêtre (les valeurs width et height doivent être initialisé)
             * @return self
             */
            BaseScene* centerWindow();

            /**
             * met à jour les fps à partir de la configuration
             * @return self
             */
            BaseScene* setFps();

            /**
             * met à jour les fps
             * @param fps les fps à ajouter
             * @return self
             */
            BaseScene* setFps(int fps);

        protected:
            /**
             * fps minimum du jeux (plus important que la config)
             */
            static const int MIN_FPS;
            /**
             * fps maximum du jeux (plus important que la config)
             */
            static const int MAX_FPS;

            /**
             * fps par défaut en cas de mauvaise configuration
             */
            static const int DEFAULT_FPS;

            /**
             * le jeux lié à la scène
             */
            Game::Core::Game* linkedGame;

            /**
             * défini si la scène est actuellement entrain et doit poursuivre son dessin
             */
            bool isDrawing = false;

            /**
             * gestionnaire d'accès à la variable isDrawing
             */
            std::mutex accessLocker;

            /**
             * largeur de la fenêtre
             */
            float width;

            /**
             * hauteur de la fenêtre
             */
            float height;

            /**
             * nom de la fenêtre
             */
             std::string windowName;
    };

}

#endif //Z_WAR_BASESCENE_HPP

