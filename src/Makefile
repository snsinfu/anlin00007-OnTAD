CXXFLAGS ?= -O2 -std=c++11
LDLIBS ?= -lm -lcurl -lz

SRCS = main.cpp step1.cpp step2.cpp step3.cpp step4.cpp common.cpp straw.cpp
OBJS = $(SRCS:.cpp=.o)

CLANG_FORMAT ?= clang-format
FORMAT_FILES = $(filter-out straw.cpp straw.h,$(SRCS) $(wildcard *.h))

all: OnTAD

OnTAD: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

test: OnTAD
	./OnTAD ../test/mES_rep2.40Kb.raw.chr19.mat -o ../mES_rep2.40Kb.raw.chr19 -bedout chr19 61342430 40000

clean:
	$(RM) $(OBJS) OnTAD

format:
	$(CLANG_FORMAT) -i -style=file $(FORMAT_FILES)

format-check:
	$(CLANG_FORMAT) --dry-run --Werror -style=file $(FORMAT_FILES)

.PHONY: all test clean format format-check
