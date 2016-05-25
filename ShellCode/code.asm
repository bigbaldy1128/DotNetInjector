.data
.code
PUBLIC get_peb
get_peb PROC
mov rax,qword ptr gs:[60h]
ret
get_peb ENDP
END