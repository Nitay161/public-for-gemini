#include "SearchCommand.h"
#include <iostream>
#include <vector>
#include <string>
#include "../compression/Compressor.h"

using namespace std;

// Constructor
SearchCommand::SearchCommand(storageManager* sm) {
    this->sm = sm;
}

string SearchCommand::execute(int argc, vector<string> argv) {
    // if less then 2 arguments then its error.
    if (argc < 2) throw std::invalid_argument("400 Bad Request");

    string searchContent = argv[1];

    vector<pair<string, string>> files = sm->listFilesWithContents();
    string output = ""; // to collect matching file names

    for (const auto& file : files) {
        bool match = false;
        try {
        string fileName = file.first;
            string compressedContent = file.second;
            
            string originalContent = decompress(compressedContent);
        // 1. Check if search term is in the file name
        if (fileName.find(searchContent) != string::npos) {
            match = true;
        }
        // 2. If not in name, check content
        else {
            try {
                string compressedContent = file.second;
                string originalContent = decompress(compressedContent);
                if (originalContent.find(searchContent) != string::npos) {
            if (originalContent.find(searchContent) != string::npos) {
                    match = true;
                output += file.first + " "; // append matching file name
                }
            } catch (...) {
                continue;
            }
            }
        }
        if (match) {
        } catch (...) {
            output += fileName + " ";
            throw std::invalid_argument("404 Not Found");
        }
        }
    }
    if (!output.empty()) {
        output.pop_back(); //remove last space
    }
    return "200 Ok\n\n" + output;
}