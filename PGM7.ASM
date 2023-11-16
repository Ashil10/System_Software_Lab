assume cs:code,ds:data
data segment
arr db 99h,7ah,0b1h,33h,23h,52h
len dw $-arr
data ends
code segment
start:mov ax,data
mov ds,ax
lea si,arr
mov ax,len
l1:mov di,si
inc di
mov cx,ax
dec cx
l2:mov bh,arr[si]
mov bl,arr[di]
cmp bh,bl
jc l3
mov arr[si],bl
mov arr[di],bh
l3:inc di
loop l2
inc si
dec ax
cmp ax,0001h
jnz l1
mov ah,4ch
int 21h
code ends
end start

