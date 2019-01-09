EMP_LOCATION = ~/Documents/School/FA18/EC/TermProject/
    #~/Research/tools/Empirical
EMP_EXTS_LOCATION = ~/Documents/School/FA18/EC/TermProject/
    #~/Research/tools/emp_exts

# Flags to use regardless of compiler
CFLAGS_all := -Wall -Wno-unused-function -iquote $(EMP_LOCATION)/source/ -iquote $(EMP_EXTS_LOCATION)
CFLAGS_version := -std=c++14

# Emscripten compiler information
#CXX_native := clang++
CXX_native := g++

OFLAGS_native_opt := -O3 -DNDEBUG
OFLAGS_native_debug := -g -pedantic -DEMP_TRACK_MEM  -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual
OFLAGS_native_grumpy := -g -pedantic -DEMP_TRACK_MEM  -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual -Wconversion -Weffc++

CFLAGS_native_opt := $(CFLAGS_all) $(OFLAGS_native_opt)
CFLAGS_native_debug := $(CFLAGS_all) $(OFLAGS_native_debug)
CFLAGS_native_grumpy := $(CFLAGS_all) $(OFLAGS_native_grumpy)


SFMLFlags := #-lsfml-graphics -lsfml-system -lsfml-window

TARGETS := ./CA ./CA_Control ./CA_Classic ./CA_Quads ./CA_Stripes

EVO_DEPEND := $(EMP_LOCATION)/source/Evolve/World.h

default: native

CXX := $(CXX_native)
CFLAGS := $(CFLAGS_native_opt)

debug: CFLAGS := $(CFLAGS_native_debug)
debug: all

grumpy: CFLAGS := $(CFLAGS_native_grumpy)
grumpy: all


native: all

all: $(TARGETS)

$(TARGETS): % : ./src/%.cc $(EVO_DEPEND)
	$(CXX) $(CFLAGS_version) $(CFLAGS) $< -o $@ $(SFMLFlags)

debug-%: ./src/$*.cc $(EVO_DEPEND)
	$(CXX) $(CFLAGS_version) $(CFLAGS_native_debug) $< -o $@ $(SFMLFlags)

profile-%: ./src/$*.cc $(EVO_DEPEND)
	$(CXX) $(CFLAGS_version) $(CFLAGS_native_debug) $< -o $@ -pg $(SFMLFlags)

clean:
	rm -rf debug-* *~ *.dSYM $(TARGETS)

# Debugging information
#print-%: ; @echo $*=$($*)
print-%: ; @echo '$(subst ','\'',$*=$($*))'
