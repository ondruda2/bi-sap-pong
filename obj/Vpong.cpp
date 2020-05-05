// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpong.h for the primary calling header

#include "Vpong.h"             // For This
#include "Vpong__Syms.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(Vpong) {
    Vpong__Syms* __restrict vlSymsp = __VlSymsp = new Vpong__Syms(this, name());
    Vpong* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vpong::__Vconfigure(Vpong__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vpong::~Vpong() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vpong::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vpong::eval\n"); );
    Vpong__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vpong* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    while (VL_LIKELY(__Vchange)) {
	VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (VL_UNLIKELY(++__VclockLoop > 100)) VL_FATAL_MT(__FILE__,__LINE__,__FILE__,"Verilated model didn't converge");
    }
}

void Vpong::_eval_initial_loop(Vpong__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    int __VclockLoop = 0;
    QData __Vchange = 1;
    while (VL_LIKELY(__Vchange)) {
	_eval_settle(vlSymsp);
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (VL_UNLIKELY(++__VclockLoop > 100)) VL_FATAL_MT(__FILE__,__LINE__,__FILE__,"Verilated model didn't DC converge");
    }
}

//--------------------
// Internal Methods

VL_INLINE_OPT void Vpong::_sequent__TOP__1(Vpong__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpong::_sequent__TOP__1\n"); );
    Vpong* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__pong__DOT__lsfr,7,0);
    VL_SIG8(__Vdly__pong__DOT__colldone,0,0);
    VL_SIG8(__Vdly__pong__DOT__vblank,0,0);
    VL_SIG8(__Vdly__pong__DOT__paddle_lai,0,0);
    VL_SIG8(__Vdly__pong__DOT__balldy,1,0);
    VL_SIG8(__Vdly__pong__DOT__ballx,7,0);
    VL_SIG8(__Vdly__pong__DOT__paddle_ry,5,0);
    VL_SIG8(__Vdly__pong__DOT__hblank,0,0);
    VL_SIG8(__Vdly__pong__DOT__paddle_ly,5,0);
    VL_SIG8(__Vdly__pong__DOT__paddle_rai,0,0);
    VL_SIG8(__Vdly__pong__DOT__x,6,0);
    VL_SIG8(__Vdly__pong__DOT__bally,6,0);
    VL_SIG8(__Vdly__pong__DOT__y,5,0);
    VL_SIG8(__Vdly__pong__DOT__move_enable,0,0);
    VL_SIG8(__Vdly__pong__DOT__balldx,1,0);
    // Body
    __Vdly__pong__DOT__lsfr = vlTOPp->pong__DOT__lsfr;
    __Vdly__pong__DOT__colldone = vlTOPp->pong__DOT__colldone;
    __Vdly__pong__DOT__vblank = vlTOPp->pong__DOT__vblank;
    __Vdly__pong__DOT__paddle_lai = vlTOPp->pong__DOT__paddle_lai;
    __Vdly__pong__DOT__balldy = vlTOPp->pong__DOT__balldy;
    __Vdly__pong__DOT__ballx = vlTOPp->pong__DOT__ballx;
    __Vdly__pong__DOT__paddle_ry = vlTOPp->pong__DOT__paddle_ry;
    __Vdly__pong__DOT__hblank = vlTOPp->pong__DOT__hblank;
    __Vdly__pong__DOT__paddle_ly = vlTOPp->pong__DOT__paddle_ly;
    __Vdly__pong__DOT__paddle_rai = vlTOPp->pong__DOT__paddle_rai;
    __Vdly__pong__DOT__x = vlTOPp->pong__DOT__x;
    __Vdly__pong__DOT__bally = vlTOPp->pong__DOT__bally;
    __Vdly__pong__DOT__y = vlTOPp->pong__DOT__y;
    __Vdly__pong__DOT__move_enable = vlTOPp->pong__DOT__move_enable;
    __Vdly__pong__DOT__balldx = vlTOPp->pong__DOT__balldx;
    // ALWAYS at obj/pong.v:47
    if (vlTOPp->reset) {
	__Vdly__pong__DOT__lsfr = 0U;
    } else {
	__Vdly__pong__DOT__lsfr = (0x7fU & ((IData)(vlTOPp->pong__DOT__lsfr) 
					    >> 1U));
	__Vdly__pong__DOT__lsfr = ((0x7fU & (IData)(__Vdly__pong__DOT__lsfr)) 
				   | (0x80U & ((~ (
						   ((((IData)(vlTOPp->pong__DOT__lsfr) 
						      >> 7U) 
						     ^ 
						     ((IData)(vlTOPp->pong__DOT__lsfr) 
						      >> 5U)) 
						    ^ 
						    ((IData)(vlTOPp->pong__DOT__lsfr) 
						     >> 4U)) 
						   ^ 
						   ((IData)(vlTOPp->pong__DOT__lsfr) 
						    >> 3U))) 
					       << 7U)));
    }
    // ALWAYS at obj/pong.v:58
    if (vlTOPp->reset) {
	__Vdly__pong__DOT__colldone = 0U;
	__Vdly__pong__DOT__vblank = 0U;
	__Vdly__pong__DOT__paddle_lai = 0U;
	vlTOPp->outvsync = 0U;
	__Vdly__pong__DOT__balldy = 1U;
	__Vdly__pong__DOT__ballx = 0x32U;
	__Vdly__pong__DOT__paddle_ry = 0x19U;
	__Vdly__pong__DOT__hblank = 0U;
	__Vdly__pong__DOT__paddle_ly = 0x19U;
	__Vdly__pong__DOT__paddle_rai = 0U;
	__Vdly__pong__DOT__x = 0U;
	__Vdly__pong__DOT__bally = 0x19U;
	__Vdly__pong__DOT__y = 0U;
	__Vdly__pong__DOT__move_enable = 0U;
	__Vdly__pong__DOT__balldx = 3U;
	vlTOPp->outcolor = 0U;
	vlTOPp->outhsync = 0U;
    } else {
	__Vdly__pong__DOT__move_enable = 0U;
	__Vdly__pong__DOT__x = (0x7fU & ((IData)(1U) 
					 + (IData)(vlTOPp->pong__DOT__x)));
	if ((0x63U == (IData)(vlTOPp->pong__DOT__x))) {
	    __Vdly__pong__DOT__hblank = 1U;
	}
	if ((0x64U == (IData)(vlTOPp->pong__DOT__x))) {
	    vlTOPp->outhsync = 1U;
	}
	if ((0x67U == (IData)(vlTOPp->pong__DOT__x))) {
	    vlTOPp->outhsync = 0U;
	}
	if ((0x68U == (IData)(vlTOPp->pong__DOT__x))) {
	    __Vdly__pong__DOT__x = 0U;
	    __Vdly__pong__DOT__hblank = 0U;
	    __Vdly__pong__DOT__y = (0x3fU & ((IData)(1U) 
					     + (IData)(vlTOPp->pong__DOT__y)));
	    if ((0x31U == (IData)(vlTOPp->pong__DOT__y))) {
		__Vdly__pong__DOT__vblank = 1U;
	    }
	    if ((0x32U == (IData)(vlTOPp->pong__DOT__y))) {
		vlTOPp->outvsync = 1U;
	    }
	    if ((0x35U == (IData)(vlTOPp->pong__DOT__y))) {
		vlTOPp->outvsync = 0U;
		__Vdly__pong__DOT__move_enable = 1U;
	    }
	    if ((0x36U == (IData)(vlTOPp->pong__DOT__y))) {
		__Vdly__pong__DOT__y = 0U;
		__Vdly__pong__DOT__vblank = 0U;
	    }
	}
	if ((1U & ((~ (IData)(vlTOPp->pong__DOT__hblank)) 
		   & (~ (IData)(vlTOPp->pong__DOT__vblank))))) {
	    vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__top 
		= (0U == (IData)(vlTOPp->pong__DOT__y));
	    vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__bottom 
		= (0x31U == (IData)(vlTOPp->pong__DOT__y));
	    vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__tx 
		= (0xffffU & (VL_EXTENDS_II(16,8, (IData)(vlTOPp->pong__DOT__x)) 
			      - VL_EXTENDS_II(16,9, (IData)(vlTOPp->pong__DOT__ballx))));
	    vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__ty 
		= (0xffffU & (VL_EXTENDS_II(16,7, (IData)(vlTOPp->pong__DOT__y)) 
			      - VL_EXTENDS_II(16,8, (IData)(vlTOPp->pong__DOT__bally))));
	    vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__ball 
		= ((5U > (IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__tx)) 
		   & (5U > (IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__ty)));
	    vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__pt_ly 
		= (0xffffU & (VL_EXTENDS_II(16,7, (IData)(vlTOPp->pong__DOT__y)) 
			      - VL_EXTENDS_II(16,7, (IData)(vlTOPp->pong__DOT__paddle_ly))));
	    vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__left 
		= (((0U == (IData)(vlTOPp->pong__DOT__x)) 
		    & (0xcU > (IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__pt_ly))) 
		   & ((~ (IData)(vlTOPp->pong__DOT__paddle_lai)) 
		      | (IData)(vlTOPp->pong__DOT__y)));
	    vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__pt_ry 
		= (0xffffU & (VL_EXTENDS_II(16,7, (IData)(vlTOPp->pong__DOT__y)) 
			      - VL_EXTENDS_II(16,7, (IData)(vlTOPp->pong__DOT__paddle_ry))));
	    vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__right 
		= (((0x63U == VL_EXTENDS_II(32,8, (IData)(vlTOPp->pong__DOT__x))) 
		    & (0xcU > (IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__pt_ry))) 
		   & ((~ (IData)(vlTOPp->pong__DOT__paddle_rai)) 
		      | (IData)(vlTOPp->pong__DOT__y)));
	    vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__net 
		= ((0x32U == (IData)(vlTOPp->pong__DOT__x)) 
		   & (0U == (3U & (IData)(vlTOPp->pong__DOT__y))));
	    vlTOPp->outcolor = ((((((IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__top) 
				    | (IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__bottom)) 
				   | (IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__ball)) 
				  | (IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__left)) 
				 | (IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__right)) 
				| (IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__net));
	    if (((~ (IData)(vlTOPp->pong__DOT__colldone)) 
		 & (IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__ball))) {
		if (((IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__top) 
		     | (IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__bottom))) {
		    __Vdly__pong__DOT__balldy = (3U 
						 & VL_NEGATE_I((IData)(vlTOPp->pong__DOT__balldy)));
		    __Vdly__pong__DOT__colldone = 1U;
		} else {
		    if (((IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__left) 
			 | (IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__right))) {
			__Vdly__pong__DOT__balldx = 
			    (3U & VL_NEGATE_I((IData)(vlTOPp->pong__DOT__balldx)));
			__Vdly__pong__DOT__colldone = 1U;
		    }
		    if (vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__left) {
			__Vdly__pong__DOT__balldy = 
			    (((IData)(vlTOPp->pong__DOT__y) 
			      < ((IData)(2U) + (IData)(vlTOPp->pong__DOT__paddle_ly)))
			      ? 3U : (VL_GTS_III(1,32,32, 
						 VL_EXTENDS_II(32,7, (IData)(vlTOPp->pong__DOT__y)), 
						 ((IData)(7U) 
						  + 
						  VL_EXTENDS_II(32,7, (IData)(vlTOPp->pong__DOT__paddle_ly))))
				       ? 1U : 0U));
		    } else {
			if (vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__right) {
			    __Vdly__pong__DOT__balldy 
				= (((IData)(vlTOPp->pong__DOT__y) 
				    < ((IData)(2U) 
				       + (IData)(vlTOPp->pong__DOT__paddle_ry)))
				    ? 3U : (VL_GTS_III(1,32,32, 
						       VL_EXTENDS_II(32,7, (IData)(vlTOPp->pong__DOT__y)), 
						       ((IData)(7U) 
							+ 
							VL_EXTENDS_II(32,7, (IData)(vlTOPp->pong__DOT__paddle_ry))))
					     ? 1U : 0U));
			}
		    }
		}
	    }
	}
	if (vlTOPp->pong__DOT__move_enable) {
	    __Vdly__pong__DOT__colldone = 0U;
	    if (((0x7dU > (IData)(vlTOPp->pong__DOT__ballx)) 
		 | VL_LTS_III(1,32,32, 0xecU, VL_EXTENDS_II(32,9, (IData)(vlTOPp->pong__DOT__ballx))))) {
		__Vdly__pong__DOT__ballx = (0xffU & 
					    ((IData)(vlTOPp->pong__DOT__ballx) 
					     + (0x1ffU 
						& VL_EXTENDS_II(9,2, (IData)(vlTOPp->pong__DOT__balldx)))));
		__Vdly__pong__DOT__bally = (0x7fU & 
					    ((IData)(vlTOPp->pong__DOT__bally) 
					     + (0xffU 
						& VL_EXTENDS_II(8,2, (IData)(vlTOPp->pong__DOT__balldy)))));
	    } else {
		__Vdly__pong__DOT__ballx = 0x34U;
		__Vdly__pong__DOT__bally = 0x1bU;
		__Vdly__pong__DOT__balldx = (3U & (
						   (8U 
						    & (IData)(vlTOPp->pong__DOT__lsfr))
						    ? 0xffffffffU
						    : 1U));
		__Vdly__pong__DOT__balldy = (3U & (
						   (2U 
						    & (IData)(vlTOPp->pong__DOT__lsfr))
						    ? 1U
						    : 
						   ((4U 
						     & (IData)(vlTOPp->pong__DOT__lsfr))
						     ? 0xffffffffU
						     : 0U)));
	    }
	    if ((0x2000U & (IData)(vlTOPp->switches))) {
		__Vdly__pong__DOT__paddle_lai = 1U;
	    }
	    if ((0x1000U & (IData)(vlTOPp->switches))) {
		__Vdly__pong__DOT__paddle_lai = 0U;
	    }
	    if ((8U & (IData)(vlTOPp->switches))) {
		__Vdly__pong__DOT__paddle_rai = 1U;
	    }
	    if ((4U & (IData)(vlTOPp->switches))) {
		__Vdly__pong__DOT__paddle_rai = 0U;
	    }
	    vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__lai 
		= ((IData)(vlTOPp->pong__DOT__paddle_lai) 
		   & (0x32U > (IData)(vlTOPp->pong__DOT__ballx)));
	    vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__rai 
		= ((IData)(vlTOPp->pong__DOT__paddle_rai) 
		   & (0x32U < (IData)(vlTOPp->pong__DOT__ballx)));
	    if ((((((IData)(vlTOPp->switches) >> 0xfU) 
		   & (~ ((IData)(vlTOPp->switches) 
			 >> 0xeU))) | ((IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__lai) 
				       & (((IData)(3U) 
					   + (IData)(vlTOPp->pong__DOT__bally)) 
					  < (IData)(vlTOPp->pong__DOT__paddle_ly)))) 
		 & (1U < (IData)(vlTOPp->pong__DOT__paddle_ly)))) {
		__Vdly__pong__DOT__paddle_ly = (0x3fU 
						& ((IData)(vlTOPp->pong__DOT__paddle_ly) 
						   - (IData)(1U)));
	    }
	    if ((((((IData)(vlTOPp->switches) >> 0xeU) 
		   & (~ ((IData)(vlTOPp->switches) 
			 >> 0xfU))) | ((IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__lai) 
				       & ((IData)(vlTOPp->pong__DOT__bally) 
					  >= ((IData)(0xbU) 
					      + (IData)(vlTOPp->pong__DOT__paddle_ly))))) 
		 & VL_GTS_III(1,32,32, 0x26U, VL_EXTENDS_II(32,7, (IData)(vlTOPp->pong__DOT__paddle_ly))))) {
		__Vdly__pong__DOT__paddle_ly = (0x3fU 
						& ((IData)(1U) 
						   + (IData)(vlTOPp->pong__DOT__paddle_ly)));
	    }
	    if ((((((IData)(vlTOPp->switches) >> 1U) 
		   & (~ (IData)(vlTOPp->switches))) 
		  | ((IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__rai) 
		     & (((IData)(3U) + (IData)(vlTOPp->pong__DOT__bally)) 
			< (IData)(vlTOPp->pong__DOT__paddle_ry)))) 
		 & (1U < (IData)(vlTOPp->pong__DOT__paddle_ry)))) {
		__Vdly__pong__DOT__paddle_ry = (0x3fU 
						& ((IData)(vlTOPp->pong__DOT__paddle_ry) 
						   - (IData)(1U)));
	    }
	    if (((((IData)(vlTOPp->switches) & (~ ((IData)(vlTOPp->switches) 
						   >> 1U))) 
		  | ((IData)(vlTOPp->pong__DOT__PONG_MAINLOOP__DOT__rai) 
		     & ((IData)(vlTOPp->pong__DOT__bally) 
			>= ((IData)(0xbU) + (IData)(vlTOPp->pong__DOT__paddle_ry))))) 
		 & VL_GTS_III(1,32,32, 0x26U, VL_EXTENDS_II(32,7, (IData)(vlTOPp->pong__DOT__paddle_ry))))) {
		__Vdly__pong__DOT__paddle_ry = (0x3fU 
						& ((IData)(1U) 
						   + (IData)(vlTOPp->pong__DOT__paddle_ry)));
	    }
	}
    }
    vlTOPp->pong__DOT__x = __Vdly__pong__DOT__x;
    vlTOPp->pong__DOT__y = __Vdly__pong__DOT__y;
    vlTOPp->pong__DOT__hblank = __Vdly__pong__DOT__hblank;
    vlTOPp->pong__DOT__vblank = __Vdly__pong__DOT__vblank;
    vlTOPp->pong__DOT__ballx = __Vdly__pong__DOT__ballx;
    vlTOPp->pong__DOT__bally = __Vdly__pong__DOT__bally;
    vlTOPp->pong__DOT__paddle_ly = __Vdly__pong__DOT__paddle_ly;
    vlTOPp->pong__DOT__paddle_lai = __Vdly__pong__DOT__paddle_lai;
    vlTOPp->pong__DOT__paddle_ry = __Vdly__pong__DOT__paddle_ry;
    vlTOPp->pong__DOT__paddle_rai = __Vdly__pong__DOT__paddle_rai;
    vlTOPp->pong__DOT__colldone = __Vdly__pong__DOT__colldone;
    vlTOPp->pong__DOT__balldy = __Vdly__pong__DOT__balldy;
    vlTOPp->pong__DOT__balldx = __Vdly__pong__DOT__balldx;
    vlTOPp->pong__DOT__move_enable = __Vdly__pong__DOT__move_enable;
    vlTOPp->pong__DOT__lsfr = __Vdly__pong__DOT__lsfr;
}

