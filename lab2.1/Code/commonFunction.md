define testTemplate
	for i in $1; \
	do echo; \
	echo Now testing $$i.cmm; \
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="mem_log_$$i" ../parser $$i.cmm > $$i.output; \
	echo Comparing; \
	diff $$i.output $2/$$i.expect; \
	wc -l mem_log_$$i; \
	done;
endef

define cleanTemplate
    -@ rm *.output
    -@ rm mem_log_*
    -@ rm core
    -@ rm unused_log
endef

define compileTemplate
    @ cp $1/DebugMacro.h ../DebugMacro.h
    @ cd .. && make
endef
