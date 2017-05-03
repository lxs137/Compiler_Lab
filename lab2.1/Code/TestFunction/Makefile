include ../commonFunction.md

.PHONY: syntax type clean

all: syntax type

syntax: 
	@ $(call compileTemplate, 'syntax')
	@ $(call testTemplate, 1 2 3 4 5 6 7 8, 'syntax')

type:
	@ $(call testTemplate, 1 2 3 4 5 6 7 8, 'type')

clean:
	@ $(call cleanTemplate)
