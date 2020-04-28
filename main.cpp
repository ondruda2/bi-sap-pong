#include "verilated.h"
#include "obj/Vpong.h"
#include "obj/pong_cfg.h"

#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;

struct rgb {
    uint8_t r, g, b, a;
};

rgb frame[VGA_HEIGHT][VGA_WIDTH];

Vpong top;

int test EMSCRIPTEN_KEEPALIVE = 10;

void clk(){
    top.clk = 0;
    top.eval();
    top.clk = 1;
    top.eval();
}

EM_BOOL loop(double time, void*){
    top.switches = 0;

    for(int y = 0; y < VGA_HEIGHT; y++){
        for(int x = 0; x < VGA_WIDTH; x++){
            clk();
            frame[y][x] = top.outcolor ? rgb{0, 0, 0, 255} : rgb{255, 255, 255, 255};
        }
        for(int i = 0; i < VGA_EXTRA_LINE_CLOCKS; i++)
            clk();
    }
    for(int i = 0; i < VGA_EXTAR_FRAME_CLOCKS; i++)
        clk();

    EM_ASM(
        image = new ImageData(new Uint8ClampedArray(Module.get_frame()), Module.vga_width, Module.vga_height);
        ctx.putImageData(image, 0, 0);
    );

    return EM_TRUE;    
}

int main(){
    EM_ASM(
        canvas = document.getElementById("canvas");
        canvas.width = Module.vga_width;
        canvas.height = Module.vga_height;
        ctx = canvas.getContext('2d');
    );
    emscripten_request_animation_frame_loop(loop, NULL);
    return 0;
}

val get_frame(){
    return val(typed_memory_view(sizeof(frame), (uint8_t*)frame));
}

EMSCRIPTEN_BINDINGS(pong){
    function("get_frame", get_frame);
    constant("vga_width", VGA_WIDTH);
    constant("vga_height", VGA_HEIGHT);
}