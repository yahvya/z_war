//
// Created by devel on 12/10/2023.
//

#ifndef Z_WAR_ANIMATION_HPP
#define Z_WAR_ANIMATION_HPP

namespace Game::Scene::Components::Animation{
    /***
     * class abstraite des animations
     */
    class Animation {
        public:
            /**
             * joue l'animation
             * à override si animation classique
             * @return self
             */
            virtual Animation* animate() noexcept;

            /**
             * joue l'animation
             * à override si animation avec vitesse
             * @param speed vitesse de l'animation
             * @return self
             */
            virtual Animation* animate(int speed) noexcept;
    };
}



#endif //Z_WAR_ANIMATION_HPP
