//
// Created by adire on 30-Jun-17.
//
#include <iostream>

#include "../EscapeRoomWrapper.h"

using namespace mtm::escaperoom;
using std::cout;
using std::endl;

int main(){
    cout << "Starting temporary Wrapper tests:" << endl;
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
}
