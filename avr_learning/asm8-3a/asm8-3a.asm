; definice pro nas typ procesoru
.include "m169def.inc"
; podprogramy pro praci s displejem
.org 0x1000
.include "print.inc"

; Zacatek programu - po resetu
.org 0
jmp start

; Numbers to add
.equ num_a = 1234
.equ num_b = 0xffffff00

; Result strings
res_over: .db "OVER",0
res_carry: .db "CARRY",0
res_zero: .db "0",0

; Array of strings
res: .db low(2*res_over), high(2*res_over), low(2*res_carry), high(2*res_carry), low(2*res_zero), high(2*res_zero)

; Zacatek programu - hlavni program
.org 0x100
start:
    ; Inicializace zasobniku
	ldi r16, 0xFF
	out SPL, r16
	ldi r16, 0x04
	out SPH, r16
    ; Inicializace displeje
	call init_disp

	; Load numbers	
	ldi r18, LOW(num_a)
	ldi r19, BYTE2(num_a)
	ldi r20, BYTE3(num_a)
	ldi r21, BYTE4(num_a)

	ldi r22, LOW(num_b)
	ldi r23, BYTE2(num_b)
	ldi r24, BYTE3(num_b)
	ldi r25, BYTE4(num_b)

	; Long addition, result is in r18-r21
	add r18, r22
	adc r19, r23
	adc r20, r24
	adc r21, r25

	; Decide which string to display
	ldi r16, 0
	brcs display
	ldi r16, 2
	brvs display
	ldi r16, 4

display:	
	ldi zl, low(2*res)
	ldi zh, high(2*res)

	; Look! Double indirection
	add zl, r16
	adc zh, r0
	
	; Copy through X because only 'lpm Z' can load into an arbitrary register
	lpm xl, z+
	lpm xh, z+
	mov zl, xl
	mov zh, xh

	ldi r17, 2		; Display position
next:
	lpm r16, z+
	cpi r16, 0
	breq end
	call show_char
	inc r17
	rjmp next

end: jmp end        ; Zastavime program - nekonecna smycka
