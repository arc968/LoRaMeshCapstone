PATH_SRC = src/
PATH_SRC_MODULES = src/hal/
PATH_SRC_LIB = src/drivers/
PATH_SRC_BINARY = src/app/
PATH_BUILD = build/
UNIX_PATH_BUILD = build/unix/
UNIX_PATH_BUILD_BINARY = build/unix/bin/
PATH_ALL = $(PATH_SRC) $(PATH_SRC_MODULES) $(PATH_SRC_LIB) $(PATH_SRC_BINARY) $(PATH_BUILD) $(UNIX_PATH_BUILD) $(UNIX_PATH_BUILD_BINARY)
VPATH = $(PATH_ALL)

UNIX_CC = gcc
UNIX_CFLAGS = -DIBUG -Wall -std=gnu99 -Os -Wno-unused-variable -fdata-sections
UNIX_INCLUDES = 
UNIX_LFLAGS = -pthread -lm -Wl,--gc-sections
UNIX_LIBS =

SRCS_MODULE = $(wildcard $(PATH_SRC_MODULES)*.c)
UNIX_OBJS_MODULE = $(addprefix $(UNIX_PATH_BUILD), $(notdir $(SRCS_MODULE:.c=.o)))

SRCS_LIB = $(wildcard $(PATH_SRC_LIB)*.c)
UNIX_OBJS_LIB = $(addprefix $(UNIX_PATH_BUILD), $(notdir $(SRCS_LIB:.c=.o)))

SRCS_BINARY = $(wildcard $(PATH_SRC_BINARY)*.c)
UNIX_OBJS_BINARY = $(addprefix $(UNIX_PATH_BUILD_BINARY), $(notdir $(SRCS_BINARY:.c=)))

post-build: pre-build build

pre-build: makefile
	@mkdir -p $(PATH_ALL)

build: pre-build $(UNIX_OBJS_LIB) $(UNIX_OBJS_MODULE) $(UNIX_OBJS_BINARY)

$(UNIX_PATH_BUILD_BINARY)%: %.c %.h $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB)
	$(UNIX_CC) $(UNIX_CFLAGS) $(UNIX_INCLUDES) $< $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) -o $@ $(UNIX_LFLAGS) $(UNIX_LIBS)
	
$(UNIX_PATH_BUILD_BINARY)%: %.c $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB)
	$(UNIX_CC) $(UNIX_CFLAGS) $(UNIX_INCLUDES) $< $(UNIX_OBJS_MODULE) $(UNIX_OBJS_LIB) -o $@ $(UNIX_LFLAGS) $(UNIX_LIBS)

$(UNIX_PATH_BUILD)%.o: %.c %.h
	$(UNIX_CC) $(UNIX_CFLAGS) -c $< -o $@

clean:
	find $(PATH_BUILD) -name "*" -type f -printf "%p\n" -delete