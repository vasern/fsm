//
//  index_set.hpp
//  Vasern
//
//  Created by Hieu (Jack) Nguyen on 25/11/18.
//  Copyright © 2018 Hieu (Jack) Nguyen. All rights reserved.
//

#ifndef index_set_hpp
#define index_set_hpp

#include <string>
#include <unordered_map>

#include "index_types/index_t.h"
#include "../index_set_types.h"
//#include "value_i.h"

namespace vs {
//    typedef std::shared_ptr<value_i<size_t>> value_ptr;
    
    template<typename T>
    class index_set {
    public:
        index_set();
        
        index_set(std::unordered_map<std::string, type_desc_t> args);
        
        void push(std::shared_ptr<value_i<T>> value);
        void remove(value_ptr);
        
        std::vector<value_ptr> filter(upair_t*);
        std::vector<value_ptr> filter(upair_t*, const char*, bool);
        
        void sort(std::vector<value_ptr>*, const char*, bool);
        
        value_ptr get(upair_t*);
        const char* get_id(upair_t*);
        
//        std::vector<T> get_multiple(upair_t*);
        
        type_desc_t type_of(const char*);
        
    private:
        std::unordered_map<std::string, index_t*> _set;
    };
}

#endif /* index_set_hpp */
