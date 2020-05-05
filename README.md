# Pong over VGA for Basys 3 or Web

This repository contains source code (and if on github, build fragments) for a simple Pong game realized in hardware / hardware simulation. The VGA output is paremetrized and is set to 100x50 resolution for simulation.

### How it works:
- Using the MyHDL `pong.py` generates verilog code
- Verilator compiles the verilog to C++
- `main.cpp` draws the VGA output to a HTML canvas
- Emscripten compiles C++ to runnable WebAssembly
- `index.html` provides a 'nice' UI

### Dependencies:
- Python
- MyHDL
- Verilator
- Emscripten (recent version with Embind)

### Build
`emmake make all`

### Improvements
- Test on real hardware
- Improve autoscaling on differente resolutions
    - Currently the gameplay is way too slow on high def
    - `enable_movement` signal
- Sign and magnitude representaion
    - Arithmetic with `balldx` or `balldy` happens only once, but many places want to negate / set a specific value
