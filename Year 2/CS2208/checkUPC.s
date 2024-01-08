; Josh Bakelaar
; 951139121
; 11/08/2022
;
; question1.s
; checks that a UPC code is correct. The steps are the following
; 1) add the 1,3,5,7,9,11 digits
; 2) add the 2,4,6,8,10 digits
; 3) multiply first sum by 3 and add it to second sum
; 4) add the check digit (12 digit) and check to see if it produces a multiple of 10 (can add the check digit in step 2)
; 5) if multiple of 10, UPC = valid. Else UPC = invalid.

        AREA question1, CODE, READONLY
        ENTRY
      
        ADR    r1, UPC2          ; Put the UPC code into r1
        MOV    r3, #counter       ; Initilize a counter 

                                  ; Start the loop for adding the even and odd bits (step 1&2)
sumCode LDRB   r2, [r1], #1       ; load the digit then shift position
        SUB    r2, #toInt         ; Convert ASCII code
        TST    r3, #odd           ; Check if counter is odd or even (odd numbers will end with a 1)
        ADDNE  r4, r2             ; If previous check = 0, it is odd. add into r4
        ADDEQ  r5, r2             ; If previous check = 1, it is even. add into r5
        SUBS   r3, #1             ; Decrement counter
        BPL    sumCode            ; If counter is equal to 0 escape the loop
		
                                  ; Step 3
sumAll  ADD    r4, r4, LSL #1     ; Multiply the first sum by 3
        ADD    r4, r5             ; Add the first and second sum together		

                                  ; Check to see if its a multiple of 10 by repeatedly deviding by 10 as much as you can (step 4)
divSum  CMP    r4, #0             ; Is sum larger than 0 (this line helps with the case of the UPC being all 0's)
        SUBGTS r4, r4, #10        ; Repeated SUBS to keep deviding the sum by 10
        BGT    divSum             ; Go until you cannot devide anymore
		
                                  ; If multiple of 10, assign r0 = 1, if not assign r0 = 2 (step 5)
isValid CMP   r4, #0              ; Compare the MOD10 number to see if its 0
        BNE   notZero             ; If Branch not equal 0 go to notZero
        MOV   r0, #valid          ; If MOD10 number 0 put 1 in r0
        B     leave               ; Skip to leave, this exits the if 
notZero MOV   r0, #invalid        ; If MOD10 number not 0, put a 2 in r0
leave                             ; Exit for the loop

loop    B    loop
                                  ; Constants
counter EQU    11                 ; Counter for the sumCode loop (0-10, dont count 11 because it is the check)								  
toInt   EQU    48                 ; Num to convert the ASCII Code to int
odd     EQU    0x1                ; Test the least signifigant bit to see if it is odd (1) or even (0)
valid   EQU    1                  ; 1 if UPC is valid
invalid EQU    2                  ; 2 if UPC is invalid
	
                                  ; UPC Strings
UPC     DCB    "999999999999"     ; correct UPC string
UPC2    DCB    "110000000011"     ; correct UPC string
UPC3    DCB    "055633454712"     ; incorrect UPC string
UPC4    DCB    "000000000000"     ; correct UPC string
        END