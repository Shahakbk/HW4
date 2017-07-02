//
// Created by Shahak on 30/06/2017.
//

#include <iostream>
#include "../List.h"
#include "mtmtest.h"

using namespace mtm;
using std::string;
using std::cout;
using std::endl;

/**
 * ARRAY CLASS
 */

class Array {
    int size;
    int* arr;
public:
    explicit Array(const int size = 10);
    Array(const Array& arr);
    ~Array();
    int &operator[](const int& idx) const ;
    Array &operator=(const int& array) = delete ;
    bool operator<(const Array arr_right) const ;
    bool operator==(const Array arr_right) const;
    void replace(const int& idx, const int& num);
};

Array::Array(const int size) : size(size), arr(new int[size]) {
    for (int i = 0; i < size; ++i) {
        arr[i] = i;
    }
}

Array::Array(const Array &array) : size(array.size), arr(new int[array.size]){
    for (int i = 0; i < size; ++i) {
        arr[i] = array.arr[i];
    }
}

Array::~Array() {
    delete[] arr;
}

int &Array::operator[](const int &idx) const {
    return arr[idx];
}

void Array::replace(const int &idx, const int& num) {
    arr[idx] = num;
}

bool Array::operator<(const Array arr_right) const {
    return size < arr_right.size;
}

bool Array::operator==(const Array arr_right) const {
    return size == arr_right.size;
}

/**
 * PREDICATE CLASS
 */

template <class T>
class MinValFirst {

public:
    MinValFirst(){}
    bool operator()(T n, T m) const{
        return n < m;
    }
};

/**
 * COMPARE CLASS
 */

template <class T>
class GreaterThan {
    T val;

public:
    GreaterThan(T v) : val(v){}
    bool operator()(const T m) const{
        return m > val;
    }
};

void testListCtor() {
    //test int type list
    List<int> intList;
    ASSERT_EQUALS(0, intList.getSize());
    ASSERT_EQUALS(intList.end(), intList.begin()); //if list is empty
    // iterators should be the same

    //test complex type list
    List<Array> arrList;
    ASSERT_EQUALS(0, intList.getSize());
    ASSERT_EQUALS(intList.end(), intList.begin());
}

void testListCopyCtor() {
    //test int type list
    List<int> intList;
    intList.insert(1);
    intList.insert(2);
    intList.insert(3);
    intList.insert(4);
    intList.insert(5);
    List<int> copiedIntList = intList;
    //test that the size of the lists is equal
    ASSERT_EQUALS(intList.getSize(), copiedIntList.getSize());
    List<int>::Iterator intIt = intList.begin();
    List<int>::Iterator copiedIntIt = copiedIntList.begin();
    //test that the iterators are not on the same list
    ASSERT_NOT_EQUAL(intIt, copiedIntIt);
    //test if all the elements are equal and in the same order
    ASSERT_EQUALS(*intIt, *copiedIntIt);
    intIt++;
    copiedIntIt++;
    ASSERT_EQUALS(*intIt, *copiedIntIt);
    intIt++;
    copiedIntIt++;
    ASSERT_EQUALS(*intIt, *copiedIntIt);
    intIt++;
    copiedIntIt++;
    ASSERT_EQUALS(*intIt, *copiedIntIt);
    intIt++;
    copiedIntIt++;
    ASSERT_EQUALS(*intIt, *copiedIntIt);

    //test if the element has been removed from both lists
    copiedIntIt = copiedIntList.begin();
    intIt = intList.begin();
    intList.remove(intIt);
    intIt = intList.begin();
    ASSERT_NOT_EQUAL(*intIt, *copiedIntIt);
}

void testListDtor() {
    //test destruction of array type list with allocations in the type
    List<Array> arrList;
    Array arr1(5);
    Array arr2(20);
    Array arr3;
    arrList.insert(arr1);
    arrList.insert(arr2);
    arrList.insert(arr3);
}

void testListAssignment() {
    //test the assignment of array type list
    List<Array> arrList;
    Array arr1(5);
    Array arr2(20);
    Array arr3;
    arr2.replace(0, 10);
    arrList.insert(arr1);
    arrList.insert(arr2);
    arrList.insert(arr3);
    List<Array> assignedArrList;
    assignedArrList = arrList;
    List<Array>::Iterator it = assignedArrList.begin();
    Array testResult = *it;
    ASSERT_EQUALS(arr1[0], testResult[0]);
    ASSERT_EQUALS(arr1[1], testResult[1]);
    ASSERT_EQUALS(arr1[4], testResult[4]);

    //test second element
    it++;
    Array testResult2 = *it;
    ASSERT_EQUALS(arr2[15], testResult2[15]);

}

