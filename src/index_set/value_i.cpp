//
//  value_i.cpp
//  CiPlayground
//
//  Created by Hieu (Jack) Nguyen on 15/12/18.
//  Copyright © 2018 Ambi Studio. All rights reserved.
//


//#include "../types.h"
//#include "../values/value_t.h"
#include "value_i.h"

namespace vs {
        
    template <typename T>
    bool value_i<T>::match_query(std::unordered_map<std::string, value_t*> *query, const char* exclude) {
        
        for (auto itr: *query) {
            
            if (itr.first.compare(exclude) != 0) {
                
                if(itr.second->is_match(items[itr.first]) == false) {
                    return false;
                };
                
            }
        }
        
        return true;
    }
}
