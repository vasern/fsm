//
//  v_value.h
//  Vasern
//
//  Created by Hieu (Jack) Nguyen on 26/11/18.
//  Copyright © 2018 Hieu (Jack) Nguyen. All rights reserved.
//

#ifndef v_value_h
#define v_value_h

#include <vector>
#include <unordered_map>
//#include "../types.h"
#include "../values/value_t.h"

namespace vs {
    
    template<typename T>
    struct value_i {
        T value;
        std::unordered_map<std::string, value_t*> items;
        
        bool match_query(std::unordered_map<std::string, value_t*> *query, const char* exclude);
    };
    
    template <typename T>
    struct result_t {
        size_t count;
        std::vector<T> items;
    };
}

#endif /* v_value_h */
