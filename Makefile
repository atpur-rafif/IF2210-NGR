CCX=g++

SRC=src
OUT=bin
OBJ=$(OUT)/obj
EXE=$(OUT)/main

FLAGS=-I src/header
RECUR_WILDCARD=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call RECUR_WILDCARD,$d/,$2))
SOURCE_CODE=$(call RECUR_WILDCARD,$(SRC),*.cpp)
OBJECT_FILE=$(patsubst $(SRC)/%,$(OBJ)/%,$(patsubst %.cpp,%.o,$(SOURCE_CODE)))

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CCX) $(FLAGS) -c -o $@ $<

run: build
	$(OUT)/main

build: $(OBJECT_FILE)
	@mkdir -p $(@D)
	$(CCX) $^ -o $(EXE)

clean:
	rm -rf $(OUT)
