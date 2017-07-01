//
// Created by Shahak on 30/06/2017.
//

#include <iostream>
#include "../List.h"

class MinValFirst {

public:
    MinValFirst(){}
    bool operator()(int n, int m) const{
        return n < m;
    }
};

class GreaterThan {
    int val;

public:
    GreaterThan(int v) : val(v){}
    bool operator()(const int m) const{
        return m > val;
    }
};


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

    GreaterThan greaterThan1(9);
    it = list.find(greaterThan1);
    if (*it != 10){
        cout << "problem with find" << endl;
    }

    List to_be_sorted;
    to_be_sorted.insert(7);
    to_be_sorted.insert(2);
    to_be_sorted.insert(9);
    to_be_sorted.insert(-1);
    to_be_sorted.insert(5);
    to_be_sorted.insert(3);
    MinValFirst min;
    to_be_sorted.sort(min);
    it = to_be_sorted.begin();
    if (*it != -1){
        cout << "sort problem 1" << endl;
    }
    ++it;
    if (*it != 2){
        cout << "sort problem 2" << endl;
    }
    ++it;
    if (*it != 3){
        cout << "sort problem 3" << endl;
    }
    ++it;
    if (*it != 5){
        cout << "sort problem 4" << endl;
    }
    ++it;
    if (*it != 7){
        cout << "sort problem 5" << endl;
    }
    ++it;
    if (*it != 9){
        cout << "sort problem 6" << endl;
    }

    return 0;
}