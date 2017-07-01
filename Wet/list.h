//
// Created by adire on 01-Jul-17.
//
#ifndef HW4_LIST_H
#define HW4_LIST_H

#include "Enigma.h"
#include "Exceptions.h"

/*--------------------------------------------------------------------------*//*
 *                          __    _      __
 *                         / /   (_)____/ /_
 *                        / /   / / ___/ __/
 *                       / /___/ (__  ) /_
 *                      /_____/_/____/\__/
 *
*//*--------------------------------------------------------------------------*/

using namespace mtm::ListExceptions;

namespace mtm {
    namespace list {

        class list {
            //declaration of class Node
            class Node {
                int data;
                Node *next;
                Node *previous;

                friend class list;
                friend class Iterator;
            public:
                Node(const int data);
                ~Node() = default;
            };

        private:
            //private fields of list
            Node *head;
            Node *last;
            int size;

        public:
            //declaration of class Iterator
            class Iterator {
                const list* list;
                Node *cur_node;
                Iterator(const list* list, Node *cur_node);

                friend class list;

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
            //public fields of list
            list();
            list(const list &list);
            ~list();
            list &operator=(const list &list);
            Iterator begin() const;
            Iterator end() const;
            void insert(const int& data, Iterator iterator);
            void insert(const int& data);
            void remove(Iterator iterator);
            bool operator==(const list& list) const;
            bool operator!=(const list& list) const;
            //TODO: >>
//            Iterator find(const Predicate& predicate) const;
//            void sort(const Compare& compare);
            int getSize() const;
        };

        list::list() : head(nullptr), last(nullptr), size(0) {}

        list::list(const list &list) : head(nullptr), last(nullptr), size(0) {
            for (Iterator it = list.begin(); it != list.end(); ++it) {
                insert(it.cur_node->data);
            }
        }

        list::~list() {
            Iterator it = begin();
            while (it != end()){
                remove(it);
                it = begin();
            }
        }

        list &list::operator=(const list &list) {
            list tmp = list;

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

        list::Iterator list::begin() const {
            return Iterator(this, head);
        }

        list::Iterator list::end() const {
            return ++Iterator(this, last);
        }

        void list::insert(const int &data, list::Iterator iterator) {
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

        void list::insert(const int &data) {
            insert(data, end());
        }

        void list::remove(Iterator iterator){
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

        int list::getSize() const{
            return size;
        }

        bool list::operator==(const list &list) const {
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

        bool list::operator!=(const list &list) const {
            return !(*this == list);
        }

/*--------------------------------------------------------------------------*//*
 *                          _   __          __
 *                         / | / /___  ____/ /__
 *                        /  |/ / __ \/ __  / _ \
 *                       / /|  / /_/ / /_/ /  __/
 *                      /_/ |_/\____/\__,_/\___/
 *
*//*--------------------------------------------------------------------------*/

        list::Node::Node(const int data) : data(data),
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

        list::Iterator::Iterator(const list *list, list::Node *cur_node) :
                                                            list(list),
                                                     cur_node(cur_node) {}

        const int &list::Iterator::operator*() const {
            if (cur_node == nullptr){
                throw ElementNotFound();
            }
            return cur_node->data;
        }

        list::Iterator &list::Iterator::operator++() {
            if(this->cur_node == nullptr){
                return *this;
            }
            cur_node = cur_node->next;
            return *this;
        }

        list::Iterator list::Iterator::operator++(int) {
            Iterator it = *this;
            ++*this;
            return it;
        }

        list::Iterator &list::Iterator::operator--() {
            cur_node = cur_node->previous;
            return *this;
        }

        list::Iterator list::Iterator::operator--(int) {
            Iterator it = *this;
            --*this;
            return it;
        }

        bool list::Iterator::operator==(const list::Iterator iterator) const {
            return list == iterator.list && cur_node == iterator.cur_node;
        }

        bool list::Iterator::operator!=(const list::Iterator iterator) const {
            return !(*this == iterator);
        }

    }
}

#endif //HW4_LIST_H
