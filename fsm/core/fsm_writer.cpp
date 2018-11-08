//
//  fsm_writer.m
//  LoggerPage
//
//  Created by Hieu (Jack) Nguyen on 5/11/18.
//  Copyright © 2018 Ambi Studio. All rights reserved.
//

#import "fsm_writer.h"
#include <sys/stat.h>

namespace vs {
    
    // Constructor
    fsm_writer::fsm_writer(const char * path, int block_size, int record_size):
        fsm_mode(block_size, record_size)
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
        int total_blocks = (int)(data_size / b_size);
        if (data_size % b_size != 0) {
            total_blocks++;
        }
        
        // convert total blocks to char
        // (writing 2 number next to each other caused confusion when reading)
        char total_blocks_char = total_blocks;
        
        // Split data into blocks and write to data file
        // (with meta data in each block)
        for (int i = 0; i < total_blocks; i++) {
            file.write(buffer->substr(i * r_size, (i + 1) * r_size).c_str(), r_size);
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
        
        struct stat file_info = {0};
        int fd = 0;
        fstat(fd, &file_info);
        
        size_t size = file_info.st_size;
        
        return size;
    }
}
