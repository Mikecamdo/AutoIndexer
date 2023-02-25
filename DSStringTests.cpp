//
// Created by mikec_g1kgiu8 on 9/23/2021.
//
#include "catch.hpp"
#include "DSString.h"
#include <cstring>

TEST_CASE("DSString class", "[DSString]") {
    DSString s[10];
    s[0] = DSString("TestDSString");
    s[1] = DSString("not a test DSString");
    s[2] = DSString("");
    s[3] = DSString("these words are lowercase");
    s[4] = DSString("This is so fun");
    s[5] = DSString("\n");
    s[6] = DSString("THESE WORDS ARE LOWERCASE");
    s[7] = DSString("");
    s[8] = DSString("far       apart");
    s[9] = DSString("TestDSString");

    SECTION("Equality operators") {
        CHECK(s[0] == DSString("TestDSString"));
        CHECK(s[0] == s[9]);
        CHECK(s[2] == s[7]);
        CHECK(s[1] == "not a test DSString");
        CHECK(!(s[3] == s[6]));
    }

    SECTION("Inequality operators") {
        CHECK(s[0] != "Hello there!");
        CHECK(s[6] != "General Kenobi!");
        CHECK(s[4] != "You are a bold one");
    }

    SECTION("Assignment operators") {
        DSString str;
        str = "This is so fun";
        CHECK(str == s[4]);
        str = DSString("not a test DSString");
        CHECK(str == s[1]);
        str = "\n";
        CHECK(str == s[5]);
        str = "far       apart";
        CHECK(str == s[8]);
        CHECK(!(str == s[7]));
    }

    SECTION("Addition operator") {
        CHECK(DSString("TestDSStringnot a test DSString") == (s[0] + s[1]));
        CHECK(s[7] + s[7] == "");
        CHECK(s[5] + s[7] == DSString("\n"));
        CHECK(s[2] + s[7] + s[8] == "far       apart");
    }

    SECTION("Greater than operator") {
        CHECK(s[3] > s[8]);
        CHECK(s[3] > s[6]);
        CHECK(s[3] > s[1]);
        CHECK(DSString("hello") > DSString("hellO"));
    }

    SECTION("Less than operator") {
        CHECK(s[8] < s[3]);
        CHECK(s[6] < s[3]);
        CHECK(s[1] < s[3]);
        CHECK(DSString("hellO") < DSString("hello"));
    }

    SECTION("[] Operator") {
        CHECK(s[3][6] == 'w');
        CHECK(s[8][3] == ' ');
        CHECK(s[9][4] == 'D');
    }

    SECTION("getLength function") {
        DSString apples("apples");
        CHECK(s[0].getLength() == 12);
        CHECK(apples.getLength() == 6);
        CHECK(s[7].getLength() == 0);
        CHECK(s[8].getLength() == 15);
        CHECK(s[3].getLength() == 25);
    }

    SECTION("Substring function") {
        CHECK(s[8].substring(0, 3) == "far");
        CHECK(s[4].substring(5, 5) == "is so");
        CHECK(s[9].substring(2, 4) == "stDS");
    }

    SECTION("c_str function") {
        CHECK(strcmp(s[4].c_str(), "This is so fun") == 0);
        CHECK(strcmp(s[0].c_str(), s[9].c_str()) == 0);
        CHECK(strcmp(s[5].c_str(), "\n") == 0);
    }

    SECTION("count function") {
        CHECK(s[8].count(' ') == 7);
        CHECK(s[0].count('w') == 0);
        CHECK(s[1].count('S') == 2);
    }

    SECTION("find functions") {
        CHECK(s[0].find('T') == 0);
        CHECK(s[0].find('T') == s[0].find('T', 1));
        CHECK(s[8].find('a') == 1);
        CHECK(s[8].find('a', 2) == 10);
        CHECK(s[2].find('Z') == -1);
        CHECK(s[6].find('W', 3) == -1);
    }

    SECTION("end function") {
        CHECK(s[0].end() == 'g');
        CHECK(s[3].end() == 'e');
        CHECK(s[6].end() == 'E');
        CHECK(s[8].end() == 't');
    }

    SECTION("beginning function") {
        CHECK(s[0].beginning() == 'T');
        CHECK(s[1].beginning() == 'n');
        CHECK(s[8].beginning() == 'f');
        CHECK(s[9].beginning() == 'T');
    }

    SECTION("lowercase function") {
        s[6].lowercase();
        s[7].lowercase();

        DSString temp(s[8]);
        s[8].lowercase();

        DSString temp2 = "123 Can't CATCH mE";
        temp2.lowercase();

        CHECK(s[6] == s[3]);
        CHECK(s[7] == "");
        CHECK(s[8] == temp);
        CHECK(temp2 == "123 can't catch me");
    }

}
