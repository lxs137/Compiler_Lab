include ../commonFunction.md

.PHONY: all syntax type clean

all: syntax type

syntax: 
	@ $(call compileTemplate, 'syntax') > unused_log
	@ $(call testTemplate, 1 2 3 4 5 6 7 8, 'syntax')

type:
	@ $(call compileTemplate, 'type') > unused_log
	@ $(call testTemplate, 1 2 3 4 5 6 7 8, 'type')

clean:
	@ $(call cleanTemplate)
