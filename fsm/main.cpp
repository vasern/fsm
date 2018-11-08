//
//  main.cpp
//  vasern
//
//  Created by Hieu (Jack) Nguyen on 8/11/18.
//  Copyright © 2018 Ambi Studio. All rights reserved.
//

#include <iostream>
#include "core/fsm.h"

int main(int argc, const char * argv[]) {
    
    // Init fsm and get writer
    vs::fsm db("./fsm_dump.bin", 1024);
    vs::fsm_writer* writer = db.open_writer();

    std::string buffer;

    // size = 574
    std::string data = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. "
        "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer "
        "took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries,"
        "but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s "
        "with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing "
        "software like Aldus PageMaker including versions of Lorem Ipsum.";
    
    // check file is open
    if (writer->opened) {
        for (int i = 0; i < 10; i++) {

            // write record
            // args(std::string, const char*, size_t)
            writer->write_record(&buffer, data.c_str(), data.size());
        }
    }
    
    // close file
    writer->close_conn();
    return 0;
}
