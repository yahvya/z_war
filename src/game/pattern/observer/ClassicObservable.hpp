//
// Created by devel on 05/10/2023.
//

#ifndef Z_WAR_CLASSICOBSERVABLE_HPP
#define Z_WAR_CLASSICOBSERVABLE_HPP

#include <map>
#include <list>
#include <functional>
#include <variant>
#include <string>
#include "ClassicObserver.hpp"

namespace Game::Pattern::Observer {
    /**
     * class de marquage d'un élement pouvant être observé
     */
    class ClassicObservable{
        // structures
        public:
            /**
             * types de données possibles des évenements à enregistrer ici
             */
            typedef std::variant<
                    bool,
                    int,
                    double,
                    float,
                    std::string
            > EventDataType;

            /**
             * lambda de gestion des notificqtions
             */
            typedef std::function<void(ClassicObservable*,EventDataType)> ObserverNotificationExecutor;

            /**
             * structures conteneur des données de notification
             */
            typedef struct ObserverDatasContainer{
                public:
                    ClassicObserver* observer;
                    ObserverNotificationExecutor notificationExecutor;

                public:
                    ObserverDatasContainer(ClassicObserver* observer,ObserverNotificationExecutor notificationExecutor){
                        this->observer = observer;
                        this->notificationExecutor = std::move(notificationExecutor);
                    }
            }ObserverDatasContainer;
        // méthodes

        public:
            /**
             * enregistre un obrservateur
             * @param methodId id de la méthode à écouté (enum personnalisé)
             * @param observerDatas donnée de gestion notifications
             * @return self
             */
            ClassicObservable* registerObserver(
                int methodId,
                ObserverDatasContainer* observerDatas
            ) noexcept;

            /**
             * vide la map des observateurs
             * @return self
             */
            ClassicObservable* clearObservers() noexcept;

            /**
             * supprime les observateurs de la liste de notification
             * @param methodId id de la méthode
             * @param observers liste des observateurs à supprimer
             * @return self
             */
            ClassicObservable* removeObserversFrom(
                int methodId,
                std::initializer_list<ClassicObserver*> observers
            ) noexcept;

        protected:
            /**
             * notifie les observateurs
             * @attention le type de données doit être enregistré
             * @param methodId id de la méthode qui notifie
             * @param datas les données à partager
             * @return self
             */
            ClassicObservable* notifyObservers(int methodId,EventDataType datas) noexcept;

        private:
            /**
             * map des observateurs
             * int id de la méthode à écouté (enum personnalisé)
             * std::pair<ClassicObserver,void(ClassicObserver::*)(ClassicObservable*,std::any data)> l'observateur ainsi qu'un pointeur sur méthode prenant l'obervable envoyeur du message et la donnée du message
             */
            std::map<int,std::list<ObserverDatasContainer*> > observersMap;
    };
}

#endif