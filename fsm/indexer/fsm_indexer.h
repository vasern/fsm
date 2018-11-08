//
//  fs_indexer.hpp
//  Vasern
//
//  Created by Hieu (Jack) Nguyen on 5/11/18.
//  Copyright © 2018 Hieu (Jack) Nguyen. All rights reserved.
//

#ifndef fs_indexer_hpp
#define fs_indexer_hpp

#include <unordered_map>
#include <string>
#include "fsm_writer.h"

namespace vs {
    
    class fsm_indexer {
    public:
        
        // Initiate indexer with file directory and data block_size
        fsm_indexer(const char* dir, const char* name, size_t block_size);
        ~fsm_indexer();
        
        // Add an index value to 'indexes' dictionary
        // and write to indexes db file
        template <typename T>
        bool insert(const char* name, T key, int block_pos);
        
        // Find a value's block position from an index value
        template <typename T>
        int get_int(const char* name, T key);
        
        // Find multiple value's block position
        template <typename T>
        int* filter_int(const char* name, T filter[]);
        
    private:
        
        // in-memory storage
        std::unordered_map<std::string, std::unordered_map<id, int>> imstore;
        
        // db writer
        vs::fsm_writer* writer;
        
        // Directory path for index db files
        const char* dir;
        const char* name;
        
        // DB block size
        size_t block_size;
        
        // Load index saved from db files into imstore
        void init_load();
    };
}
#endif /* fs_indexer_hpp */
