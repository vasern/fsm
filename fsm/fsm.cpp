//* ===============================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//============================================================= */

#include "fsm.h"

namespace vs {
    
    fsm::fsm(const char* path, int block_size) :
        path(path),
        b_size(block_size)
    { }
    fsm::~fsm() { }
    
    
    fsm_writer* fsm::open_writer() {
        if (!is_writing) {
            is_writing = true;
            return new fsm_writer(path, b_size);
        }
        return new fsm_writer("", b_size);
    }
    
    fsm_reader* fsm::open_reader() {
        return new fsm_reader(path, b_size);
    }
}
