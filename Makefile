SHELL := /bin/bash
CXX ?= g++
CXXFLAGS ?= -Wall -std=c++11
# lib options for compiler
SDL_LIBS ?= -lSDL2 -lSDL2_image
# source and objcet directorys
SRC_DIR ?= src
OBJ_DIR ?= objs
# name of executable (program)
execable ?= monopoly
# autodetect projects in SRC_DIR
PROJECT_DIRS := $(dir $(wildcard $(SRC_DIR)/*/*.hpp))
# includes
INCLUDES := $(addprefix -I,$(PROJECT_DIRS))
# autodetect *.cpp files
CPPS := $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/main.cpp)
# all object files
OBJS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(CPPS:.cpp=.o))

_default: _makeODir $(execable)
	@echo -e "\e[32mCompiled.\e[0m"
debug: _setDebug _default

mingw: _setMingw _default

_setDebug:
	$(eval CXXFLAGS += -g)
	@echo -e "\e[33mDebug.\e[0m"
_setMingw:
	$(eval execable := monopoly.exe)
	$(eval LIBS += -mwindows -lmingw32 -lsdl2main)
	@echo -e "\e[32mMinGW.\e[0m"
_makeODir:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo -e "\e[1;33m$(CXX) $(CXXFLAGS) -c $< -o $@\e[0m"
	@$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@
$(execable): $(OBJS)
	@echo -e "\e[1;32m$(CXX) $(CXXFLAGS) <obj_files> -o $@ $(LIBS) $(SDL_LIBS)\e[0m"
	@$(CXX) $(INCLUDES) $(CXXFLAGS) $(OBJS) -o $@ $(LIBS) $(SDL_LIBS)
clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(execable)
	@echo -e "\e[32mCleaned.\e[0m"
mingwClean: _setMingw clean

help: info
info:
	@echo -e "\nMakefile, for compile \e[1;32m$(execable)\e[0m\n"
	@echo -e "------\e[31m Use the following targets \e[0m-----------------"
	@echo -e "\e[35m<None>\e[0m\n\tto make the \e[1;32m$(execable)\e[0m."
	@echo -e "\e[36mdebug\e[0m\n\tto compile the \e[1;32m$(execable)\e[0m with debugging flags."
	@echo -e "\e[36mmingw\e[0m\n\tto compile the \e[1;32m$(execable)\e[0m with mingw flags."
	@echo -e "\e[36mclean\e[0m\n\tto cleanup."
	@echo -e "\e[36mhelp\e[0m | \e[36minfo\e[0m\n\tto type this message."
	@echo -e "------\e[31m Setable variables \e[0m-------------------------"
	@echo -e "\e[33mCXX\e[0m\n\tfor set the compiler."
	@echo -e "\tby default: '\e[35m$(CXX)\e[0m'"
	@echo -e "\e[33mCXXFLAGS\e[0m\n\tfor set compilation flags."
	@echo -e "\tby default: '\e[35m$(CXXFLAGS)\e[0m'"
	@echo -e "\e[33mSDL_LIBS\e[0m\n\tfor set SDL libs."
	@echo -e "\tby default: '\e[35m$(SDL_LIBS)\e[0m'"
	@echo -e "\e[33mLIBS\e[0m\n\tfor set other libs."
	@echo -e "\tby default: '\e[35m$(LIBS)\e[0m'"
	@echo -e "\e[33mexecable\e[0m\n\tfor rename the executable (program)."
	@echo -e "\tby default: '\e[32m$(execable)\e[0m'"
	@echo -e "--------------------------------------------------\n"
	@echo -e "For more information please look into Makefile.\n"
