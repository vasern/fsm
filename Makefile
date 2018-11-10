files=fsm/fsm.cpp fsm/core/fsm_reader.cpp fsm/core/fsm_writer.cpp fsm/core/fsm_record.cpp

# Generate read and write example
example:
	rm -f main
	g++ -std=c++11 ${files} fsmtests/example.cpp -o example

# Run tests
tests:
	rm -f tests
	g++ -std=c++11 ${files} fsmtests/tests.cpp -o tests
	echo "\n\033[92mTests generated. If the program stopped after this message, it means tests passed.\033[0m\nYou'll need to manually close the program\n"
	./tests

# Remove all example and tests file generated
cleanup:
	rm -f ./sample_db.bin ./example ./tests ./dump.bin