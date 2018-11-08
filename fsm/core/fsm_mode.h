/* ===============================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//============================================================= */

#ifndef fsm_mode_h
#define fsm_mode_h

#include "fsm_types.h"
#include <string>

namespace vs {
    class fsm_mode {
        
    public:
        
        bool opened;
        
        fsm_mode(int block_size, int record_size) :
            b_size(block_size),
            r_size(record_size)
        { }
        
        void close_conn();
        
        size_t file_size();
        
        record_desc get_record(int block_pos);
        int write_record(std::string* buffer, char* data, size_t data_size);
        
    protected:
        int b_size; // Record block size
        int r_size; // Record size (exclude meta data)
    };
}

#endif /* fsm_mode_h */
