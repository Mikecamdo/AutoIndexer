//
// Created by MARK FONTENOT on 9/14/21.
//

/**
 * This file contains some simple tests.
 *
 * DO NOT add the #define CATCH_CONFIG_RUNNER to this file.
 * It is already in catch_setup.cpp
 *
 * Note that you can have more than one cpp file with tests in them.
 * For example, you could have a test file for your DSString and a
 * separate one for your DSVector.
 */

#include "catch.hpp"
#include "DSVector.h"
#include "DSString.h"

TEST_CASE("Testing Tests", "[multiplication]") { //FIXME I think I need multiple test files (one for DSString and one for DSVector)
    REQUIRE((2 * 2) == 4);
    REQUIRE((1 * 5) == 5);
}