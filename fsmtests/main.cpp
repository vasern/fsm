//
//  fsm_tests.m
//  fsm_tests
//
//  Created by Hieu (Jack) Nguyen on 8/11/18.
//  Copyright © 2018 Ambi Studio. All rights reserved.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../fsm/core/fsm.h"
#include <string>

// Create a file path (~/Documents/fsm.bin)
const size_t block_size = 1024;
const size_t repeat = 10;

//NSString* path = [NSString stringWithFormat:@"%@/fsm.bin", [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]];
std::string line = "Because you say fileIn is an fstream object that is static and declared and instantiated in another method that is located in the same class I guess it is a pointer, really.";


vs::fsm fsm("/Users/hieunc/Desktop/Vase/Projects/vasern/fsmtests/", block_size);

TEST_CASE("Writer", "[fsm]") {
    
    
    vs::fsm_writer* writer = fsm.open_writer();
    
    SECTION("Open") {
        
        REQUIRE( writer->opened == true );
    }
    
   SECTION("Single write") {
       std::string buff;
       int num_of_blocks = 0;

       if (writer->opened) {
           num_of_blocks = writer->write_record(&buff, line.c_str(), line.size());
       }

       REQUIRE( num_of_blocks > 0 );
   }
    
    SECTION("Close") {

        writer->close_conn();
        REQUIRE( writer->opened == false );
    }
}

TEST_CASE( "Reader", "[fsm]") {

    vs::fsm_reader* reader = fsm.open_reader();

    SECTION("Open") {
        REQUIRE( reader->opened == true );
    }


   SECTION("Single, sequential read") {
       std::string record = std::string(reader->get_record(0).c_str());

       REQUIRE( record.compare(line) == 0 );
   }

    SECTION("Close") {
        reader->close_conn();
        REQUIRE( reader->opened );
    }
}
