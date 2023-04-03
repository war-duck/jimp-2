kompresja:
	@$(CC) -o kompresja compressor/main.c compressor/compressor.c compressor/encode.c compressor/make_dict.c compressor/output.c compressor/queue.c compressor/stack.c compressor/tree.c

kompresjad:
	@$(CC) -DDEBUG -o kompresjad compressor/main.c compressor/compressor.c compressor/encode.c compressor/make_dict.c compressor/output.c compressor/queue.c compressor/stack.c compressor/tree.c

dekompresja:
	@$(CC) -o dekompresja decompressor/decompressor.c

test1:
	@make kompresjad
	@./kompresjad -i tests/test1.txt
	@make clean

test2:
	@make dekompresja
	@./dekompresja tests/test2.cps
	@make clean

test3:
	@make kompresjad
	@apg -a 1 -m 100 -x 100 -M L > tests/test3.txt
	@./kompresjad -i tests/test3.txt
	@make clean

test4:
	@make kompresja
	@make dekompresja
	@apg -a 1 -m 150 -x 150 -M CL > tests/test4_v1.txt
	@apg -a 1 -m 150 -x 150 -M CL > tests/test4_v1.txt
	@cp tests/test4_v1.txt tests/test4.txt
	@./kompresja -i tests/test4.txt
	@./dekompresja tests/test4.cps
	@echo "Roznice miedzy plikami przed kompresja i po dekompresji:"
	@diff tests/test4.txt tests/test4_v1.txt
	@echo
	@make clean

cleantst:
	@rm tests/test1.cps tests/test2.txt tests/test3.cps tests/test3.txt tests/test4.txt tests/test4_v1.txt tests/test4.cps

clean:
	@rm kompresja kompresjad dekompresja
