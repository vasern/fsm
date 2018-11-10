# FSM Storage Engine (Fixed Size Mapping)

FSM is a fast, embedded transaction-log database. Allows a single write and many concurrent reads.
FSM has fixed size records and [map file to memory](https://stackoverflow.com/questions/192527/what-are-the-advantages-of-memory-mapped-files) for reading data to allow zero-copy.
Hence, the name stands for "Fixed Size Mapping".

FSM is developed as the [Vasern](https://github.com/vasern/vasern) storage engine and licensed under [Apache License](/LICENSE).

Table of contents:

- [Development Status](#development-status)
- [Performance](#performance)
- [Installation](#installation)
- [Example Code](#example-code)
- [APIs](#apis)
- [Help and feedback](#help-and-feedback)
- [Contribute](#contribute)
---

## Development Status

FSM is in development mode and is not production ready. A few APIs might need updated.

You can try FSM with [Make](https://en.wikipedia.org/wiki/Make_(software)) scripts including:
- `example`: compile the `example.cpp` file. Run `./example {command} {repeat}`
    - command: `run_write` to write records, or `run_read` to read records.
    - repeat(optional, default 1,000,000): number of records will be write/read
- `tests`: compile and run tests
- `cleanup`: remove all example, tests and data file generated.

## Performance

Results are conducted in a Macbook Pro 2014, 2.6 GHz i5, 8GB RAM, and with a 250GB Flash Storage. 
Each tests will be run 3 times. The results will give you an idea about FSM performance. You can find the source code at `fsmtests/example.cpp`.

### Write

Measure performance of writing 10 billions records with block size is 1024 (generate a 10GB data file).

| (real)  | (user) | (sys)   | writes/s      | MB/s     |
| ------- | ------ | ------- | ------------- | -------- |
| 28.904s | 9.001s | 13.608s | 345,972 ops/s | 354 MB/s |
| 29.680s | 9.495s | 14.678s | 336,927 ops/s | 345 MB/s |
| 28.065s | 9.158s | 14.005s | 356,315 ops/s | 365 MB/s |

### Read

Measure performance of reading 1 billions records with block size is 1024 (~a 1GB data file).

| (real) | (user) | (sys)  | reads/s       | MB/s     |
| ------ | ------ | ------ | ------------- | -------- |
| 2.293s | 2.012s | 0.275s | 436,109 ops/s | 444 MB/s |
| 2.292s | 2.014s | 0.269s | 436,300 ops/s | 445 MB/s |
| 2.308s | 2.035s | 0.264s | 433,275 ops/s | 442 MB/s |


## Installation

The easiest way is to download fsm, then copy and include into your project using:

```c++
#include "fsm/fsm.h"
```

## Example Code


```c++
// Init fsm and get writer
vs::fsm db("./fsm_dump.bin");
vs::fsm_writer* writer = db.open_writer();

std::string buffer;

std::string data = "Lorem Ipsum is simply dummy text of the printing and typesetting industry.";

// check connection is open
if (writer->opened) {

    for (int i = 0; i < 10; i++) {

        // write record
        // args(std::string*, const char*, size_t)
        writer->write_record(&buffer, data.c_str(), data.size());
    }
}

// close connection
writer->close_conn();
```

# APIs

Before you start, don't forget to [include FSM header file](#installation).
Note that FSM classes use namespace __`vs::`__ (short for Vasern).

## Start a FSM Instance

```c++
vs::fsm::fsm(const char* path);
```

#### Arguments
- path: file path

#### Example:
```c++
// absolute path might be required in some OS
vs::fsm db("./fsm_data.bin");
```

## 1. Writing data


### Quick example
```c++
vs::fsm_writer* writer = db.open_writer();

std::string r = "Lorem Ipsum is simply dummy text of the printing and typesetting industry.";
std::string buff;

// return number of blocks record consumed
int num_of_blocks = writer->write_record(&buff, r.c_str(), c.size());

writer->close_conn();
```

### 1.1. Open connection
```c++
vs::fsm_writer* = vs::fsm::open_writer();
```

#### Arguments _(N/A)_


### 1.2. Write data
```c++
int = vs::fsm_writer::write_record(sdt::string* buff, const char* data, size_t data_len);
```

#### Arguments:
- buff: an empty string, will be used as buffer to format string before write to data file
- data: record data as literal string (__`const char*`__)
- data_len: size of data (length of string)

#### Return:
- int: number of blocks data consume

### 1.3. Close connection
```c++
vs::fsm_writer::close_conn();
```

#### Arguments _(N/A)_

## 2.Reading data

You can load data using its block position. A block position is the order of the block in the structured data file. _End of each block contains 2 chars `meta data`. One is the total number of blocks the record consume(1-9), and the other is its distance counting from the first block(0-8)._

For example, let's have a `fsm` instance with the block size is 1024:
- If each record size is less than 1022
    - 1st block_position is 0
    - 2nd block_position is 1
- Or if each record size is more than 1022
    - 1st block_position is 0
    - 2nd block_position is 2

In practice, each record will have different number of blocks depend on the record size.

### Quick example

```c++
vs::fsm_reader* reader = db.open_reader();
std::string r = std::string(reader->write_record(0)); // read first record
reader->close_conn();
```

### 2.1. Open connection
```c++
vs::fsm_reader* = vs::fsm::open_reader();
```

#### Arguments _(N/A)_

### 2.2. Read/Get data by block position
```c++
vs::fsm_record = vs::fsm_reader::get_record(size_t block_position);
```

#### Arguments:
- block_position: the position (in order) of the block.

#### Return:
- vs::fsm_record: memory mapped arbitrary byte arrays values

### 2.3. Close connection
```c++
vs::fsm_writer::close_conn();
```

#### Arguments _(N/A)_

## 3. vs::fsm_record

Reading data will return a `vs::fsm_record` instance, contains a reference of memory-mapped file,
and the block position. At this point, record is still in lazy mode, which only be loaded when requested
through following methods.

### 3.1 Get content
```c++
void vs::fsm_record::c_str(char* buff)
```

#### Arguments
- buff: a buffer that will be used to assign record content

## Help and Feedback

- For quick questions, chat and discussion, [join us on Slack](https://join.slack.com/t/vasern/shared_invite/enQtNDU4NTk2MDI5OTcyLTRiYzRjZDI5YTAyMjlhYzg1YTdhNjFjZGNkODI1OTQwYzExZjA3NWRkYTY1MGE2ZjU0YzU3NzE2NzUwZmEwMjM).
- For bugs, suggest improvements, or feature requests, feel free to [file an issue](https://github.com/vasern/vasern/issues).

The more concise and informative, the better it helps us to understand your concern.

## Contribute

Your contributions are welcome and appreciated. At the moment, you can [create an issue](https://github.com/vasern/fsm/issues) with (1) Goal and (2) Details of your code.