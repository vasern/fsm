//
//  index_double.h
//  Vasern
//
//  Created by Hieu (Jack) Nguyen on 26/11/18.
//  Copyright © 2018 Hieu (Jack) Nguyen. All rights reserved.
//

#ifndef index_double_h
#define index_double_h

#include "index_t.h"

namespace vs {
    
    class index_double: public index_t {
    public:
        
        index_double()
        : index_t(DOUBLE_N)
        { }
        
        void push(value_t* key, value_ptr value) {
            if (items.count(key->double_value()) == 0) {
                items[key->double_value()] = std::vector<value_ptr> { value };
            } else {
                items[key->double_value()].push_back(value);
            }
        }
        
        void update(value_t* old_key, value_t* key) {
            auto values = items[old_key->double_value()];
            items.erase(old_key->double_value());
            items[key->double_value()] = values;
        }
        
        void remove(value_t* key, value_ptr value) {
            auto vec = &items[key->double_value()];
            
            vec->erase(std::remove_if(vec->begin(), vec->end(), [&value](value_ptr ptr){ return ptr == value; }), vec->end());
        }
        
        std::vector<value_ptr> get(value_t* key) {
            return items[key->double_value()];
        }
        
        std::vector<value_ptr> range(value_t* value) {
            std::vector<value_ptr> rs;
            std::vector<value_ptr> temp;
            for (auto itr: items) {
                if (value->is_in_range(value_f::create( itr.first ))) {
                    rs.reserve(temp.size() + itr.second.size());
                    rs.insert(rs.end(), temp.begin(), temp.end());
                    rs.insert(rs.end(), itr.second.begin(), itr.second.end());
                    temp = rs;
                }
            }
            
            return rs;
        }
        
    private:
        std::unordered_map<double, std::vector<value_ptr>> items;
    };
    
}


#endif /* index_double_h */
