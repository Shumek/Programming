SG segment
org 100h
start:
mov al,10h
call SetVM
mov al,1
mov bl,2
call CreateFigure
mov bh,1
mov b,1
mov al,2
mov bl,4
call CreateFigure
PageChange:
call HitKey
cmp ah,30h
jz Page1
mov ah,31h
cmp ah,31h
jz Page2
jmp PageChange
Page1:
mov al,0
call SetPage
jmp PageChange
Page2:
mov al,1
call SetPage
retn

SetPage:
mov ah,5
int 10h
ret
SetVM:
mov ah,0
int 10h
ret
SetBG:
mov ah,0Bh
int 10h
ret
SetPixel:
mov ah,0Ch
inc cx
int 10h
ret
HitKey:
mov ah,1
int 16h
ret
CreateFigure:
mov cx,2
mov dx,2
Draw:
mov a,bl
mov cx,2
cmp b,0
jnz LineDraw
dec bl
LineDraw:
call SetPixel
dec a
jnz LineDraw
inc dx
cmp dx,4
jnz Draw
ret
a db 20
b db 0
SG ends
end start