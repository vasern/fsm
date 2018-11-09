/* ===============================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//============================================================= */

#ifndef fsm_mode_h
#define fsm_mode_h

#include "fsm_record.h"
#include <string>

namespace vs {
    class fsm_mode {
        
    public:
        
        bool opened;
        
        fsm_mode(const char* path): 
            path(path)
        { }
        
        void close_conn();
        
        size_t file_size();
        
        fsm_record get_record(int block_pos);
        
        int write_record(std::string* buffer, char* data, size_t data_size);

    protected:
        const char* path;
    };
}

#endif /* fsm_mode_h */
