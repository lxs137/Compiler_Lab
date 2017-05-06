define compileAbstractTemplate
    @ cp DebugMacro.h ../DebugMacro.h
    @ cd .. && make > $(current_dir)/compile.output 2>&1
endef

define compileDetailTemplate
    @ cat compile.output
endef

define runAbstractTemplate
    @ for i in $1; \
    do \
        valgrind \
            --tool=memcheck \
            --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --log-file="mem_log_$$i" \
        ../parser $$i.cmm > $$i.output; \
    done
endef

define runDetailTemplate
    @ for i in $1; \
    do \
        cat $$i.output; \
    done
endef

define testAbstractTemplate
	@ for i in $1; \
	do \
	    cmp $$i.output $$i.expect; \
	done
endef

define testDetailTemplate
    @ for i in $1; \
    do \
        diff $$i.output $$i.expect; \
    done
endef

define checkMemoryAbstractTemplate
    @ ../checkMemory.sh $1
endef

define checkMemoryDetailTemplate
    @ for i in $1; \
    do \
        cat mem_log_$$i; \
    done
endef

define cleanTemplate
    - @ rm -f *.output
    - @ rm -f mem_log_*
    - @ rm -f core
endef

define updateExpectTemplate
	for i in $1; \
	do \
        mv $$i.output $$i.expect; \
	done
endef
