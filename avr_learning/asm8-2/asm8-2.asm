; definice pro nas typ procesoru
.include "m169def.inc"
; podprogramy pro praci s displejem
.org 0x1000
.include "print.inc"

; Zacatek programu - po resetu
.org 0
jmp start

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

	ldi r18, 5 	; <-- Number to display
	ldi r17, 2	; Display position

	; Extract higher and lower nibbles, call digit
	mov r16, r18
	lsr r16
	lsr r16
	lsr r16
	lsr r16
	call digit
	mov r16, r18
	andi r16, 0xF
	call digit


end: jmp end        ; Zastavime program - nekonecna smycka

; Display r16 as a hex digit and move to next position
digit:
	cpi r16, 9
	brge letter
	subi r16, -'0'
	rjmp letter_end
letter:
	subi r16, 10-'A'
letter_end:
	call show_char
	inc r17
	ret
