include ../commonFunction.md

.PHONY: all syntax updateSyntaxExpect type updateTypeExpect clean

all: syntax type

syntax: 
	@ $(call compileTemplate, 'syntax') > unused_log
	@ $(call testTemplate, 1 2 3 4 5 6 7 8, 'syntax')

updateSyntaxExpect:
	@ $(call updateExpectTemplate, 1 2 3 4 5 6 7 8 , 'syntax')

type:
	@ $(call compileTemplate, 'type') > unused_log
	@ $(call testTemplate, 1 2 3 4 5 6 7 8, 'type')

updateTypeExpect:
	@ $(call updateExpectTemplate, 1 2 3 4 5 6 7 8 , 'type')

clean:
	@ $(call cleanTemplate)
