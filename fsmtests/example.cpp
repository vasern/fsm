//* ===============================================================
//
//  Copyright by Ambi Studio 2018
//  Licensed under the Apache License, Version 2.0 (the "License");
//  (Please find "LICENSE" file attached for license details)
//============================================================= */

#include "../fsm/fsm.h"

size_t repeat = 1000000;
std::string str = "After a month in production, I recently finished un-breaking a process I rewrote from scratch for my company. Despite painstaking efforts to replicate the production environment elsewhere, we couldn't reproduce it in any environment but production. At wits' end, I finally got approval to run production data through the system on my development workstation. Lo and behold, the same symptoms manifested plain as day. I profiled the application and traced the CPU load to an XSL transformation.";
void write(vs::fsm_writer *writer)
{

    std::string buff;
    int num_of_blocks = -1;

    if (writer->opened)
    {
        for (int i = 0; i < repeat; i++)
        {
            num_of_blocks = writer->write_record(&buff, str.c_str(), str.size());
        }

        writer->close_conn();
        printf("Inserted: %zu records. Number of blocks the last record consume: %d\n", repeat, num_of_blocks);
    }
    else
    {
        printf("Unable to insert data\n");
    }
}

void read(vs::fsm_reader *reader)
{

    if (reader->opened)
    {

        // This loop is legit in this case
        // since str data size is less than 1024 (1kb, by default)
        int i = 0;
        char* buff;
        while (i < repeat)
        {
            reader->get_record(i).c_str(buff);
            i++;
        }
        printf("Read %zu records!\n", repeat);
        printf("Last record content: %s\n", buff);
        reader->close_conn();
    }
    else
    {
        printf("Unable to read data. Check if data file is existed!\n");
    }
}

int main(int argc, const char *argv[])
{

    vs::fsm fsm("./sample_db.bin");

    if (argc > 1)
    {

        if (argc == 3)
        {
            const char *n_size = argv[2];
            repeat = atoi(n_size);
        }

        const char *arg = argv[1];

        if (strcmp(arg, "run_write") == 0)
        {

            write(fsm.open_writer());
            return 0;
        }
        else if (strcmp(arg, "run_read") == 0)
        {

            // Run read file
            read(fsm.open_reader());
            return 0;
        }
    }
    
    printf("Invalid argument provided. Run program with either 'run_write' or 'run_read' argument\n");

    return 1;
}
