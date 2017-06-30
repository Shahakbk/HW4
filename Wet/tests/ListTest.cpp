//
// Created by Shahak on 30/06/2017.
//

#include <iostream>

#include "../list.h"
#include "../Enigma.h"

using namespace mtm::escaperoom;
using namespace mtm::list;


int main() {
    std::cout << "Starting temporary List tests:" << std::endl;
    Enigma enigma1("MyFirstEnigma", EASY_ENIGMA, 2);
    Enigma enigma2("MySecondEnigma", EASY_ENIGMA, 2);
    Enigma enigma3("MyThirdEnigma", MEDIUM_ENIGMA, 1);
    Enigma enigma4("MyFourthEnigma", MEDIUM_ENIGMA, 2);
    List list;
    list.pushLast(enigma3);
    list.pushFirst(enigma2);
    list.pushLast(enigma4);
    list.pushFirst(enigma1);




    return 0;
}