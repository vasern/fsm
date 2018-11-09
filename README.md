# FSM Storage Engine (Fixed Size Mapping)

FSM is a fast, embedded transaction-log database. Allows a single write and many concurrent reads.
FSM has fixed size records and [map file to memory](https://stackoverflow.com/questions/192527/what-are-the-advantages-of-memory-mapped-files) for reading data to allow zero-copy.
Hence, the name stands for "Fixed Size Mapping".

FSM is developed as the [Vasern](https://github.com/vasern/vasern) storage engine and licensed under [Apache License](/LICENSE).

Table of contents:

- [Current Status](#current-status)
- [Performance](#performance)
- [Installation](#installation)
- [Example Code](#example-code)
- [APIs](#apis)
- [Help and feedback](#help-and-feedback)
- [Contribute](#contribute)
---

## Current Status

FSM is in development mode and is not production ready. A few APIs might need updated.

## Performance

Results are conducted in a Macbook Pro 2014, 2.6 GHz i5, 8GB RAM on a 250GB Flash Storage. The results will give you an idea about FSM performance. _You can find the source code at `fsmtests/example.cpp`_

### Write

Measure performance of writing 10 billions records.

| (real)  | (user) | (sys)   | writes/s      | MB/s     |
| ------- | ------ | ------- | ------------- | -------- |
| 28.904s | 9.001s | 13.608s | 345,972 ops/s | 354 MB/s |
| 29.680s | 9.495s | 14.678s | 336,927 ops/s | 345 MB/s |
| 28.065s | 9.158s | 14.005s | 356,315 ops/s | 365 MB/s |

### Read

Measure performance of reading 1 billions records.

| (real) | (user) | (sys)  | reads/s       | MB/s     |
| ------ | ------ | ------ | ------------- | -------- |
| 2.293s | 2.012s | 0.275s | 436,109 ops/s | 444 MB/s |
| 2.292s | 2.014s | 0.269s | 436,300 ops/s | 445 MB/s |
| 2.308s | 2.035s | 0.264s | 433,275 ops/s | 442 MB/s |


## Installation

The easiest way is to download fsm, then copy and include into your project using:

```c++
#include "fsm/core/fsm.h"
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

Before you start, don't forget to (include FSM header file)[#installation].
_Note: FSM has the namespace __`vs::`__ (short for Vasern).

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
vs::fsm_writer* writer = db->open_writer();

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

You can load data using its block position. A block position is the order of the block in the structured
data file. Note that end of each block is its `meta data` (2 chars).

For example, let's have a `fsm` instance with block size is 1024:
- If each record size is less than 1022, 1st block_position = 0, 2nd block_position = 1, etc.
- Or if each record size is more than 1022, 1st block_position = 0, 2nd block_position = 2, etc.

In practice, each record will have different number of blocks depend on data size.

### Quick example

```c++
vs::fsm_reader* reader = db->open_reader();
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
vs::fsm_reader::get_record(size_t block_position);
```

#### Arguments:
- block_position: the position (in order) of the block.

### 2.3. Close connection
```c++
vs::fsm_writer::close_conn();
```

#### Arguments _(N/A)_

## Help and Feedback

- For quick questions, chat and discussion, [join us on Slack](https://join.slack.com/t/vasern/shared_invite/enQtNDU4NTk2MDI5OTcyLTRiYzRjZDI5YTAyMjlhYzg1YTdhNjFjZGNkODI1OTQwYzExZjA3NWRkYTY1MGE2ZjU0YzU3NzE2NzUwZmEwMjM).
- For bugs, suggest improvements, or feature requests, feel free to [file an issue](https://github.com/vasern/vasern/issues).

The more concise and informative, the better it helps us to understand your concern.

## Contribute

Your contributions are welcome and appreciated. At the moment, you can [create an issue](https://github.com/vasern/fsm/issues) with (1) Goal and (2) Details of your code.