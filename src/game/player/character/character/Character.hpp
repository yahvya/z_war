//
// Created by devel on 12/10/2023.
//

#ifndef Z_WAR_CHARACTER_HPP
#define Z_WAR_CHARACTER_HPP

#include "../../../core/Game.hpp"
#include <map>

using namespace Game::Core;

namespace Game::Player::Character::Character{

    /**
     * personnage du jeux
     */
    class Character{
        public:
            /**
             * données sur une action d'un personnage
             */
            typedef struct CharacterAction{
                /**
                 * chemin du fichier de description de l'action
                 */
                const char* actionDescriptionFilePath = nullptr;

                /**
                 * nom de l'action
                 */
                const char* actionName = nullptr;

                /**
                 * description de l'action
                 */
                YAML::Node actionDescription;

            private:
                /**
                 * si la description de l'action est bien chargé
                 */
                bool actionDescriptionIsCorrect = false;

            public:
                /**
                 *
                 * @return si l'action est chargé
                 */
                bool getActionIsLoaded(){
                    return
                        this->actionDescriptionFilePath != nullptr &&
                        this->actionName != nullptr &&
                        this->actionDescriptionIsCorrect;
                };
            }CharacterAction;

            /**
             * données sur l'animqtion de présentartion du personnage
             */
            typedef struct PresentationAnimationData{
                /**
                 * nom de la forme lié
                 */
                const char* formName;

                /**
                 * nom des actions dans requises pour l'animation
                 */
                std::vector<const char*> requiredActions;

                /**
                 * liste des noms d'actions à lancer dans l'ordre de lancement pour l'animation
                 */
                std::vector<const char*> animationList;
            }PresentationAnimationData;

            /**
             * données d'une forme du jeux
             */
            typedef struct CharacterFormData{
                // chemmin du dossier
                    /**
                     * chemin du dossier de la forme
                     */
                    const char* dirPath = nullptr;

                    /**
                     *
                     * @return si le chemin du dossier est chargé
                     */
                    bool getDirPathIsLoaded() const{
                        return this->dirPath != nullptr;
                    }

                // images de la forme
                    /**
                     * map des images
                     * @key clé lié à l'image
                     * @value chemin complet de l'image
                     */
                    std::map<const char*,const char*> imagesMap;

                    /**
                     *
                     * @return si les images sont chargés
                     */
                    bool getImagesAreLoaded() const{
                        return this->imagesMap.empty();
                    }

                    /**
                     *
                     * @param key clé de l'image
                     * @return si l'image est chargé
                     */
                    bool getImageIsLoaded(const char* key) const{
                        return this->imagesMap.contains(key);
                    }

                // nom du personnage
                    /**
                     * nom du personnage
                     */
                    const char* characterName = nullptr;
    
                    /**
                     * 
                     * @return si le nom du personnage est chargé
                     */
                    bool getCharacterNameIsLoad() const{
                        return this->characterName != nullptr;
                    }

                // énergie
                    /**
                     * énergie requise pour charger débloquer la forme
                     */
                    float requiredEnergy = -1.f;

                    /**
                     *
                     * @return si l'énergie requise pour charger la forme est chargé
                     */
                    bool getRequiredEnergyIsLoaded() const{
                        return this->requiredEnergy > -1.f;
                    }

                // durée
                    /**
                     * durée de la forme en seconde
                     */
                    float duration = -1.f;

                    /**
                     * @return si la durée de la forme est chargé
                     */
                    bool getDurationIsLoaded() const{
                        return this->duration != -1.f;
                    }

                // formule de gain de combo
                    /**
                     * formule de gain de combo
                     */
                    float comboGainFormula = -1.f;

                    /**
                     * @return si la formule de gain de combo est chargé
                     */
                    bool getComboGainFormulaIsLoaded() const{
                        return this->comboGainFormula != -1.f;
                    }

                // points de base de bouclier
                    /**
                     * points de base de bouclier
                     */
                    float shieldPoints = -1.f;

                    /**
                     * @return si les points de base sont chargés
                     */
                    bool getShieldPointsIsLoaded() const{
                        return this->shieldPoints != -1.f;
                    }

                // images à exécuter pour le bouclier
                    /**
                     * liste des clés d'images présentes dans la map d'image dans l'ordre pour rendre l'image de bouclier
                     */
                    std::vector<const char*> shieldImagesList;

                    /**
                     *
                     * @return si la liste des images boucliers sont chargés
                     */
                    bool getShieldImagesListAreLoaded() const{
                        return !this->shieldImagesList.empty();
                    }

                // images à exécuter pour le tomber
                    /**
                     * liste des clés d'images présentes dans la map d'image dans l'ordre pour rendre l'image tomber
                     */
                    std::vector<const char*> fellImagesList;

                    /**
                     *
                     * @return si la liste des images tomber sont chargés
                     */
                    bool getFellImagesListAreLoaded() const{
                        return !this->fellImagesList.empty();
                    }

                // images à exécuter pour se relever
                    /**
                     * liste des clés d'images présentes dans la map d'image dans l'ordre pour rendre l'image relever
                     */
                    std::vector<const char*> getUpImagesList;

                    /**
                     *
                     * @return si la liste des images tomber sont chargés
                     */
                    bool getUpImagesListAreLoaded() const{
                        return !this->getUpImagesList.empty();
                    }

                // actions du personnage
                    /**
                     * map des actions du personnage
                     */
                    std::map<const char*,CharacterAction*> actionsMap;

                    /**
                     *
                     * @return si toutes les actions sont chargé
                     */
                    bool getActionsMapIsLoaded() const{
                        if(this->actionsMap.empty() ) return false;

                        return std::all_of(this->actionsMap.begin(),this->actionsMap.end(),[](auto actionData){
                            return actionData.second->getActionIsLoaded();
                        });
                    }

                    /**
                     *
                     * @param actionName nom de l'action
                     * @return si l'action est chargé
                     */
                    bool getActionIsLoaded(const char* actionName){
                        return this->actionsMap.contains(actionName) && this->actionsMap[actionName]->getActionIsLoaded();
                    }

                /**
                 *
                 * @return si la forme est chargé
                 */
                bool getFormIsLoaded() const{
                    return
                        this->getActionsMapIsLoaded() &&
                        this->getCharacterNameIsLoad() &&
                        this->getComboGainFormulaIsLoaded() &&
                        this->getDurationIsLoaded() &&
                        this->getFellImagesListAreLoaded() &&
                        this->getImagesAreLoaded() &&
                        this->getDirPathIsLoaded() &&
                        this->getRequiredEnergyIsLoaded() &&
                        this->getUpImagesListAreLoaded() &&
                        this->getShieldPointsIsLoaded() &&
                        this->getShieldImagesListAreLoaded();
                }
            }CharacterFormData;

