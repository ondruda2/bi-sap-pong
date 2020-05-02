.include "m169def.inc"

.org 0x0
	jmp start

.org 0x100

; Check for two's-complement overflow
check:
	brvc good
	ldi r21, 1
good:
	ret

start:
	; Initialize stack
	ldi r16, 0xFF
	out SPL, r16
	ldi r16, 0x04
	out SPH, r16

	; Load inputs
	ldi R16, 5
	ldi R17, 10
	ldi R18, 58

	; Error indicator
	ldi r21, 0

	; Computing: R20 = (4 * R16 + 3 * R17 - R18) / 8
	mov r20, r16
	lsl r20
	call check
	lsl r20
	call check
	add r20, r17
	call check
	add r20, r17
	call check
	add r20, r17
	call check
	sub r20, r18
	call check
	; Check lower 3 bits manually because ASR gets it wrong with negative numbers
	mov r22, r20
	andi r22, 7
	cpse r22, r0
	ldi r21, 1
	asr r20
	asr r20
	asr r20
	
	; Set V on arithmetic error
	cpse r21, r0
	sev

	
end: rjmp end
