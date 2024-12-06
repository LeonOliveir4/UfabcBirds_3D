#ifndef BIRDDESCRIPTIONS_HPP_
#define BIRDDESCRIPTIONS_HPP_

#include <unordered_map>
#include <string>

namespace BirdDescriptions {
    const std::unordered_map<std::string, std::string> descriptions = {
        {"Tucano", "Este é o Tucano!\n"
                   "Você sabia?\n"
                   "Os tucanos vivem nas florestas tropicais da América do Sul!\n"
                   "Eles têm bicos grandes e coloridos, que ajudam a pegar frutas e pequenos insetos.\n"
                   "Curiosidade: apesar do tamanho do bico, ele é leve e o tucano consegue voar facilmente."},
        {"Papagaio", "Este é o Papagaio!\n"
                     "Você sabia?\n"
                     "Os papagaios são conhecidos por sua habilidade de imitar sons e fala humana.\n"
                     "Eles vivem em florestas tropicais e se alimentam de frutas, sementes e néctar.\n"
                     "Curiosidade: papagaios têm uma vida longa, podendo viver até 80 anos."},
        // Adicione mais descrições aqui
    };
}

#endif