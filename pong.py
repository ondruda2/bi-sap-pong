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

    ballx = Signal(intbv(cfg.hvis // 2, 0, x.max*2))
    bally = Signal(intbv(cfg.vvis // 2, 0, y.max*2))
    balldx = Signal(intbv(-1, -1, 2))
    balldy = Signal(intbv(1, -1, 2))
    ballx_nrbits = ballx._nrbits
    ballsize = 5

    paddleh = cfg.vvis // 4
    paddle_ly = Signal(intbv(cfg.vvis//2, 0, cfg.vvis+1))
    paddle_ry = Signal(intbv(cfg.vvis//2, 0, cfg.vvis+1))
    paddle_lai = Signal(bool(0))
    paddle_rai = Signal(bool(0))

    colldone = Signal(bool(0))
    move_enable = Signal(bool(0))

    lsfr = Signal(intbv(0, 0, 2**8))
    @always_seq(clk.posedge, reset)
    def random():
        lsfr.next[8:] = lsfr[:1]
        lsfr.next[7] = lsfr[7] ^ lsfr[5] ^ lsfr[4] ^ lsfr[3] ^ 1

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
    
    @always_seq(clk.posedge, reset)
    def mainloop():
        pixclock_feedback.next = 0
        move_enable.next = 0
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

                    move_enable.next = 1
                if y == cfg.b4:
                    "End frame"
                    "Start vertically visible"
                    y.next = 0
                    vblank.next = 0

            if not hblank and not vblank:
                top = y == 0
                bottom = y == cfg.b1
                tx = modbv(x - ballx, 0, 2**16)
                ty = modbv(y - bally, 0, 2**16)
                ball = tx < ballsize and ty < ballsize

                pt_ly = modbv(y - paddle_ly, 0, 2**16)
                left = x == 0 and pt_ly < paddleh and (not paddle_lai or y[0] == 1)

                pt_ry = modbv(y - paddle_ry, 0, 2**16)
                right = x == cfg.hvis-1 and pt_ry < paddleh and (not paddle_rai or y[0] == 1)

                net = x == cfg.hvis//2 and y[2:] == 0

                outcolor.next = top or bottom or ball or left or right or net

                if not colldone and ball:
                    if top or bottom:
                        colldone.next = 1
                        balldy.next = -balldy
                    else:
                        if left or right:
                            colldone.next = 1
                            balldx.next = -balldx
                        if left:
                            if y < paddle_ly + paddleh // 5:
                                balldy.next = -1
                            elif y > paddle_ly + (paddleh - paddleh // 5 - 3):
                                balldy.next = 1
                            else:
                                balldy.next = 0
                        elif right:
                            if y < paddle_ry + paddleh // 5:
                                balldy.next = -1
                            elif y > paddle_ry + (paddleh - paddleh // 5 - 3):
                                balldy.next = 1
                            else:
                                balldy.next = 0
        
        "Can be asserted multiple times per frame to allow faster movement"
        if move_enable:
            colldone.next = 0

            if ballx < x.max + 20 or ballx > 2**ballx_nrbits - 20:
                ballx.next = ballx + balldx
                bally.next = bally + balldy
            else:
                ballx.next = x.max // 2
                bally.next = y.max // 2
                balldx.next = -1 if lsfr[3] else 1
                balldy.next = 1 if lsfr[1] else (-1 if lsfr[2] else 0)
                # Testing: launch the ball straight left
                # balldx.next = -1
                # balldy.next = 0

            if switches[13]:
                paddle_lai.next = 1
            if switches[12]:
                paddle_lai.next = 0

            if switches[3]:
                paddle_rai.next = 1
            if switches[2]:
                paddle_rai.next = 0

            lai = paddle_lai and ballx < cfg.hvis // 2
            rai = paddle_rai and ballx > cfg.hvis // 2

            if (switches[15] and not switches[14] 
                or lai and bally + ballsize - 2 < paddle_ly) \
                and paddle_ly > 1:
                    paddle_ly.next = paddle_ly - 1
            if (switches[14] and not switches[15] 
                or lai and bally >= paddle_ly + paddleh - 1) \
                and paddle_ly < cfg.vvis - paddleh:
                    paddle_ly.next = paddle_ly + 1

            if (switches[1] and not switches[0] 
                or rai and bally + ballsize - 2 < paddle_ry) \
                and paddle_ry > 1:
                    paddle_ry.next = paddle_ry - 1
            if (switches[0] and not switches[1] 
                or rai and bally >= paddle_ry + paddleh - 1) \
                and paddle_ry < cfg.vvis - paddleh:
                    paddle_ry.next = paddle_ry + 1

    return instances()

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
    pong_inst.convert("VHDL", std_logic_ports = True, path="obj")
    try:
        pong_inst.convert("verilog", testbench = False, path="obj")
    except:
        os.remove("obj/pong.v")
        raise

    with open("obj/pong_cfg.h", "w") as header:
        header.write(f"""#pragma once
    #define VGA_WIDTH ({cfg.hvis})
    #define VGA_HEIGHT ({cfg.vvis})
    #define VGA_EXTRA_LINE_CLOCKS ({cfg.a4 - cfg.hvis + 1})
    #define VGA_EXTAR_FRAME_CLOCKS ({(cfg.b4 - cfg.vvis + 1) * (cfg.a4 + 1)})
    """)