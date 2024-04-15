CCX=g++-13

SRC=src
OUT=bin
OBJ=$(OUT)/obj
EXE=$(OUT)/main

TMP=tmp
TMP_OBJ=$(OUT)/tmp_obj

FLAGS=-I src/header -Wall -Wextra -Werror -std=c++20
RECUR_WILDCARD=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call RECUR_WILDCARD,$d/,$2))
SOURCE_CODE=$(call RECUR_WILDCARD,$(SRC),*.cpp)
OBJECT_FILE=$(patsubst $(SRC)/%,$(OBJ)/%,$(patsubst %.cpp,%.o,$(SOURCE_CODE)))

.SECONDARY:
.SECONDEXPANSION:

run: build
	$(EXE)

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CCX) $(FLAGS) -c -o $@ $<

$(TMP_OBJ)/%.o: $(TMP)/%.cpp
	@mkdir -p $(@D)
	$(CCX) $(FLAGS) -c -o $@ $<

$(EXE): $(OBJECT_FILE)
	@mkdir -p $(@D)
	$(CCX) $^ -o $(EXE)

build: $(EXE)

clean:
	rm -rf $(OUT)

$(OUT)/%.tmp: $(TMP_OBJ)/%.o $(filter-out %main.o,$(OBJECT_FILE))
	echo $^
	$(CCX) $^ -o $@

%.tmp: $(OUT)/%.tmp
	$^
