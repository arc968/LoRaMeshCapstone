# Andrew Courtemanche
# December 2021

# Targets:
# 	compile (default): compiles everything
#	clean: deletes all build artifacts
#	deepclean: deletes all build artifacts and generated documentation
#	docs: generates documentation
#	debug: prints all variables
#	all: compiles everything and generates documentation

compile: post-build $(MAKEFILE_MONITOR)

all: pre-build build post-build docs $(MAKEFILE_MONITOR)

include config.mk
#$(info $$PATHS_ALL is [${PATHS_ALL}])

post-build: pre-build build $(MAKEFILE_MONITOR)

pre-build: $(MAKEFILE_MONITOR)
	@mkdir -p $(PATHS_ALL)

build: pre-build $(FILES_ALL_OBJS) $(MAKEFILE_MONITOR)

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
	@( cat $(DOXYGEN_CONFIG) ; echo "INPUT=$(PATH_SRC)/" ; echo "OUTPUT_DIRECTORY=$(PATH_DOCS)/" ) | doxygen -

debug:
	@:
