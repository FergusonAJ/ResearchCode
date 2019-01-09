# Flags to use regardless of compiler
CFLAGS_all := -Wall -Wno-unused-function -I ../../source/
CFLAGS_version := -std=c++14

# Emscripten compiler information
CXX_native := clang++
#CXX_native := g++

OFLAGS_native_opt := -O3 -DNDEBUG
OFLAGS_native_debug := -g -pedantic -DEMP_TRACK_MEM  -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual
OFLAGS_native_grumpy := -g -pedantic -DEMP_TRACK_MEM  -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual -Wconversion -Weffc++

CFLAGS_native_opt := $(CFLAGS_all) $(OFLAGS_native_opt)
CFLAGS_native_debug := $(CFLAGS_all) $(OFLAGS_native_debug)
CFLAGS_native_grumpy := $(CFLAGS_all) $(OFLAGS_native_grumpy)


TARGETS := test

EVO_DEPEND := ../source/Evolve/World.h

default: native

CXX := $(CXX_native)
CFLAGS := $(CFLAGS_native_opt)

debug: CFLAGS := $(CFLAGS_native_debug)
debug: all

grumpy: CFLAGS := $(CFLAGS_native_grumpy)
grumpy: all


native: all

all: $(TARGETS)

$(TARGETS): % : %.cc $(EVO_DEPEND)
	$(CXX) $(CFLAGS_version) $(CFLAGS) $< -o $@

debug-%: $*.cc $(EVO_DEPEND)
	$(CXX) $(CFLAGS_version) $(CFLAGS_native_debug) $< -o $@

clean:
	rm -rf debug-* *~ *.dSYM $(TARGETS)

# Debugging information
#print-%: ; @echo $*=$($*)
print-%: ; @echo '$(subst ','\'',$*=$($*))'

