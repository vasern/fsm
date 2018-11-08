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


_...TO BE UPDATED_
<!-- 
Results are conducted in a Macbook Pro 2014, 2.6 GHz i5, 8GB RAM.
_Note: The results proved to give you an idea about FSM performance_

```
Write: 
```

```
Read:
``` -->

## Installation

The easiest way is to download fsm, then copy and include into your project using:

```c++
#include "fsm/core/fsm.h"
```

## Example Code


```c++
// Init fsm and get writer
// arguments take file path, and block size
// Note:
//  Block size is based on the record length.
//  It can consume more than 1 blocks if record length > block size)
vs::fsm db("./fsm_dump.bin", 512);
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
vs::fsm::fsm(const char* path, size_t block_size);
```

#### Arguments
- path: file path
- block_size: record block size

#### Example:
```c++
// on some os, path must be absolute
// block size is 1kb
vs::fsm db("./fsm_data.bin", 1024);
```

## 1. Writing data


### Quick example
```c++
vs::fsm_writer* writer = db->open_writer();

std::string r = "Lorem Ipsum is simply dummy text of the printing and typesetting industry.";
writer->write_record(r.c_str(), c.size());

writer->close_conn();
```

### 1.1. Open connection
```c++
vs::fsm_writer* = vs::fsm::open_writer();
```

#### Arguments _(N/A)_


### 1.2. Write data
```c++
vs::fsm_writer::write_record(const char* data, size_t data_len);
```

#### Arguments:
- data: record data as literal string (__`const char*`__)
- data_len: size of data (length of string)

### 1.3. Close connection
```c++
vs::fsm_writer::close_conn();
```

#### Arguments _(N/A)_

## 2.Reading data

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
_For example, if each records take 2 blocks => 1st block_position = 0, 2nd block_position = 2, etc_


### 2.3. Close connection
```c++
// close
vs::fsm_writer::close_conn();
```

#### Arguments _(N/A)_

## Help and Feedback

- For quick questions, chat and discussion, [join us on Slack](https://join.slack.com/t/vasern/shared_invite/enQtNDU4NTk2MDI5OTcyLTRiYzRjZDI5YTAyMjlhYzg1YTdhNjFjZGNkODI1OTQwYzExZjA3NWRkYTY1MGE2ZjU0YzU3NzE2NzUwZmEwMjM).
- For bugs, suggest improvements, or feature requests, feel free to [file an issue](https://github.com/vasern/vasern/issues).

The more concise and informative, the better it helps us to understand your concern.

## Contribute

Your contributions are welcome and appreciated. At the moment, you can [create an issue](https://github.com/vasern/fsm/issues) with (1) Goal and (2) Details of your code.