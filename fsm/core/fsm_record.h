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
        
        fsm_record(char* map_add, size_t begin_pos);
        
        const char* c_str();
        
        fsm_record next();
        
        fsm_record prev();
        
        const char* substr(int len);
        
        const char* substr(int start, int len);
        
    private:
        
        char* map;
        const size_t beg;
    };
}

#endif /* Header_h */
