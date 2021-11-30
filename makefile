rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

PATH_SRC = src
PATH_SRC_MODULE = src/hal
PATH_SRC_LIB = src/drivers
PATH_SRC_BINARY = src/app
PATH_BUILD = build

UNIX_PATH_BUILD = build/unix
UNIX_PATH_BUILD_MODULE = build/unix/module
UNIX_PATH_BUILD_LIB = build/unix/lib
UNIX_PATH_BUILD_BINARY = build/unix/bin

UNIX_CC = gcc
UNIX_CFLAGS = -DIBUG -Wall -std=gnu99 -Os -Wno-unused-variable -fdata-sections
UNIX_INCLUDES = 
UNIX_LFLAGS = -pthread -lm -Wl,--gc-sections
UNIX_LIBS =

SRCS_MODULE = $(patsubst $(PATH_SRC_MODULE)/%,%,$(call rwildcard,$(PATH_SRC_MODULE), *.c))
UNIX_OBJS_MODULE = $(addprefix $(UNIX_PATH_BUILD_MODULE)/, $(SRCS_MODULE:.c=.o))
UNIX_PATH_BUILD_MODULES = $(dir $(UNIX_OBJS_MODULE))

SRCS_LIB = $(patsubst $(PATH_SRC_LIB)/%,%,$(call rwildcard,$(PATH_SRC_LIB), *.c))
UNIX_OBJS_LIB = $(addprefix $(UNIX_PATH_BUILD_LIB)/, $(SRCS_LIB:.c=.o))
UNIX_PATH_BUILD_LIBS = $(dir $(UNIX_OBJS_LIB))

SRCS_BINARY = $(patsubst $(PATH_SRC_BINARY)/%,%,$(call rwildcard,$(PATH_SRC_BINARY), *.c))
UNIX_OBJS_BINARY = $(addprefix $(UNIX_PATH_BUILD_BINARY)/, $(SRCS_BINARY:.c=))
UNIX_PATH_BUILD_BINARIES = $(dir $(UNIX_OBJS_BINARY))

PATH_ALL = $(PATH_SRC) $(PATH_SRC_MODULE) $(PATH_SRC_LIB) $(PATH_SRC_BINARY) $(PATH_BUILD) $(UNIX_PATH_BUILD) $(UNIX_PATH_BUILD_BINARY) $(UNIX_PATH_BUILD_MODULES) $(UNIX_PATH_BUILD_LIBS) $(UNIX_PATH_BUILD_BINARIES)
VPATH = $(PATH_ALL)

$(info -----DEBUG-----)

$(info $$PATH_SRC is [${PATH_SRC}])
$(info $$PATH_SRC_MODULE is [${PATH_SRC_MODULE}])
$(info $$PATH_SRC_LIB is [${PATH_SRC_LIB}])
$(info $$PATH_SRC_BINARY is [${PATH_SRC_BINARY}])
$(info $$PATH_BUILD is [${PATH_BUILD}])

$(info $$UNIX_PATH_BUILD is [${UNIX_PATH_BUILD}])
$(info $$UNIX_PATH_BUILD_MODULE is [${UNIX_PATH_BUILD_MODULE}])
$(info $$UNIX_PATH_BUILD_LIB is [${UNIX_PATH_BUILD_LIB}])
$(info $$UNIX_PATH_BUILD_BINARY is [${UNIX_PATH_BUILD_BINARY}])

$(info $$UNIX_CC is [${UNIX_CC}])
$(info $$UNIX_CFLAGS is [${UNIX_CFLAGS}])
$(info $$UNIX_INCLUDES is [${UNIX_INCLUDES}])
$(info $$UNIX_LFLAGS is [${UNIX_LFLAGS}])
$(info $$UNIX_LIBS is [${UNIX_LIBS}])

$(info $$SRCS_MODULE is [${SRCS_MODULE}])
$(info $$UNIX_OBJS_MODULE is [${UNIX_OBJS_MODULE}])
$(info $$UNIX_PATH_BUILD_MODULES is [${UNIX_PATH_BUILD_MODULES}])

$(info $$SRCS_LIB is [${SRCS_LIB}])
$(info $$UNIX_OBJS_LIB is [${UNIX_OBJS_LIB}])
$(info $$UNIX_PATH_BUILD_LIBS is [${UNIX_PATH_BUILD_LIBS}])

$(info $$SRCS_BINARY is [${SRCS_BINARY}])
$(info $$UNIX_OBJS_BINARY is [${UNIX_OBJS_BINARY}])
$(info $$UNIX_PATH_BUILD_BINARIES is [${UNIX_PATH_BUILD_BINARIES}])

$(info $$PATH_ALL is [${PATH_ALL}])

$(info ---------------)

post-build: pre-build build

pre-build: makefile
	@mkdir -p $(PATH_ALL)

build: pre-build $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) $(UNIX_OBJS_BINARY)

$(UNIX_PATH_BUILD_BINARY)%: %.c %.h $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB)
	$(UNIX_CC) $(UNIX_CFLAGS) $(UNIX_INCLUDES) $< $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) -o $@ $(UNIX_LFLAGS) $(UNIX_LIBS)
	
$(UNIX_PATH_BUILD_BINARY)%: %.c $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB)
	$(UNIX_CC) $(UNIX_CFLAGS) $(UNIX_INCLUDES) $< $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) -o $@ $(UNIX_LFLAGS) $(UNIX_LIBS)

$(UNIX_PATH_BUILD_MODULE)/%.o: $(PATH_SRC_MODULE)/%.c $(PATH_SRC_MODULE)/%.h
	$(UNIX_CC) $(UNIX_CFLAGS) -c $< -o $@
	
$(UNIX_PATH_BUILD_LIB)/%.o: $(PATH_SRC_LIB)/%.c $(PATH_SRC_LIB)/%.h
	$(UNIX_CC) $(UNIX_CFLAGS) -c $< -o $@

clean:
	rm -rf $(PATH_BUILD) 2>/dev/null
#find $(PATH_BUILD) -name "*" -type f -printf "%p\n" -delete 2>/dev/null