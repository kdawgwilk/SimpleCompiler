//
//  main.cpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 1/11/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#include "Scanner.hpp"
#include "Symbol.hpp"
#include "Parser.hpp"
#include "SimpleCompilerConfig.h"

int main(int argc, char * argv[]) {
    fprintf(stdout, "SimpleCompiler Version %d.%d\n", SimpleCompiler_VERSION_MAJOR, SimpleCompiler_VERSION_MINOR);

    if (argc == 1) {
        cerr << "You need to supply either an argument `test` to run the compiler tests or a filename to compile a file." << endl;
        return 1;
    } else if (argc >= 2 && !strcmp(argv[1], "test")) {
        InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else if (argc == 2) {
        ScannerClass scanner(argv[1]);
//        ScannerClass scanner("test_code.c");
        SymbolTableClass symbolTable;
        ParserClass parser(&scanner, &symbolTable);

        auto startNode = parser.Start();

        cout << "########## Interpret Start ##########" << endl;
        startNode->Interpret();
        cout << "########## Interpret End ##########" << endl;

        cout << "########## Code Start ##########" << endl;
        InstructionsClass instructions;
        startNode->Code(instructions);
        instructions.Finish();
//        instructions.PrintAllMachineCodes();
        instructions.Execute();
        cout << "########## Code End ##########" << endl;

        delete startNode;
    } else {
        cerr << "Too many arguments supplied" << endl;
        return 1;
    }
    return 0;
}

