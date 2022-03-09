R12      EQU   12
R13      EQU   13
R14      EQU   14
R15      EQU   15

*        R12   BASE REGISTER
*        R13   SAVE AREA
*        R14   RETURN ADDRESS
*        R15   ENTRY POINT / RC ON EXIT

TEST#1   CSECT
         STM   R14,R12,12(R13)
         BASR  R12,0
         USING *,R12
         ST    R13,SAVE+4
         LA    R13,SAVE
         L     R13,SAVE+4
*
         WTO   'HELLO'
*
         LM    R14,R12,12(R13)
         LA    R15,0
         BR    R14
SAVE     DS    18F
         LTORG
         END   TEST#1

