        AREA QUESTION, CODE, READONLY
        ENTRY
		; Josh Bakelaar (251139121)
		; 11/29/2022
		; Step 1: copy string1 into r0
		; Step 2: go through string
		; Step 3: if space check for next character, else keep going
		; Step 4: if t check for next character, else keep going
		; Step 5: if h check for next charater, else keep going
		; Step 6: if e check for next character, else keep going
		; Step 7: if space remove last 3 letters and keep going
		; Step 8: store in String 2;
		
		
		ADR    r0, STRING1                  ; Copy STRING1 into r0
        ADR    r1, STRING2                  ; Where to store the final string
        MOV    r2, #-1                      ; Make a counter at -1 (because were adding at the start of the reader we need to start at -1)

Reader  ADD    r2, #1                       ; Add 1 to counter
        MOV    r3, r2                       ; Make a clone so the original pointer will still be pointing to the original spot
        LDRB   r4, [r0, r2]                 ; Load the character into r4
        MOV    r5, r4                       ; clone the character into r5 so we can still be pointing to the original character

Checker CMP    r4, #spacech                 ; Check to see if the character is a space
        ADDEQ  r3, #1                       ; Increment counter
		LDRBEQ r4, [r0, r3]                 ; Go to next character
		CMPEQ  r4, #t                       ; Check to see if the character is a t
        ADDEQ  r3, #1                       ; Increment counter
		LDRBEQ r4, [r0, r3]                 ; Go to next character
		CMPEQ  r4, #h                       ; Check to see if the characer is a h
        ADDEQ  r3, #1                       ; Increment counter
		LDRBEQ r4, [r0, r3]                 ; Go to next character
		CMPEQ  r4, #e                       ; Check to see if the characer is a e
        ADDEQ  r3, #1                       ; Increment counter
		LDRBEQ r4, [r0, r3]                 ; Go to next character
		CMPEQ  r4, #spacech                 ; Check to see if the characer is a space
        ADDEQ  r2, #2                       ; Adjust the original pointer by 2 to skip "the"
        BEQ    Reader                       ; Go back to the Reader to read next charaters
		
        CMPNE  r4, #end                     ; See if its the end of the string
		STRBNE r5, [r1], #1                 ; Store the original character if not "the" or end of string
		BNE    Reader                       ; Go back to Reader if not the end
		
loop    b      loop

t       EQU 0x74                            ; t in ASCII
h       EQU 0x68                            ; h in ASCII
e       EQU 0x65                            ; e in ASCII
spacech EQU 0x20                            ; space in ASCII
end     EQU 0x0                             ; null in ASCII

STRING1 DCB "and the man said they must go" ; String1
EoS     DCB 0x00                            ; end of string1
STRING2 DCB 0x7F                            ; just allocating 127 bytes
        END