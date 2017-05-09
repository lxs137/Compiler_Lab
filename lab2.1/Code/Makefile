# 编译器设定和编译选项
CC = gcc -fprofile-arcs -ftest-coverage
FLEX = flex
BISON = bison
CFLAGS = -std=c99 -ggdb -fprofile-arcs -ftest-coverage
LDFLAGS = -fprofile-arcs -ftest-coverage

# 编译目标：src目录下的所有.c文件
CFILES = $(shell find ./ -name "*.c")
OBJS = $(CFILES:.c=.o)
LFILE = $(shell find ./ -name "*.l")
YFILE = $(shell find ./ -name "*.y")
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntax.tab.c/)
LFO = $(LFC:.c=.o)
YFO = $(YFC:.c=.o)

parser: clean syntax $(filter-out $(LFO),$(OBJS))
	$(CC) -o parser $(filter-out $(LFO),$(OBJS)) -lfl -ly

syntax: lexical syntax-c
	$(CC) -c $(YFC) -o $(YFO)

lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -t -v $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))

# 定义的一些伪目标
.PHONY: clean test

ACTIONFILES = $(shell find ./ -name "[1-9]*.c")
SUBDIRS = $(shell find ./ -maxdepth 1 -type d -name "Test*")

debug:
	cp DebugMacroCopy.h DebugMacro.h
	make
	./parser test.cmm

coverage:
	make
	for subdir in $(SUBDIRS); do \
	    ehco "$$subdir"; \
	    (cd $$subdir && make runAbstract); \
	done;
	for file in $(ACTIONFILES); do \
	    gcov -f -n $$file >> coverage.output; \
	done;
	! grep -q :0.00% coverage.output

clean:
	- @ for subdir in $(SUBDIRS); do \
	    	echo "Clean in $$subdir"; \
	    	(cd $$subdir && make clean); \
	  done;
	- @ rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	- @ rm *.gcno
	- @ rm *.gcda
	- @ rm -f $(OBJS) $(OBJS:.o=.d)
	- @ rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	- @ rm -f core
