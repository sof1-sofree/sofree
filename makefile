SHELL := /bin/bash
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
	-Ihdr
CFLAGS = \
	-std=c++11 -fpermissive -w -DSOFREE_DEBUG
OFLAGS = \
	-lpthread -shared -Wl,--enable-stdcall-fixup -static-libgcc -static-libstdc++ -Wno-write-strings
_OBJS = \
	sofreeS.o \
	updater.o \
	DetourXS/ADE32.o \
	DetourXS/detourxs.o \
	crc32.o \
	func_addrs.o \
	cvars.o \
	var_addrs.o \
	ghoul.o \
	hooks.o \
	commands_lua.o \
	util_funcs.o \
	sp_detours.o \
	server_begin.o \
	client_begin.o \
	menu.o \
	ondamage.o \
	vaccine.o \
	deathmatch.o \
	dm_always.o \
	dm_sofree.o \
	dm_standard.o \
	dm_ctf.o \
	dm_realistic.o \
	minecraft.o \
	spawn.o \
	sofree_strip.o \
	matrix4.o
OBJS = \
	$(patsubst %,$(ODIR)/%,$(_OBJS)) # insert ODIR in front of each whitespace seperated word

# Build number file.  Increment if any object file changes.
$(OUT): $(OBJS)
	@if ! test -f $(BUILD_NUMBER_FILE); then echo 0 > $(BUILD_NUMBER_FILE); fi
	@echo $$(($$(cat $(BUILD_NUMBER_FILE)) + 1)) > $(BUILD_NUMBER_FILE)

	$(CC) $(OFLAGS) rsrc/sofreeS.def $^ -o$(OUT) -lws2_32 -lwinmm -L "./rsrc/" -llua  $(BUILD_NUMBER_LDFLAGS)
	@echo "Compiled "$(OUT)" successfully!"

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)

$(ODIR)/matrix4.o: $(SDIR)/Game/ghoul/matrix4.cpp
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)
	



.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(ODIR)/Game/gamecpp/*.o $(ODIR)/DetourXS/*.o $(OUT)
