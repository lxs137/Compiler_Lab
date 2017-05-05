include ../commonFunction.md

.PHONY: all insert updateExpect clean

all: insert

insert: 
	@ $(call compileTemplate, '.') > unused_log
	@ $(call testTemplate, 1 2, '.')

clean:
	@ $(call cleanTemplate)

updateExpect:
	@ $(call updateExpectTemplate, 1 2, '.')
