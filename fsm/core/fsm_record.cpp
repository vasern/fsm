/* ===============================================================
 //
 //  Copyright by Ambi Studio 2018
 //  Licensed under the Apache License, Version 2.0 (the "License");
 //  (Please find "LICENSE" file attached for license details)
 //============================================================= */

#include "fsm_record.h"
#include "../config.h"
#include <iostream>

namespace vs {
  
    fsm_record::fsm_record(char* map_add, size_t begin_pos): 
        map(map_add), 
        beg(begin_pos)
    { };
    
    void fsm_record::c_str(char* buff) {

        // buffer with max size = block size (except meta) * number of blocks
        int num_of_blocks = map[beg + vs_config::RECORD_SIZE] & 0xff;
        
        // buff = new char[vs_config::RECORD_SIZE * num_of_blocks];
        int r = 0, b = 0; // row & block iterator
        size_t buff_pos = 0;
        size_t beg_pos = beg;
        
        for (b = 0; b < num_of_blocks; b++) {
            
            r = 0;
            
            // This loop will exclude meta chars
            while (map[beg_pos + r] != '\0') {
                
                buff[buff_pos++] = map[beg_pos + r];
                r++;
            }
            beg_pos += vs_config::BLOCK_SIZE;
        }
        
        buff[buff_pos] = '\0';
    }
    
    fsm_record fsm_record::next() {
        
        size_t next_block_beg = beg +
        ((map[beg + vs_config::RECORD_SIZE] & 0xff) * vs_config::BLOCK_SIZE) + 1;
        
        return fsm_record(map, next_block_beg);
    }
    
    fsm_record fsm_record::prev() {
        size_t last_block_beg = beg -
        (map[beg - 1] & 0xff * vs_config::BLOCK_SIZE);
        return fsm_record(map, last_block_beg);
    }
    
    const char* fsm_record::substr(int len) {
        return "";
    }
    
    const char* fsm_record::substr(int start, int len) {
        return "";
    }
}