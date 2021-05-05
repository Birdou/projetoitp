#Makefile for multiples projects *Linux version
#By Felipe Sena - Last updated in 11/11/2020 at 00:59

#################### SUBTITLE ####################
#TARGET_LIST=[id]          #DON'T FORGET TO ADD THE TARGET ID TO THE TARGETS LIST

#                       ...

#              FILE-[id] = #EXECUTABLE NAME (AND EXTENSION)

#          COMPILER-[id] = #COMPILER
# COMPILATION_FLAGS-[id] = #COMPILATION FLAGS
#      LINKER_FLAGS-[id] = #LINKER FLAGS

#          MAINFILE-[id] = #MAIN FUNCTION'S FILE (WITHOUT EXTENSION)
#           SRCPATH-[id] = #WHERE THE SOURCE FILES ARE LOCATED
#           INCPATH-[id] = #WHERE THE HEADER FILES ARE LOCATED
#           OBJPATH-[id] = #WHERE THE BINARY FILES WILL BE LOCATED

#        SOURCE_EXT-[id] = #SOURCE FILES EXTENSION
#        HEADER_EXT-[id] = #HEADER FILES EXTENSION
##################################################

#################### EXAMPLE #####################
# TARGET_LIST=example #ALWAYS SEPARATE TARGETS WITH BLANK SPACES

# FILE-example=prog.exe

# COMPILER-example=x86_64-w64-mingw32-c++
# COMPILATION_FLAGS-example=-Wall -Wextra -pedantic #YOU CAN LEAVE THIS SPACE IN BLANK
# LINKER_FLAGS-example=-static -static-libgcc -static-libstdc++ #YOU CAN LEAVE THIS SPACE IN BLANK

# MAINFILE-example=main
# SRCPATH-example=./src/
# INCPATH-example=./include/ #SEPARATE WITH BLANK SPACES IF THERE IS MORE THAN ONE PATH
# OBJPATH-example=./objects/Windows/

# SOURCE_EXT-example=.cpp
# HEADER_EXT-example=.h
##################################################

##################### TARGETS ####################
TARGET_LIST=debug release

FILE-debug=prog

COMPILER-debug=gcc
COMPILATION_FLAGS-debug=-Wall -Wextra -pedantic -g -Debug
LINKER_FLAGS-debug=-lm

MAINFILE-debug=main
 SRCPATH-debug=./src/
 INCPATH-debug=./include/
 OBJPATH-debug=./objects/Debug/

SOURCE_EXT-debug=.c
HEADER_EXT-debug=.h
#================================================#
FILE-release=paintIt

COMPILER-release=gcc
COMPILATION_FLAGS-release=-O3 -Wall -Wextra -pedantic -Wno-unused-result
LINKER_FLAGS-release=-static -static-libgcc -static-libstdc++ -lm

MAINFILE-release=main
 SRCPATH-release=./src/
 INCPATH-release=./include/
 OBJPATH-release=./objects/Release/

SOURCE_EXT-release=.c
HEADER_EXT-release=.h
##################################################

##################### DEFINES ####################
FIRST_TARGET=$(firstword $(TARGET_LIST))

.DEFAULT_GOAL:=$(FIRST_TARGET)

FILE=

FILE-SOURCE=$(wildcard $(SRCPATH-$(FILE))*$(SOURCE_EXT-$(FILE)))
HEADERS=$(wildcard $(INCPATH-$(FILE))*$(HEADER_EXT-$(FILE)))
OBJECTS=$(subst $(SOURCE_EXT-$(FILE)),.o,$(subst $(SRCPATH-$(FILE)),$(OBJPATH-$(FILE)),$(FILE-SOURCE)))

OBJCOUNT=$$(($(words $(OBJECTS))+1))
CURCOUNT=1
##################################################


#	$@	Nome da regra.
#	$<	Nome da primeira dependência
#	$^	Lista de dependências
#	$?	Lista de dependências mais recentes que a regra.
#	$*	Nome do arquivo sem sufixo


all: objdir
	@ $(foreach F,$(TARGET_LIST), $(MAKE) --silent --stop $(F);)

%:
	@ $(eval FILE=$@)
	@ if [ "$(findstring $(FILE),$(TARGET_LIST))" = "$(FILE)" ]; then ($(MAKE) --silent --stop FILE=$(FILE) objdir $(FILE-$(FILE));printf "[100%%] Built target %s\n" $(FILE);); else (echo "make: There is no recipe for target '$(FILE)'"; exit); fi

$(FILE-$(FILE)): $(OBJECTS)
	@ printf "[%3i%%]" $$(($(CURCOUNT)*100/$(OBJCOUNT)))
	@ echo " \e[92mLinking executable $(FILE-$(FILE))\e[0m"
	@ $(COMPILER-$(FILE)) $^ $(COMPILATION_FLAGS-$(FILE)) $(LINKER_FLAGS-$(FILE)) -o $(FILE-$(FILE)) $(foreach I,$(INCPATH-$(FILE)),$(shell echo -I$(I)))

$(OBJPATH-$(FILE))%.o: $(SRCPATH-$(FILE))%$(SOURCE_EXT-$(FILE)) $(HEADERS)
	@ printf "[%3i%%]" $$(($(CURCOUNT)*100/$(OBJCOUNT)))
	@ echo " \e[32mBuilding $(COMPILER-$(FILE)) object $@\e[0m"
	@ $(COMPILER-$(FILE)) $< -c $(COMPILATION_FLAGS-$(FILE)) -o $@ $(foreach I,$(INCPATH-$(FILE)),$(shell echo -I$(I)))
	@ $(eval CURCOUNT=$(shell echo $$(($(CURCOUNT)+1))))

$(OBJPATH-$(FILE))$(MAINFILE-$(FILE)).o: $(SRCPATH-$(FILE))$(MAINFILE-$(FILE))$(SOURCE_EXT-$(FILE)) $(HEADERS)
	@ printf "[%3i%%]" $$(($(CURCOUNT)*100/$(OBJCOUNT)))
	@ echo " \e[32mBuilding $(COMPILER-$(FILE)) object $@\e[0m"
	@ $(COMPILER-$(FILE)) $< -c $(COMPILATION_FLAGS-$(FILE)) -o $@ $(foreach I,$(INCPATH-$(FILE)),$(shell echo -I$(I)))
	@ $(eval CURCOUNT=$(shell echo $$(($(CURCOUNT)+1))))

objdir:
	@ $(foreach F,$(TARGET_LIST), $(shell mkdir -p $(OBJPATH-$(F))))

clean:
	@ $(foreach F,$(TARGET_LIST), $(shell rm -rf $(OBJPATH-$(F))*.o $(FILE-$(F)) *~))
	@ echo "All binaries have been deleted."

.PHONY: all clean