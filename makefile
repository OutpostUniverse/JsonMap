
UTILITYDIR := OP2Utility/

CPPFLAGS := -I $(UTILITYDIR)include -I packages/nlohmann.json.3.2.0/build/native/include/nlohmann/
CXXFLAGS := -std=c++14 -g -Wall -Wno-unknown-pragmas
LDFLAGS := -L$(UTILITYDIR)
LDLIBS := -lOP2Utility -lstdc++fs -lstdc++ -lm

SRCDIR := src/
BUILDDIR := .build/
BINDIR := ./
OBJDIR := $(BUILDDIR)obj/

DEPFLAGS = -MT $@ -MMD -MP -MF $(OBJDIR)$*.Td

COMPILE.cpp = $(CXX) $(DEPFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = @mv -f $(OBJDIR)$*.Td $(OBJDIR)$*.d && touch $@

SRCS := $(shell find $(SRCDIR) -name '*.cpp')
OBJS := $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SRCS))

.PHONY: all restore op2utility clean clean-all
all: mapToJson

restore: packages/
packages/: packages.config
	nuget restore packages.config -SolutionDirectory ./

mapToJson: $(OBJS) | op2utility
	$(CXX) $(LDFLAGS) -o "$@" $^ $(LDLIBS)

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.cpp $(OBJDIR)%.d packages/
	@mkdir -p ${@D}
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(OBJDIR)%.d: ;
.PRECIOUS: $(OBJDIR)%.d

include $(wildcard $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.d,$(SRCS)))


op2utility:
	$(MAKE) -C $(UTILITYDIR)

clean:
	rm -rf "$(BUILDDIR)"
clean-all: clean
	rm -rf packages/
	rm -f mapToJson
