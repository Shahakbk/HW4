//
// Created by Shahak on 02/07/2017.
//

#include <iostream>

#include "../ScaryRoom.h"
#include "../Exceptions.h"

using namespace mtm::escaperoom;
using std::cout;
using std::endl;

int main(){
    cout << "Starting temporary Wrapper tests:" << endl;

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

    ScaryRoom scary1((char*)"FirstScary", 50, 3, 5, 18, 2);
    ScaryRoom scary2((char*)"EmptyScary", 40, 2, 4, 21, 3);

    scary1.addEnigma(sameEnigma1);
    scary1.addEnigma(diffEnigma1);
    scary1.addEnigma(diffEnigma2);
    scary1.removeEnigma(sameEnigma1);

/*    try {
        scary1.removeEnigma(sameEnigma1);
    } catch (EscapeRoomEnigmaNotFoundException) {
        cout << "Enigma not found!" << endl;
    }*/
    try {
        scary2.removeEnigma(sameEnigma1);
    } catch (mtm::escaperoom::EscapeRoomNoEnigmasException) {
        //TODO ^^^^ doesn't work without mtm::escaperoom::
        cout << "No enigma found!" << endl;
    }

    scary1.addEnigma(sameEnigma1);
    scary1.addEnigma(sameEnigma2);
    scary1.addEnigma(diffEnigma1);
    scary1.addEnigma(diffEnigma2);
    scary1.addEnigma(emptyEnigma);

    Enigma hardest = scary1.getHardestEnigma();
    vector<Enigma> &roomEnigmas = scary1.getAllEnigmas();
    roomEnigmas.pop_back();

    return 0;
}
