/* ===============================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//============================================================= */

#ifndef Header_h
#define Header_h

typedef unsigned long size_t;

namespace vs {
    class record_desc {
    public:
        
        record_desc(char*& map_add, size_t begin_pos, size_t block_size, size_t record_size):
        map(map_add),
        beg(begin_pos),
        b_size(block_size),
        r_size(record_size)
        { }
        
        const char* c_str() {
            
            // buffer with max size = block size (except meta) * number of blocks
            int num_of_blocks = map[beg + r_size] & 0xff;
            
            char buff[r_size * num_of_blocks];
            int r = 0, b = 0; // row & block iterator
            size_t buff_pos = 0;
            size_t beg_pos = beg;
            
            for (b = 0; b < num_of_blocks; b++) {
                
                r = 0;
                
                // This loop will not added the last 2 chars
                while (map[beg_pos + r] != '\0') {
                    
                    buff[buff_pos++] = map[beg_pos + r];
                    r++;
                }
                beg_pos += b_size;
            }
            
            buff[++buff_pos] = '\0';
            
            return buff;
        }
        
        record_desc next() {
            
            size_t next_block_beg = beg +
                ((map[beg + r_size] & 0xff) * b_size) + 1;
            
            return record_desc(map, next_block_beg, b_size, r_size);
        }
        
        record_desc prev() {
            size_t last_block_beg = beg -
                (map[beg - 1] & 0xff * b_size);
            return record_desc(map, last_block_beg, b_size, r_size);
        }
        
        const char* substr(int len) {
            return "";
        }
        
        const char* substr(int start, int len) {
            return "";
        }
        
    private:
        
        char*& map;
        const size_t beg;
        const size_t b_size;
        const size_t r_size;
    };
}

#endif /* Header_h */
