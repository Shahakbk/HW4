//
// Created by Shahak on 02/07/2017.
//

#include <iostream>

#include "../KidsRoom.h"
#include "../Exceptions.h"

using namespace mtm::escaperoom;
using std::cout;
using std::endl;

int main(){
    cout << "Starting temporary KidsRoom tests:" << endl;

    set<string> elements1;
    elements1.insert("element1");
    elements1.insert("element2");
    elements1.insert("element3");
    elements1.insert("element3");
    set<string> elements2;
    elements2.insert("lonely element");
    set<string> elements3;
    Enigma sameEnigma1("MyFirstEnigma", EASY_ENIGMA, 3, elements1);
    Enigma sameEnigma2("MyFirstEnigma", EASY_ENIGMA, 2, elements1);
    Enigma diffEnigma1("MySecondEnigma", MEDIUM_ENIGMA, 2, elements2);
    Enigma diffEnigma2("MyThirdEnigma", MEDIUM_ENIGMA, 0, elements3);
    Enigma emptyEnigma("EmptyEnigma", HARD_ENIGMA);
    emptyEnigma.addElement("No longer empty");
    emptyEnigma.addElement("Oops I did it again");

    KidsRoom kids1((char*)"FirstKidsRoom", 50, 3, 5, 18);
    KidsRoom kids2((char*)"EmptyKidsRoom", 40, 2, 4, 21);

    kids1.addEnigma(sameEnigma1);
    kids1.addEnigma(diffEnigma1);
    kids1.addEnigma(diffEnigma2);
    kids1.removeEnigma(sameEnigma1);

    try {
        kids1.removeEnigma(sameEnigma1);
    } catch (EscapeRoomEnigmaNotFoundException) {
        cout << "Enigma not found!" << endl;
    }
    try {
        kids2.removeEnigma(sameEnigma1);
    } catch (EscapeRoomNoEnigmasException) {
        cout << "No enigma found!" << endl;
    }

    kids1.addEnigma(sameEnigma1);
    kids1.addEnigma(sameEnigma2);
    kids1.addEnigma(diffEnigma1);
    kids1.addEnigma(diffEnigma2);
    kids1.addEnigma(emptyEnigma);

    Enigma hardest = kids1.getHardestEnigma();
    vector<Enigma> &roomEnigmas = kids1.getAllEnigmas();
    roomEnigmas.pop_back();

    if (kids1.getAgeLimit() != 18) {
        cout << "Error: 'getAgeLimit'!" << endl;
    }

    kids2.setNewAgeLimit(20);
    if (kids2.getAgeLimit() != 20) {
        cout << "Error: 'setNewAgeLimit'!" << endl;
    }
    cout << kids1 << endl;

    return 0;
}
