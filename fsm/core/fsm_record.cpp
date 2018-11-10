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
  
    fsm_record::fsm_record(char* map_add, size_t begin_pos, int block_size, int record_size): 
        map(map_add), 
        beg(begin_pos),
        b_size(block_size),
        r_size(record_size)
    { };
    
    int fsm_record::c_str(char* buff) {

        // buffer with max size = block size (except meta) * number of blocks
        int num_of_blocks = map[beg + r_size + 1] & 0xff;
        
        int r = 0, b = 0; // row & block iterator
        size_t buff_pos = 0;
        size_t beg_pos = beg;
        
        for (b = 0; b < num_of_blocks; b++) {
            
            r = beg_pos;
            
            // This loop will exclude meta chars
            while (map[r] != '\0') {
                
                buff[buff_pos++] = map[r];
                r++;
            }
            beg_pos += b_size;
        }
        
        buff[buff_pos] = '\0';
        return num_of_blocks;
    }
    
    fsm_record fsm_record::next() {
        
        // current block begin + (total blocks * block_size) + 1
        size_t next_beg = beg +
        ((map[beg + r_size + 1] & 0xff) * b_size) + 1;
        
        return fsm_record(map, next_beg, b_size, r_size);
    }
    
    fsm_record fsm_record::prev() {

        // current block begin - (prev total blocks * block_size)
        size_t prev_beg = beg -
        (map[beg - 2] & 0xff * b_size);
        return fsm_record(map, prev_beg, b_size, r_size);
    }
    
    int fsm_record::substr(char* buff, int len) {
        return substr(buff, 0, len);
    }
    
    int fsm_record::substr(char* buff, int start, int len) {

        int num_of_blocks = map[beg + r_size + 1] & 0xff;
        
        int r = 0, b = 0; // row & block iterator
        size_t buff_pos = 0;
        size_t beg_pos = beg + start;
        int i = 0;
        for (b = 0; b < num_of_blocks; b++) {
            
            r = beg_pos;
            
            // This loop will exclude meta chars
            while (map[r] != '\0' && len > i) {
                
                buff[buff_pos++] = map[r];
                r++;
                i++;
            }
            beg_pos += b_size;
        }
        
        buff[buff_pos] = '\0';
        return num_of_blocks;
    }
}