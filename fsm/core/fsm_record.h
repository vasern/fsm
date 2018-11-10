/* ===============================================================
 //
 //  Copyright by Ambi Studio 2018
 //  Licensed under the Apache License, Version 2.0 (the "License");
 //  (Please find "LICENSE" file attached for license details)
 //============================================================= */

#ifndef fsm_record_h
#define fsm_record_h

typedef unsigned long size_t;

namespace vs {
    
    class fsm_record {
    public:
        
        fsm_record(char* map_add, size_t begin_pos, int block_size, int record_size);
        
        // Get a whole record content into buffer
        // Return number of blocks record consumed
        int c_str(char* buff);
        
        // Get next record
        fsm_record next();
        
        // Get previous record
        fsm_record prev();
        
        // Get a part of record content
        // counting from 0
        int substr(char* buff, int len);
        
        int substr(char* buff, int start, int len);
        
    private:
        
        char* map;
        const size_t beg;
        int b_size;
        int r_size;
    };
}

#endif /* Header_h */
