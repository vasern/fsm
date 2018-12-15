//
//  index_f.h
//  Vasern
//
//  Created by Hieu (Jack) Nguyen on 26/11/18.
//  Copyright © 2018 Hieu (Jack) Nguyen. All rights reserved.
//

#ifndef index_f_h
#define index_f_h

#include "../../../enums.h"

#include "index_str.h"
#include "index_int.h"
#include "index_bool.h"
#include "index_long.h"
#include "index_double.h"

namespace vs {
    
    class index_f {
    public:
        static index_t* create(type_desc_t type) {
            
            index_t* t;
            
            switch(type) {
                case STRING:
                case KEY:
                    t = new index_str();
                    break;
                case INT_N:
                    t = new index_int();
                    break;
                case LONG_N:
                    t = new index_long();
                    break;
                case DOUBLE_N:
                    t = new index_double();
                    break;
                case BOOLEAN:
                    t = new index_bool();
                    break;
                default:
                    t = new index_t();
                    break;
            }
            
            return t;
        }
    };
}

#endif /* index_f_h */
