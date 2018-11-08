/* ===============================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//============================================================= */

#ifndef fsm_h
#define fsm_h

#include "fsm_types.h"
#include "fsm_reader.h"
#include "fsm_writer.h"

namespace vs {
    
    class fsm {
    public:
        
        // Initiate writer with absolute path and record block size
        fsm(const char* path, int block_size);
        ~fsm();
        
        fsm_reader* open_reader();
        
        fsm_writer* open_writer();
    private:
        
        // File path
        const char* path;
        
        bool is_writing;
        
        int b_size; // Record block size
        int r_size; // Record size (exclude meta data)
    };
}

#endif /* fsm_writer_h */