void Vpong::_eval(Vpong__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpong::_eval\n"); );
    Vpong* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
	vlTOPp->_sequent__TOP__1(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void Vpong::_eval_initial(Vpong__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpong::_eval_initial\n"); );
    Vpong* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vpong::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpong::final\n"); );
    // Variables
    Vpong__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vpong* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vpong::_eval_settle(Vpong__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpong::_eval_settle\n"); );
    Vpong* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

VL_INLINE_OPT QData Vpong::_change_request(Vpong__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpong::_change_request\n"); );
    Vpong* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vpong::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpong::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
	Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((reset & 0xfeU))) {
	Verilated::overWidthError("reset");}
}
#endif // VL_DEBUG

void Vpong::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpong::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    reset = VL_RAND_RESET_I(1);
    switches = VL_RAND_RESET_I(16);
    outvsync = VL_RAND_RESET_I(1);
    outhsync = VL_RAND_RESET_I(1);
    outcolor = VL_RAND_RESET_I(1);
    pong__DOT__y = VL_RAND_RESET_I(6);
    pong__DOT__x = VL_RAND_RESET_I(7);
    pong__DOT__vblank = VL_RAND_RESET_I(1);
    pong__DOT__paddle_ry = VL_RAND_RESET_I(6);
    pong__DOT__paddle_rai = VL_RAND_RESET_I(1);
    pong__DOT__paddle_ly = VL_RAND_RESET_I(6);
    pong__DOT__paddle_lai = VL_RAND_RESET_I(1);
    pong__DOT__move_enable = VL_RAND_RESET_I(1);
    pong__DOT__lsfr = VL_RAND_RESET_I(8);
    pong__DOT__hblank = VL_RAND_RESET_I(1);
    pong__DOT__colldone = VL_RAND_RESET_I(1);
    pong__DOT__bally = VL_RAND_RESET_I(7);
    pong__DOT__ballx = VL_RAND_RESET_I(8);
    pong__DOT__balldy = VL_RAND_RESET_I(2);
    pong__DOT__balldx = VL_RAND_RESET_I(2);
    pong__DOT__PONG_MAINLOOP__DOT__top = VL_RAND_RESET_I(1);
    pong__DOT__PONG_MAINLOOP__DOT__bottom = VL_RAND_RESET_I(1);
    pong__DOT__PONG_MAINLOOP__DOT__tx = VL_RAND_RESET_I(16);
    pong__DOT__PONG_MAINLOOP__DOT__ty = VL_RAND_RESET_I(16);
    pong__DOT__PONG_MAINLOOP__DOT__ball = VL_RAND_RESET_I(1);
    pong__DOT__PONG_MAINLOOP__DOT__pt_ly = VL_RAND_RESET_I(16);
    pong__DOT__PONG_MAINLOOP__DOT__left = VL_RAND_RESET_I(1);
    pong__DOT__PONG_MAINLOOP__DOT__pt_ry = VL_RAND_RESET_I(16);
    pong__DOT__PONG_MAINLOOP__DOT__right = VL_RAND_RESET_I(1);
    pong__DOT__PONG_MAINLOOP__DOT__net = VL_RAND_RESET_I(1);
    pong__DOT__PONG_MAINLOOP__DOT__lai = VL_RAND_RESET_I(1);
    pong__DOT__PONG_MAINLOOP__DOT__rai = VL_RAND_RESET_I(1);
    __Vclklast__TOP__clk = VL_RAND_RESET_I(1);
}
