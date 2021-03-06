# Run as 'emmake make'

VERILATOR_ROOT := /usr/share/verilator/include

VERILATOR_SRC := \
	$(VERILATOR_ROOT)/verilated.cpp \
	$(VERILATOR_ROOT)/verilated_cov.cpp \
	$(VERILATOR_ROOT)/verilated_dpi.cpp \
	$(VERILATOR_ROOT)/verilated_save.cpp \
	$(VERILATOR_ROOT)/verilated_vpi.cpp

OBJ := obj

CXXFLAGS += -I$(VERILATOR_ROOT) -I$(VERILATOR_ROOT)/vltstd -Iout -flto -fno-exceptions -Os
# CXXFLAGS += -I$(VERILATOR_ROOT) -I$(VERILATOR_ROOT)/vltstd -Iout -flto -fno-exceptions

VOUT := \
	$(OBJ)/Vpong.cpp \
	$(OBJ)/Vpong.h \
	$(OBJ)/Vpong__Syms.cpp \
	$(OBJ)/Vpong__Syms.h

RUNTIME := $(OBJ)/vl_runtime.bc
DESIGN := $(OBJ)/vl_design.bc 

OUT := $(OBJ)/pong.js $(OBJ)/pong.wasm

.PHONY: all
all: create_dirs $(OUT)

.PHONY: clean
clean:
	rm -r $(OBJ)

.PHONY: create_dirs
create_dirs: $(OBJ)

$(OBJ): Makefile
	mkdir -p $(OBJ)

$(RUNTIME) : $(VERILATOR_SRC)
	emcc $(CXXFLAGS) $(CPPFLAGS) -r -o $@  $(VERILATOR_SRC)

$(OBJ)/pong.v $(OBJ)/pong_cfg.h: pong.py
	python3 pong.py generate_verilog

$(VOUT) : $(OBJ)/pong.v
	verilator $(OBJ)/pong.v --cc --clk clk -Mdir $(OBJ) --Wno-fatal

$(DESIGN) : $(VOUT)
	emcc $(CXXFLAGS) $(CPPFLAGS) -r -o $@ $(filter %.cpp,$(VOUT))

#  -s SINGLE_FILE=1
$(OUT) : $(RUNTIME) $(DESIGN) main.cpp $(VOUT) $(OBJ)/pong_cfg.h
	emcc $(CXXFLAGS) $(CPPFLAGS) -s FILESYSTEM=0 -s WASM=1 --bind -o $(OBJ)/pong.js $(RUNTIME) $(DESIGN) main.cpp

