#include "./include/buffer.hpp"

void Buffer::init() {
    lineNo = 0;
    inPosition = 0;
    eofChar = 0x7f;
    current = input[lineNo];
    readChar = current[inPosition];
}

Buffer::Buffer() {
            
}
void Buffer::load(vector<string>& text) {
    input = text;
    init();
}

void Buffer::load(string text) {
    input = { text };
    init();
}

char Buffer::nextChar() {
    if (inPosition+1 == current.size()) {
        inPosition = 0;
        if (lineNo+1 == input.size()) {
            readChar = eofChar;
            return eofChar;
        }
        else current = input[++lineNo];
    } else {
        inPosition++;
    }
    readChar = current[inPosition];
    return readChar;
}
int Buffer::lineNumber() {
    return lineNo;
}
char Buffer::unGet() {
    if (inPosition-1 < 0) {
        if (lineNo == 0) {
            readChar = eofChar;
            return eofChar;
        }
        else current = input[--lineNo];
        inPosition = current.size() - 1;
    } else {
        --inPosition;
    }
    readChar = current[inPosition];
    return readChar;
}
char Buffer::getChar() const {
    return readChar;
}
string Buffer::asString() {
    string ret;
    ret.push_back(getChar());
    return ret;
}
char Buffer::EOFMark() {
    return eofChar;
}