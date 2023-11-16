assume cs:code,ds:data
data segment
num1 db 04h
num2 db 03h
num3 db 02h
sum db 01h dup(?)
carry db 01h dup(?)
data ends
code segment
start:mov ax,data
mov ds,ax
mov cl,00
mov al,num1
mov bl,num2
add al,bl
jnc l1
inc cl
l1:mov bl,num3
add al,bl
jnc l2
inc cl
l2:mov sum,al
mov carry,cl
mov ax,4c00h
int 21h
code ends
end start
