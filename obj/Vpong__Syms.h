// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vpong__Syms_H_
#define _Vpong__Syms_H_

#include "verilated.h"

// INCLUDE MODULE CLASSES
#include "Vpong.h"

// SYMS CLASS
class Vpong__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vpong*                         TOPp;
    
    // CREATORS
    Vpong__Syms(Vpong* topp, const char* namep);
    ~Vpong__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(64);

#endif // guard
