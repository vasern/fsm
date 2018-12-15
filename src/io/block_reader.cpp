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
    
    block_reader::block_reader(unsigned long _begin, char* _fmap, layout_t *_layout)
    : begin(_begin)
    , fmap(_fmap)
    , layout(_layout)
    { }
    
    // ===========
    //  DATA EXTRACTORs
    // ===========
    
    // Load then return key and indexes
    upair_t block_reader::tags() {
        upair_t rs;
        
        size_t pos;
        
        for (auto itr: layout->keys) {
            
            pos = begin + layout->index_of(itr.name);
            switch (itr.type) {
                    
                case STRING:
                    
                    rs[itr.name] = block_helper::get_str(&pos, fmap);
                    break;
                    
                case NUMBER:
                    
                    rs[itr.name] = block_helper::get_number(pos, fmap);
                    break;
                    
                case BOOLEAN:
                    
                    rs[itr.name] = block_helper::get_bool(pos, fmap);
                    break;
                    
                default:
                    break;
            }
        }
        
        return rs;
    }
    
    // Load then return all properties and values
    upair_t block_reader::object() {
        upair_t rs;
        
        size_t pos = begin + MT_BLOCK_START;
        int total_props = fmap[begin + MT_TOTAL_PROPS] & 0xff;
        int i = 0, type;
        ulist_t props;
        type_desc_t ptype;
        std::string prop;
        
        while (i++ < total_props) {
            
            prop = layout->name_of((int)fmap[pos] & 0xff);
            ptype = layout->type_of(prop);
            pos += TYPE_SIZE;
            
            switch (ptype) {
                    
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
        int b_s = layout->size() * (int)(fmap[begin] & 0xff);
        begin += b_s;
    }
    
    void block_reader::prev() {
        begin -= layout->size() * (fmap[begin] & 0xff);
    }
    
    block_reader* block_reader::next_ptr() {
        return new block_reader(begin + layout->size()  * (fmap[begin] & 0xff), fmap, layout);
    }
    
    block_reader* block_reader::prev_ptr() {
        return new block_reader(begin - layout->size() * (fmap[begin] & 0xff), fmap, layout);
    }
    
    // ===========
    //  UTILS
    // ===========
    
    int block_reader::total_blocks() {
        return fmap[begin] & 0xff;
    }
    
    bool block_reader::is_valid() {
        return (fmap[begin] & 0xff) != 0;
    }
}
