
default: design.cpp
	# g++ main.cpp -std=c++11 -o main
	# clang -O2 design.cpp src/*.cpp src/values/*.cpp src/io/*.cpp -o main -std=c++11 -lstdc++
	clang -O3 design.cpp src/*.cpp src/values/*.cpp src/io/*.cpp -o main -std=c++11 -lstdc++
	clear && echo "COMPLETED"

clean:
	rm -f ./main ./wb.bin ./data.bin
	make