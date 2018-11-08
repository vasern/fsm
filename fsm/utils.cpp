//================================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//================================================================

#include "utils.h"
#include "config.h"

namespace vs_utils {
    
    int atoi( char * str )
    {
        int val = 0;
        while( *str ) {
            val = val*10 + (*str++ - '0');
        }
        return val;
    }
    
} // namespace vasern
