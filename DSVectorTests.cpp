//
// Created by mikec_g1kgiu8 on 9/23/2021.
//

#include "catch.hpp"
#include "DSVector.h"
#include "DSString.h"


TEST_CASE("DSVector class", "[DSVector]") {
    DSVector<int> test;
    test.push_back(5);
    test.push_back(17);
    test.push_back(0);
    test.push_back(-201);

    DSVector<char> test2;
    test2.push_back('c');
    test2.push_back('w');
    test2.push_back('W');

    DSVector<bool> test3;
    test3.push_back(true);
    test3.push_back(false);
    test3.push_back(true);

    SECTION(".at() == [] operator") {
        CHECK(test.at(0) == test[0]);
        CHECK(test.at(1) == test[1]);
        CHECK(test.at(2) == test[2]);
        CHECK(test.at(3) == test[3]);
        CHECK(test2.at(0) == test2[0]);
        CHECK(test2.at(1) == test2[1]);
        CHECK(test2.at(2) == test2[2]);
        CHECK(test3.at(0) == test3[0]);
        CHECK(test3.at(1) == test3[1]);
    }

    SECTION("push_back function") {
        DSVector<int> a;
        a.push_back(2);
        a.push_back(-17);
        a.push_back(0);

        CHECK(a[0] == 2);
        CHECK(a[1] == -17);
        CHECK(a[2] == 0);
    }

    SECTION("length function") {
        CHECK(test.length() == 4);
        CHECK(test2.length() == 3);
        CHECK(test3.length() == 3);
    }

    SECTION("at function") {
        CHECK(test.at(1) == 17);
        CHECK(test2.at(2) == 'W');
        CHECK(test3.at(0) == true);
    }

    SECTION("find function") {
        CHECK(test.find(17) == 1);
        CHECK(test.find(-201) == 3);
        CHECK(test2.find('W') == 2);
        CHECK(test3.find(false) == 1);
    }

    SECTION("[] operator") {
        CHECK(test[1] == 17);
        CHECK(test2[2] == 'W');
        CHECK(test3[0] == true);
    }

    SECTION("= operator") {
        DSVector<int> temp = test;
        DSVector<char> temp2 = test2;
        DSVector<bool> temp3 = test3;

        CHECK(temp[0] == 5);
        CHECK(temp[2] == 0);
        CHECK(temp2[0] == 'c');
        CHECK(temp3[0] == true);
        CHECK(temp3[1] == false);

    }

    SECTION("erase function") {
        DSVector<DSString> temp;
        temp.push_back("Hello");
        temp.push_back("Hola");
        temp.push_back("Bonjour");
        temp.push_back("Goodbye");
        temp.push_back("Adios");
        temp.push_back("Au revoir");

        temp.erase(0);
        CHECK(temp.at(0) == "Hola");
        CHECK(temp.at(4) == "Au revoir");
        CHECK(temp.length() == 5);

        temp.erase(2);

        CHECK(temp.at(0) == "Hola");
        CHECK(temp.at(1) == "Bonjour");
        CHECK(temp.at(2) == "Adios");
        CHECK(temp.length() == 4);

        temp.erase(1);
        CHECK(temp.at(1) == "Adios");
        CHECK(temp.length() == 3);
    }

    SECTION("Copy constructor") {
        DSVector<int> temp(test);
        DSVector<char> temp2(test2);
        DSVector<bool> temp3(test3);

        CHECK(temp.at(0) == 5);
        CHECK(temp.at(1) == test.at(1));
        CHECK(temp[2] == test[2]);

        CHECK(temp2.at(0) == 'c');
        CHECK(temp2.at(1) == test2.at(1));
        CHECK(temp2[2] == test2[2]);

        CHECK(temp3.at(0) == true);
        CHECK(temp3.at(1) == test3.at(1));
        CHECK(temp3[2] == test3[2]);
    }

}