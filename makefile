# Andrew Courtemanche
# December 2021

# Targets:
# 	compile (default): compiles everything
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
PATH_SRC_MODULE = hal
PATH_SRC_LIB = drivers
PATH_SRC_BINARY = app
PATH_BUILD = build

C_AND_CPP_FLAGS = -DIBUG -g -Wall -Os -Wno-unused-variable -fdata-sections
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
UNIX_PATH_BUILD_MODULE = module
UNIX_PATH_BUILD_LIB = lib
UNIX_PATH_BUILD_BINARY = bin

UNIX_C_AND_CPP_FLAGS = 
UNIX_C_AND_CPP_INCLUDES = 
UNIX_C_AND_CPP_LFLAGS = -pthread -lm -Wl,--gc-sections
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
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

MAKEFILE_MONITOR := $(addprefix $(PATH_BUILD)/,$(MAKEFILE_MONITOR))

PATH_SRC_MODULE := $(addprefix $(PATH_SRC)/,$(PATH_SRC_MODULE))
PATH_SRC_LIB := $(addprefix $(PATH_SRC)/,$(PATH_SRC_LIB))
PATH_SRC_BINARY := $(addprefix $(PATH_SRC)/,$(PATH_SRC_BINARY))

PATH_ALL = $(PATH_SRC) $(PATH_BUILD) $(PATH_SRC_MODULE) $(PATH_SRC_LIB) $(PATH_SRC_BINARY)

SRCS_MODULE = $(patsubst $(PATH_SRC_MODULE)/%,%,$(call rwildcard,$(PATH_SRC_MODULE),*.c)) $(patsubst $(PATH_SRC_MODULE)/%,%,$(call rwildcard,$(PATH_SRC_MODULE),*.cpp))
SRCS_LIB = $(patsubst $(PATH_SRC_LIB)/%,%,$(call rwildcard,$(PATH_SRC_LIB),*.c)) $(patsubst $(PATH_SRC_LIB)/%,%,$(call rwildcard,$(PATH_SRC_LIB),*.cpp))
SRCS_BINARY = $(patsubst $(PATH_SRC_BINARY)/%,%,$(call rwildcard,$(PATH_SRC_BINARY),*.c)) $(patsubst $(PATH_SRC_BINARY)/%,%,$(call rwildcard,$(PATH_SRC_BINARY),*.cpp))

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
UNIX_PATH_BUILD_MODULE := $(addprefix $(UNIX_PATH_BUILD)/,$(UNIX_PATH_BUILD_MODULE))
UNIX_PATH_BUILD_LIB := $(addprefix $(UNIX_PATH_BUILD)/,$(UNIX_PATH_BUILD_LIB))
UNIX_PATH_BUILD_BINARY := $(addprefix $(UNIX_PATH_BUILD)/,$(UNIX_PATH_BUILD_BINARY))

UNIX_C_FLAGS += $(C_FLAGS) $(UNIX_C_AND_CPP_FLAGS)
UNIX_C_INCLUDES += $(C_INCLUDES) $(UNIX_C_AND_CPP_INCLUDES)
UNIX_C_LFLAGS += $(C_LFLAGS) $(UNIX_C_AND_CPP_LFLAGS)
UNIX_C_LIBS += $(C_LIBS) $(UNIX_C_AND_CPP_LIBS)

UNIX_CPP_FLAGS += $(CPP_FLAGS) $(UNIX_C_AND_CPP_FLAGS)
UNIX_CPP_INCLUDES += $(CPP_INCLUDES) $(UNIX_C_AND_CPP_INCLUDES)
UNIX_CPP_LFLAGS += $(CPP_LFLAGS) $(UNIX_C_AND_CPP_LFLAGS)
UNIX_CPP_LIBS += $(CPP_LIBS) $(UNIX_C_AND_CPP_LIBS)

UNIX_OBJS_MODULE = $(addprefix $(UNIX_PATH_BUILD_MODULE)/,$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS_MODULE))))
UNIX_DEPS_MODULE = $(addprefix $(UNIX_PATH_BUILD_MODULE)/,$(patsubst %.c,%.d,$(patsubst %.cpp,%.d,$(SRCS_MODULE))))
UNIX_PATH_BUILD_MODULES = $(dir $(UNIX_OBJS_MODULE))

