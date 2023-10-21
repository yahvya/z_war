//
// Created by devel on 19/10/2023.
//

#ifndef Z_WAR_CHARACTERDESCRIPTION_HPP
#define Z_WAR_CHARACTERDESCRIPTION_HPP

#include <string>
#include "yaml-cpp/yaml.h"
#include "raylib.h"

namespace Game::Player::Character::Character{
    // structures de description d'un personnage

    /**
     * variables de durée
     */
    const std::map<std::string,int> DURATION_VAR = {
        {"INFINITE",-1}
    };

    /**
     * variables de type de description
     */
    const std::map<std::string,int> DESCRIPTION_TYPE_VAR = {
        /**
         * action pouvant être répété
         */
        {"REPEATABLE",2},
    };

    /**
     * variables de type de description de controlleurs
     */
    const std::map<std::string,int> CONTROLLER_TYPE_VAR = {
        /**
         * touche simple
         */
        {"SIMPLE",1},
        /**
         * condition posé sur l'action
         */
        {"CONDITION",2},
        /**
         * plusieurs touches mapé
         */
        {"COMBINED-TOUCH",3},
        /**
         * action séquentiel
         */
        {"SEQUENCE",4},
        /**
         * référence sur une séquance défini ailleurs
         */
        {"SEQUENCE-REFERENCE",5}
    };

    /**
     * variables de mappage des touches clavier
     */
    const std::map<std::string,int> KEYBOARD_TOUCH_MAP_VAR = {
        /**
         * flèche basse clavier
         */
        {"ARROW-DOWN",KeyboardKey::KEY_DOWN},
        /**
         * flèche gauche clavier
         */
        {"ARROW-LEFT",KeyboardKey::KEY_LEFT},
        /**
         * flèche droite clavier
         */
        {"ARROW-RIGHT",KeyboardKey::KEY_RIGHT},
        /**
         * flèche haute clavier
         */
        {"ARROW-UP",KeyboardKey::KEY_UP},
        /**
         * touche espace
         */
        {"SPACE-BAR",KeyboardKey::KEY_SPACE},
    };

    /**
     * variables de mappage des touches manettes
     */
    const std::map<std::string,int> GAMEPAD_TOUCH_MAP_VAR = {
        /**
         * touche x manettes ps3
         */
        {"GAMEPAD-X-TOUCH",GamepadButton::GAMEPAD_BUTTON_RIGHT_FACE_DOWN}
    };

    /**
     * données sur une action d'un personnage
     */
    typedef struct CharacterAction{
        public:
            /**
             * chemin du fichier de description de l'action
             */
            std::string actionDescriptionFilePath;

            /**
             * nom de l'action
             */
            std::string actionName;

            /**
             * description de l'action
             */
            YAML::Node actionDescription;

            /**
             *
             * @return si l'action est chargé
             */
            bool getActionIsLoaded(){
            return
                    !this->actionDescriptionFilePath.empty() &&
                    !this->actionName.empty();
        };
    }CharacterAction;

    /**
     * données sur l'animqtion de présentartion du personnage
     */
    typedef struct PresentationAnimationData{
        /**
         * nom de la forme lié
         */
        std::string formName;

        /**
         * nom des actions dans requises pour l'animation
         */
        std::vector<std::string> requiredActions;

        /**
         * liste des noms d'actions à lancer dans l'ordre de lancement pour l'animation
         */
        std::vector<std::string> animationList;
    }PresentationAnimationData;

