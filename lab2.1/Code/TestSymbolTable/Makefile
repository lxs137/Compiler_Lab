include ../commonFunction.md

.PHONY: all insert clean updateExpect

all: insert

insert: 
	@ $(call compileTemplate, '.') > unused_log
	@ $(call testTemplate, 1 2, '.')

clean:
	@ $(call cleanTemplate)

updateExpect:
	@ $(call updatExpectTemplate, 1 2, '.')