            /**
             * données globales d'un personnage du jeux
             */
            typedef struct CharacterDatas{
                public:
                    //  formes du personnage
                        /**
                         * map de listage des formes du personnage
                         * @key nom de la forme
                         */
                        std::map<const char*,CharacterFormData*> characterFormsMap;

                        /**
                         * @return si toutes les formes du personnage sont chargé
                         */
                        bool getCharacterFormsAreLoaded() const{
                            if(this->characterFormsMap.empty() ) return false;

                            return std::all_of(this->characterFormsMap.begin(),this->characterFormsMap.end(),[](auto formData){
                                return formData.second->getFormIsLoaded();
                            });
                        }

                        /**
                         *
                         * @param formName nom de la forme
                         * @return si la forme au nom donné est chargé ou non
                         */
                        bool getCharacterFormIsLoaded(const char* formName){
                            return this->characterFormsMap.contains(formName) && this->characterFormsMap[formName]->getFormIsLoaded();
                        }

                        /**
                         *
                         * @param formName nom de la forme
                         * @param actionName nom de l'action
                         * @return si la forme au nom donné est chargé ou non et l'action donné est chargé
                         */
                        bool getCharacterFormActionIsLoaded(const char* formName,const char* actionName){
                            return this->characterFormsMap.contains(formName) && this->characterFormsMap[formName]->getActionIsLoaded(actionName);
                        }

                    // poster du personnage

                        /**
                         * chemin de poster du personnage
                         */
                        const char* presentationImagePath = nullptr;

                        /**
                         *
                         * @return le chemin de poster du personnage
                         */
                        const char* getPresentationImagePath(){
                            return this->presentationImagePath;
                        }

                        /**
                         *
                         * @return si le chemin poster est chargé
                         */
                        bool getPresentationImagePathIsLoaded() const{
                            return this->presentationImagePath != nullptr;
                        }

                    // controlleurs du jeux

                        /**
                         * nom du personnage
                         */
                        std::vector<const char*> controllers;

                        /**
                         *
                         * @return la liste des controllers
                         */
                        std::vector<const char*> getControllers(){
                            return this->controllers;
                        }

                        /**
                         *
                         * @return si les controllers sont chargés
                         */
                        bool getControllersAreLoaded() const{
                            return !this->controllers.empty();
                        }

                    // animation de présentation du personnage
                        PresentationAnimationData* presentationAnimationData = nullptr;

                        /**
                         *
                         * @return si les données d'animation sont chargé
                         */
                        bool getPresentationAnimationDataIsLoaded() const{
                            return this->presentationAnimationData;
                        }
                    /**
                     *
                     * @return si toutes les données du personnage sont chargé
                     */
                    bool getCharacterDatasAreLoaded(){
                        return
                            this->getCharacterFormsAreLoaded() &&
                            this->getControllersAreLoaded() &&
                            this->getPresentationImagePathIsLoaded() &&
                            this->getPresentationAnimationDataIsLoaded();
                    }
            }CharacterDatas;

        public:
            /**
             *
             * @param linkedGame le jeux lié
             */
            explicit Character(Core::Game* linkedGame) noexcept;

            /**
             *
             * @return les données du personnage
             */
            CharacterDatas* getDatas() noexcept;

            /**
             * charge les données pour l'animation, peut être appelé plusieurs fois
             * @return si le chargement à bien réussi
             */
            virtual bool loadAnimationDatas() noexcept = 0;

        protected:
            /**
             * données globales du personnage
             */
            CharacterDatas* characterDatas;

            /**
             * jeux lié
             */
            Core::Game* linkedGame;
    };
}

#endif //Z_WAR_CHARACTER_HPP
