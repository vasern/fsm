/*
 * STREAM READER
 */
#ifndef br_stream_h
#define br_stream_h

#include <unordered_map>
#include <vector>

#include "../types.h"
#include "../values/value_t.h"
#include "../layout.h"

namespace vs {
    
    class block_reader {
    public:
        
        block_reader(unsigned long begin, char* mmap_file, layout_t* layout);
        
        // Load then return key and indexes
        upair_t tags();
        
        // Load then return all properties and values
        upair_t object();
        
        // Load and return only properties that match `props`
        upair_t get(std::vector<std::string> props);
        
        // Navigate between blocks
        void next();
        void prev();
        block_reader* next_ptr();
        block_reader* prev_ptr();
        
        int total_blocks();
        bool is_valid();
        
    private:
        
        char* fmap;
        unsigned long begin;
        layout_t *layout;
    };
}

#endif /* br_stream_hpp */
