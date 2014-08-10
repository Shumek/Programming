SG segment
org 100h
start:
call setvideomode
call setpage
call message

call getpos
lea si,a

inputcycle1:
call input
cmp ah,1Ch
jz br
call setcursor
call print
mov [si],al
inc si
inc capacity
jmp inputcycle1
;mov [si],0
br:
call setcursor

mov ax,0
lea si,a
mov dx,capacity
transdig:
call transdigit
inc si
dec dx
cmp dx,-1
jnz transdig

digitsadd:
fadd
dec capacity
cmp capacity,-1
jnz digitsadd

;call inputsqrt
call mathoper
fist dig
lea si,dig
inc si
mov ah,[si]
dec si
mov al,[si]
call print
push ax

call getpos
inc dh
lea si,b

inputcycle2:
call input
cmp ah,1Ch
jz br1
call setcursor
call print
mov [si],al
inc si
inc capacity
jmp inputcycle2
;mov [si],0
br1:
call setcursor

mov ax,0
lea si,b
mov dx,capacity
trandig:
call transdigit
inc si
dec dx
cmp dx,-1
jnz trandig

digadd:
fadd
dec capacity
cmp capacity,-1
jnz digadd

call inputsqrt
call mathoper
fist dig
lea si,dig
inc si
mov ah,[si]
dec si
mov al,[si]
call print
push ax
pop ax
pop bx
retn

setvideomode:
mov ah,07h
mov al,0h
int 10h
ret

getpos:
mov ah,3
int 10h
ret

setcursor:
mov ah,2
mov bh,0
inc dl
int 10h
ret

print:
mov ah,9
mov bh,0
mov cx,1
mov bl,21
int 10h
ret

setpage:
mov ah,5
mov al,0
int 10h
ret


input:
mov ah,0
int 16h
ret

message:
call getpos
lea si,welcome

cycle:

mov al,[si]
call print
call setcursor
inc si
dec iter
jnz cycle
ret

inputoper:
call getpos
call input
cmp al,94
jz br2
call print
call setcursor
jmp inputsqrt
br2:
call setcursor
ret

transdigit:
mov al,[si]
sub ax,30
mov dig,ax
fild dig
mov cx,capacity
cmp cx,0
jz break 
cap:
fild pos
dec cx
jnz cap
mov cx,capacity
multi:
fmul
dec cx
jnz multi
break:

ret

mathoper:
fsqrt
ret

a dw 0
b dw 0
welcome db 'Welcome!Enter your numbers:'
pos dw 10
iter dw 27
capacity dw -1
dig dw 0
 
SG ends
end start