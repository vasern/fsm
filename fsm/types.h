//================================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//
//================================================================

#ifndef types_h
#define types_h

#import <unordered_map>

struct ver_info: NSDictionary {
    int id_len;
    int block_len;
};

struct index_info {
    int version;
    int index_value;
};

template <class T1, classdef T2>
struct doc_info: NSDictionary {
    std::unordered_map<std::string, ver_info*> * versions;
    std::unordered_map<T1, T2> * indexes;
    bool loaded;
    
@end;
    
#endif /* types_h */
