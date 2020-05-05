// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vpong_H_
#define _Vpong_H_

#include "verilated.h"

class Vpong__Syms;

//----------

VL_MODULE(Vpong) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(reset,0,0);
    VL_OUT8(outvsync,0,0);
    VL_OUT8(outhsync,0,0);
    VL_OUT8(outcolor,0,0);
    VL_IN16(switches,15,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(pong__DOT__y,5,0);
    VL_SIG8(pong__DOT__x,6,0);
    VL_SIG8(pong__DOT__vblank,0,0);
    VL_SIG8(pong__DOT__paddle_ry,5,0);
    VL_SIG8(pong__DOT__paddle_rai,0,0);
    VL_SIG8(pong__DOT__paddle_ly,5,0);
    VL_SIG8(pong__DOT__paddle_lai,0,0);
    VL_SIG8(pong__DOT__move_enable,0,0);
    VL_SIG8(pong__DOT__lsfr,7,0);
    VL_SIG8(pong__DOT__hblank,0,0);
    VL_SIG8(pong__DOT__colldone,0,0);
    VL_SIG8(pong__DOT__bally,6,0);
    VL_SIG8(pong__DOT__ballx,7,0);
    VL_SIG8(pong__DOT__balldy,1,0);
    VL_SIG8(pong__DOT__balldx,1,0);
    VL_SIG8(pong__DOT__PONG_MAINLOOP__DOT__top,0,0);
    VL_SIG8(pong__DOT__PONG_MAINLOOP__DOT__bottom,0,0);
    VL_SIG8(pong__DOT__PONG_MAINLOOP__DOT__ball,0,0);
    VL_SIG8(pong__DOT__PONG_MAINLOOP__DOT__left,0,0);
    VL_SIG8(pong__DOT__PONG_MAINLOOP__DOT__right,0,0);
    VL_SIG8(pong__DOT__PONG_MAINLOOP__DOT__net,0,0);
    VL_SIG8(pong__DOT__PONG_MAINLOOP__DOT__lai,0,0);
    VL_SIG8(pong__DOT__PONG_MAINLOOP__DOT__rai,0,0);
    VL_SIG16(pong__DOT__PONG_MAINLOOP__DOT__tx,15,0);
    VL_SIG16(pong__DOT__PONG_MAINLOOP__DOT__ty,15,0);
    VL_SIG16(pong__DOT__PONG_MAINLOOP__DOT__pt_ly,15,0);
    VL_SIG16(pong__DOT__PONG_MAINLOOP__DOT__pt_ry,15,0);
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    VL_SIG8(__Vclklast__TOP__clk,0,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vpong__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    Vpong& operator= (const Vpong&);  ///< Copying not allowed
    Vpong(const Vpong&);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible WRT DPI scope names.
    Vpong(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vpong();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vpong__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vpong__Syms* symsp, bool first);
  private:
    static QData _change_request(Vpong__Syms* __restrict vlSymsp);
    void _ctor_var_reset();
  public:
    static void _eval(Vpong__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vpong__Syms* __restrict vlSymsp);
    static void _eval_settle(Vpong__Syms* __restrict vlSymsp);
    static void _sequent__TOP__1(Vpong__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif // guard
