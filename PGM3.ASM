assume cs:code,ds:data
                data segment
                num1 dw 0abcfh
                num2 dw 00c4h            
                prol dw 01h dup(?)
                proh dw 01h dup(?)
                data ends
                code segment
      start:mov ax,data
            mov ds,ax
            mov cx,0000h
            mov ax,num1
            mov bx,num2
            mul bx
           mov prol,ax
           mov proh,dx
             mov ax,4c00h
            int 21h
            code ends
            end start