void testListIteratorBegin() {
    List<int> list;
    //test when list is empty begin is equal to the end
    List<int>::Iterator itBegin = list.begin();
    List<int>::Iterator itEnd = list.end();
    ASSERT_EQUALS(itEnd, itBegin);

    //test begin when 1 element
    list.insert(1);
    List<int>::Iterator it1 = list.begin();
    ASSERT_EQUALS(1, *it1);

    //test begin when several elements
    list.insert(2);
    list.insert(3);
    list.insert(4);
    List<int>::Iterator it2 = list.begin();
    ASSERT_EQUALS(1, *it2);

}

void testListIteratorEnd() {
    List<int> list;
    //test begin when 1 element
    list.insert(1);
    List<int>::Iterator it1 = list.end();
    it1--;
    ASSERT_EQUALS(1, *it1);

    //test begin when several elements
    list.insert(2);
    list.insert(3);
    list.insert(4);
    List<int>::Iterator it2 = list.end();
    it2--;
    ASSERT_EQUALS(4, *it2);

}

void testListInsert() {
    List<int> list;
    List<int>::Iterator it = list.begin();
    //test insert to an empty list of the list
    list.insert(1, it);
    it = list.begin();
    ASSERT_EQUALS(1, *it);
    //test insert to the start of the list
    it = list.begin();
    list.insert(0, it);
    it = list.begin();
    ASSERT_EQUALS(0, *it);
    //test insert to the middle of the list
    //also testing insert without iterator
    list.insert(3);
    list.insert(4);
    list.insert(5);
    it = list.begin();
    it++;
    it++;
    it++;
    list.insert(1, it);
    it = list.begin();
    it++;
    it++;
    it++;
    ASSERT_EQUALS(1, *it);
    //test insert to the end of the list
    it = list.end();
    list.insert(6, it);
    it = list.end();
    --it;
    ASSERT_EQUALS(6, *it);
    //test exception when iterator does not belong to the list
    List<int> list2;
    list2.insert(10);
    list2.insert(11);
    list2.insert(12);

    //not the same list
    it = list.begin();
    it++;

    ASSERT_THROWS(ElementNotFound, list2.insert(13, it));

}

void testListRemove() {
    List<Array> arrList;
    //test exception when trying to remove from empty list
    List<Array>::Iterator it = arrList.begin();
    ASSERT_THROWS(ElementNotFound, arrList.remove(it));

    Array arr1(5);
    Array arr2(20);
    Array arr3;
    Array arr4(12);
    Array arr5(18);
    arrList.insert(arr1);
    arrList.insert(arr2);
    arrList.insert(arr3);
    arrList.insert(arr4);
    arrList.insert(arr5);
    //test exception when iterator is not on an element
    it = arrList.end();
    ASSERT_THROWS(ElementNotFound, arrList.remove(it));

    //test exception when iterator does not belong to the list
    List<Array> arrList2;
    arrList.insert(arr1);
    arrList.insert(arr2);
    arrList.insert(arr3);
    arrList.insert(arr4);
    arrList.insert(arr5);

    //not the same list
    it = arrList.begin();

    ASSERT_THROWS(ElementNotFound, arrList2.remove(it));

    List<int> intList;
    intList.insert(0);
    intList.insert(1);
    intList.insert(2);
    intList.insert(3);
    intList.insert(4);

    //test remove first element
    List<int>::Iterator intIt = intList.begin();
    intList.remove(intIt);
    intIt = intList.begin();
    ASSERT_EQUALS(1, *intIt);

    //test remove middle element
    intIt = intList.begin();
    intIt++;
    intList.remove(intIt);
    intIt = intList.begin();
    intIt++;
    ASSERT_EQUALS(3, *intIt);

    //test remove last element
    intIt = intList.end();
    intIt--;
    intList.remove(intIt);
    intIt = intList.end();
    intIt--;
    ASSERT_EQUALS(3, *intIt);

}

