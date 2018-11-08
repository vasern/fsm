//
//  fsm.c
//  LoggerPage
//
//  Created by Hieu (Jack) Nguyen on 8/11/18.
//  Copyright © 2018 Ambi Studio. All rights reserved.
//

#include "fsm.h"

namespace vs {
    
    fsm::fsm(const char* path, int block_size) :
        path(path),
        b_size(block_size),
        r_size(block_size - 2)
    { }
    fsm::~fsm() { }
    
    
    fsm_writer* fsm::open_writer() {
        if (!is_writing) {
            is_writing = true;
            return new fsm_writer(path, b_size, r_size);
        }
        return new fsm_writer("", 0, 0);
    }
    
    fsm_reader* fsm::open_reader() {
        return new fsm_reader(path, b_size, r_size);
    }
}
