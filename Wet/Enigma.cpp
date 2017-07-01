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

Enigma::Enigma(const std::string& name, const Difficulty& difficulty,
               const int& numOfElements, const set<string> &elements) {

    //TODO nullptr parameter??
    int num = (int)elements.size();
    if (num != numOfElements) {
        //throw EnigmaIllegalSizeParamException();
    }
    this->elements = elements;
    this->name = name;
    this->difficulty = difficulty;
    this->numOfElements = numOfElements;
}

Enigma::Enigma(const std::string& name, const Difficulty& difficulty) {
    this->name = name;
    this->difficulty = difficulty;
    this->numOfElements = 0;
    // elements is initialized as an empty set by default
}

void Enigma::addElement(const string& element) {
    elements.insert(element);
    numOfElements++;
}

void Enigma::removeElement(const string& element) {

    if (0 == numOfElements) {
        throw EnigmaNoElementsException();
    }

    // erase returns the number of elements removed
    if (0 == elements.erase(element)) {
        throw EnigmaElementNotFoundException();
    }
    numOfElements--;
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



