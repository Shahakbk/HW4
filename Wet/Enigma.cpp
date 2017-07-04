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

Enigma::Enigma(const std::string& name, const Difficulty& difficulty,
               const int &numOfElements, const set<string> &elements) :
        name(name), difficulty(difficulty), numOfElements(numOfElements),
        elements(elements) {
    if ((int) elements.size() != numOfElements) {
        throw EnigmaIllegalSizeParamException();
    }
}

Enigma::Enigma(const std::string &name, const Difficulty &difficulty) : name(
        name), difficulty(difficulty), numOfElements(0) {
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
    if (name != enigma.name) {
        return false;
    }

    return (difficulty == enigma.difficulty);
}

bool Enigma::operator!=(const Enigma &enigma) const {
    return (!(*this == enigma));
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
/*    string newName = name;
    return newName;*/
    return name;
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