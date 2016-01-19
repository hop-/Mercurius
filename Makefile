SHELL := /bin/bash
CXX ?= g++
CXXFLAGS ?= -Wall -std=c++11
# lib options for compiler
SDL_LIBS ?= -lSDL2 -lSDL2_image
# source and objcet directorys
SRC_DIR ?= src
OBJ_DIR ?= objs
# definitions
DEF_FLAGS := $(addprefix -D, $(DEFINES))
# name of executable (program)
execable ?= mercurius
# autodetect projects in SRC_DIR
PROJECT_DIRS := $(sort $(dir $(abspath $(wildcard $(SRC_DIR)/*/*.hpp))))
# includes
#INCLUDES := $(addprefix -I,$(PROJECT_DIRS))
INCLUDES := $(addprefix -I,$(abspath $(SRC_DIR)))
# autodetect *.cpp files
CPPS := $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/main.cpp)
ifdef SKIP
    CPPS := $(filter-out $(wildcard $(SKIP)), $(CPPS))
endif
# all object files
OBJS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(CPPS:.cpp=.o))
# all dependensy files
DEPS := $(OBJS:.o=.d)
# setting colored output
INTERACTIVE := $(shell [ -t 0 ] && echo 1)
NOCOLORS := 0
ifdef INTERACTIVE
    NOCOLORS := $(shell tput colors 2> /dev/null)
    ifeq ($(NOCOLORS), 8)
        BOLD := $(shell tput bold)
        RCOLOR := $(shell tput sgr0)
        BLACK := $(shell tput setaf 0)
        RED := $(shell tput setaf 1)
        GREEN := $(shell tput setaf 2)
        YELLOW := $(shell tput setaf 3)
        BLUE := $(shell tput setaf 4)
        MAGENTA := $(shell tput setaf 5)
        CYAN := $(shell tput setaf 6)
        WHITE := $(shell tput setaf 7)
    endif
endif
#########################################

_default: _makeODir $(execable)
	@echo -e "$(GREEN)Compiled.$(RCOLOR)"
debug: _setDebug _default

noassert: _setNoassert _default

mingw: _setMingw _default

_setDebug:
	$(eval CXXFLAGS += -g)
	@echo -e "$(YELLOW)Debug.$(RCOLOR)"
_setNoassert:
	$(eval DEF_FLAGS += -DNDEBUG)
	@echo -e "$(GREEN)Noassert.$(RCOLOR)"
_setMingw:
	$(eval execable := mercurius.exe)
	$(eval LIBS += -mwindows -lmingw32 -lsdl2main)
	@echo -e "$(GREEN)MinGW.$(RCOLOR)"
_makeODir:
	@mkdir -p $(OBJ_DIR)
resolve:
	@echo -e "$(GREEN)Resolved.$(RCOLOR)"
	@find $(OBJ_DIR) -name *.d | xargs rm -rf
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
#@echo -e "$(YELLOW)$(CXX) $(CXXFLAGS) $(DEF_FLAGS) -MM $< -o $@$(RCOLOR)"
	@$(CXX) $(INCLUDES) $(CXXFLAGS) $(DEF_FLAGS) -MM $< -o $@
	@sed -i 's|$(notdir $*).o:|$(@:.d=.o):|g' $@

-include $(DEPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo -e "$(BOLD)$(YELLOW)$(CXX) $(CXXFLAGS) $(DEF_FLAGS) -c $< -o $@$(RCOLOR)"
	@$(CXX) $(INCLUDES) $(CXXFLAGS) $(DEF_FLAGS) -c $< -o $@
$(execable): $(OBJS)
	@echo -e "$(BOLD)$(GREEN)$(CXX) $(CXXFLAGS) $(DEF_FLAGS) <obj_files> -o $@ $(LIBS) $(SDL_LIBS)$(RCOLOR)"
	@$(CXX) $(INCLUDES) $(CXXFLAGS) $(DEF_FLAGS) $(OBJS) -o $@ $(LIBS) $(SDL_LIBS)
clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(execable)
	@echo -e "$(GREEN)Cleaned.$(RCOLOR)"
mingwClean: _setMingw clean

help: info
info:
	@echo -e "\nMakefile, for compile $(BOLD)$(GREEN)$(execable)$(RCOLOR)\n"
	@echo -e "------$(RED) Use the following targets $(RCOLOR)-----------------"
	@echo -e "$(MAGENTA)<None>$(RCOLOR) | $(CYAN)default$(RCOLOR)\n\tto make the $(BOLD)$(GREEN)$(execable)$(RCOLOR)."
	@echo -e "$(CYAN)debug$(RCOLOR)\n\tto compile the $(BOLD)$(GREEN)$(execable)$(RCOLOR) with debugging flags."
	@echo -e "$(CYAN)noassert$(RCOLOR)\n\tto compile the $(BOLD)$(GREEN)$(execable)$(RCOLOR) without asserts."
	@echo -e "$(CYAN)mingw$(RCOLOR)\n\tto compile the $(BOLD)$(GREEN)$(execable)$(RCOLOR) with mingw flags."
	@echo -e "$(CYAN)clean$(RCOLOR)\n\tto cleanup."
	@echo -e "$(CYAN)resolve$(RCOLOR)\n\tto resolve dependencies after hierarchical changes."
	@echo -e "$(CYAN)help$(RCOLOR) | $(CYAN)info$(RCOLOR)\n\tto type this message."
	@echo -e "------$(RED) Setable variables $(RCOLOR)-------------------------"
	@echo -e "$(YELLOW)CXX$(RCOLOR)\n\tfor set the compiler."
	@echo -e "\tby default: '$(MAGENTA)$(CXX)$(RCOLOR)'"
	@echo -e "$(YELLOW)CXXFLAGS$(RCOLOR)\n\tfor set compilation flags."
	@echo -e "\tby default: '$(MAGENTA)$(CXXFLAGS)$(RCOLOR)'"
	@echo -e "$(YELLOW)SKIP$(RCOLOR)\n\tlist of skipping files(can be used windcard)."
	@echo -e "\tby default: '$(MAGENTA)$(SKIP)$(RCOLOR)'"
	@echo -e "$(YELLOW)DEFINES$(RCOLOR)\n\tlist of defined macros."
	@echo -e "\tby default: '$(MAGENTA)$(DEFINES)$(RCOLOR)'"
	@echo -e "$(YELLOW)SDL_LIBS$(RCOLOR)\n\tfor set SDL libs."
	@echo -e "\tby default: '$(MAGENTA)$(SDL_LIBS)$(RCOLOR)'"
	@echo -e "$(YELLOW)LIBS$(RCOLOR)\n\tfor set other libs."
	@echo -e "\tby default: '$(MAGENTA)$(LIBS)$(RCOLOR)'"
	@echo -e "$(YELLOW)execable$(RCOLOR)\n\tfor rename the executable (program)."
	@echo -e "\tby default: '$(GREEN)$(execable)$(RCOLOR)'"
	@echo -e "--------------------------------------------------\n"
	@echo -e "For more information please look into Makefile.\n"