void testListOperatorEqual() {
    List<int> intList;
    intList.insert(0);
    intList.insert(1);
    intList.insert(2);

    List<int> intList2;
    intList2.insert(0);
    intList2.insert(1);
    intList2.insert(2);

    //test same list equals
    ASSERT_TRUE(intList == intList);
    //test diff lists with same elements and order
    ASSERT_TRUE(intList == intList2);
    //test false when on list has more elements than the other
    intList2.insert(3);
    ASSERT_FALSE(intList == intList2);

    //test same elements diff order fails
    List<int> intList3;
    intList3.insert(0);
    intList3.insert(1);
    intList3.insert(2);

    List<int> intList4;
    intList4.insert(0);
    intList4.insert(2);
    intList4.insert(1);
    ASSERT_FALSE(intList3 == intList4);

}

void testListOperatorNotEqual() {
    //test opposite results than equal
    List<int> intList;
    intList.insert(0);
    intList.insert(1);
    intList.insert(2);

    List<int> intList2;
    intList2.insert(0);
    intList2.insert(1);
    intList2.insert(2);

    ASSERT_FALSE(intList != intList);
    ASSERT_FALSE(intList != intList2);
    intList2.insert(3);
    ASSERT_TRUE(intList != intList2);

    List<int> intList3;
    intList3.insert(0);
    intList3.insert(1);
    intList3.insert(2);

    List<int> intList4;
    intList4.insert(0);
    intList4.insert(2);
    intList4.insert(1);
    ASSERT_TRUE(intList3 != intList4);
}

void testListFind() {
    List<int> intList;
    intList.insert(0);
    intList.insert(1);
    intList.insert(2);
    intList.insert(11);
    intList.insert(4);
    intList.insert(5);

    //test find success
    GreaterThan<int> greaterThan1(10);
    List<int>::Iterator resultIt = intList.find(greaterThan1);
    ASSERT_EQUALS(11, *resultIt);

    //test find first out of several matches
    GreaterThan<int> greaterThan2(1);
    resultIt = intList.find(greaterThan2);
    ASSERT_EQUALS(2, *resultIt);

    //test find when no match
    GreaterThan<int> greaterThan3(11);
    resultIt = intList.find(greaterThan3);
    List<int>::Iterator endIt = intList.end();
    ASSERT_EQUALS(endIt, resultIt);
}

void testListSort() {
    //test sort on int type list
    List<int> intList;
    intList.insert(5);
    intList.insert(4);
    intList.insert(2);
    intList.insert(3);
    intList.insert(4);

    MinValFirst<int> intMinValFirst;
    intList.sort(intMinValFirst);
    List<int>::Iterator intIt = intList.begin();
    ASSERT_EQUALS(2, *intIt);
    intIt++;
    ASSERT_EQUALS(3, *intIt);
    intIt++;
    ASSERT_EQUALS(4, *intIt);
    intIt++;
    ASSERT_EQUALS(4, *intIt);
    intIt++;
    ASSERT_EQUALS(5, *intIt);

    //test sort on string type list
    List<string> stringList;
    stringList.insert("shahak");
    stringList.insert("reznik");
    stringList.insert("adi");
    stringList.insert("didit");
    stringList.insert("ben");

    MinValFirst<string> stringMinValFirst;
    stringList.sort(stringMinValFirst);
    List<string>::Iterator stringIt = stringList.begin();
    ASSERT_EQUALS("adi", *stringIt);
    stringIt++;
    ASSERT_EQUALS("ben", *stringIt);
    stringIt++;
    ASSERT_EQUALS("didit", *stringIt);
    stringIt++;
    ASSERT_EQUALS("reznik", *stringIt);
    stringIt++;
    ASSERT_EQUALS("shahak", *stringIt);

    List<Array> arrList;
    Array arr1(18);
    Array arr2(20);
    Array arr3;
    Array arr4(12);
    Array arr5(11);
    arrList.insert(arr1);
    arrList.insert(arr2);
    arrList.insert(arr3);
    arrList.insert(arr4);
    arrList.insert(arr5);

    MinValFirst<Array> arrayMinValFirst;
    arrList.sort(arrayMinValFirst);
    List<Array>::Iterator arrIt = arrList.begin();
    ASSERT_EQUALS(arr3, *arrIt);
    arrIt++;
    ASSERT_EQUALS(arr5, *arrIt);
    arrIt++;
    ASSERT_EQUALS(arr4, *arrIt);
    arrIt++;
    ASSERT_EQUALS(arr1, *arrIt);
    arrIt++;
    ASSERT_EQUALS(arr2, *arrIt);

}

