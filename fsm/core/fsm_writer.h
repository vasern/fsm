//
//  fsm_writer.h
//  LoggerPage
//
//  Created by Hieu (Jack) Nguyen on 5/11/18.
//  Copyright © 2018 Ambi Studio. All rights reserved.
//

#ifndef fsm_writer_h
#define fsm_writer_h

#include <fstream>
#include "fsm_mode.h"

namespace vs {
    
    class fsm_writer: public fsm_mode {
    public:
        
        fsm_writer(const char* path, int block_size, int block_end);
        ~fsm_writer();
        
        // Write new record into data file (file must be already open)
        // A record can consume multiple blocks (when data_size > block_size)
        // Each block has its meta data contains 2 flags (the last 2 chars end of block):
        //      - (1) is the beggining of record
        //      - (2) its distance from the first record
        // Return number of data consume (min: 1, max 9)
        int write_record(std::string* buffer, const char* data, size_t data_size);
        
        // Close file stream (file should be already open)
        void close_conn();
        
        size_t file_size();
        
    private:
        
        // use for writing records
        std::ofstream file;
    };
}

#endif /* fsm_writer_h */
