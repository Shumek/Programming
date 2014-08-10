SG segment
org 100h
start:

mov ax,a
add ax,d
mov bx,ax
mov ax,a
add ax,b
sub ax,d
sub bx,ax
sub bx,a
mov r,bx

retn
a dw 2
b dw 9
d dw 1
r dw 0
SG ends
end start