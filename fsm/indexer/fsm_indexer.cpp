/* ===============================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//============================================================= */

#include "fsm_indexer.h"
#include "fsm_writer.h"
#include "config.h"
#include "utils.h"

#include <vector>
#include <sstream>

namespace vs {
    // Initiate indexer with file directory and data block_size
    fsm_indexer::fsm_indexer(const char* dir, const char* name, size_t block_size) :
    dir(dir), name(name), block_size(block_size) {
        init_load();
    };
    
    fsm_indexer::~fsm_indexer() {
//        writer->close_file();
    };
    
    // Add an index value to 'indexes' dictionary
    // and write to indexes db file
    template <typename T>
    bool fsm_indexer::insert(const char* name, T key, int block_pos) {
        
        imstore[name].insert({key, block_pos});
        std::string buffer;
        
        // Format record, more argument for size
        writer->write_record(&buffer, key, sizeof(name));
        
        return false;
    };
    
    // Find a value's block position from an index value
    template <typename T>
    int fsm_indexer::get_int(const char* name, T value) {
        return atoi(imstore[name][value]);
    };
    
    // Find multiple value's block position
    template <typename T>
    int* fsm_indexer::filter_int(const char* name, T filter[]) {
        
        std::vector<int> r;
        for (T* v in filter) {
            r.push_back(imstore[std::string(name)][v]);
        }
        return &r[0];
    };
    
    // Load indexes saved from db file into imstore
    
    void fsm_indexer::init_load() {
        
        std::stringstream path;
        path << dir << "/_" << name << vs_config::INDEX_EXT;
        
        // 1. Load what properties were indexed
        
        //        vs::fsm_writer* file(path.str().c_str(), vs_config::INDEX_BLOCK_SIZE);
        //        file.open('r');
        
        std::vector<std::string> names { "ab", "vd" };
        
        size_t size = 0;
        size_t num_of_records = 0;
        
        std::unordered_map<int, int> indexes;
        std::string str_buff("");
        const char* buffer;
        
        // 2. Loop through each indexed properties
        //    and loaded all index variables into memory
        for (std::string i_name: names) {
            path << dir << "/" << i_name << vs_config::INDEX_EXT;
            
//            vs::fsm_writer file(path.str().c_str(), vs_config::INDEX_BLOCK_SIZE);
//            file.open_file('r');
//            size = file.file_size();
//            num_of_records = size / vs_config::INDEX_BLOCK_SIZE;
//            
//            if (size % vs_config::INDEX_BLOCK_SIZE != 0) {
//                num_of_records++;
//            }
//            
//            for (int i = 0; i < num_of_records; i++) {
////                buffer = file.get_record(i);
//                imstore[i_name][0] = 0;
//            }
        }
        
    };
    
} // namespace vs
