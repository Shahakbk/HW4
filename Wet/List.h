//
// Created by adire on 01-Jul-17.
//
#ifndef HW4_LIST_H
#define HW4_LIST_H

#include "Enigma.h"
#include "Exceptions.h"

using namespace mtm::ListExceptions;

namespace mtm {
    class List {
        class Node;
        Node *head;
        Node *last;
        int size;

    public:
        class Iterator;
        List();
        List(const List &list);
        ~List();
        List &operator=(const List &list);
        Iterator begin() const;
        Iterator end() const;
        void insert(const int& data, Iterator iterator);
        void insert(const int& data);
        void remove(Iterator iterator);
        bool operator==(const List& list) const;
        bool operator!=(const List& list) const;
        template <class Predicate>
        Iterator find(const Predicate& predicate) const;
        template <class Compare>
        void sort(const Compare& compare);
        int getSize() const;
    };

    class List::Iterator {
        const List* list;
        Node *cur_node;
        Iterator(const List* list, Node *cur_node);

        friend class List;

    public:
        Iterator(const Iterator &) = default;
        Iterator &operator=(const Iterator &) = default;
        ~Iterator() = default;
        const int &operator*() const;
        Iterator &operator++();
        Iterator operator++(int);
        Iterator &operator--();
        Iterator operator--(int);
        bool operator==(const Iterator iterator) const;
        bool operator!=(const Iterator iterator) const;
    };

    class List::Node {
        int data;
        Node *next;
        Node *previous;

        friend class List;
        friend class Iterator;
    public:
        Node(const int data);
        ~Node() = default;
    };

/*--------------------------------------------------------------------------*//*
 *                          __    _      __
 *                         / /   (_)____/ /_
 *                        / /   / / ___/ __/
 *                       / /___/ (__  ) /_
 *                      /_____/_/____/\__/
 *
*//*--------------------------------------------------------------------------*/

    List::List() : head(nullptr), last(nullptr), size(0) {}

    List::List(const List &list) : head(nullptr), last(nullptr), size(0) {
        for (Iterator it = list.begin(); it != list.end(); ++it) {
            insert(it.cur_node->data);
        }
    }

    List::~List() {
        Iterator it = begin();
        while (it != end()){
            remove(it);
            it = begin();
        }
    }

    List &List::operator=(const List &list) {
        List tmp = list;

        Iterator it_left = begin();
        while (it_left != end()){
            remove(it_left);
            it_left = begin();
        }

        for (Iterator it = list.begin(); it != list.end(); ++it) {
            insert(it.cur_node->data);
        }
        return *this;
    }

    List::Iterator List::begin() const {
        return Iterator(this, head);
    }

    List::Iterator List::end() const {
        return ++Iterator(this, last);
    }

    void List::insert(const int &data, List::Iterator iterator) {
        if(iterator.list != this){
            throw ElementNotFound();
        }
        Node *new_node = new Node(data);
        size++;
        if(size == 1){
            head = new_node;
            last = new_node;
            return;
        }
        Node *next_node = iterator.cur_node;
        if (next_node == nullptr) {
            new_node->previous = last;
            new_node->next = last->next;
            last->next = new_node;
            last = new_node;
            return;
        }
        Node *prev_node = iterator.cur_node->previous;
        if (prev_node == nullptr) {
            new_node->next = head;
            new_node->previous = nullptr;
            head->previous = new_node;
            head = new_node;
            return;
        }
        new_node->next = next_node;
        new_node->previous = prev_node;
        next_node->previous = new_node;
        prev_node->next = new_node;
    }

    void List::insert(const int &data) {
        insert(data, end());
    }

    void List::remove(Iterator iterator){
        if(iterator.list != this || iterator == end() || size == 0){
            throw ElementNotFound();
        }
        size--;
        if(size == 0){
            delete(iterator.cur_node);
            head = nullptr;
            last = nullptr;
            return;
        }
        Node *prev_node = iterator.cur_node->previous;
        Node *next_node = iterator.cur_node->next;

        if (iterator.cur_node == head) {
            next_node->previous = nullptr;
            delete(iterator.cur_node);
            head = next_node;
            return;
        }
        if (iterator.cur_node == last) {
            prev_node->next = nullptr;
            delete(iterator.cur_node);
            last = prev_node;
            return;
        }
        next_node->previous = prev_node;
        prev_node->next = next_node;
        delete(iterator.cur_node);
    }

    int List::getSize() const{
        return size;
    }

    bool List::operator==(const List &list) const {
        if (size != list.size){
            return false;
        }

        Iterator it_left = begin();
        Iterator it_right = list.begin();

        for (; it_left != end(); ++it_left, ++it_right) {
            if (it_left.cur_node->data != it_right.cur_node->data){
                return false;
            }
        }
        return true;
    }

    bool List::operator!=(const List &list) const {
        return !(*this == list);
    }


    template <class Predicate>
    List::Iterator List::find(const Predicate& predicate) const{
        Iterator it = this->begin();
        for( ; it != this->end(); ++it){
            if(predicate(*it) == true){
                break;
            }
        }
        return it;
    }

    template <class Compare>
    void List::sort(const Compare& compare) {
        for (Iterator i = begin(); i != end() ; ++i) {
            Iterator j = i;
            for (++j; j != end(); ++j) {
                if (!compare(i.cur_node->data, j.cur_node->data)){
                    int tmp_data = i.cur_node->data;
                    i.cur_node->data = j.cur_node->data;
                    j.cur_node->data = tmp_data;
                }
            }
        }
    }

/*--------------------------------------------------------------------------*//*
 *                          _   __          __
 *                         / | / /___  ____/ /__
 *                        /  |/ / __ \/ __  / _ \
 *                       / /|  / /_/ / /_/ /  __/
 *                      /_/ |_/\____/\__,_/\___/
 *
*//*--------------------------------------------------------------------------*/

    List::Node::Node(const int data) : data(data),
                                       next(nullptr),
                                       previous(nullptr) {}

/*--------------------------------------------------------------------------*//*
 *                       ____ __                   __
 *                      /  _// /____  _________  _/ /____  _____
 *                      / / / __/ _ \/ ___/ __ \/ __/ __ \/ ___/
 *                    _/ / / /_/  __/ /  / /_/ / /_/ /_/ / /
 *                   /___/ \__/\___/_/   \__,_/\__/\____/_/
 *
*//*--------------------------------------------------------------------------*/

    List::Iterator::Iterator(const List *list, List::Node *cur_node) :
                                                list(list),
                                                cur_node(cur_node) {}

    const int &List::Iterator::operator*() const {
        if (cur_node == nullptr){
            throw ElementNotFound();
        }
        return cur_node->data;
    }

    List::Iterator &List::Iterator::operator++() {
        if(this->cur_node == nullptr){
            return *this;
        }
        cur_node = cur_node->next;
        return *this;
    }

    List::Iterator List::Iterator::operator++(int) {
        Iterator it = *this;
        ++*this;
        return it;
    }

    List::Iterator &List::Iterator::operator--() {
        if(cur_node == nullptr){
            cur_node = list->last;
            return *this;
        }
        cur_node = cur_node->previous;
        return *this;
    }

    List::Iterator List::Iterator::operator--(int) {
        Iterator it = *this;
        --*this;
        return it;
    }

    bool List::Iterator::operator==(const List::Iterator iterator) const {
        return list == iterator.list && cur_node == iterator.cur_node;
    }

    bool List::Iterator::operator!=(const List::Iterator iterator) const {
        return !(*this == iterator);
    }

}

#endif //HW4_LIST_H
