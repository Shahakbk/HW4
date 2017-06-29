//
// Created by Shahak on 28/06/2017.
//

#include "Enigma.h"

using namespace mtm::escaperoom;
using std::string;

Enigma::Enigma(const std::string &name, const Difficulty &difficulty,
               const int &numOfElements) {
    //TODO nullptr parameter
    this->name = name;
    this->difficulty = difficulty;
    this->numOfElements = numOfElements;
}


bool Enigma::operator==(const Enigma &enigma) const {
    //TODO nullptr parameter
    if (this->name != enigma.name) {
        return false;
    }

    return (this->difficulty == enigma.difficulty);
}

bool Enigma::operator!=(const Enigma &enigma) const {
    //TODO nullptr parameter
    if (this->name == enigma.name) {
        return false;
    }

    return (this->difficulty != enigma.difficulty);
}

bool Enigma::operator<(const Enigma &enigma) const {
    return ((int) this->difficulty < (int) enigma.difficulty);
}

bool Enigma::operator>(const Enigma &enigma) const {
    return ((int) this->difficulty > (int) enigma.difficulty);
}

bool Enigma::areEqualyComplex(const Enigma &enigma) const {
    if ((int) this->difficulty != (int) enigma.difficulty) {
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



