//
// Created by Shahak on 30/06/2017.
//

#include <iostream>
#include "../List.h"
using std::string;

class MinValFirst {

public:
    MinValFirst(){}
    bool operator()(string n, string m) const{
        return n < m;
    }
};

class GreaterThan {
    string val;

public:
    GreaterThan(string v) : val(v){}
    bool operator()(const string m) const{
        return m > val;
    }
};


using namespace mtm;
using std::cout;
using std::endl;

int main() {
    cout << "Starting temporary List tests:" << endl;
    List<string> list;
    list.insert("aa");
    list.insert("bb");
    list.insert("cc");
    list.insert("ab");
    list.insert("zz");

    List<string> copy_ctor = list;

    if(list.getSize() != copy_ctor.getSize()){
        cout << "size problem with copy C'tor" << endl;
    }

    if(list != copy_ctor){
        cout << "copy c'tor problem" << endl;
    }

    List<string>::Iterator it = list.begin();
    if(*it != "aa"){
        cout << "something wrong with the iterator" << endl;
    }

    List<string> assignment_list;
    assignment_list = copy_ctor;

    if(list != copy_ctor){
        cout << "assignment problem" << endl;
    }

    assignment_list.insert("zza");
    if(list == assignment_list){
        cout << "not supposed to be equal" << endl;
    }

    list.insert("a", it);
    it = list.begin();
    if(*it != "a"){
        cout << "insert first node problem" << endl;
    }

    it++;
    it++;
    ++it;
    if(*it != "cc"){
        cout << "++ problem" << endl;
    }

    list.insert("zzz", it);
    it = list.begin();
    it++;
    it++;
    ++it;
    if(*it != "zzz"){
        cout << "insert in the middle problem" << endl;
    }

    it = list.end();
    it--;
    if (*it != "zz"){
        cout << "-- problem when iterator is at end" << endl;
    }

    it = list.end();
    list.insert("zza", it);
    it = list.end();
    it--;
    if (*it != "zza"){
        cout << "insert on end problem" << endl;
    }

    GreaterThan greaterThan1("zzb");
    it = list.find(greaterThan1);
    if (*it != "zzz"){
        cout << "problem with find" << endl;
    }

    List<string> to_be_sorted;
    to_be_sorted.insert("c");
    to_be_sorted.insert("adi");
    to_be_sorted.insert("reznik");
    to_be_sorted.insert("a");
    to_be_sorted.insert("zz");
    to_be_sorted.insert("didit");
    MinValFirst min;
    to_be_sorted.sort(min);
    it = to_be_sorted.begin();
    if (*it != "a"){
        cout << "sort problem 1" << endl;
    }
    ++it;
    if (*it != "adi"){
        cout << "sort problem 2" << endl;
    }
    ++it;
    if (*it != "c"){
        cout << "sort problem 3" << endl;
    }
    ++it;
    if (*it != "didit"){
        cout << "sort problem 4" << endl;
    }
    ++it;
    if (*it != "reznik"){
        cout << "sort problem 5" << endl;
    }
    ++it;
    if (*it != "zz"){
        cout << "sort problem 6" << endl;
    }

    return 0;
}