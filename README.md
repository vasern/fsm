# FSM Storage Engine (Fixed Size Mapping)

FSM is a fast, embeded transaction-log database, with single write and multiple concurrent reads.
FSM has fixed size records and [map file to memory](https://stackoverflow.com/questions/192527/what-are-the-advantages-of-memory-mapped-files) for reading data to allow zero-copy.
Hence, the name stands for "Fixed Size Mapping".

FSM is originally developed as the [Vasern](https://github.com/vasern/vasern) storage engine.