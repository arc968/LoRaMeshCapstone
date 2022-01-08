# Andrew Courtemanche
# Created December 2021
# Updated January 2022

# Targets:
#	compile (default): compiles everything
#	oneshot: compiles final binary with no intermediate files. Will fail if multiple main() are defined
#	clean: deletes all build artifacts
#	deepclean: deletes all build artifacts and generated documentation
#	docs: generates documentation
#	debug: prints all variables
#	all: compiles everything and generates documentation

# CONFIG
MAKEFILE_MONITOR = makefile.uptodate

PATH_DOCS = docs
DOXYGEN_CONFIG = doxygen.conf

PATH_SRC = src
PATH_SRC_BINARY = app
PATH_BUILD = build

C_AND_CPP_FLAGS = -DIBUG -g -Wall -Os -Wno-unused-variable -Wno-unused-function -ffunction-sections -fdata-sections
C_AND_CPP_INCLUDES =
C_AND_CPP_LFLAGS =
C_AND_CPP_LIBS =

C_FLAGS =
C_INCLUDES =
C_LFLAGS =
C_LIBS =

CPP_FLAGS =
CPP_INCLUDES =
CPP_LFLAGS =
CPP_LIBS =

# CONFIG-UNIX
UNIX_PATH_BUILD = unix

UNIX_C_AND_CPP_FLAGS =
UNIX_C_AND_CPP_INCLUDES =
UNIX_C_AND_CPP_LFLAGS = -Wl,--gc-sections
UNIX_C_AND_CPP_LIBS =

UNIX_C_CC = gcc
UNIX_C_FLAGS = -std=gnu99
UNIX_C_INCLUDES =
UNIX_C_LFLAGS =
UNIX_C_LIBS =

UNIX_CPP_CC = g++
UNIX_CPP_FLAGS = -std=gnu++11
UNIX_CPP_INCLUDES = 
UNIX_CPP_LFLAGS = 
UNIX_CPP_LIBS =
# END CONFIG-UNIX
# END CONFIG

# MACRO
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2)$(filter $(subst *,%,$2),$d))

PATH_BINARY := $(PATH_SRC_BINARY)

PATH_SRC_BINARY := $(addprefix $(PATH_SRC)/,$(PATH_SRC_BINARY))

PATH_BUILD_ALL = $(PATH_BUILD)

SRCS_BINARY = $(patsubst $(PATH_SRC_BINARY)/%,%,$(call rwildcard,$(PATH_SRC_BINARY),*.c)) $(patsubst $(PATH_SRC_BINARY)/%,%,$(call rwildcard,$(PATH_SRC_BINARY),*.cpp))
SRCS = $(filter-out $(addprefix $(PATH_BINARY)/,$(SRCS_BINARY)),$(patsubst $(PATH_SRC)/%,%,$(call rwildcard,$(PATH_SRC),*.c))) $(filter-out $(addprefix $(PATH_BINARY)/,$(SRCS_BINARY)),$(patsubst $(PATH_SRC)/%,%,$(call rwildcard,$(PATH_SRC),*.cpp)))

C_FLAGS += $(C_AND_CPP_FLAGS)
C_INCLUDES += $(C_AND_CPP_INCLUDES)
C_LFLAGS += $(C_AND_CPP_LFLAGS)
C_LIBS += $(C_AND_CPP_LIBS)

CPP_FLAGS += $(C_AND_CPP_FLAGS)
CPP_INCLUDES += $(C_AND_CPP_INCLUDES)
CPP_LFLAGS += $(C_AND_CPP_LFLAGS)
CPP_LIBS += $(C_AND_CPP_LIBS)

# MACRO-UNIX
UNIX_PATH_BUILD := $(addprefix $(PATH_BUILD)/,$(UNIX_PATH_BUILD))
UNIX_PATH_BUILD_BINARY := $(addprefix $(UNIX_PATH_BUILD)/,$(patsubst $(PATH_SRC)/%,%,$(PATH_SRC_BINARY)))

UNIX_C_FLAGS += $(C_FLAGS) $(UNIX_C_AND_CPP_FLAGS)
UNIX_C_INCLUDES += $(C_INCLUDES) $(UNIX_C_AND_CPP_INCLUDES)
UNIX_C_LFLAGS += $(C_LFLAGS) $(UNIX_C_AND_CPP_LFLAGS)
UNIX_C_LIBS += $(C_LIBS) $(UNIX_C_AND_CPP_LIBS)

UNIX_CPP_FLAGS += $(CPP_FLAGS) $(UNIX_C_AND_CPP_FLAGS)
UNIX_CPP_INCLUDES += $(CPP_INCLUDES) $(UNIX_C_AND_CPP_INCLUDES)
UNIX_CPP_LFLAGS += $(CPP_LFLAGS) $(UNIX_C_AND_CPP_LFLAGS)
UNIX_CPP_LIBS += $(CPP_LIBS) $(UNIX_C_AND_CPP_LIBS)

