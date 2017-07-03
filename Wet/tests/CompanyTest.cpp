//
// Created by Shahak on 03/07/2017.
//

#include <iostream>

#include "../EscapeRoomWrapper.h"
#include "../Company.h"
#include "../Exceptions.h"

using namespace mtm::escaperoom;
using std::cout;
using std::endl;

int main(){
    cout << "Starting temporary Company tests:" << endl;

    set<string> elements1;
    elements1.insert("element1");
    elements1.insert("element2");
    elements1.insert("element3");
    elements1.insert("element3");
    set<string> elements2;
    elements2.insert("element1");
    elements2.insert("element2");
    set<string> elements3;
    Enigma sameEnigma1("MyFirstEnigma", EASY_ENIGMA, 3, elements1);
    Enigma sameEnigma2("MyFirstEnigma", EASY_ENIGMA, 2, elements2);
    Enigma diffEnigma1("MySecondEnigma", MEDIUM_ENIGMA, 2, elements2);
    Enigma diffEnigma2("MyThirdEnigma", MEDIUM_ENIGMA, 0, elements3);
    Enigma emptyEnigma("EmptyEnigma", HARD_ENIGMA);
    sameEnigma1.addElement("First Element");
    sameEnigma1.addElement("Second Element");
    sameEnigma1.addElement("Third Element");
    sameEnigma2.addElement("First Element");
    sameEnigma2.addElement("Second Element");
    diffEnigma1.addElement("First Element");
    diffEnigma1.addElement("Second Element");

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

    wrapper3.addEnigma(sameEnigma1);
    wrapper3.addEnigma(sameEnigma2);
    wrapper3.addEnigma(diffEnigma1);
    wrapper3.addEnigma(diffEnigma2);
    wrapper3.addEnigma(emptyEnigma);

    Enigma hardest = wrapper3.getHardestEnigma();
    vector<Enigma> &roomEnigmas = wrapper3.getAllEnigmas();
    roomEnigmas.pop_back();

    Company company("First Company", "04-829-20-53");
    company.createKidsRoom((char*)"Kids1", 30, 1, 5, 5);
    company.createScaryRoom((char*)"Scary1", 40, 2, 6, 21, 0);

    set<EscapeRoomWrapper*> onlyKids = company.getAllRoomsByType(KIDS_ROOM);

    cout << "End." << endl;
    return 0;
}
