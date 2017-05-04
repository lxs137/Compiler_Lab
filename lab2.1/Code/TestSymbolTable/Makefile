include ../commonFunction.md

.PHONY: all insert clean

all: insert

insert: 
	@ $(call compileTemplate, '.') > unused_log
	@ $(call testTemplate, 1 2, '.')

clean:
	@ $(call cleanTemplate)