UNIX_OBJS = $(addprefix $(UNIX_PATH_BUILD)/,$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS))))
UNIX_DEPS = $(addprefix $(UNIX_PATH_BUILD)/,$(patsubst %.c,%.d,$(patsubst %.cpp,%.d,$(SRCS))))
UNIX_PATH_BUILD_OBJS = $(dir $(UNIX_OBJS))

UNIX_OBJS_BINARY = $(addprefix $(UNIX_PATH_BUILD_BINARY)/,$(patsubst %.c,%,$(patsubst %.cpp,%,$(SRCS_BINARY))))
UNIX_DEPS_BINARY = $(addprefix $(UNIX_PATH_BUILD_BINARY)/,$(patsubst %.c,%.d,$(patsubst %.cpp,%.d,$(SRCS_BINARY))))
UNIX_PATH_BUILD_BINARIES = $(dir $(UNIX_OBJS_BINARY))

PATH_BUILD_ALL += $(UNIX_PATH_BUILD) $(UNIX_PATH_BUILD_BINARY) $(UNIX_PATH_BUILD_OBJS) $(UNIX_PATH_BUILD_BINARIES)
# END MACRO-UNIX

VPATH = $(PATH_SRC)
# END MACRO

# DEBUG
ifeq ("$(findstring debug,$(MAKECMDGOALS))","debug")
$(info -----DEBUG-----)

$(info $$MAKEFILE_MONITOR is [${MAKEFILE_MONITOR}])

$(info $$PATH_DOCS is [${PATH_DOCS}])
$(info $$DOXYGEN_CONFIG is [${DOXYGEN_CONFIG}])

$(info $$PATH_SRC is [${PATH_SRC}])
$(info $$PATH_SRC_BINARY is [${PATH_SRC_BINARY}])
$(info $$PATH_BUILD is [${PATH_BUILD}])

$(info $$C_AND_CPP_FLAGS is [${C_AND_CPP_FLAGS}])
$(info $$C_AND_CPP_INCLUDES is [${C_AND_CPP_INCLUDES}])
$(info $$C_AND_CPP_LFLAGS is [${C_AND_CPP_LFLAGS}])
$(info $$C_AND_CPP_LIBS is [${C_AND_CPP_LIBS}])

$(info $$C_FLAGS is [${C_FLAGS}])
$(info $$C_INCLUDES is [${C_INCLUDES}])
$(info $$C_LFLAGS is [${C_LFLAGS}])
$(info $$C_LIBS is [${C_LIBS}])

$(info $$CPP_FLAGS is [${CPP_FLAGS}])
$(info $$CPP_INCLUDES is [${CPP_INCLUDES}])
$(info $$CPP_LFLAGS is [${CPP_LFLAGS}])
$(info $$CPP_LIBS is [${CPP_LIBS}])

$(info $$UNIX_PATH_BUILD is [${UNIX_PATH_BUILD}])

$(info $$UNIX_C_AND_CPP_FLAGS is [${UNIX_C_AND_CPP_FLAGS}])
$(info $$UNIX_C_AND_CPP_INCLUDES is [${UNIX_C_AND_CPP_INCLUDES}])
$(info $$UNIX_C_AND_CPP_LFLAGS is [${UNIX_C_AND_CPP_LFLAGS}])
$(info $$UNIX_C_AND_CPP_LIBS is [${UNIX_C_AND_CPP_LIBS}])

$(info $$UNIX_C_CC is [${UNIX_C_CC}])
$(info $$UNIX_C_FLAGS is [${UNIX_C_FLAGS}])
$(info $$UNIX_C_INCLUDES is [${UNIX_C_INCLUDES}])
$(info $$UNIX_C_LFLAGS is [${UNIX_C_LFLAGS}])
$(info $$UNIX_C_LIBS is [${UNIX_C_LIBS}])

$(info $$UNIX_CPP_CC is [${UNIX_CPP_CC}])
$(info $$UNIX_CPP_FLAGS is [${UNIX_CPP_FLAGS}])
$(info $$UNIX_CPP_INCLUDES is [${UNIX_CPP_INCLUDES}])
$(info $$UNIX_CPP_LFLAGS is [${UNIX_CPP_LFLAGS}])
$(info $$UNIX_CPP_LIBS is [${UNIX_CPP_LIBS}])

$(info $$PATH_BINARY is [${PATH_BINARY}])
$(info $$PATH_SRC_BINARY is [${PATH_SRC_BINARY}])
$(info $$PATH_BUILD_ALL is [${PATH_BUILD_ALL}])

