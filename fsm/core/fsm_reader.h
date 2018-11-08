/* ===============================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//============================================================= */

#ifndef fsm_reader_h
#define fsm_reader_h

#include "fsm_mode.h"
#include <sys/stat.h>


namespace vs {
    
    class fsm_reader : public fsm_mode {
    public:
        
        fsm_reader(const char* path, int block_size, int block_end);
        ~fsm_reader();
        
        // Get record in the from a given block position (file must be already open)
        // It will first read meta data then read all blocks of the record
        // then return the value
        record_desc get_record(int block_pos);
        
        // Close and un-map db file
        void close_conn();
        
        size_t file_size();
    private:
        
        struct stat file_info;
        int fd;
        char *map;
    };
    
} // namespace vs


#endif /* fsm_reader_h */
