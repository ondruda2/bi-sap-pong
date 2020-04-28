import math
from myhdl import *
import os
import sys

class VgaConfig:
    def __init__(self, pixel_clock, hvis, hfporch, hsync, hbporch, vvis, vfporch, vsync, vbporch):
        self.pixel_clock = pixel_clock
        self.hvis = hvis
        self.hfporch = hfporch
        self.hsync = hsync
        self.hbporch = hbporch
        self.vvis = vvis
        self.vfporch = vfporch
        self.vsync = vsync
        self.vbporch = vbporch


        self.a1 = hvis
        self.a2 = hvis + hfporch
        self.a3 = hvis + hfporch + hsync
        self.a4 = hvis + hfporch + hsync + hbporch
        self.b1 = vvis
        self.b2 = vvis + vfporch
        self.b3 = vvis + vfporch + vsync
        self.b4 = vvis + vfporch + vsync + vbporch

vga_syn = VgaConfig(65, 1024, 24, 136, 160, 768, 3, 6, 29)
vga_sim = VgaConfig(100, 100, 1, 3, 1, 50, 1, 3, 1)

@block
def paddle(clk, move_enable, up, down, drawout):
    y = intbv(0, 0, scanx.max)

    @always_seq(clk, None)
    def move():
        if move_enable:
            if up and not down and y:
                y.next = y - 1
            if down and not up and y < h:
                y.nexy = y + 1
    
    return instances()

@block
def pong(clk, switches, outvsync, outhsync, outcolor, cfg : VgaConfig):
    pixclock_feedback = Signal(bool(0))
    hblank = Signal(bool(0))
    vblank = Signal(bool(0))
    visible = Signal(bool(0))
    x = Signal(intbv(0, 0, cfg.a4 + 1))
    y = Signal(intbv(0, 0, cfg.b4 + 1))
    frame = Signal(intbv(0)[16:])

    if cfg.pixel_clock == 100:
        pix_enable = True
    else:
        incby = int(cfg.pixel_clock / 100 * 256)
        accumulator = Signal(modbv(0)[8:])
        pix_enable = Signal(bool())
        nacc = Signal(modbv(0)[9:])

        @always(clk.posedge)
        def pixclock_generator():
            """Reduce the 100 Mhz clock to the desired pixel clock"""
            nacc = intbv(accumulator + incby, 0, 2**9)
            if pixclock_feedback:
                accumulator.next = 0
                pix_enable.next = 0
            else:
                accumulator.next = nacc[8:]
                pix_enable.next = nacc[8]
    
    @always(clk.posedge)
    def mainloop():
        pixclock_feedback.next = 0
        if pix_enable:
            tx = intbv(x + 1, 0, x.max)
            x.next = tx
            thblank = bool(hblank)
            tvblank = bool(vblank)
            if tx == cfg.a1:
                """End of horizontally visible area"""
                thblank = 1
            elif tx == cfg.a2:
                """Begin hsync pulse"""
                outhsync.next = 1
            elif tx == cfg.a3:
                """End hsync pulse"""
                outhsync.next = 0
            elif tx == cfg.a4:
                """End line"""
                thblank = 0
                x.next = 0
                pixclock_feedback.next = 1

                ty = intbv(y + 1, 0, y.max)
                y.next = ty

                if ty == cfg.b1:
                    """End of vertically visible area"""
                    tvblank = 1
                elif ty == cfg.b2:
                    """Begin vsync pulse"""
                    outvsync.next = 1
                elif ty == cfg.b3:
                    """End vsync pulse"""
                    outvsync.next = 0
                elif ty == cfg.b4:
                    """End frame"""
                    tvblank = 0
                    y.next = 0

                    # Per frame logic:
                    frame.next = frame + 1
            # visible.next = not thblank and not tvblank
            if not thblank and not tvblank:
                # tmp = (x + frame) ^ y
                # outcolor.next = tmp[2]
                outcolor.next = y[2] ^ x[2]
            else:
                outcolor.next = 0
            hblank.next = thblank
            vblank.next = tvblank

    return instances()

"""
Todo:
    SDL1 pixel output
    Non hack makefile
    build with lto and without exceptions and rtti
"""

clk = Signal(bool(0))
switches = Signal(intbv(0)[16:])
vsyncout = Signal(bool(0))
hsyncout = Signal(bool(0))
colout = Signal(bool(0))

if len(sys.argv) >= 2 and sys.argv[1] == 'generate_verilog':
    cfg = vga_syn

    pong_inst = pong(clk, switches, vsyncout, hsyncout, colout, cfg)

    os.makedirs("obj", exist_ok=True)
    # pong_inst.convert("VHDL", std_logic_ports = True, path="obj")
    pong_inst.convert("verilog", testbench = False, path="obj")

    with open("obj/pong_cfg.h", "w") as header:
        header.write(f"""#pragma once
    #define VGA_WIDTH ({cfg.hvis})
    #define VGA_HEIGHT ({cfg.vvis})
    #define VGA_EXTRA_LINE_CLOCKS ({cfg.a4 - cfg.hvis})
    #define VGA_EXTAR_FRAME_CLOCKS ({(cfg.b4 - cfg.vvis) * cfg.a4})
    """)