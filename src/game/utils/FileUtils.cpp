//
// Created by devel on 12/10/2023.
//

#include "FileUtils.hpp"
#include <stdexcept>
#include <filesystem>
#include <algorithm>
#include "raylib.h"

namespace Game::Utils {
    unsigned int FileUtils::countOfFileInDir(std::string dirPath) noexcept{
        try{
            if(!std::filesystem::is_directory(dirPath) ) throw std::runtime_error("Le dossier n'existe pas");

            auto dirIterator = std::filesystem::directory_iterator(dirPath);

            return std::distance(std::filesystem::begin(dirIterator),std::filesystem::end(dirIterator) );
        }
        catch(std::exception&){}

        return -1;
    }

    std::vector<std::string> FileUtils::getRandomElementsInDir(std::string dirPath,unsigned int countOfElements) noexcept{
        std::vector<std::string> elements{};

        try{
            // récupération du nombre d'élements pouvant être récupéré
                auto dirSize = FileUtils::countOfFileInDir(dirPath);

                if(dirSize <= 0) throw std::runtime_error("Aucun élement dans le dossier fourni");

                if(dirSize < countOfElements) countOfElements = dirSize;

            // récupération des élements aléatoire et unique
                auto randomNumbers = std::vector<int>{};

                for(int i = 0; i < countOfElements;i++){
                    const int rdNumber = GetRandomValue(0,static_cast<int>(dirSize) - 1);

                    if(std::find(randomNumbers.begin(), randomNumbers.end(),rdNumber) != randomNumbers.end() ){
                        i--;
                        continue;
                    }

                    randomNumbers.push_back(rdNumber);
                }

                // on ordonne la liste pour permettre d'avancer sans reculer dans l'itérateur et on récupère les élements
                    std::sort(randomNumbers.begin(),randomNumbers.end() );

                    auto dirIterator = std::filesystem::directory_iterator(dirPath);

                    int previousPlace = 0;

                    for(int index = 0; index < countOfElements; index++){
                        auto number = randomNumbers[index];
                        auto next = std::next(dirIterator,number - previousPlace);

                        elements.push_back(next->path().string() );

                        previousPlace = number;
                    }
        }
        catch(std::exception&){}

        return elements;
    }
}