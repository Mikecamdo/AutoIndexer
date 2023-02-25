//
// Created by mikec_g1kgiu8 on 9/14/2021.
//

#include "Indexer.h"
#include <map>

Indexer::Indexer() {
    argv = nullptr;
}

Indexer::Indexer(char** files) {
    argv = files;
}

Indexer::~Indexer() = default;

int Indexer::index() {
    input = openInputFile();

    if (!input.is_open()) {
        cout << "Could not open input file" << endl;
        return -1;
    }

    while (!input.eof()) { //loop that continues until the end of the file is reached or -1 is found
        char c = input.get(); //goes over the input character by character
        if (c == '<') { //activates when a number is found
            char number[100]; //temporarily stores the page number
            c = input.get();

            if (c == '[') { //activates if an open bracket appears right after a '<'
                findTerms(input, indexedTerms, pageNumber);
            }

            int i = 0;
            while (((c >= 48) && (c <= 57)) || (c == 45)) { //only reads in negative sign and numbers
                number[i] = c;
                ++i;
                c = input.get();
            }
            number[i] = '\0'; //adds a \0 to the end of the c string
            if (number[0] != '\0') { //only activates if number contains a number; if number[0] == '\0', then that means the term inside the <> was not a page number
                pageNumber = number;//gets the page number
            }
            if (pageNumber == "-1") { //ends program when <-1> is found
                break;
            }
        }
        else if (c == '[') { //activates when an opening bracket is found
            findTerms(input, indexedTerms, pageNumber); //finds the bracketed terms (including any nested terms)
        }
    }

    input.close();
    output = openOutputFile();

    if (!output.is_open()) {
        cout << "Could not open output file" << endl;
        return -1;
    }

    printIndex(); //prints the index to an output file
    output.close();

    return 0;
}

ifstream Indexer::openInputFile() { //opens the input file
    ifstream input(argv[1]);
    return input;
}

ofstream Indexer::openOutputFile() { //opens the output file
    ofstream output(argv[2]);
    return output;
}

//the following recursive function finds all bracketed
DSString Indexer::findTerms(ifstream& input, map<DSString, DSVector<DSString>>& indexedTerms, DSString& pageNumber) {
    DSString term;
    char buffer[400];
    char c = input.get();

    int i = 0;
    while (c != ']') { //loop that doesn't end until the closing bracket for the term is found
        if (c == '[') { //activates if a nested term is found
            buffer[i] = '\0'; //adds a \0 to the end of the c string
            term = term + buffer; //adds everything read before the nested word to term
            memset(buffer, '\0', i); //clears buffer
            i = 0; //resets the counter
            term = term + findTerms(input, indexedTerms, pageNumber); //recursively finds the nested term and then adds it to the current term
        } else {
            if (c == '\n') { //only activates when a term spans multiple lines
                if (buffer[i - 1] != ' ') { //only adds a space if the word at the end of the line did not already have a space after it
                    buffer[i] = ' ';
                    ++i;
                }
            } else if (c == '\r') {
                //ignores \r characters, as it sometimes messes up the output on my computer
            } else { //adds any character that is not a \n, \r, [, or ] to the term
                buffer[i] = c;
                ++i;
            }
        }
        c = input.get();
    }
    buffer[i] = '\0'; //adds \0 to the end of the c string

    term = term + buffer; //adds everything in buffer to term

    term.lowercase(); //lowercases all letters
    if (indexedTerms[term].find(pageNumber) == -1) { //only adds the page number if the page number has not already been added for that term
        indexedTerms[term].push_back(pageNumber);           //if a term appears twice on one page, this prevents the page number from being added twice
    }

    return term; //returns the term found (only really necessary when dealing with nested terms)
}

void Indexer::printIndex() { //prints the index to an output file
    char section, previousSection;
    previousSection = '\0'; //previousSection is initially equal to nothing
    int lineLength = 0;

    for (auto const & pair: indexedTerms) { //loop that goes through every key-value pair in the indexedTerms map
        lineLength = pair.first.getLength(); //finds the length of the term
        section = toupper(pair.first.beginning()); //section is equal to the first letter (or symbol) capitalized

        if (section != previousSection) { //only activates if a new section is reached (and thus a new header is needed)
            output << "[" << section << "]" << endl; //prints the header for each section
        }

        if (lineLength >= 68) { //activates if the term is too long to be displayed on one line (68 is the cutoff because a : and a space are added after the term)
            lineLength = 0; //resets line length
            output << pair.first.substring(0, 70) << endl; //outputs the first 70 characters of the term
            output << "    " << pair.first.substring(70, pair.first.getLength() - 70) << ": "; //outputs the rest of the term
            lineLength += 6 + pair.first.getLength() - 70; //increases line length by the number of characters added
        } else {
            output << pair.first << ": "; //outputs the term
            lineLength += 2;
        }

        for (int i = 0; i < pair.second.length(); i++) {
            if (i == (pair.second.length() - 1)) { //activates when the last pageNumber is found
                lineLength += pair.second.at(i).getLength();

                if (lineLength > 70) { //activates if the line would be too long if you added the page number
                    lineLength = 4 + pair.second.at(i).getLength(); //resets line length
                    output << endl << "    "; //starts a new line
                }
                output << pair.second.at(i) << endl; //outputs the page number
            } else { //activates for every pageNumber except the last
                lineLength += 2 + pair.second.at(i).getLength();

                if (lineLength > 70) { //activates if the line would be too long if you added the page number
                    lineLength = 6 + pair.second.at(i).getLength(); //resets line length
                    output << endl << "    "; //starts a new line
                }
                output << pair.second.at(i) << ", "; //outputs the page number
            }
        }
        previousSection = section; //sets previousSection equal to section before moving to the next term
    }
}

