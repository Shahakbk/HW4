//
// Created by adire on 01-Jul-17.
//
#ifndef HW4_LIST_H
#define HW4_LIST_H

#include "Enigma.h"
#include "Exceptions.h"

using namespace mtm::ListExceptions;

namespace mtm {

    template <class T>
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
        List<T> &operator=(const List<T> &list);
        Iterator begin() const;
        Iterator end() const;
        void insert(const T& data, Iterator iterator);
        void insert(const T& data);
        void remove(List::Iterator iterator);
        bool operator==(const List<T>& list) const;
        bool operator!=(const List<T>& list) const;
        template <class Predicate>
        List::Iterator find(const Predicate& predicate) const;
        template <class Compare>
        void sort(const Compare& compare);
        int getSize() const;
    };

    template <class T>
    class List<T>::Iterator {
        const List<T>* list;
        Node *cur_node;
        Iterator(const List<T>* list, Node *cur_node);

        friend class List<T>;

    public:
        Iterator(const Iterator &) = default;
        Iterator &operator=(const Iterator &) = default;
        ~Iterator() = default;
        const T &operator*() const;
        Iterator &operator++();
        Iterator operator++(int);
        Iterator &operator--();
        Iterator operator--(int);
        bool operator==(const List<T>::Iterator& iterator) const;
        bool operator!=(const List<T>::Iterator& iterator) const;
    };

    template <class T>
    class List<T>::Node {
        T data;
        Node *next;
        Node *previous;

        friend class List<T>;
        friend class List<T>::Iterator;
    public:
        Node(const T data);
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

    template <class T>
    List<T>::List() : head(nullptr), last(nullptr), size(0) {}

    template <class T>
    List<T>::List(const List<T> &list) : head(nullptr), last(nullptr), size(0) {
        for (List<T>::Iterator it = list.begin(); it != list.end(); ++it) {
            insert(it.cur_node->data);
        }
    }

    template <class T>
    List<T>::~List() {
        Iterator it = begin();
        while (it != end()){
            remove(it);
            it = begin();
        }
    }

    template <class T>
    List<T> &List<T>::operator=(const List<T> &list) {
        List<T> tmp = list;

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

    template <class T>
    typename Iterator List<T>::begin() const {
        return Iterator(this, head);
    }

    template <class T>
    typename Iterator List<T>::end() const {
        return ++Iterator(this, last);
    }

    template <class T>
    void List<T>::insert(const T &data, Iterator iterator) {
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

    template <class T>
    void List<T>::insert(const T &data) {
        insert(data, end());
    }

    template <class T>
    void List<T>::remove(List::Iterator iterator){
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
        List<T>::Node *prev_node = iterator.cur_node->previous;
        List<T>::Node *next_node = iterator.cur_node->next;

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

    template <class T>
    int List<T>::getSize() const{
        return size;
    }

    template <class T>
    bool List<T>::operator==(const List<T> &list) const {
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

    template <class T>
    bool List<T>::operator!=(const List<T> &list) const {
        return !(*this == list);
    }


    template <class T>
    template <class Predicate>
    typename List<T>::Iterator List<T>::find(const Predicate& predicate) const {
        Iterator it = this->begin();
        for( ; it != this->end(); ++it){
            if(predicate(*it) == true){
                break;
            }
        }
        return it;
    }

    //TODO: assuming the T has assignment func might be a problem
    template <class Compare, class T>
    void List<T>::sort(const Compare& compare) {
        for (Iterator i = begin(); i != end() ; ++i) {
            Iterator j = i;
            for (++j; j != end(); ++j) {
                if (!compare(i.cur_node->data, j.cur_node->data)){
                    T tmp_data = i.cur_node->data;
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

    template <class T>
    List<T>::Node::Node(const T data) : data(data), next(nullptr),
                                        previous(nullptr) {}

/*--------------------------------------------------------------------------*//*
 *                       ____ __                   __
 *                      /  _// /____  _________  _/ /____  _____
 *                      / / / __/ _ \/ ___/ __ \/ __/ __ \/ ___/
 *                    _/ / / /_/  __/ /  / /_/ / /_/ /_/ / /
 *                   /___/ \__/\___/_/   \__,_/\__/\____/_/
 *
*//*--------------------------------------------------------------------------*/

    template <class T>
    List<T>::Iterator::Iterator(const List<T>* list, Node *cur_node) :
                                                list(list),
                                                cur_node(cur_node) {}

    template <class T>
    const T& List<T>::Iterator::operator*() const {
        if (cur_node == nullptr){
            throw ElementNotFound();
        }
        return cur_node->data;
    }

    template <class T>
    typename List<T>::Iterator& List<T>::Iterator::operator++() {
        if(this->cur_node == nullptr){
            return *this;
        }
        cur_node = cur_node->next;
        return *this;
    }

    template <class T>
    typename List<T>::Iterator List<T>::Iterator::operator++(int) {
        Iterator it = *this;
        ++*this;
        return it;
    }

    template <class T>
    typename List<T>::Iterator& List<T>::Iterator::operator--() {
        if(cur_node == nullptr){
            cur_node = list->last;
            return *this;
        }
        cur_node = cur_node->previous;
        return *this;
    }

    template <class T>
    typename List<T>::Iterator List<T>::Iterator::operator--(int) {
        Iterator it = *this;
        --*this;
        return it;
    }

    template <class T>
    bool List<T>::Iterator::operator==(const List<T>::Iterator& iterator) const{
        return (list == iterator.list && cur_node == iterator.cur_node);
    }

    template <class T>
    bool List::Iterator::operator!=(const List<T>::Iterator& iterator) const {
        return !(*this == iterator);
    }

}

#endif //HW4_LIST_H
