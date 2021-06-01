
DATA SEGMENT
M1 DB 10,13,"HOW MANY NUMBERS DO YOU WANT TO ADD?$"
M2 DB 10,13,"ENTER THE NUMBERS->$"
M3 DB 10,13,"RESULT OF ADDITION IS-> $"
M4 DB 10,13,"INVALID CHARACTER! PRESS A KEY TO EXIT.$"
NO DB ?
NUMBERS DB 10 DUP(0)
RESULT DW 0
DATA ENDS
CODE SEGMENT
ASSUME CS:CODE,DS:DATA
START:
MOV AX,DATA
MOV DS,AX
MOV AH,09H
LEA DX,M1
INT 21H
CALL ACCEPT
MOV NO,BL
MOV AH,09H
LEA DX,M2
INT 21H

LEA SI,NUMBERS
MOV BH,NO

L3:CALL ACCEPT
MOV [SI],BL
INC SI
MOV AH,02H
MOV DL,' '
INT 21H
DEC BH
JNZ L3

LEA SI,NUMBERS
MOV DL,NO

BACK: MOV AL,[SI]
MOV AH,00
ADD RESULT,AX
INC SI
DEC DL
JNZ BACK

MOV AH,09H
LEA DX,M3
INT 21H
MOV AX,RESULT
MOV CL,04H
SHR AH,CL
ADD AH,30H
CMP AH,39H
JLE L5
ADD AH,07H

L5:MOV DL,AH
MOV AH,02H
INT 21H
MOV AX,RESULT
AND AH,0FH
ADD AH,30H
CMP AH,39H
JLE L6
ADD AH,07H

L6:MOV DL,AH
MOV AH,02H
INT 21H


MOV AX,RESULT
MOV CL,04H
SHR AL,CL
ADD AL,30H
CMP AL,39H
JLE L7
ADD AL,07H

L7:MOV DL,AL
MOV AH,02H
INT 21H
MOV AX,RESULT
AND AL,0FH
ADD AL,30H
CMP AL,39H
JLE L8
ADD AL,07H

L8:MOV DL,AL
MOV AH,02H
INT 21H

MOV AH,4CH
INT 21H
ACCEPT PROC
MOV AH,01H
INT 21H
CALL VALIDITY
CMP AL,39H
JLE L1
SUB AL,07H

L1:SUB AL,30H
MOV CL,04H
SHL AL,CL
MOV BL,AL
MOV AH,01H
INT 21H
CALL VALIDITY
CMP AL,39H
JLE L2

L2: SUB AL,30H
ADD BL,AL
RET
ACCEPT ENDP

VALIDITY PROC
CMP AL,30H
JL ERROR
CMP AL,46H
JG ERROR
CMP AL,3AH
JL PASS
CMP AL,40H
JG PASS

ERROR: MOV AH,09H
LEA DX,M4
INT 21H
MOV AH,4CH
INT 21H
RET
PASS:RET
VALIDITY ENDP
CODE ENDS
END START