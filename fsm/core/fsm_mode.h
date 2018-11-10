/* ===============================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//============================================================= */

#ifndef fsm_mode_h
#define fsm_mode_h

#include "fsm_record.h"
#include "../config.h"
#include <sys/stat.h>

#include <string>

namespace vs {
    class fsm_mode {
        
    public:
        
        bool opened;
        
        fsm_mode(const char* path, int block_size): 
            path(path),
            b_size(block_size),
            r_size(block_size - vs_config::META_SIZE)
        { }
        
        void close_conn();
        
        fsm_record get_record(int block_pos);
        
        int write_record(std::string* buffer, char* data, size_t data_size);

    protected:

        const char* path;
        int b_size;
        int r_size;

        size_t file_size() {
            struct stat st;
            fstat(*path, &st);
            return st.st_size;
        }
    };
}

#endif /* fsm_mode_h */
