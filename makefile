# build-part1: part1.out

# part1.out: part1_searcher.cpp
# 	g++ -g part1_searcher.cpp -o part1.out

# run-part1: part1.out
# 	./part1.out file.txt NGTNIJGK 0 67108863

# clean-part1:
# 	rm part1.out

# build-part2: part2.out

# part2.out: part2_partitioner.cpp
# 	g++ -g part2_partitioner.cpp -o part2.out

# run-part2: part2.out
# 	./part2.out file.txt NGTNIJGK 0 127 32

# clean-part2:
# 	rm part2.out

# clean:
# 	rm *.out
# Targets for Part 1
# Part 1 Targets
build-part1: part1.out

part1.out: part1_searcher.cpp
	g++ -g part1_searcher.cpp -o part1.out

run-part1: part1.out
	./part1.out file.txt NGTNIJGK 0 67108863

clean-part1:
	rm -f part1.out

# Part 2 Targets
build-part2: part2.out part2_searcher.out

part2.out: part2_partitioner.cpp
	g++ -g part2_partitioner.cpp -o part2.out

part2_searcher.out: part2_searcher.cpp
	g++ -g part2_searcher.cpp -o part2_searcher.out

run-part2: part2.out part2_searcher.out
	./part2.out file.txt NGTNIJGK 0 67108863 8388608

clean-part2:
	rm -f part2.out part2_searcher.out

# Part 3 Targets
build-part3: part3.out part3_searcher.out 

part3.out : part3_partitioner.cpp
	g++ -g part3_partitioner.cpp -o part3.out

part3_searcher.out : part3_searcher.cpp
	g++ -g part3_searcher.cpp -o part3_searcher.out

run-part3: part3.out part3_searcher.out
	./part3.out file.txt NGTNIJGK 0 67108863 8388608

clean-part3:
	rm -f part3.out part3_searcher.out

# Clean all
clean: clean-part1 clean-part2 clean-part3
