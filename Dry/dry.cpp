#ifndef HW4_DRY_H
#define HW4_DRY_H

#include <list>
#include <set>

using std::list;
using std::set;

/**
 * receives 2 generic sets and a boolean term and sorts by the rules
 * @tparam Iterator - a template iterator
 * @tparam Value - the value the template container holds
 * @tparam isTerm - the boolean function to sort by
 */
template<typename Iterator, typename Value, typename isTerm>

/**
 * @param begin_1 - iterator pointing to the beginning of the first container
 * @param begin_2 - iterator pointing to the beginning of the second container
 * @param end_1 - iterator pointing to after the last value of the container
 * @param end_2 - iterator pointing to after the last value of the container
 * @param cmp - a boolean term to compare between the containers by
 * @param newList - the list to return, in order for the func to recognize
 *                  the template Value
 * @return - the new sorted list
 */
list<Value> mergeContainers(Iterator begin_1, Iterator begin_2,
                             Iterator end_1, Iterator end_2,
                             const isTerm &cmp, list<Value> &newList) {
    while (begin_1 != end_1 && begin_2 != end_2) {
        if (cmp(*begin_1, *begin_2)) {
            newList.push_back(*begin_2);
            ++begin_2;
            continue;
        }
        newList.push_back(*begin_1);
        ++begin_1;
    }

    while (begin_1 != end_1) {
        newList.push_back(*begin_1);
        ++begin_1;
    }

    while  (begin_2 != end_2) {
        newList.push_back(*begin_2);
        ++begin_2;
    }

    return newList;
}

class sortNumbers {

public:
    bool operator()(int num_1, int num_2) const {
        return num_1 >= num_2;
    }
};

int main() {
    set<int> set1, set2;
    set1.insert(1); set1.insert(3); set1.insert(5);
    set1.insert(6); set1.insert(9); set2.insert(2);
    set2.insert(4); set2.insert(7); set2.insert(8);
    // set1 and set2 are 2 sorted containers of integers. when sending them to
    // the function, the result will be a sorted list of the united set

    sortNumbers cmp;
    list<int> sortedList;

    mergeContainers(set1.begin(), set2.begin(), set1.end(), set2.end(), cmp,
                    sortedList);
    // the new sorted list will be inserted to sortedList
    return 0;
}


#endif //HW4_DRY_H
