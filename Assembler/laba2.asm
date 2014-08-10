SG segment
org 100h
start:


mov ax,a
add ax,3
mov bx,i
cycle:
jnp  regpf1
	inc rp

regpf1:
	add ax,3
jnp  regpf2
	inc rp
regpf2:

cmp ax,p
jns regaf
	inc ra
regaf:

jnp  regpf3
	inc rp
regpf3:

dec bx
jnz cycle
	inc rc
jnp  regpf4
	inc rp
regpf4:

	mov dx,rp
	mov si,rc
	mov di,ra
retn
	a dw 47
	b dw 87
	i dw 28
	p dw 255 
	rp dw 0
	rc dw 0
	ra dw 0
SG ends
end start