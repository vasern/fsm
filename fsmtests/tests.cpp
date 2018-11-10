//* ===============================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//============================================================= */

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../fsm/fsm.h"
#include <string>

// Create a file path (~/Documents/fsm.bin)
const size_t block_size = 1024;
const size_t repeat = 10;

//NSString* path = [NSString stringWithFormat:@"%@/fsm.bin", [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]];
std::string line = "Because you say fileIn is an fstream object that is static and declared and instantiated in another method that is located in the same class I guess it is a pointer, really.";

vs::fsm fsm("./dump.bin", 1024);

TEST_CASE("Writer", "[fsm]")
{
    vs::fsm_writer *writer = fsm.open_writer();

    SECTION("Single write") {
        std::string buff;
        int num_of_blocks = 0;

        REQUIRE(writer->opened == true);

        if (writer->opened)
        {
            num_of_blocks = writer->write_record(&buff, line.c_str(), line.size());
            REQUIRE(num_of_blocks > 0);
        } 

        writer->close_conn();
        REQUIRE(writer->opened == false);
    }
}

TEST_CASE("Reader", "[fsm]")
{

    vs::fsm_reader *reader = fsm.open_reader();

    SECTION("Open")
    {
        REQUIRE(reader->opened == true);
    }

    SECTION("Single, sequential read")
    {
        char* buff;
        reader->get_record(0).c_str(buff);
        std::string record(buff);

        // Compare length
        REQUIRE( record.length() == line.length());
    }

    SECTION("Close")
    {
        reader->close_conn();
        REQUIRE(reader->opened == false);
    }

    printf("Test is completed, you might want to kill the Terminal.");
}

int test() {
    return 0;
}