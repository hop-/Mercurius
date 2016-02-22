SHELL := /bin/bash
CXX ?= g++
CXXFLAGS ?= -Wall -std=c++11
# lib options for compiler
SDL_LIBS ?= -lSDL2 -lSDL2_image
# source and objcet directorys
SRC_DIR ?= src
OBJ_DIR ?= objs
OBJ_DIR_D := $(addsuffix -d, $(OBJ_DIR))
# definitions
DEF_FLAGS := $(addprefix -D, $(DEFINES))
# name of executable (program)
execable ?= mercurius
execable_d := $(addsuffix -d,$(abspath $(execable)))
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
OBJS_D := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR_D)/%,$(CPPS:.cpp=.o))
# all dependensy files
DEPS := $(OBJS:.o=.d)
DEPS_D := $(OBJS_D:.o=.d)
# setting colored output
INTERACTIVE := $(shell [ -t 0 ] && echo 1)
NOCOLORS := 0
ifdef INTERACTIVE
    NOCOLORS := $(shell tput colors 2> /dev/null)
    ifeq ($(shell test $(NOCOLORS) -ge 8 2> /dev/null; echo $$?), 0)
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

# exporting variables
export OBJ_DIR
export execable
export CXXFLAGS
export LIBS
export DEF_FLAGS
#########################################

_default: _makeODir $(execable)
	@echo -e "$(GREEN)Compiled.$(RCOLOR)"

.PHONY: install debug noassert mingw clean resolve

install:
	@$(MAKE) --no-print-directory $(MAKEFILE)
debug:
	$(eval CXXFLAGS += -g)
	$(eval OBJ_DIR := $(addsuffix -d, $(OBJ_DIR)))
	$(eval execable := $(addsuffix -d, $(execable)))
	@echo -e "$(YELLOW)Debug.$(RCOLOR)"
noassert:
	$(eval DEF_FLAGS += -DNDEBUG)
	@echo -e "$(GREEN)Noassert.$(RCOLOR)"
mingw:
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

help info:
	@echo -e "\nMakefile to compile $(BOLD)$(GREEN)$(execable)$(RCOLOR)\n"
	@echo -e "------$(RED) Use the following targets $(RCOLOR)-----------------"
	@echo -e "$(MAGENTA)<None>$(RCOLOR) | $(CYAN)install$(RCOLOR)\n\tto make the $(BOLD)$(GREEN)$(execable)$(RCOLOR)."
	@echo -e "$(CYAN)debug$(RCOLOR)\n\tto setup debugging env (use with $(CYAN)install$(RCOLOR) to have a result)."
	@echo -e "$(CYAN)noassert$(RCOLOR)\n\tto add $(YELLOW)-DNDEBUG$(RCOLOR) flag (use with $(CYAN)install$(RCOLOR) to have a result)."
	@echo -e "$(CYAN)mingw$(RCOLOR)\n\tto add mingw flags (use with $(CYAN)install$(RCOLOR) to have a result)."
	@echo -e "$(CYAN)clean$(RCOLOR)\n\tto cleanup (use after $(CYAN)debug$(RCOLOR) to cleanup debug build)."
	@echo -e "$(CYAN)resolve$(RCOLOR)\n\tto resolve dependencies after hierarchical changes."
	@echo -e "$(CYAN)help$(RCOLOR) | $(CYAN)info$(RCOLOR)\n\tto type this message."
	@echo -e "------$(RED) Setable variables $(RCOLOR)-------------------------"
	@echo -e "$(YELLOW)CXX$(RCOLOR)\n\tto set the compiler."
	@echo -e "\tby default: '$(MAGENTA)$(CXX)$(RCOLOR)'"
	@echo -e "$(YELLOW)CXXFLAGS$(RCOLOR)\n\tto set compilation flags."
	@echo -e "\tby default: '$(MAGENTA)$(CXXFLAGS)$(RCOLOR)'"
	@echo -e "$(YELLOW)SKIP$(RCOLOR)\n\tlist of skipping files(can be used windcard)."
	@echo -e "\tby default: '$(MAGENTA)$(SKIP)$(RCOLOR)'"
	@echo -e "$(YELLOW)DEFINES$(RCOLOR)\n\tlist of defined macros."
	@echo -e "\tby default: '$(MAGENTA)$(DEFINES)$(RCOLOR)'"
	@echo -e "$(YELLOW)SDL_LIBS$(RCOLOR)\n\tto set SDL libs."
	@echo -e "\tby default: '$(MAGENTA)$(SDL_LIBS)$(RCOLOR)'"
	@echo -e "$(YELLOW)LIBS$(RCOLOR)\n\tto set other libs."
	@echo -e "\tby default: '$(MAGENTA)$(LIBS)$(RCOLOR)'"
	@echo -e "$(YELLOW)execable$(RCOLOR)\n\tto rename the executable (program)."
	@echo -e "\tby default: '$(GREEN)$(execable)$(RCOLOR)'"
	@echo -e "--------------------------------------------------\n"
	@echo -e "For more information please look into Makefile.\n"