$(info $$SRCS_BINARY is [${SRCS_BINARY}])
$(info $$SRCS is [${SRCS}])

$(info $$UNIX_PATH_BUILD is [${UNIX_PATH_BUILD}])
$(info $$UNIX_PATH_BUILD_BINARY is [${UNIX_PATH_BUILD_BINARY}])

$(info $$UNIX_OBJS is [${UNIX_OBJS}])
$(info $$UNIX_DEPS is [${UNIX_DEPS}])
$(info $$UNIX_PATH_BUILD_OBJS is [${UNIX_PATH_BUILD_OBJS}])

$(info $$UNIX_OBJS_BINARY is [${UNIX_OBJS_BINARY}])
$(info $$UNIX_DEPS_BINARY is [${UNIX_DEPS_BINARY}])
$(info $$UNIX_PATH_BUILD_BINARIES is [${UNIX_PATH_BUILD_BINARIES}])

$(info $$PATH_BUILD_ALL is [${PATH_BUILD_ALL}])

$(info $$VPATH is [${VPATH}])

$(info ---------------)
endif
# END DEBUG

compile: post-build $(MAKEFILE_MONITOR)

.PHONY: oneshot
oneshot: pre-build $(MAKEFILE_MONITOR)
	@echo oneshot build...
	$(UNIX_CPP_CC) $(UNIX_CPP_FLAGS) $(UNIX_CPP_INCLUDES) $(strip $(call rwildcard,$(PATH_SRC),*.c)) $(strip $(call rwildcard,$(PATH_SRC),*.cpp)) -o $(UNIX_PATH_BUILD_BINARY)/main $(UNIX_CPP_LFLAGS) $(UNIX_CPP_LIBS)

post-build: pre-build build $(MAKEFILE_MONITOR)

all: pre-build build post-build docs $(MAKEFILE_MONITOR)

pre-build: $(MAKEFILE_MONITOR)
	@mkdir -p $(PATH_BUILD_ALL)

build: pre-build $(UNIX_OBJS) $(UNIX_OBJS_BINARY) $(MAKEFILE_MONITOR)

#C
$(UNIX_PATH_BUILD_BINARY)/%.d: $(PATH_SRC_BINARY)/%.c $(PATH_SRC_BINARY)/%.h 
	@mkdir -p $(@D)
	$(UNIX_C_CC) $(UNIX_C_FLAGS) $(UNIX_C_INCLUDES) -MM -MF $@ $<
	
$(UNIX_PATH_BUILD_BINARY)/%.d: $(PATH_SRC_BINARY)/%.c 
	@mkdir -p $(@D)
	$(UNIX_C_CC) $(UNIX_C_FLAGS) $(UNIX_C_INCLUDES) -MM -MF $@ $<

$(UNIX_PATH_BUILD)/%.d: $(PATH_SRC)/%.c $(PATH_SRC)/%.h
	@mkdir -p $(@D)
	$(UNIX_C_CC) $(UNIX_C_FLAGS) -MM -MF $@ -c $<

$(UNIX_PATH_BUILD)/%.d: $(PATH_SRC)/%.c 
	@mkdir -p $(@D)
	$(UNIX_C_CC) $(UNIX_C_FLAGS) -MM -MF $@ -c $<

#C++
$(UNIX_PATH_BUILD_BINARY)/%.d: $(PATH_SRC_BINARY)/%.cpp $(PATH_SRC_BINARY)/%.h 
	@mkdir -p $(@D)
	$(UNIX_CPP_CC) $(UNIX_CPP_FLAGS) $(UNIX_CPP_INCLUDES) -MM -MF $@ $< 
	
$(UNIX_PATH_BUILD_BINARY)/%.d: $(PATH_SRC_BINARY)/%.cpp 
	@mkdir -p $(@D)
	$(UNIX_CPP_CC) $(UNIX_CPP_FLAGS) $(UNIX_CPP_INCLUDES) -MM -MF $@ $< 
	
$(UNIX_PATH_BUILD)/%.d: $(PATH_SRC)/%.cpp $(PATH_SRC)/%.h 
	@mkdir -p $(@D)
	$(UNIX_CPP_CC) $(UNIX_CPP_FLAGS) -MM -MF $@ -c $<

$(UNIX_PATH_BUILD)/%.d: $(PATH_SRC)/%.cpp 
	@mkdir -p $(@D)
	$(UNIX_CPP_CC) $(UNIX_CPP_FLAGS) -MM -MF $@ -c $<

ifneq ("$(findstring deepclean,$(MAKECMDGOALS))","deepclean")
ifneq ("$(findstring clean,$(MAKECMDGOALS))","clean")
include $(UNIX_DEPS)
include $(UNIX_DEPS_BINARY)
endif
endif