void testListGetSize() {
    List<int> intList;

    //test get size when empty
    ASSERT_EQUALS(0, intList.getSize());
    //test get size when list has elements
    intList.insert(0);
    intList.insert(1);
    intList.insert(2);
    ASSERT_EQUALS(3, intList.getSize());
    //test get size after remove element
    List<int>::Iterator it = intList.begin();
    intList.remove(it);
    ASSERT_EQUALS(2, intList.getSize());
}

void testIteratorCopyCtor() {
    List<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);

    List<int>::Iterator it = list.begin();
    it++;
    List<int>::Iterator copiedIt = it;
    ASSERT_EQUALS(2, *copiedIt);
}

void testIteratorAssignment() {
    List<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);

    List<int>::Iterator it = list.begin();
    it++;
    List<int>::Iterator assignedIt = list.begin();
    assignedIt = it;
    ASSERT_EQUALS(2, *assignedIt);
}

void testIteratorDereference() {
    List<int> list;
    list.insert(1);

    //test success of dereference
    List<int>::Iterator it = list.begin();
    ASSERT_EQUALS(1, *it);

    //test exception when iterator is on the end of the list
    it = list.end();
    ASSERT_THROWS(ElementNotFound, *it);

}

void testIteratorInc() {
    List<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);

    List<int>::Iterator it = list.begin();
    //test it++
    ASSERT_EQUALS(*it, *(it++));
    ASSERT_EQUALS(2, *it);

    //test ++it
    it = list.begin();
    List<int>::Iterator it2 = list.begin();
    it2++;
    ASSERT_EQUALS(it2, ++it);
}

void testIteratorDec() {
    List<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);

    List<int>::Iterator it = list.begin();
    it++;
    //test it--
    ASSERT_EQUALS(*it, *(it--));
    ASSERT_EQUALS(1, *it);

    //test --it
    it = list.begin();
    it++;
    ASSERT_EQUALS(1, *(--it));
}

void testIteratorEqual() {
    List<int> list;
    list.insert(1);
    list.insert(2);

    List<int> list2;
    list2.insert(1);
    list2.insert(2);

    List<int>::Iterator it = list.begin();
    List<int>::Iterator itSameList = list.begin();
    List<int>::Iterator it2 = list2.begin();

    //test equal when the same iterator
    ASSERT_TRUE(it == it);
    //test not equal when not on the same list
    ASSERT_FALSE(it == it2);
    //test diff iterators on same list and element
    ASSERT_TRUE(it == itSameList);
    //test diff iterators on same list and diff elements
    itSameList++;
    ASSERT_FALSE(it == itSameList);
    //test diff iterators on same list and both end of list
    it = list.end();
    itSameList = list.end();
    ASSERT_TRUE(it == itSameList);
}

void testIteratorNotEqual() {
    //test opposite results than equal
    List<int> list;
    list.insert(1);
    list.insert(2);

    List<int> list2;
    list2.insert(1);
    list2.insert(2);

    List<int>::Iterator it = list.begin();
    List<int>::Iterator itSameList = list.begin();
    List<int>::Iterator it2 = list2.begin();


    ASSERT_FALSE(it != it);

    ASSERT_TRUE(it != it2);

    ASSERT_FALSE(it != itSameList);

    itSameList++;
    ASSERT_TRUE(it != itSameList);

    it = list.end();
    itSameList = list.end();
    ASSERT_FALSE(it != itSameList);
}

int main() {

    //testing the list funcs
    RUN_TEST(testListCtor);
    RUN_TEST(testListCopyCtor);
    RUN_TEST(testListDtor);
    RUN_TEST(testListAssignment);
    RUN_TEST(testListIteratorBegin);
    RUN_TEST(testListIteratorEnd);
    RUN_TEST(testListInsert);
    RUN_TEST(testListRemove);
    RUN_TEST(testListOperatorEqual);
    RUN_TEST(testListOperatorNotEqual);
    RUN_TEST(testListFind);
    RUN_TEST(testListSort);
    RUN_TEST(testListGetSize);

    //testing the iterator funcs
    RUN_TEST(testIteratorCopyCtor);
    RUN_TEST(testIteratorAssignment);
    RUN_TEST(testIteratorDereference);
    RUN_TEST(testIteratorInc);
    RUN_TEST(testIteratorDec);
    RUN_TEST(testIteratorEqual);
    RUN_TEST(testIteratorNotEqual);

    return 0;
}