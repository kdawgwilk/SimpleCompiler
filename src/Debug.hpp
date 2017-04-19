//
//  Debug.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 2/1/17.
//  Copyright © 2017 Kaden Wilkinson. All rights reserved.
//

#ifndef Debug_hpp
#define Debug_hpp

//#define DEBUG 1


#include <iostream>

#if DEBUG
    #define MSG(X) std::cout << X << std::endl;
#else
    #define MSG(X) ;
#endif

#endif /* Debug_hpp */
