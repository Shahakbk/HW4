//
// Created by Shahak on 29/06/2017.
//

#include <iostream>

#include "../Enigma.h"

using namespace mtm::escaperoom;

int main() {
    std::cout << "Starting temporary Enigma tests:" << std::endl;
    Enigma sameEnigma1("MyFirstEnigma", EASY_ENIGMA, 2);
    Enigma sameEnigma2("MyFirstEnigma", EASY_ENIGMA, 2);
    Enigma diffEnigma1("MySecondEnigma", MEDIUM_ENIGMA, 1);
    Enigma diffEnigma2("MyThirdEnigma", MEDIUM_ENIGMA, 2);
    std::cout << "The first enigma is: " << sameEnigma1 << std::endl;
    std::cout << "The second enigma is: " << sameEnigma2 << std::endl;
    std::cout << "The third enigma is: " << diffEnigma1 << std::endl;
    std::cout << "The fourth enigma is: " << diffEnigma2 << std::endl;
    if (!(sameEnigma1 == sameEnigma2)) {
        std::cout << "Error: '==' operator." << std::endl;
    }

    if (sameEnigma1 == diffEnigma1 || sameEnigma2 == diffEnigma1) {
        std::cout << "Error: '==' operator." << std::endl;
    }
    if (sameEnigma1 != sameEnigma1) {
        std::cout << "Error: '!=' operator." << std::endl;
    }
    if (!(sameEnigma1 != diffEnigma1 || sameEnigma2 != diffEnigma1)) {
        std::cout << "Error: '!=' operator." << std::endl;
    }
    if (sameEnigma1 < sameEnigma2 || sameEnigma2 < sameEnigma1 ||
        diffEnigma1 < sameEnigma1 || diffEnigma1 < sameEnigma2) {
        std::cout << "Error: '<' operator." << std::endl;
    }
    if (sameEnigma1 > sameEnigma2 || sameEnigma2 > sameEnigma1 ||
        sameEnigma1 > diffEnigma1 || sameEnigma2 > diffEnigma1) {
        std::cout << "Error: '>' operator." << std::endl;
    }

    if (sameEnigma1.areEqualyComplex(diffEnigma1) ||
        sameEnigma2.areEqualyComplex(diffEnigma1)) {
        std::cout << "Error: areEqualyComplex function." << std::endl;
    }
    if (!(sameEnigma1.areEqualyComplex(sameEnigma2) &&
          sameEnigma2.areEqualyComplex(sameEnigma1))) {
        std::cout << "Error: areEqualyComplex function." << std::endl;
    }
    if (diffEnigma1.areEqualyComplex(diffEnigma2)) {
        std::cout << "Error: areEqualyComplex function." << std::endl;
    }

    if (sameEnigma1.getDifficulty() != 0 || sameEnigma2.getDifficulty() != 0 ||
        diffEnigma1.getDifficulty() != 1) {
        std::cout << "Error: getDifficulty function." << std::endl;
    }

    std::cout << "Enigma tests are done." << std::endl;
    return 0;
}