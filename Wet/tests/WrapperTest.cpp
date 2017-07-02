//
// Created by adire on 30-Jun-17.
//
#include <iostream>

#include "../EscapeRoomWrapper.h"
#include "../Enigma.h"
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

    EscapeRoomWrapper wrapper1((char*)"same", 40, 5, 5);
    EscapeRoomWrapper wrapper2 = wrapper1;
    EscapeRoomWrapper wrapper3((char*)"check =", 6);
    wrapper3 = wrapper1;

    if (!(wrapper1 == wrapper2)) {
        cout << "Error: '==' operator." << endl;
    }

    if (!(wrapper1 == wrapper3)) {
        cout << "Error: '==' operator." << endl;
    }

    cout << "The first wrapper is: " << wrapper1 << endl;

    wrapper1.addEnigma(sameEnigma1);
    wrapper1.addEnigma(diffEnigma1);
    wrapper1.addEnigma(diffEnigma2);
    wrapper1.removeEnigma(sameEnigma1);

    try {
        wrapper1.removeEnigma(sameEnigma1);
    } catch (EscapeRoomEnigmaNotFoundException) {
        std::cout << "Enigma not found!" << std::endl;
    }
    try {
        wrapper2.removeEnigma(sameEnigma1);
    } catch (EscapeRoomNoEnigmasException) {
        std::cout << "No enigma found!" << std::endl;
    }

    wrapper3.addEnigma(sameEnigma1);
    wrapper3.addEnigma(sameEnigma2);
    wrapper3.addEnigma(diffEnigma1);
    wrapper3.addEnigma(diffEnigma2);
    wrapper3.addEnigma(emptyEnigma);

    Enigma hardest = wrapper3.getHardestEnigma();
    vector<Enigma> &roomEnigmas = wrapper3.getAllEnigmas();
    roomEnigmas.pop_back();


    return 0;
}
