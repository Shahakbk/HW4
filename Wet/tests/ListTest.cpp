//
// Created by Shahak on 30/06/2017.
//

#include <iostream>
#include "../List.h"

using namespace mtm;
using std::cout;
using std::endl;

int main() {
    cout << "Starting temporary List tests:" << endl;
    List list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);

    List copy_ctor = list;

    if(list.getSize() != copy_ctor.getSize()){
        cout << "size problem with copy C'tor" << endl;
    }

    if(list != copy_ctor){
        cout << "copy c'tor problem" << endl;
    }

    List::Iterator it = list.begin();
    if(*it != 1){
        cout << "something wrong with the iterator" << endl;
    }

    List assignment_list;
    assignment_list = copy_ctor;

    if(list != copy_ctor){
        cout << "assignment problem" << endl;
    }

    assignment_list.insert(6);
    if(list == assignment_list){
        cout << "not supposed to be equal" << endl;
    }

    list.insert(0, it);
    it = list.begin();
    if(*it != 0){
        cout << "insert first node problem" << endl;
    }

    it++;
    it++;
    ++it;
    if(*it != 3){
        cout << "++ problem" << endl;
    }

    list.insert(10, it);
    it = list.begin();
    it++;
    it++;
    ++it;
    if(*it != 10){
        cout << "insert in the middle problem" << endl;
    }

/*    it = list.end();
    if (*it != nullptr){
        cout << "list end problem" << endl;
    }*/

    it = list.end();
    it--;
    if (*it != 5){
        cout << "-- problem when iterator is at end" << endl;
    }

    it = list.end();
    list.insert(6, it);
    it = list.end();
    it--;
    if (*it != 6){
        cout << "insert on end problem" << endl;
    }

    return 0;
}