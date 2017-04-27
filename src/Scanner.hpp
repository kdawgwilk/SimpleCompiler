//
//  Scanner.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 1/30/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef Scanner_hpp
#define Scanner_hpp

#include "Token.hpp"


class InterfaceInputStreamer {
public:
    virtual ~InterfaceInputStreamer() = default;
    virtual void open(string filename) = 0;
    virtual bool is_open() = 0;
    virtual char get() = 0;
    virtual void unget() = 0;
    virtual std::streampos tellg() = 0;
    virtual void clear() = 0;
    virtual void seekg(streamoff position) = 0;
    virtual void close() = 0;
};

class FileStringStreamer : public InterfaceInputStreamer {
    std::istream *mIfstream;
public:
    FileStringStreamer(std::istream *istream = new ifstream()) : mIfstream(istream) {}
    ~FileStringStreamer() {
        delete mIfstream;
    }

    void open(string filename) override {
        ifstream *fin = dynamic_cast<ifstream *>(mIfstream);
        if (fin == NULL) {
            return;
        }
        fin->open(filename, std::ios::binary);
    }

    bool is_open() override {
        ifstream *fin = dynamic_cast<ifstream *>(mIfstream);
        if (fin == NULL) {
            return true;
        }
        return fin->is_open();
    }

    char get() override {
        return mIfstream->get();
    }

    void unget() override {
        mIfstream->unget();
    }

    std::streampos tellg() override {
        return mIfstream->tellg();    }

    void clear() override {
        mIfstream->clear();
    }

    void seekg(streamoff position) override {
        mIfstream->seekg(position);
    }

    void close() override {
        ifstream *fin = dynamic_cast<ifstream *>(mIfstream);
        if (fin == NULL) {
            return;
        }
        fin->close();
    }
};

//class MockFileStream : public InterfaceInputStreamer {
//    std::istringstream *mIStringStream;
//public:
//    MockFileStream(std::istringstream *istringstream = new std::istringstream()) : mIStringStream(istringstream) {}
//    MOCK_METHOD1(open, void(string filename));
//    MOCK_METHOD0(is_open, bool());
//    MOCK_METHOD0(get, char());
//    MOCK_METHOD0(tellg, char());
//    MOCK_METHOD0(clear, void());
//    MOCK_METHOD1(seekg, void(streamoff position));
//    MOCK_METHOD0(close, void());
//};



class ScannerClass {
    string mFilename;
    InterfaceInputStreamer *mFin;
    int mLineNumber;
    int mColumnNumber;

public:
    ScannerClass(string filename = "", InterfaceInputStreamer *inputFileStream = new FileStringStreamer());
    virtual ~ScannerClass();

    virtual TokenClass GetNextToken();
    virtual TokenClass PeekNextToken();

    string GetFilename();
    int GetLineNumber();
    int GetColumnNumber();
};


#endif /* Scanner_hpp */
