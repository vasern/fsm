//
//  vasern_utils.h
//  Vasern
//
//  Created by Hieu (Jack) Nguyen on 11/10/18.
//  Copyright © 2018 Hieu (Jack) Nguyen. All rights reserved.
//

#ifndef vasern_utils_h
#define vasern_utils_h

#import <Foundation/Foundation.h>
#import <string>
#import <vector>

namespace vasern_utils {
    
// Convert a NSArray (objective-c) to vector<string> (cpp)
std::string NSArrayToStr(NSArray* input);

// Convert a vector<string> (cpp) to NSArray (objective-c)
NSArray* VectorStrToNSArray(std::vector<char*> *input);

std::string RecordsToChars(NSArray* input, int start_pos);
    
int atoi( char * str );
}


#endif /* vasern_utils_h */
