SHELL := /bin/bash
.ONESHELL:

# Use 4 cores for parallel compilation
MAKEFLAGS += -j4

# $@ The filename representing the target.
# $% The filename element of an archive member specification.
# $< The filename of the first prerequisite.
# $? The names of all prerequisites that are newer than the target, separated by spaces.
# $^ The filenames of all the prerequisites, separated by spaces. This list has duplicate filenames removed since for most uses, such as # #compiling, copying, etc., duplicates are not wanted.
# $+ Similar to $^, this is the names of all the prerequisites separated by spaces, except that $+ includes duplicates. This variable was #created for specific situations such as arguments to linkers where duplicate values have meaning.
# $* The stem of the target filename. A stem is typically a filename without its suffix. Its use outside of pattern rules is discouraged.


# Name of text file containing build number.
BUILD_NUMBER_FILE=buildnum
BUILD_NUMBER_LDFLAGS  = -Wl,--defsym=__BUILD_YEAR=$$((`date +'%Y'`))
BUILD_NUMBER_LDFLAGS += -Wl,--defsym=__BUILD_MONTH=$$((10\#`date +'%m'` + 16))
BUILD_NUMBER_LDFLAGS += -Wl,--defsym=__BUILD_DAY=$$((10\#`date +'%d'` + 64))

BUILD_NUMBER_LDFLAGS += -Wl,--defsym=__BUILD_NUMBER=$$(cat $(BUILD_NUMBER_FILE))

# Feature configuration
FEATURES_TXT = features/FEATURES.txt
FEATURE_CONFIG_H = hdr/feature_config.h
# BUILD_NUMBER_LDFLAGS  = -Xlinker --defsym -Xlinker __BUILD_DATE=$$(date +'%Y%m%d')
# BUILD_NUMBER_LDFLAGS += -Xlinker --defsym -Xlinker __BUILD_NUMBER=$$(cat $(BUILD_NUMBER_FILE))

OUT = \
	bin/sofreeS.dll
CC = \
	i686-w64-mingw32-g++
ODIR = \
	obj
SDIR = \
	src
INC = \
	-Ihdr \
	-Isrc \
	-Isrc/Game/qcommon \
	-Isrc/Game/gamecpp
CFLAGS = \
	-std=c++11 -fpermissive -w -DSOFREE_DEBUG -DLUA_ON
OFLAGS = \
	-static -pthread -shared -static-libgcc -static-libstdc++ -Wl,--enable-stdcall-fixup -Wno-write-strings

# Automatically find all .cpp files (exclude Game directory - SDK headers only)
SRCS := $(shell find $(SDIR) -name "*.cpp" -type f ! -path "*/Game/*" 2>/dev/null)

# Convert source paths to object paths
# Remove src/ prefix and replace .cpp with .o, prefix with $(ODIR)/
OBJS := $(patsubst $(SDIR)/%,$(ODIR)/%,$(SRCS:.cpp=.o))

# Special case: matrix4.cpp is in Game/ghoul/ but needs to be compiled
SRCS += $(SDIR)/Game/ghoul/matrix4.cpp
OBJS += $(ODIR)/matrix4.o

# Special case: Remove DetourXS from path since it's already a subdirectory
OBJS := $(patsubst $(ODIR)/DetourXS/%,$(ODIR)/DetourXS/%,$(OBJS))

# Default target
all: $(OUT)
	@echo ""
	@echo "=========================================="
	@echo "Build complete! Output: $(OUT)"
	@echo "=========================================="

# Generate feature configuration header from FEATURES.txt
$(FEATURE_CONFIG_H): $(FEATURES_TXT)
	@echo "Generating feature configuration from $(FEATURES_TXT)..."
	@echo "Active features:"
	@awk '{ line=$$0; sub(/\r$$/,"",line); gsub(/^[ \t]+|[ \t]+$$/,"",line); if(line=="") next; if(substr(line,1,1)=="#") next; if(substr(line,1,2)=="//") next; print " - " line }' $(FEATURES_TXT) || true
	@echo '#pragma once' > $@
	@echo '' >> $@
	@echo '/*' >> $@
	@echo '    Compile-time Feature Configuration' >> $@
	@echo '    ' >> $@
	@echo '    Auto-generated from $(FEATURES_TXT)' >> $@
	@echo '    Enable/disable features by commenting/uncommenting lines in $(FEATURES_TXT)' >> $@
	@echo '    ' >> $@
	@echo '    Format in $(FEATURES_TXT):' >> $@
	@echo '    - feature_name     (enabled)' >> $@
	@echo '    - // feature_name  (disabled)' >> $@
	@echo '*/' >> $@
	@echo '' >> $@
	@grep -v '^#' $(FEATURES_TXT) | grep -v '^$$' > /tmp/features_$$$$.tmp
	@while IFS= read -r line || [ -n "$$line" ]; do \
		line=$$(echo "$$line" | sed 's/^[[:space:]]*//;s/[[:space:]]*$$//'); \
		[ -z "$$line" ] && continue; \
		if echo "$$line" | grep -q '^//'; then \
			feature=$$(echo "$$line" | sed 's|^//[[:space:]]*||'); \
			macro=$$(echo "FEATURE_$$feature" | tr '[:lower:]' '[:upper:]' | tr '-' '_'); \
			echo "#define $$macro 0  // disabled" >> $@; \
		else \
			macro=$$(echo "FEATURE_$$line" | tr '[:lower:]' '[:upper:]' | tr '-' '_'); \
			echo "#define $$macro 1  // enabled" >> $@; \
		fi; \
	done < /tmp/features_$$$$.tmp
	@rm -f /tmp/features_$$$$.tmp
	@echo '' >> $@
	@echo '/*' >> $@
	@echo '    Usage in feature files:' >> $@
	@echo '    ' >> $@
	@echo '    #include "../../../hdr/feature_config.h"' >> $@
	@echo '    ' >> $@
	@echo '    #if FEATURE_MY_FEATURE' >> $@
	@echo '    // ... feature implementation' >> $@
	@echo '    #endif' >> $@
	@echo '*/' >> $@
	@echo "Generated feature configuration with $$(grep -c '^#define' $@) features"

# This target now uses .ONESHELL, so the whole recipe runs as one script.
$(OUT): $(FEATURE_CONFIG_H) $(OBJS)
	@echo "Linking $(OUT) with $(words $(OBJS)) object files..."
	@echo "Checking if all object files exist..."
	# 1. Set a default value if the file doesn't exist.
	#    Use printf for no newline.
	if ! test -f $(BUILD_NUMBER_FILE); then
		printf "0" > $(BUILD_NUMBER_FILE)
	fi
	
	# 2. Read the number into a shell variable.
	#    Using $(...) command substitution automatically strips trailing newlines.
	#    This makes the script robust even if the file is broken.
	build_num=$$(cat $(BUILD_NUMBER_FILE))
	
	# 3. Increment the shell variable. Note $$ for make to escape the $.
	build_num=$$((build_num + 1))
	
	# 4. Write the new, incremented number back to the file.
	printf "%d" $$build_num > $(BUILD_NUMBER_FILE)
	
	# 5. Now, run the compiler. It will use the LDFLAGS which correctly
	#    reads the newly updated file.
	$(CC) $(OFLAGS) rsrc/sofreeS.def $(OBJS) -o$(OUT) -lws2_32 -lwinmm -L "./rsrc/" -llua $(BUILD_NUMBER_LDFLAGS)
	
	@echo "Compiled "$(OUT)" successfully with build number $$build_num!"

# General rule for all .cpp files
$(ODIR)/%.o: $(SDIR)/%.cpp $(FEATURE_CONFIG_H)
	@echo "Compiling $<..."
	@mkdir -p $(@D)
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)

# Special case: matrix4.cpp is in Game/ghoul/ but object goes to obj/matrix4.o
$(ODIR)/matrix4.o: $(SDIR)/Game/ghoul/matrix4.cpp $(FEATURE_CONFIG_H)
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)

.PHONY: clean features all
clean:
	find $(ODIR) -name "*.o" -type f -delete 2>/dev/null || true
	rm -f $(OUT) $(FEATURE_CONFIG_H)

features:
	@echo "Active features:"
	@awk '{ line=$$0; sub(/\r$$/,"",line); gsub(/^[ \t]+|[ \t]+$$/,"",line); if(line=="") next; if(substr(line,1,1)=="#") next; if(substr(line,1,2)=="//") next; print " - " line }' $(FEATURES_TXT) || true
	@echo "Active feature count: $$(awk '{ line=$$0; sub(/\r$$/,"",line); gsub(/^[ \t]+|[ \t]+$$/,"",line); if(line=="") next; if(substr(line,1,1)=="#") next; if(substr(line,1,2)=="//") next; print line }' $(FEATURES_TXT) | wc -l)"
