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

	; Load inputs
	ldi R16, 5
	ldi R17, 10
	ldi R18, 58

	; Computing: R20 = (4 * R16 + 3 * R17 - R18) / 8
	mov r23, r16
	call signe
	mov r20, r23
	mov r21, r24
	lsl r20
	rol r21
	lsl r20
	rol r21

	mov r23, r17
	call signe
	add r20, r23
	adc r21, r24
	add r20, r23
	adc r21, r24
	add r20, r23
	adc r21, r24

	mov r23, r18
	call signe
	sub r20, r23
	sbc r21, r24

	; Check lower 3 bits manually because ASR gets it wrong with negative numbers
	ldi r25, 0
	mov r23, r20
	andi r23, 7
	cpse r23, r0
	ldi r25, 1
	asr r21
	ror r20
	asr r21
	ror r20
	asr r21
	ror r20

	
	ldi r17, 2	; Display position

	; Print ('digit' masks out the higher nibble)
	mov r16, r21
	swap r16
	call digit
	mov r16, r21
	call digit
	mov r16, r20
	swap r16
	call digit
	mov r16, r20
	call digit

	ldi r16, 'P'
	cpse r25, r0
	call show_char


end: jmp end        ; Zastavime program - nekonecna smycka

; Display r16 as a hex digit and move to next position
digit:
	andi r16, 0x0f
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

; Sign extend r23 to r24
signe:
	ldi r24, 0
	sbrc r23,7
	ldi r24, 0xff
	ret