UNIX_OBJS_LIB = $(addprefix $(UNIX_PATH_BUILD_LIB)/,$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS_LIB))))
UNIX_DEPS_LIB = $(addprefix $(UNIX_PATH_BUILD_LIB)/,$(patsubst %.c,%.d,$(patsubst %.cpp,%.d,$(SRCS_LIB))))
UNIX_PATH_BUILD_LIBS = $(dir $(UNIX_OBJS_LIB))

UNIX_OBJS_BINARY = $(addprefix $(UNIX_PATH_BUILD_BINARY)/,$(patsubst %.c,%,$(patsubst %.cpp,%,$(SRCS_BINARY))))
UNIX_DEPS_BINARY = $(addprefix $(UNIX_PATH_BUILD_BINARY)/,$(patsubst %.c,%.d,$(patsubst %.cpp,%.d,$(SRCS_BINARY))))
UNIX_PATH_BUILD_BINARIES = $(dir $(UNIX_OBJS_BINARY))

PATH_ALL += $(UNIX_PATH_BUILD) $(UNIX_PATH_BUILD_BINARY) $(UNIX_PATH_BUILD_MODULES) $(UNIX_PATH_BUILD_LIBS) $(UNIX_PATH_BUILD_BINARIES)
# END MACRO-UNIX

VPATH = $(PATH_ALL)
# END MACRO

# DEBUG
ifeq ("$(findstring debug,$(MAKECMDGOALS))","debug")
$(info -----DEBUG-----)

$(info $$PATH_DOCS is [${PATH_DOCS}])
$(info $$DOXYGEN_CONFIG is [${DOXYGEN_CONFIG}])

$(info $$PATH_SRC is [${PATH_SRC}])
$(info $$PATH_SRC_MODULE is [${PATH_SRC_MODULE}])
$(info $$PATH_SRC_LIB is [${PATH_SRC_LIB}])
$(info $$PATH_SRC_BINARY is [${PATH_SRC_BINARY}])
$(info $$PATH_BUILD is [${PATH_BUILD}])

$(info $$UNIX_PATH_BUILD is [${UNIX_PATH_BUILD}])
$(info $$UNIX_PATH_BUILD_MODULE is [${UNIX_PATH_BUILD_MODULE}])
$(info $$UNIX_PATH_BUILD_LIB is [${UNIX_PATH_BUILD_LIB}])
$(info $$UNIX_PATH_BUILD_BINARY is [${UNIX_PATH_BUILD_BINARY}])

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

$(info $$SRCS_MODULE is [${SRCS_MODULE}])
$(info $$UNIX_OBJS_MODULE is [${UNIX_OBJS_MODULE}])
$(info $$UNIX_DEPS_MODULE is [${UNIX_DEPS_MODULE}])
$(info $$UNIX_PATH_BUILD_MODULES is [${UNIX_PATH_BUILD_MODULES}])

$(info $$SRCS_LIB is [${SRCS_LIB}])
$(info $$UNIX_OBJS_LIB is [${UNIX_OBJS_LIB}])
$(info $$UNIX_DEPS_LIB is [${UNIX_DEPS_LIB}])
$(info $$UNIX_PATH_BUILD_LIBS is [${UNIX_PATH_BUILD_LIBS}])

$(info $$SRCS_BINARY is [${SRCS_BINARY}])
$(info $$UNIX_OBJS_BINARY is [${UNIX_OBJS_BINARY}])
$(info $$UNIX_DEPS_BINARY is [${UNIX_DEPS_BINARY}])
$(info $$UNIX_PATH_BUILD_BINARIES is [${UNIX_PATH_BUILD_BINARIES}])

$(info $$PATH_ALL is [${PATH_ALL}])

$(info ---------------)
endif
# END DEBUG

compile: post-build $(MAKEFILE_MONITOR)

post-build: pre-build build $(MAKEFILE_MONITOR)

all: pre-build build post-build docs $(MAKEFILE_MONITOR)

pre-build: $(MAKEFILE_MONITOR)
	@mkdir -p $(PATH_ALL)

build: pre-build $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) $(UNIX_OBJS_BINARY) $(MAKEFILE_MONITOR)

