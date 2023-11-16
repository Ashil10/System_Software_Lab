assume cs:code,ds:data
                data segment
                num1 dw 0A427h
                num2 dw 0FE67h
                num3 dw 6A27h
                sum dw 01h dup(?)
                carry dw 01h dup(?)
                data ends
                code segment
      start:mov ax,data
            mov ds,ax
            mov cx,0000h
            mov ax,num1
            mov bx,num2
            add ax,bx
            jnc l1
            inc cx
         l1:mov bx,num3
            add ax,bx
            jnc l2
            inc cx
         l2:mov sum,ax
             mov carry,cx
             mov ax,4c00h
            int 21h
            code ends
            end start

