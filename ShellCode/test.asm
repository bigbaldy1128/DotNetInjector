org 100h
mov ax,cs
mov ds,ax

mov ax,00300h
mov bx,000ch
int 10h

mov ax,msg
mov cx,msglen
mov bp, ax ; ES:BP = 串地址
mov ax, 01301h ; AH = 13, AL = 01h
mov bx, 000ch ; 页号为0(BH = 0) 
int 10h ; 10h 号中断

jmp $  ;让程序停在这里，否则一个窗口一闪程序就结束了

msg:  db  'Hello, world',0
msglen:  equ $-msg