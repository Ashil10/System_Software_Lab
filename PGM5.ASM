assume cs:code,ds:data
data segment
arr dw 25h,43h,0aah,12h,10h
len dw $-arr
lar dw 1 dup(?)
sma dw 1 dup(?)
data ends
code segment
start:mov ax,data
mov ds,ax
lea si,arr
mov cx,len
shr cx,1
mov ax,0000h
mov bx,arr[si]
l1:cmp ax,arr[si]
jnc l2
mov ax,arr[si]
l2:cmp bx,arr[si]
jc l3
mov bx,arr[si]
l3:inc si
inc si
loop l1
mov lar,ax
mov sma,bx
mov ah,4ch
int 21h
code ends
end start

