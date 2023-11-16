assume cs:code,ds:data
data segment
arr db 99h,12h,56h
len dw $-arr
ev dw 1 dup(?)
data ends
code segment
start:mov ax,data
mov ds,ax
lea si,arr
mov cx,len
mov bx,0000h
l1:mov al,arr[si]
and al,01h
cmp al,00h
jnz l2
mov ah,00h
mov al,arr[si]
add bx,ax
l2:inc si
loop l1
mov ev,bx
mov ah,4ch
int 21h
code ends
end start

