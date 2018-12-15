//
//  block_write_stream.cpp
//  CiPlayground
//
//  Created by Hieu (Jack) Nguyen on 11/12/18.
//  Copyright © 2018 Ambi Studio. All rights reserved.
//

#include "block_writer.h"
#include "block_config.h"

namespace vs
{
    
    block_writer::block_writer(int _b_size)
    : buff(new char[_b_size])
    , pos(MT_BLOCK_START)
    , b_size(_b_size)
    , total_blocks(1)
    , total_props(-1)
    { }

    block_writer::~block_writer() {
        delete[] buff;
    }
    
    // ===========
    //  APPENDs
    // ===========

    void block_writer::assign(char* _buff, int _pos, int len) {
        
        if (free_size() < len) {
            push_block();
        }
        
        std::memcpy(&buff[_pos], &_buff[0], len);
    }

    void block_writer::append(const char* _buff, int len) {
        
        if (free_size() < len) {
            push_block();
        }
        
        std::memcpy(&buff[pos], &_buff[0], len);
        
        pos += len;
    }
    
    void block_writer::append(long double value) {
        
        if (free_size() < NUMBER_SIZE) {
            push_block();
        }
        
        std::memcpy(&buff[pos], (char*)&value, NUMBER_SIZE);
        pos += NUMBER_SIZE;
    }
    
    void block_writer::append(int value) {
        
        if (free_size() < TYPE_SIZE) {
            push_block();
        }
        
        buff[pos] = value;
        pos += TYPE_SIZE;
    }
    
    void block_writer::append(bool value) {
        
        if (free_size() < BOOL_SIZE) {
            push_block();
        }
        
        buff[pos] = value;
        pos += BOOL_SIZE;
    }
    
    // ===========
    //  FORMATER
    // ===========
    
    void block_writer::build_meta() {
        
        // Begining of block
        buff[MT_TOTAL_BLOCK] = total_blocks;
        buff[MT_TOTAL_PROPS] = total_props;
        
        // End of block
        buff[total_blocks * b_size - 1] = total_blocks;
        
    }
    
    // ===========
    //  I/O
    // ===========

    void block_writer::write(std::ofstream* writer) {
        
        build_meta();
        
        writer->write(buff, b_size);
        clear();
    }
    
    void block_writer::set_total_props(int total) {
        total_props = total;
    }
    
    // ===========
    //  UTILs
    // ===========
    
    void block_writer::clear() {
        memset(buff, 0, b_size);
        
        pos = MT_BLOCK_START;
        total_props = -1;
        total_blocks = 1;
    }

    int block_writer::size() {
        return b_size * total_blocks;
    }

    int block_writer::free_size() {
        return b_size * total_blocks - pos - 1;
    }
    
    void block_writer::push_block() {
        
        total_blocks++;
        
        char new_buff[b_size * total_blocks];
        std::memcpy(&new_buff[0], &buff[0], pos);
        
        delete[] buff;
        buff = new_buff;
    }
    
    int block_writer::num_of_blocks() {
        return total_blocks;
    }
} // vs
