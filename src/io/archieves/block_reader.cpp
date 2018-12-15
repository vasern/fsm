//
//  br_stream.cpp
//  CiPlayground
//
//  Created by Hieu (Jack) Nguyen on 11/12/18.
//  Copyright © 2018 Ambi Studio. All rights reserved.
//

#include "block_reader.h"
#include "block_helper.h"
#include "block_config.h"
#include "../values/value_f.h"

namespace vs {
    
    block_reader::block_reader(unsigned long _begin, char* _fmap, descript_t* _prop_desc, block_desc_t* _desc)
    : begin(_begin)
    , fmap(_fmap)
    , prop_desc(_prop_desc)
    , desc(_desc)
    { }
    
    // ===========
    //  DATA EXTRACTORs
    // ===========
    
    // Load then return key and indexes
    upair_t block_reader::tags() {
        upair_t rs;
        
        size_t pos = begin + MT_BLOCK_START;
        int total_props = (int)prop_desc->size();
        ulist_t props;
        block_helper::read_list(&props, &pos, total_props, fmap);
        
        int i = 0;
        for (auto itr: *prop_desc) {
            rs[itr.first] = props[i++];
        }
        
        return rs;
    }
    
    // Load then return all properties and values
    upair_t block_reader::object(std::unordered_map<int, std::string> schemas) {
        upair_t rs;
        
        size_t pos = begin + MT_BLOCK_START;
        int total_props = fmap[begin + MT_TOTAL_PROPS] & 0xff;
        int i = 0, type;
        ulist_t props;
        prop_desc_t ptype;
        std::string prop;
        
        while (i++ < total_props) {
            
            type = fmap[pos] & 0xff;
            prop = schemas[type];
            ptype = (*prop_desc)[prop];
            pos += TYPE_SIZE;
            
            switch (ptype.type) {
                    
                case STRING:
                    
                    rs[prop] = block_helper::get_str(&pos, fmap);
                    break;
                    
                case NUMBER:
                    
                    rs[prop] = block_helper::get_number(pos, fmap);
                    pos += NUMBER_SIZE;
                    
                    break;
                    
                case BOOLEAN:
                    
                    rs[prop] = block_helper::get_bool(pos, fmap);
                    pos += BOOL_SIZE;
                    break;
                    
                case OBJECT: {
                    
                    upair_t ob;
                    type = (int)(fmap[pos] & 0xff);
                    pos += TYPE_SIZE;
                    
                    block_helper::read_obj(&ob, &pos, type, fmap);
                    rs[prop] = value_f::create(ob);
                    break;
                }
                case LIST: {
                    
                    ulist_t list;
                    type = (int)(fmap[pos] & 0xff);
                    pos += TYPE_SIZE;
                    
                    block_helper::read_list(&list, &pos, type, fmap);
                    rs[prop] = value_f::create(list);
                    
                    break;
                }
                default:
                    break;
            }
        }
        
        return rs;
    }
    
    // Load and return only properties that match `props`
    upair_t block_reader::get(std::vector<std::string> props) {
        upair_t rs;
        
        return rs;
    }
    
    
    // ===========
    //  NAVIGATORs
    // ===========
    
    void block_reader::next() {
        int b_s = desc->b_size * (int)(fmap[begin] & 0xff);
        begin += b_s;
    }
    
    void block_reader::prev() {
        begin -= desc->b_size * (fmap[begin] & 0xff);
    }
    
    block_reader* block_reader::next_ptr() {
        return new block_reader(begin + desc->b_size * (fmap[begin] & 0xff), fmap, prop_desc, desc);
    }
    
    block_reader* block_reader::prev_ptr() {
        return new block_reader(begin - desc->b_size * (fmap[begin] & 0xff), fmap, prop_desc, desc);
    }
    
    // ===========
    //  UTILS
    // ===========
    
    
}
