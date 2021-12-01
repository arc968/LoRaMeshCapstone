
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

MAKEFILE_MONITOR := $(addprefix $(PATH_BUILD)/,$(MAKEFILE_MONITOR))

PATHS_SRC_OBJS := $(addprefix $(PATH_SRC)/,$(PATHS_SRC_OBJS))
PATHS_SRC_BIN := $(addprefix $(PATH_SRC)/,$(PATHS_SRC_BIN))

PATHS_ALL := $(PATHS_ALL) $(PATH_SRC) $(PATH_BUILD) $(PATH_SRC_OBJS) $(PATH_SRC_BIN)

FILES_SRC_OBJS = $(call rwildcard,$(PATHS_SRC_OBJS),*.c) $(call rwildcard,$(PATHS_SRC_OBJS),*.cpp)
#FILES_SRC_OBJS_H = $(call rwildcard,$(PATHS_SRC_OBJS),*.h)
FILES_SRC_BIN = $(call rwildcard,$(PATHS_SRC_BIN),*.c) $(call rwildcard,$(PATHS_SRC_BIN),*.cpp)

C_FLAGS += $(C_AND_CPP_FLAGS)
C_INCLUDES += $(C_AND_CPP_INCLUDES)
C_LFLAGS += $(C_AND_CPP_LFLAGS)
C_LIBS += $(C_AND_CPP_LIBS)

CPP_FLAGS += $(C_AND_CPP_FLAGS)
CPP_INCLUDES += $(C_AND_CPP_INCLUDES)
CPP_LFLAGS += $(C_AND_CPP_LFLAGS)
CPP_LIBS += $(C_AND_CPP_LIBS)

# DEBUG
ifeq ("$(findstring debug,$(MAKECMDGOALS))","debug")
$(info $$PATHS_SRC_OBJS is [${PATHS_SRC_OBJS}])
$(info $$PATHS_SRC_BIN is [${PATHS_SRC_BIN}])
$(info $$FILES_SRC_OBJS is [${FILES_SRC_OBJS}])
$(info $$FILES_SRC_BIN is [${FILES_SRC_BIN}])
endif
# END DEBUG
