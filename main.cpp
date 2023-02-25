/**
 * Fall 2021 PA 02 Template Repo.
 */

#include "DSVector.h"
#include "DSString.h"

using namespace std;

/**
 * catch_setup.h and catch_setup.cpp contain the #define directive for
 * the CATCH2 framework.  You can see in main below how I'm calling the
 * runCatchTests() function which is declared in this header.
 *
 * On average, this should reduce the build time for your project on your local
 * machine.
 */
#include "catch_setup.h"
#include "Indexer.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        runCatchTests();
        return 0;
    } else {
        Indexer autoIndexer(argv);
        return autoIndexer.index();
    }
}