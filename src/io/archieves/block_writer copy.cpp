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
    , pos(0)
    , b_size(_b_size)
    , r_size(_b_size - 5)
    , total_blocks(1)
    , total_props(-1)
    { }

    block_writer::~block_writer() {
        delete[] buff;
    }
    
    // ===========
    //  APPENDs
    // ===========

    void block_writer::assign(char* _buff, int pos, int len) {
        std::memcpy(&buff[pos], &_buff[0], len);
    }

    void block_writer::append(const char* _buff, int len) {
        
        if (free_size() < len) {
            
            // If current block not fit content
            // 1. Fill `_buff` to end of current block
            // 2. Calculate total blocks needed for whatever left in `_buff`
            // 3. Fill the rest of `_buff`
            
            int _size = free_size();
            
            // 1. Fill value to current block
            std::memcmp(&buff[pos], &_buff[0], _size);
            len -= _size;
            
            // 2. Calculate total blocks needed for whatever left in `_buff`
            short int i = 0, _total_blocks = len / r_size;
            if (len % r_size > 0) {
                _total_blocks++;
            }
            
            // 3. Fill the rest of `_buff`
            int content_len = 0;
            while (i++ < _total_blocks) {
                
                push_block();
                
                content_len = r_size % len;
                
                if (content_len < r_size) {
                    content_len = r_size - content_len;
                }
                
                std::memcmp(&buff[pos], &_buff[_size], content_len);
                
                _size += r_size;
                len -= content_len;
            }
            
            
        } else {
            std::memcpy(&buff[pos], &_buff[0], len);
        }
        
        pos += len;
    }
    
    void block_writer::append(long double value) {
        
        if (free_size() < NUMBER_SIZE) {
            push_block();
        }
        
        std::memcpy(&buff[pos], (char*)&value, NUMBER_SIZE);
        
    }
    
    void block_writer::append(int value) {
        
        if (free_size() < INT_SIZE) {
            push_block();
        }
        
        std::memcpy(&buff[pos], (char*)&value, INT_SIZE);
        
    }
    
    void block_writer::append(bool value) {
        
        if (free_size() < BOOL_SIZE) {
            push_block();
        }
        
        std::memcpy(&buff[pos], (char*)&value, BOOL_SIZE);
        
    }
    
    // ===========
    //  FORMATER
    // ===========
    
    void block_writer::build(upair_t record) {
        total_props = record.size();
        
        for (auto itr: record) {
            
            // TODO: assign represent value
            // append((char*)&props[itr.first]->represent, 4);
            
            itr.second->assign(this);
        }
    }
    
    void block_writer::build_meta() {
        
        short int i = 0;
        
        // write number of total props into first block meta
        buff[b_size - MT_TOTAL_PROPS] = total_props;
        
        // since i++, inside loop, i will start with 1
        while (i++ < total_blocks) {
            buff[i * b_size - MT_POS_BLOCK_N] = i;
            buff[i * b_size - MT_TOTAL_BLOCK] = total_blocks;
        }
        
    }
    
    // ===========
    //  I/O
    // ===========

    void block_writer::write(std::ofstream* writer) {
        
        build_meta();
        
        writer->write(buff, b_size);
    
        clear();
    }
    
    // ===========
    //  UTILs
    // ===========
    
    void block_writer::clear() {
        memset(buff, 0, b_size);
        pos = 0;
        total_props = -1;
        total_blocks = 1;
    }

    int block_writer::size() {
        return b_size;
    }

    int block_writer::free_size() {
        return r_size - (pos % r_size);
    }
    
    void block_writer::push_block() {
        
        char new_buff[b_size * total_blocks + b_size];
        std::memcpy(&new_buff[pos], &buff[0], total_blocks * b_size);
        
        delete[] buff;
        buff = new_buff;
        
        // move position to begining of next block
        pos = total_blocks * b_size;
        
        total_blocks++;
    }
    
} // vs
