//
// Created by devel on 05/10/2023.
//

#include "ClassicObservable.hpp"
#include <iostream>

namespace Game::Pattern::Observer {
    ClassicObservable* ClassicObservable::registerObserver(
        int methodId,
        ObserverDatasContainer* observerDatas
    ) noexcept{
        try {
            if (!this->observersMap.contains(methodId)) {
                // création d'une nouvelle liste lié à la méthode

                this->observersMap.insert({
                      methodId,
                      {observerDatas}
                  });
            } else this->observersMap.find(methodId)->second.push_front(observerDatas); // ajout dans la liste existante
        }
        catch(std::exception& e){
            std::wcerr << "(Echec d'enregistrement d'observable)" << std::endl;
            std::wcerr << "(Erreur : " << e.what() << ")"  << std::endl;
        }

        return this;
    }

    ClassicObservable* ClassicObservable::notifyObservers(int methodId,std::any datas) noexcept{
        try {
            if (!this->observersMap.contains(methodId) ) return this;

            auto observerDatasList = this->observersMap.find(methodId)->second;

            for(auto observerData : observerDatasList) observerData->notificationExecutor(this,datas);
        }
        catch(std::exception& e){
            std::wcerr << "(Echec de notification des observers)" << std::endl;
            std::wcerr << "(Erreur : " << e.what() << ")"  << std::endl;
        }

        return this;
    }

    ClassicObservable* ClassicObservable::clearObservers() noexcept{
        this->observersMap.clear();

        return this;
    }

    ClassicObservable* ClassicObservable::removeObserversFrom(
        int methodId,
        std::initializer_list<ClassicObserver*> observers
    ) noexcept{
        try{
            if(!this->observersMap.contains(methodId) ) return this;

            auto observersList = this->observersMap.find(methodId)->second;

            // suppression des élements de la liste
            observersList.remove_if([&observers](ObserverDatasContainer* observerData){
                return std::find(observers.begin(),observers.end(),observerData->observer) != observers.end();
            });

            // mise à jour de la liste
            this->observersMap.at(methodId) = observersList;
        }
        catch(std::exception& e){
            std::wcerr << "(Echec de suppression d'observable)" << std::endl;
            std::wcerr << "(Erreur : " << e.what() << ")"  << std::endl;
        }

        return this;
    }
}