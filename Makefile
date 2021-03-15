##########################################################
# TODO - Finish modifying to work using DBG and REL dirs #
##########################################################
CXX = g++

STD_ARGS = -std=c++2a
WARN_ARGS = -Wall -Wextra -Wpedantic

DBG_ARGS = -ggdb -g3

DBG_OPT_ARGS = -Os
REL_OPT_ARGS = -O2

OBJ_DIR = obj
OBJ_DIR_DBG = $(OBJ_DIR)/debug
OBJ_DIR_REL = $(OBJ_DIR)/release

BIN_DIR = bin
BIN_DIR_DBG = $(BIN_DIR)/debug
BIN_DIR_REL = $(BIN_DIR)/release

LINK_INPUTS_DBG = $(OBJ_DIR_DBG)/main.o $(OBJ_DIR_DBG)/graphics_settings.o $(OBJ_DIR_DBG)/game_app.o
LINK_INPUTS_REL = $(OBJ_DIR_REL)/main.o $(OBJ_DIR_REL)/graphics_settings.o $(OBJ_DIR_REL)/game_app.o

OUTPUT_DBG = $(BIN_DIR_DBG)/a.out
OUTPUT_REL = $(BIN_DIR_REL)/a.out

LINK_LIBS = -lGL -lGLEW -lsfml-window -lsfml-system

LFLAGS_DBG = $(LINK_LIBS) -o $(OUTPUT_DBG)
LFLAGS_REL = $(LINK_LIBS) -o $(OUTPUT_REL)

CFLAGS_DBG = -c $(STD_ARGS) $(WARN_ARGS) $(DBG_ARGS) $(DBG_OPT_ARGS)
CFLAGS_REL = -c $(STD_ARGS) $(WARN_ARGS) $(REL_OPT_ARGS)

.PHONY: all link_dbg link_rel shaders clean

########################
#       MAKE ALL       #
########################
all: link_dbg link_rel

########################
#     LINKER PHASE     #
########################
link_dbg: $(BIN_DIR_DBG) shaders $(LINK_INPUTS_DBG)
	$(CXX) $(LINK_INPUTS_DBG) $(LFLAGS_DBG)

link_rel: $(OBJ_DIR_REL) shaders $(LINK_INPUTS_REL)
	$(CXX) $(LINK_INPUTS_REL) $(LFLAGS_REL)

############
# DBG OBJS #
############
$(OBJ_DIR_DBG)/main.o: $(OBJ_DIR_DBG)
	$(CXX) $(CFLAGS_DBG) src/main.cpp -o $(OBJ_DIR_DBG)/main.o

$(OBJ_DIR_DBG)/graphics_settings.o: $(OBJ_DIR_DBG)
	$(CXX) $(CFLAGS_DBG) src/graphics_settings.cpp -o $(OBJ_DIR_DBG)/graphics_settings.o

$(OBJ_DIR_DBG)/game_app.o: $(OBJ_DIR_DBG)
	$(CXX) $(CFLAGS_DBG) src/game_app.cpp -o $(OBJ_DIR_DBG)/game_app.o

############
# REL OBJS #
############
$(OBJ_DIR_REL)/main.o: $(OBJ_DIR_REL)
	$(CXX) $(CFLAGS_REL) src/main.cpp -o $(OBJ_DIR_REL)/main.o

$(OBJ_DIR_REL)/graphics_settings.o: $(OBJ_DIR_REL)
	$(CXX) $(CFLAGS_REL) src/graphics_settings.cpp -o $(OBJ_DIR_REL)/graphics_settings.o

$(OBJ_DIR_REL)/game_app.o: $(OBJ_DIR_REL)
	$(CXX) $(CFLAGS_REL) src/game_app.cpp -o $(OBJ_DIR_REL)/game_app.o

#################
# DIR STRUCTURE #
#################
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR_DBG):
	mkdir -p $(BIN_DIR_DBG)

$(BIN_DIR_REL):
	mkdir -p $(BIN_DIR_REL)

$(OBJ_DIR_DBG):
	mkdir -p $(OBJ_DIR_DBG)

$(OBJ_DIR_REL):
	mkdir -p $(OBJ_DIR_REL)

###########
# shaders #
###########
shaders: $(BIN_DIR_DBG) $(BIN_DIR_REL) $(BIN_DIR)
	cp -R src/shaders $(BIN_DIR_DBG)
	cp -R src/shaders $(BIN_DIR_REL)
	cp -R src/shaders $(BIN_DIR)
	cp -R src/shaders .

########################
#   CLEAN EVERYTHING   #
########################
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) ./shaders

############################
#       USAGE  NOTES       #
############################
# Build using $ make all   #
# Clean using $ make clean #
############################

