/* ===============================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//============================================================= */

#include "fsm_writer.h"
#include "../config.h"
#include <sys/stat.h>

namespace vs {
    
    // Constructor
    fsm_writer::fsm_writer(const char * path):
        fsm_mode(path)
    {
        if (strlen(path) != 0) {
            file.open(path, std::ios::binary | std::ios::app);
            opened =  file.is_open();
        } else {
            opened = false;
        }
        
    }
    
    
    // Destructor
    fsm_writer::~fsm_writer() {
        close_conn();
    }
    
    // Write new record into data file (file must be already open)
    // A record can consume multiple blocks (when data_size > block_size)
    // Each block has its meta data contains 2 flags (the last 2 chars end of block):
    //      - (position: block_size - 2) is the beggining of record
    //      - (position: block_size - 1) its distance from the first record
    int fsm_writer::write_record(std::string* buffer, const char* data, size_t data_size) {
        
        buffer->assign(data);
        
        // Calculate number of blocks needed
        int total_blocks = (int)(data_size / vs_config::BLOCK_SIZE);
        if (data_size % vs_config::BLOCK_SIZE != 0) {
            total_blocks++;
        }
        
        // convert total blocks to char
        // (writing 2 number next to each other caused confusion when reading)
        char total_blocks_char = total_blocks;
        
        // Split data into blocks and write to data file
        // (with meta data in each block)
        for (int i = 0; i < total_blocks; i++) {
            file.write(buffer->substr(i * vs_config::RECORD_SIZE, (i + 1) * vs_config::RECORD_SIZE).c_str(), vs_config::RECORD_SIZE);
            file << total_blocks_char << i;
        }
        
        return total_blocks;
    }
    
    
    // close file
    void fsm_writer::close_conn() {
        if (opened == true) {
            file.close();
            opened = false;
        }
    }
    
    // Get file size
    size_t fsm_writer::file_size() {
        
        struct stat st;
        fstat(*path, &st);
        return st.st_size;
    }
}
