/* ===============================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//============================================================= */

#include "fsm_reader.h"
#include "../config.h"

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

namespace vs {
    
    fsm_reader::fsm_reader(const char* path, int block_size) : fsm_mode(path, block_size)
    {
        
        fd = open(path, O_RDONLY, (mode_t)0600);
        
        // mmap file start to end
        // (allows null chars)
        off_t pos = lseek(fd, 0, SEEK_CUR);
        off_t size = lseek(fd, 0, SEEK_END);
        lseek(fd, pos, SEEK_SET);
        
        int prot = PROT_READ;
        int flags = MAP_PRIVATE;
        
        void* ptr;
        int pagesize = getpagesize();
        if (size % pagesize != 0) {
            ptr = mmap(NULL, size + 1, prot, flags, fd, 0);
        } else {
            size_t fullsize = size + pagesize;
            ptr = mmap(NULL, fullsize, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
            ptr = mmap(ptr, fullsize, prot, flags | MAP_FIXED, fd, 0);
        }
        opened = ptr != MAP_FAILED;
        map = (char*)ptr;
    }
    
    fsm_reader::~fsm_reader() {
        close_conn();
    }
    
    fsm_record fsm_reader::get_record(int block_pos) {
        return fsm_record(map, block_pos * b_size, b_size, r_size);
    }
    
    // Un-map and close file
    void fsm_reader::close_conn() {
        if (opened == true) {
            munmap(map, file_info.st_size);
            close(fd);
            opened = false;
        }
    }
    
} // namespace vs