#C
$(UNIX_PATH_BUILD_BINARY)/%: $(PATH_SRC_BINARY)/%.c $(PATH_SRC_BINARY)/%.h $(UNIX_OBJS) $(MAKEFILE_MONITOR)
	@cp $(PATH_SRC)/$*.h $(UNIX_PATH_BUILD)/$*.h
	$(UNIX_C_CC) $(UNIX_C_FLAGS) $(UNIX_C_INCLUDES) -o $@ $(UNIX_OBJS) $< $(UNIX_C_LFLAGS) $(UNIX_C_LIBS)
	
$(UNIX_PATH_BUILD_BINARY)/%: $(PATH_SRC_BINARY)/%.c $(UNIX_OBJS) $(MAKEFILE_MONITOR)
	$(UNIX_C_CC) $(UNIX_C_FLAGS) $(UNIX_C_INCLUDES) -o $@ $(UNIX_OBJS) $< $(UNIX_C_LFLAGS) $(UNIX_C_LIBS)

$(UNIX_PATH_BUILD)/%.o: $(PATH_SRC)/%.c $(PATH_SRC)/%.h $(MAKEFILE_MONITOR)
	@cp $(PATH_SRC)/$*.h $(UNIX_PATH_BUILD)/$*.h
	$(UNIX_C_CC) $(UNIX_C_FLAGS) -c $< -o $@

$(UNIX_PATH_BUILD)/%.o: $(PATH_SRC)/%.c $(MAKEFILE_MONITOR)
	$(UNIX_C_CC) $(UNIX_C_FLAGS) -c $< -o $@

#C++
$(UNIX_PATH_BUILD_BINARY)/%: $(PATH_SRC_BINARY)/%.cpp $(PATH_SRC_BINARY)/%.h $(UNIX_OBJS) $(MAKEFILE_MONITOR)
	@cp $(PATH_SRC)/$*.h $(UNIX_PATH_BUILD)/$*.h
	$(UNIX_CPP_CC) $(UNIX_CPP_FLAGS) $(UNIX_CPP_INCLUDES) -o $@ $(UNIX_OBJS) $< $(UNIX_CPP_LFLAGS) $(UNIX_CPP_LIBS)
	
$(UNIX_PATH_BUILD_BINARY)/%: $(PATH_SRC_BINARY)/%.cpp $(UNIX_OBJS) $(MAKEFILE_MONITOR)
	$(UNIX_CPP_CC) $(UNIX_CPP_FLAGS) $(UNIX_CPP_INCLUDES) -o $@ $(UNIX_OBJS) $< $(UNIX_CPP_LFLAGS) $(UNIX_CPP_LIBS)
	
$(UNIX_PATH_BUILD)/%.o: $(PATH_SRC)/%.cpp $(PATH_SRC)/%.h $(MAKEFILE_MONITOR)
	@cp $(PATH_SRC)/$*.h $(UNIX_PATH_BUILD)/$*.h
	$(UNIX_CPP_CC) $(UNIX_CPP_FLAGS) -c $< -o $@

$(UNIX_PATH_BUILD)/%.o: $(PATH_SRC)/%.cpp $(MAKEFILE_MONITOR)
	$(UNIX_CPP_CC) $(UNIX_CPP_FLAGS) -c $< -o $@

$(MAKEFILE_MONITOR): makefile
	@echo makefile changed, cleaning...
	@-rm -rf $(PATH_BUILD) 2>/dev/null
	@-rm -rf $(PATH_DOCS) 2>/dev/null
	@mkdir -p $(dir $(MAKEFILE_MONITOR))
	@touch $(MAKEFILE_MONITOR)

.PHONY: clean
clean:
	@echo clean...
	@-find $(PATH_BUILD) -mindepth 1 -name "*" -type f -printf "%p\n" -delete 2>/dev/null || true

.PHONY: deepclean
deepclean:
	@echo deepclean...
	@-rm -rf $(PATH_BUILD) 2>/dev/null
	@-rm -rf $(PATH_DOCS) 2>/dev/null

$(DOXYGEN_CONFIG):
	@echo Doxygen config file "$(DOXYGEN_CONFIG)" not found, generating...
	@doxygen -g $(DOXYGEN_CONFIG)
	
.PHONY: docs
docs: post-build $(DOXYGEN_CONFIG) $(MAKEFILE_MONITOR)
	@( cat $(DOXYGEN_CONFIG); echo "INPUT=$(PATH_SRC)/"; echo "OUTPUT_DIRECTORY=$(PATH_DOCS)/"; echo "RECURSIVE=YES" ) | doxygen -

.PHONY: debug
debug:
	@:
