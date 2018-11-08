/* ===============================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//============================================================= */

#include "fsm_reader.h"

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

namespace vs {
    
    fsm_reader::fsm_reader(const char* path, int b_size, int b_end) :
        fsm_mode(b_size, b_end)
    {
        
        fd = open(path, O_RDONLY, (mode_t)0600);
        file_info = {0};
        
        if (fstat(fd, &file_info) != -1 || file_info.st_size > 0) {
            
            // mmap file start to end
            // (allows null chars)
            off_t pos = lseek(fd, 0, SEEK_CUR);
            off_t size = lseek(fd, 0, SEEK_END);
            lseek(fd, pos, SEEK_SET);
            
            int prot = PROT_READ;
            int flags = MAP_PRIVATE;
            int pagesize = getpagesize();
            
            if (size % pagesize != 0) {
                map = (char*)mmap(NULL, size + 1, prot, flags, fd, 0);
            } else {
                size_t fullsize = size + pagesize;
                map = (char*)mmap(NULL, fullsize, PROT_NONE, MAP_ANON, -1, 0);
                map = (char*)mmap(map, fullsize, prot, flags | MAP_FIXED, fd, 0);
            }
            
            opened = true;
        } else {
            
            // File not exists
            opened = false;
        }

    }
    
    fsm_reader::~fsm_reader() {
        close_conn();
    }
    
    record_desc fsm_reader::get_record(int block_pos) {
        return record_desc(map, block_pos * b_size, b_size, r_size);
    }
    
    // Un-map and close file
    void fsm_reader::close_conn() {
        if (opened == true) {
            munmap(map, file_info.st_size);
            close(fd);
            opened = false;
        }
    }
    
    size_t fsm_reader::file_size() {
        return file_info.st_size;
    }
    
} // namespace vs
