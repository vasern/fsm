files=fsm/core/fsm.cpp fsm/core/fsm_reader.cpp fsm/core/fsm_writer.cpp fsm/core/fsm_record.cpp

example:
	rm -f main
	g++ -std=c++11 ${files} fsmtests/example.cpp -o main

tests:
	rm -f tests
	g++ -std=c++11 ${files} fsmtests/tests.cpp -o tests
	# ./tests

cleanup:
	rm -f ./sample_db.bin ./main ./tests ./dump.bin