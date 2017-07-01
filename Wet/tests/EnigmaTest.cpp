//
// Created by Shahak on 29/06/2017.
//

#include <iostream>

#include "../Enigma.h"
#include "../Exceptions.h"

using namespace mtm::escaperoom;

int main() {
    set<string> elements1;
    elements1.insert("element1");
    elements1.insert("element2");
    elements1.insert("element3");
    elements1.insert("element3");
    set<string> elements2;
    elements2.insert("lonely element");
    set<string> elements3;
    std::cout << "Starting temporary Enigma tests:" << std::endl;
    Enigma sameEnigma1("MyFirstEnigma", EASY_ENIGMA, 3, elements1);
    Enigma sameEnigma2("MyFirstEnigma", EASY_ENIGMA, 2, elements1);
    Enigma diffEnigma1("MySecondEnigma", MEDIUM_ENIGMA, 2, elements2);
    Enigma diffEnigma2("MyThirdEnigma", MEDIUM_ENIGMA, 0, elements3);
    Enigma emptyEnigma("EmptyEnigma", HARD_ENIGMA);
    emptyEnigma.addElement("No longer empty");
    emptyEnigma.addElement("Oops I did it again");
    try {
        emptyEnigma.removeElement("Wasn't found!");
    } catch(EnigmaElementNotFoundException) {
        std::cout << "Element wasn't found in the enigma!" << std::endl;
    }
    emptyEnigma.removeElement("Oops I did it again");
    emptyEnigma.removeElement("No longer empty");
    try {
        emptyEnigma.removeElement("Exception!");
    } catch(EnigmaNoElementsException) {
        std::cout << "No elements in the enigma!" << std::endl;
    }

    std::cout << "The first enigma is: " << sameEnigma1 << std::endl;
    std::cout << "The second enigma is: " << sameEnigma2 << std::endl;
    std::cout << "The third enigma is: " << diffEnigma1 << std::endl;
    std::cout << "The fourth enigma is: " << diffEnigma2 << std::endl;
    std::cout << "The fifth enigma is: " << emptyEnigma << std::endl;
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