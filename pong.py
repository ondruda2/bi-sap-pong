import math
from myhdl import *
import os
import sys

class VgaConfig:
    def __init__(self, pixel_clock, hvis, hfporch, hsync, hbporch, vvis, vfporch, vsync, vbporch):
        assert(1 <= min((hvis, hfporch, hsync, hbporch, vvis, vfporch, vsync, vbporch)))
        
        self.pixel_clock = pixel_clock
        self.hvis = hvis
        self.hfporch = hfporch
        self.hsync = hsync
        self.hbporch = hbporch
        self.vvis = vvis
        self.vfporch = vfporch
        self.vsync = vsync
        self.vbporch = vbporch


        self.a1 = hvis - 1
        self.a2 = hvis + hfporch - 1
        self.a3 = hvis + hfporch + hsync - 1
        self.a4 = hvis + hfporch + hsync + hbporch -1
        self.b1 = vvis - 1
        self.b2 = vvis + vfporch - 1
        self.b3 = vvis + vfporch + vsync -1
        self.b4 = vvis + vfporch + vsync + vbporch - 1

vga_syn = VgaConfig(65, 1024, 24, 136, 160, 768, 3, 6, 29)
vga_sim = VgaConfig(100, 100, 1, 3, 1, 50, 1, 3, 1)
vga_sim_large = VgaConfig(100, 1024, 24, 136, 160, 768, 3, 6, 29)

@block
def pong(clk, reset, switches, outvsync, outhsync, outcolor, cfg : VgaConfig):
    pixclock_feedback = Signal(bool(0))
    hblank = Signal(bool(0))
    vblank = Signal(bool(0))
    x = Signal(intbv(0, 0, cfg.a4 + 1))
    y = Signal(intbv(0, 0, cfg.b4 + 1))

    ballx = Signal(intbv(10, 0, 2**15))
    bally = Signal(intbv(10, 0, 2**15))
    balldx = Signal(intbv(0, -1, 2))
    balldy = Signal(intbv(1, -1, 2))
    colldone = Signal(bool(0))

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
    
    # @block
    # def paddle(clk, move_enable, up, down, drawout):
    #     y = intbv(0, 0, scanx.max)

    #     @always_seq(clk, None)
    #     def move():
    #         if move_enable:
    #             if up and not down and y:
    #                 y.next = y - 1
    #             if down and not up and y < h:
    #                 y.nexy = y + 1
        
    #     return instances()

    @always_seq(clk.posedge, reset)
    def mainloop():
        pixclock_feedback.next = 0
        if pix_enable:
            x.next = intbv(x + 1, 0, x.max)
            if x == cfg.a1:
                "End horizontally visible"
                hblank.next = 1
            if x == cfg.a2:
                "Begin hsync pulse"
                hsyncout.next = 1
            if x == cfg.a3:
                "End hsync pulse"
                hsyncout.next = 0
            if x == cfg.a4:
                "End line"
                "Start horizontally visible"
                x.next = 0
                hblank.next = 0
                y.next = intbv(y + 1, 0, y.max)
                pixclock_feedback.next = 1

                if y == cfg.b1:
                    "End vertically visible"
                    vblank.next = 1
                if y == cfg.b2:
                    "Begin vsync pulse"
                    vsyncout.next = 1
                if y == cfg.b3:
                    "End vsync pulse"
                    vsyncout.next = 0

                    ballx.next = ballx + balldx
                    bally.next = bally + balldy
                    colldone.next = 0
                if y == cfg.b4:
                    "End frame"
                    "Start vertically visible"
                    y.next = 0
                    vblank.next = 0

            if not hblank and not vblank:
                top = y == 0
                bottom = y == cfg.b1
                # ball = x - ballx < 3 and y - bally < 3
                tx = modbv(x - ballx, 0, 2**16)
                ty = modbv(y - bally, 0, 2**16)
                ball = tx < 5 and ty < 5

                if not colldone and ball:
                    colldone.next = 1
                    if top or bottom:
                        balldy.next = -balldy

                outcolor.next = top or bottom or ball
                

    return instances()

"""
Todo:
    build with lto and without exceptions and rtti
"""

clk = Signal(bool(0))
reset = ResetSignal(0, active=1, isasync=False)
switches = Signal(intbv(0)[16:])
vsyncout = Signal(bool(0))
hsyncout = Signal(bool(0))
colout = Signal(bool(0))

if len(sys.argv) >= 2 and sys.argv[1] == 'generate_verilog':
    cfg = vga_sim

    pong_inst = pong(clk, reset, switches, vsyncout, hsyncout, colout, cfg)

    os.makedirs("obj", exist_ok=True)
    # pong_inst.convert("VHDL", std_logic_ports = True, path="obj")
    pong_inst.convert("verilog", testbench = False, path="obj")

    with open("obj/pong_cfg.h", "w") as header:
        header.write(f"""#pragma once
    #define VGA_WIDTH ({cfg.hvis})
    #define VGA_HEIGHT ({cfg.vvis})
    #define VGA_EXTRA_LINE_CLOCKS ({cfg.a4 - cfg.hvis + 1})
    #define VGA_EXTAR_FRAME_CLOCKS ({(cfg.b4 - cfg.vvis + 1) * (cfg.a4 + 1)})
    """)