    /**
     * données d'une forme du jeux
     */
    typedef struct CharacterFormData{
        // images de la forme
            /**
             * map des images
             * @key clé lié à l'image
             * @value chemin complet de l'image
             */
            std::map<std::string,std::string> imagesMap;

            /**
             *
             * @return si les images sont chargés
             */
            bool getImagesAreLoaded() const{
                return !this->imagesMap.empty();
            }

            /**
             *
             * @param key clé de l'image
             * @return si l'image est chargé
             */
            bool getImageIsLoaded(std::string key) const{
            return this->imagesMap.contains(key);
        }

        // nom du personnage
            /**
             * nom du personnage
             */
            std::string characterName;

            /**
             *
             * @return si le nom du personnage est chargé
             */
            bool getCharacterNameIsLoad() const{
                return !this->characterName.empty();
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
        float duration = -2.f;

        /**
         * @return si la durée de la forme est chargé
         */
        bool getDurationIsLoaded() const{
            return this->duration != -2.f;
        }

        // formule de gain de combo
            /**
             * formule de gain de combo
             */
            std::string comboGainFormula;

            /**
             * @return si la formule de gain de combo est chargé
             */
            bool getComboGainFormulaIsLoaded() const{
                return !this->comboGainFormula.empty();
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
            std::vector<std::string> shieldImagesList;

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
            std::vector<std::string> fellLeftImagesList;
            std::vector<std::string> fellRightImagesList;

            /**
             *
             * @return si la liste des images tomber sont chargés
             */
            bool getFellImagesListAreLoaded() const{
                return !this->fellLeftImagesList.empty() && !this->fellRightImagesList.empty();
            }

        // images à exécuter pour se relever
            /**
             * liste des clés d'images présentes dans la map d'image dans l'ordre pour rendre l'image relever
             */
            std::vector<std::string> getUpImagesList;

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
            std::map<std::string,CharacterAction*> actionsMap;

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
            bool getActionIsLoaded(std::string actionName){
            return this->actionsMap.contains(actionName) && this->actionsMap[actionName]->getActionIsLoaded();
        }

        // vitesse d'attaque du personnage
            /**
             * vitesse d'attaque du personnage
             */
            float attackSpeed = -1.f;

            /**
             *
             * @return si la vitesse d'attaque est chargé
             */
            bool getAttackSpeedIsLoaded() const{
                return this->attackSpeed;
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
                    this->getRequiredEnergyIsLoaded() &&
                    this->getUpImagesListAreLoaded() &&
                    this->getShieldPointsIsLoaded() &&
                    this->getShieldImagesListAreLoaded() &&
                    this->getAttackSpeedIsLoaded();
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
                std::map<std::string,CharacterFormData*> characterFormsMap;

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
                bool getCharacterFormIsLoaded(std::string formName){
                    return this->characterFormsMap.contains(formName) && this->characterFormsMap[formName]->getFormIsLoaded();
                }

                /**
                 *
                 * @param formName nom de la forme
                 * @param actionName nom de l'action
                 * @return si la forme au nom donné est chargé ou non et l'action donné est chargé
                 */
                bool getCharacterFormActionIsLoaded(std::string formName,std::string actionName){
                return this->characterFormsMap.contains(formName) && this->characterFormsMap[formName]->getActionIsLoaded(actionName);
            }

            // poster du personnage
                /**
                 * chemin de poster du personnage
                 */
                std::string presentationImagePath;

                /**
                 *
                 * @return le chemin de poster du personnage
                 */
                std::string getPresentationImagePath(){
                    return this->presentationImagePath;
                }

                /**
                 *
                 * @return si le chemin poster est chargé
                 */
                bool getPresentationImagePathIsLoaded() const{
                return !this->presentationImagePath.empty();
            }

            // controlleurs du jeux
                /**
                 * nom du personnage
                 */
                std::vector<std::string> controllers;

                /**
                 *
                 * @return la liste des controllers
                 */
                std::vector<std::string> getControllers(){
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

            /**
             *
             * @return si les données du personnage sont toutes chargés
             */
            bool getCharacterDatasAreLoaded(){
            return
                    this->getCharacterFormsAreLoaded() &&
                    this->getControllersAreLoaded() &&
                    this->getPresentationImagePathIsLoaded() &&
                    this->getPresentationAnimationDataIsLoaded();
        }
    }CharacterDatas;
}

#endif //Z_WAR_CHARACTERDESCRIPTION_HPP
