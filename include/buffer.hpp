#ifndef buffer_hpp
#define buffer_hpp
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
using namespace std;

class Buffer {
    private:
        string current;
        vector<string> input;
        int inPosition;
        int lineNo;
        char readChar;
        char eofChar;
        void init();
    public:
        Buffer();
        void load(vector<string>& text);
        void load(string text);
        char nextChar();
        int lineNumber();
        char unGet();
        char getChar() const;
        string asString();
        char EOFMark();
};

#endif