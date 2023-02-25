//
// Created by mikec_g1kgiu8 on 9/14/2021.
//

#ifndef INC_21F_PA02_INDEXER_H
#define INC_21F_PA02_INDEXER_H

#include <fstream>
#include "DSString.h"
#include "DSVector.h"
#include <map>

using namespace std;

class Indexer {
    private:
        char** argv;
        DSString pageNumber; //holds the pageNumber
        map<DSString, DSVector<DSString>> indexedTerms; //map that contains all indexed terms and every page number they appear on
        ifstream input;
        ofstream output;

        ifstream openInputFile(); //opens the input file
        ofstream openOutputFile(); //opens the output file
        DSString findTerms(ifstream&, map<DSString, DSVector<DSString>>&, DSString&); //recursive function that finds all terms within brackets
        void printIndex(); //prints the index to an output file

public:
        Indexer();
        Indexer(char**);
        ~Indexer();

        int index(); //only public function; main functionality of the program happens here
};


#endif //INC_21F_PA02_INDEXER_H
