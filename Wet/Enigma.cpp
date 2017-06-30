//
// Created by Shahak on 28/06/2017.
//

#include "Enigma.h"
#include "Exceptions.h"

/**
 * namespaces in use
 */
using namespace mtm::escaperoom;

/**
 * classes in use
 */
using std::string;
//TODO ?? using mtm::escaperoom::Enigma;

Enigma::Enigma(const std::string &name, const Difficulty &difficulty,
               const int &numOfElements) {
    //TODO nullptr parameter??
    if (&numOfElements < 0) {
        throw EnigmaIllegalSizeParamException();
    }
    this->name = name;
    this->difficulty = difficulty;
    this->numOfElements = numOfElements;
}

bool Enigma::operator==(const Enigma &enigma) const {
    //TODO nullptr parameter??
    if (name != enigma.name) {
        return false;
    }

    return (difficulty == enigma.difficulty);
}

bool Enigma::operator!=(const Enigma &enigma) const {
    //TODO nullptr parameter??
    if (name == enigma.name) {
        return false;
    }

    return (difficulty != enigma.difficulty);
}

bool Enigma::operator<(const Enigma &enigma) const {
    return ((int) difficulty < (int) enigma.difficulty);
}

bool Enigma::operator>(const Enigma &enigma) const {
    return ((int) difficulty > (int) enigma.difficulty);
}

bool Enigma::areEqualyComplex(const Enigma &enigma) const {
    if ((int) difficulty != (int) enigma.difficulty) {
        return false;
    }

    return (numOfElements == enigma.numOfElements);
}

Difficulty Enigma::getDifficulty() const {
    return difficulty;
}

string Enigma::getName() const {
    std::string newName = name;
    return newName;
}

int Enigma::getNumOfElements() const {
    return numOfElements;
}

std::ostream &mtm::escaperoom::operator<<(std::ostream &output,
                                          const Enigma &enigma) {
    output << enigma.getName() << " (" << (int) enigma.getDifficulty() << ") "
                  << enigma.getNumOfElements();
    return output;
}



