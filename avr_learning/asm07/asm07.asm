; definice pro nas typ procesoru
.include "m169def.inc"
; podprogramy pro praci s displejem
.org 0x1000
.include "print.inc"

; Zacatek programu - po resetu
.org 0
jmp start

; My name, xor encrypted with display index
str: .db "FBRLB",0

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

	; Load string address
	ldi zl, low(2*str)
	ldi zh, high(2*str)	


	ldi r17, 2		; Index of first display position
show_next:
	lpm r16, Z+		; Load current characeter
	cp r16, r0		; r0 is by convention always 0
	breq end		; Break on null terminuator
	eor r16, r17	; Super clever decryption
	call show_char
	inc r17			; Move to next display position
	jmp show_next	; Else repeat

end: jmp end        ; Zastavime program - nekonecna smycka
