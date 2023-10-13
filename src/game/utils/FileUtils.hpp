//
// Created by devel on 12/10/2023.
//

#ifndef Z_WAR_FILEUTILS_HPP
#define Z_WAR_FILEUTILS_HPP

#include <vector>

namespace Game::Utils {

    /**
     * utilitaire d'aide aux fichiers
     */
    class FileUtils {
        public:
            /**
             * compte le nombre de fichiers dans le dossier
             * @param dirPath chemin du dossier
             * @return le nombre de fichier ou -1 si erreur
             * @throw std::runtime_error
             */
            static unsigned int countOfFileInDir(const char* dirPath) noexcept;

            /**
             * récupère le nom des élements de manière random dans le dossier si disponible ou choisis le nombre d'élements disponibles
             * @param dirPath chemin du dossier
             * @param countOfElements nombre d'élements à récupérer
             * @return la liste des élements récupérés
             */
            static std::vector<const char*> getRandomElementsInDir(const char* dirPath,unsigned int countOfElements) noexcept;
    };

}

#endif //Z_WAR_FILEUTILS_HPP
