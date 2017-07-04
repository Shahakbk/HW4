//
// Created by Shahak on 29/06/2017.
//

#include <iostream>

#include "../Enigma.h"
#include "../Exceptions.h"
#include "../mtmtest.h"

using namespace mtm::escaperoom;
using std::string;
using std::cout;
using std::endl;
//TODO delete if not necessary
void testEnigmaCtor() {
    set<string> elements;
    elements.insert("book");
    elements.insert("clock");
    //test successful construction
    Enigma enigma("name", EASY_ENIGMA, 2, elements);
    ASSERT_NO_THROW(Enigma("name", EASY_ENIGMA, 2, elements));
    ASSERT_EQUALS("name", enigma.getName());
    ASSERT_EQUALS(EASY_ENIGMA, enigma.getDifficulty());

    //test unsuccessful construction due to wrong num of elements
    ASSERT_THROWS(EnigmaIllegalSizeParamException,
                  Enigma("wrong num elements", EASY_ENIGMA, 3, elements));

    //test successful construction with second ctor
    Enigma enigma2("name2", MEDIUM_ENIGMA);
    ASSERT_NO_THROW(Enigma("name2", MEDIUM_ENIGMA));

    ASSERT_EQUALS("name2", enigma2.getName());
    ASSERT_EQUALS(MEDIUM_ENIGMA, enigma2.getDifficulty());
}

void testEnigmaCopyCtor() {
    set<string> elements;
    elements.insert("book");
    elements.insert("clock");
    Enigma enigma("name", EASY_ENIGMA, 2, elements);

    Enigma copied_enigma = enigma;
    ASSERT_NO_THROW(Enigma(enigma));
    //test that the 2 enigmas have the same values
    ASSERT_EQUALS(enigma.getName(), copied_enigma.getName());
    ASSERT_EQUALS(enigma.getDifficulty(), copied_enigma.getDifficulty());
    //test that the 2 enigmas are not the same one
    enigma.addElement("map");
    ASSERT_THROWS(EnigmaElementNotFoundException,
                  copied_enigma.removeElement("map"));

}

void testEnigmaAddElement() {
    set<string> elements;
    elements.insert("book");
    elements.insert("clock");
    Enigma enigma("name", EASY_ENIGMA, 2, elements);

    //test adding an element to the enigma
    ASSERT_NO_THROW(enigma.addElement("map"));
    //test if the element is in the enigma it can be removed
    ASSERT_NO_THROW(enigma.removeElement("map"));
}

void testEnigmaRemoveElement() {
    //test if throws when the enigma is empty
    Enigma enigma("name", EASY_ENIGMA);
    ASSERT_THROWS(EnigmaNoElementsException, enigma.removeElement("something"));

    //test if throws when the enigma has elements but the requested is not in it
    enigma.addElement("book");
    enigma.addElement("clock");
    ASSERT_THROWS(EnigmaElementNotFoundException, enigma.removeElement("lamp"));

    //test successful removal until empty
    ASSERT_NO_THROW(enigma.removeElement("book"));
    ASSERT_NO_THROW(enigma.removeElement("clock"));
    ASSERT_THROWS(EnigmaNoElementsException, enigma.removeElement("empty"));
}

void testEnigmaOperatorEqual() {
    set<string> elements;
    elements.insert("book");
    elements.insert("clock");
    Enigma enigma("same name", EASY_ENIGMA, 2, elements);
    //test same enigma
    ASSERT_TRUE(enigma == enigma);
    //test same name and difficulty but diff elements
    Enigma enigma2("same name", EASY_ENIGMA);
    ASSERT_TRUE(enigma == enigma2);
    //test same name diff difficulty
    Enigma enigma3("same name", HARD_ENIGMA);
    ASSERT_FALSE(enigma2 == enigma3);
    //test same difficulty but diff name
    Enigma enigma4("not same", HARD_ENIGMA);
    ASSERT_FALSE(enigma3 == enigma4);

}

void testEnigmaOperatorNotEqual() {
    //test opposite results than equal
    set<string> elements;
    elements.insert("book");
    elements.insert("clock");
    Enigma enigma("same name", EASY_ENIGMA, 2, elements);
    ASSERT_FALSE(enigma != enigma);
    Enigma enigma2("same name", EASY_ENIGMA);
    ASSERT_FALSE(enigma != enigma2);
    Enigma enigma3("same name", HARD_ENIGMA);
    ASSERT_TRUE(enigma2 != enigma3);
    Enigma enigma4("not same", HARD_ENIGMA);
    ASSERT_TRUE(enigma3 != enigma4);
}

void testEnigmaOperatorSmaller() {
    Enigma enigma("smaller", EASY_ENIGMA);
    Enigma enigma2("greater", MEDIUM_ENIGMA);
    ASSERT_TRUE(enigma < enigma2);
}

void testEnigmaOperatorGreater() {
    Enigma enigma("smaller", EASY_ENIGMA);
    Enigma enigma2("greater", MEDIUM_ENIGMA);
    ASSERT_TRUE(enigma2 > enigma);
}

void testEnigmaAreEqualyComplex() {
    //test enigmas with the same difficulty and num of elements but diff ones
    set<string> elements;
    elements.insert("book");
    elements.insert("clock");
    Enigma enigma("name", EASY_ENIGMA, 2, elements);
    set<string> elements2;
    elements2.insert("map");
    elements2.insert("lamp");
    Enigma enigma2("name", EASY_ENIGMA, 2, elements2);
    ASSERT_TRUE(enigma.areEqualyComplex(enigma));
    ASSERT_TRUE(enigma.areEqualyComplex(enigma2));
    ASSERT_TRUE(enigma2.areEqualyComplex(enigma));

    //test same num of elements but diff difficulty
    Enigma enigma3("name", HARD_ENIGMA, 2, elements2);
    ASSERT_FALSE(enigma.areEqualyComplex(enigma3));

    //test same diff but diff sum of elements
    enigma2.addElement("rope");
    ASSERT_FALSE(enigma.areEqualyComplex(enigma2));
}

void testEnigmaGetDifficulty() {
    Enigma enigma("name", MEDIUM_ENIGMA);
    ASSERT_EQUALS(MEDIUM_ENIGMA, enigma.getDifficulty());
}

void testEnigmaGetName() {
    Enigma enigma("name", MEDIUM_ENIGMA);
    ASSERT_EQUALS("name", enigma.getName());
}

void testEnigmaPrint() {
    set<string> elements;
    elements.insert("book");
    elements.insert("clock");
    Enigma enigma("name", EASY_ENIGMA, 2, elements);
    ASSERT_PRINT("name (0) 2", enigma);
}

int main() {

    RUN_TEST(testEnigmaCtor);
    RUN_TEST(testEnigmaCopyCtor);
    RUN_TEST(testEnigmaAddElement);
    RUN_TEST(testEnigmaRemoveElement);
    RUN_TEST(testEnigmaOperatorEqual);
    RUN_TEST(testEnigmaOperatorNotEqual);
    RUN_TEST(testEnigmaOperatorSmaller);
    RUN_TEST(testEnigmaOperatorGreater);
    RUN_TEST(testEnigmaAreEqualyComplex);
    RUN_TEST(testEnigmaGetDifficulty);
    RUN_TEST(testEnigmaGetName);
    RUN_TEST(testEnigmaPrint);

    return 0;
}