//
// Created by Shahak on 29/06/2017.
//

#ifndef HW4_LIST_H
#define HW4_LIST_H

#include "Enigma.h"

namespace mtm{
namespace list{


/*--------------------------------------------------------------------------*//*
 *                          _   __          __
 *                         / | / /___  ____/ /__
 *                        /  |/ / __ \/ __  / _ \
 *                       / /|  / /_/ / /_/ /  __/
 *                      /_/ |_/\____/\__,_/\___/
 *
*//*--------------------------------------------------------------------------*/


using mtm::escaperoom::Enigma;

//template <class T>
class Node {
public:
    //Node(const T data);
    Node(const Enigma data); // Node creator
//    Node(const Node &toCopy); // Node copy constructor
    ~Node() = default; // Node destructor
    //TODO make sure it's ok ^

private:

    //  T data; // the type the list will hold
    Enigma data;
    Node *next; // the next node in the list
    Node *previous; // the previous node in the list


    //friend class List<T>; // so the list can access the nodes
    friend class List;
    friend class Iterator; // so the iterator can access the nodes
};

// declaring constructor for Node with initialization list
Node::Node(const Enigma data) :
        data(data),
        next(nullptr),
        previous(nullptr) {}

//TODO probably there's no need for this func
/*
// copy constructor for node
Node::Node(const Node &toCopy) :
        data(copyNode(toCopy)),
        previous(nullptr),
        next(nullptr) {

    //TODO incomplete

}
*/

/*--------------------------------------------------------------------------*//*
 *                          __    _      __
 *                         / /   (_)____/ /_
 *                        / /   / / ___/ __/
 *                       / /___/ (__  ) /_
 *                      /_____/_/____/\__/
 *
*//*--------------------------------------------------------------------------*/

//template <class T>
class List {
public:
    class Iterator; // internal iterator of the list

    List(); // creator for the list
    List(const List &list); // copy constructor
    //List(const List<T> &list); // copy constructor
    ~List(); // list destructor
    List &operator=(const List &list); // assignment operator
    //List<T> &operator=(const List<T> &list); // assignment operator

    Iterator begin() const; // get an iterator to the beginning
    Iterator end() const; // get an iterator to the end

    //void pushLast(const T &t);
    void pushLast(const Enigma &enigma);
    //void pushFirst(const T &t);
    void pushFirst(const Enigma &enigma);

private:
//TODO protected?
    Node *head; // the head of the list
    Node *last_node; // the last node in the list
};


// empty creator for the list
//template <class T>
//List<T>::List():
List::List() :
        head(nullptr),
        last_node(nullptr) {}
//TODO create iterator??

// copy constructor for the list
//template <class T>
//List<T>::List(const List &list):
List::List(const List &list) :
        head(nullptr),
        last_node(nullptr) {

    for (Node *node_iterator = list.head;
         node_iterator != nullptr;
         node_iterator = node_iterator->next) {
        pushLast(node_iterator->data);
    }
}

List::~List() {
    Node *node_iterator = head;
    while (nullptr != node_iterator) {
        Node *tmp_node = node_iterator->next;
        delete(node_iterator);
        node_iterator = tmp_node;
    }
    //TODO delete iterator??
}

//void List<T>::pushFirst(const T &t) {
void List::pushFirst(const Enigma &enigma) {

    Node *new_node = new Node(enigma);
    head->previous = new_node;
    new_node->next = head;
    head = new_node;
}

void List::pushLast(const Enigma &enigma) {

    if (nullptr == head) {
        pushFirst(enigma);
        return;
    }
    Node *new_node = new Node(enigma);
    last_node->next = new_node;
    new_node->previous = last_node;
    last_node = new_node;
    last_node->next = nullptr;
}

/*--------------------------------------------------------------------------*//*
 *                       ____ __                   __
 *                      /  _// /____  _________  _/ /____  _____
 *                      / / / __/ _ \/ ___/ __ \/ __/ __ \/ ___/
 *                    _/ / / /_/  __/ /  / /_/ / /_/ /_/ / /
 *                   /___/ \__/\___/_/   \__,_/\__/\____/_/
 *
*//*--------------------------------------------------------------------------*/




//class List<Enigma>::Iterator {
class List::Iterator {
    const List list;
    int index;

    Iterator(const List list, int index);

    friend class List;

public:
    const Enigma &operator*() const;

    Iterator &operator++(); // ++Iterator
    Iterator operator++(int); // Iterator++
    Iterator &operator--(); //--Iterator
    Iterator operator--(int); //Iterator--
    bool operator==(const Iterator iterator) const;

    bool operator!=(const Iterator iterator) const;

    Iterator(const Iterator &) = default;

    Iterator &operator=(const Iterator &) = default;

};

/*
template <class T>
class List<T>:: Iterator {
    const List<T>* list; // the list the iterator points to
    int index; // the index of the iterator in the list
    Iterator(const List<T>* list, int index); // private creator, so only the
                                              // list can create a list::iterator
    friend class List<T>; // allow the list access to the iterator

public:
    const T& operator*() const;
    Iterator &operator++(); // ++Iterator
    Iterator operator++(int); // Iterator++
    Iterator &operator--(); //--Iterator
    Iterator operator--(int); //Iterator--
    bool operator==(const Iterator& iterator) const;
    bool operator!=(const Iterator& iterator) const;

    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

};
*/



} // end of namespace eascaperoom
} // end of namespace list

#endif //HW4_LIST_H
