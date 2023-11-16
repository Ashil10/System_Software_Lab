assume cs:code,ds:data
data segment
div1 dw 7004h
div2 dw 01c1h
dvr dw 020ch
quo1 dw 01h dup(?)
quo2 dw 01h dup(?)
data ends
code segment
start:mov ax,data
mov ds,ax
mov ax,div1
mov dx,div2
mov bx,dvr
div bx
mov quo1,ax
mov quo2,dx
mov ax,4c00h
int 21h
code ends
end start

