
UTILITYBASE := OP2Utility
UTILITYDIR := OP2Utility
UTILITYLIB := $(UTILITYDIR)/lib$(UTILITYBASE).a

CPPFLAGS := -I $(UTILITYDIR)/include -I packages/nlohmann.json.3.2.0/build/native/include/nlohmann/
CXXFLAGS := -std=c++14 -g -Wall -Wno-unknown-pragmas
LDFLAGS := -L$(UTILITYDIR)
LDLIBS := -l$(UTILITYBASE) -lstdc++fs -lstdc++ -lm

SRCDIR := src
BUILDDIR := .build
BINDIR := ./
OBJDIR := $(BUILDDIR)/obj
DEPDIR := $(OBJDIR)

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.cpp = $(CXX) $(DEPFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

SRCS := $(shell find $(SRCDIR) -name '*.cpp')
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all restore op2utility clean
all: mapToJson

restore:
	nuget restore packages.config -SolutionDirectory ./

mapToJson: $(OBJS) | op2utility
	$(CXX) $(LDFLAGS) -o "$@" $^ $(LDLIBS)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPDIR)/%.d
	@mkdir -p ${@D}
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst $(SRCDIR)/%.cpp,$(DEPDIR)/%.d,$(SRCS)))


op2utility:
	$(MAKE) -C $(UTILITYDIR)

clean:
	rm $(OBJS)