-include $(UNIX_DEPS_MODULE)
-include $(UNIX_DEPS_LIB)
-include $(UNIX_DEPS_BINARY)
#C
$(UNIX_PATH_BUILD_BINARY)/%: $(PATH_SRC_BINARY)/%.c $(PATH_SRC_BINARY)/%.h $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) $(MAKEFILE_MONITOR)
	$(UNIX_C_CC) $(UNIX_C_FLAGS) $(UNIX_C_INCLUDES) -MMD -MP $< $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) -o $@ $(UNIX_C_LFLAGS) $(UNIX_LIBS)
	
$(UNIX_PATH_BUILD_BINARY)/%: $(PATH_SRC_BINARY)/%.c $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) $(MAKEFILE_MONITOR)
	$(UNIX_C_CC) $(UNIX_C_FLAGS) $(UNIX_C_INCLUDES) -MMD -MP $< $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) -o $@ $(UNIX_C_LFLAGS) $(UNIX_LIBS)

$(UNIX_PATH_BUILD_MODULE)/%.o: $(PATH_SRC_MODULE)/%.c $(PATH_SRC_MODULE)/%.h $(MAKEFILE_MONITOR)
	$(UNIX_C_CC) $(UNIX_C_FLAGS) -MMD -MP -c $< -o $@
	
$(UNIX_PATH_BUILD_LIB)/%.o: $(PATH_SRC_LIB)/%.c $(PATH_SRC_LIB)/%.h $(MAKEFILE_MONITOR)
	$(UNIX_C_CC) $(UNIX_C_FLAGS) -MMD -MP -c $< -o $@
#C++
$(UNIX_PATH_BUILD_BINARY)/%: $(PATH_SRC_BINARY)/%.cpp $(PATH_SRC_BINARY)/%.h $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) $(MAKEFILE_MONITOR)
	$(UNIX_CPP_CC) $(UNIX_CPP_FLAGS) $(UNIX_CPP_INCLUDES) -MMD -MP $< $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) -o $@ $(UNIX_CPP_LFLAGS) $(UNIX_LIBS)
	
$(UNIX_PATH_BUILD_BINARY)/%: $(PATH_SRC_BINARY)/%.cpp $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) $(MAKEFILE_MONITOR)
	$(UNIX_CPP_CC) $(UNIX_CPP_FLAGS) $(UNIX_CPP_INCLUDES) -MMD -MP $< $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) -o $@ $(UNIX_CPP_LFLAGS) $(UNIX_LIBS)
	
$(UNIX_PATH_BUILD_MODULE)/%.o: $(PATH_SRC_MODULE)/%.cpp $(PATH_SRC_MODULE)/%.h $(MAKEFILE_MONITOR)
	$(UNIX_CPP_CC) $(UNIX_CPP_FLAGS) -MMD -MP -c $< -o $@
	
$(UNIX_PATH_BUILD_LIB)/%.o: $(PATH_SRC_LIB)/%.cpp $(PATH_SRC_LIB)/%.h $(MAKEFILE_MONITOR)
	$(UNIX_CPP_CC) $(UNIX_CPP_FLAGS) -MMD -MP -c $< -o $@

$(MAKEFILE_MONITOR): makefile
	@echo makefile changed, cleaning...
	@make deepclean >/dev/null
	@mkdir -p $(dir $(MAKEFILE_MONITOR))
	@touch $(MAKEFILE_MONITOR)
	
clean:
	@-find $(PATH_BUILD) -mindepth 1 -name "*" -type f -printf "%p\n" -delete 2>/dev/null || true

deepclean:
	@-rm -rf $(PATH_BUILD) 2>/dev/null
	@-rm -rf $(PATH_DOCS) 2>/dev/null

$(DOXYGEN_CONFIG):
	@echo Doxygen config file "$(DOXYGEN_CONFIG)" not found, generating...
	@doxygen -g $(DOXYGEN_CONFIG)
	
.PHONY: docs debug
docs: post-build $(DOXYGEN_CONFIG) $(MAKEFILE_MONITOR)
	@( cat $(DOXYGEN_CONFIG); echo "INPUT=$(PATH_SRC)/"; echo "OUTPUT_DIRECTORY=$(PATH_DOCS)/"; echo "RECURSIVE=YES" ) | doxygen -

debug:
	@:
