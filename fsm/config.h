//
//  config.h
//  fsm-dev
//
//  Created by Hieu (Jack) Nguyen on 9/11/18.
//  Copyright © 2018 Ambi Studio. All rights reserved.
//

#ifndef config_h
#define config_h

namespace vs_config {
    
    const static int BLOCK_SIZE = 1024;
    const static int META_SIZE = 2;
    const static int RECORD_SIZE = BLOCK_SIZE - META_SIZE;
    
    static const char* INDEX_EXT = ".vsi";
    static const float FSM_VERSION = 0.3;
}

#endif /* config_h */
