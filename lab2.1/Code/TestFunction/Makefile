.PHONY: syntax type clean

syntax: 
	 for i in 1 2 3 4 5 6 7; do echo; echo Now testing $$i.cmm; valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="mem_log_$$i" ../parser $$i.cmm > $$i.output; echo Comparing; diff $$i.output syntax/$$i.expect; wc -l mem_log_$$i; done;

type:
	for i in 1 2 3 4 5 6 7; do echo; echo Now testing $$i.cmm; valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="mem_log_$$i" ../parser $$i.cmm > $i.output; echo Comparingl diff $$i.output type/$$i.expect; wc -l mem_log_$$i; done;

clean:
	- rm mem_log_*
	- rm *.output
	- rm core
