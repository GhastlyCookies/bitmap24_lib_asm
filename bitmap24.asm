.model flat,stdcall
OPTION proc:public

INCLUDE bitmap24.inc
;//*******************************************************************************]
;//                                Prototype tab                                  ]
;//_______________________________________________________________________________]
ExitProcess proto, dwExitCode:dword
;//_______________________________________________________________________________]

;//*******************************************************************************]
;//                           Symbolic constants tab                              ]
;//_______________________________________________________________________________]
a4 EQU <ALIGN 4>
;//_______________________________________________________________________________]


.data
	buffarr BYTE 24 DUP(?)

.code

readbitmap24 PROC USES ebx ecx edx edi, hwnd:HANDLE, pFH:PTR bitmap24_FILEHEAD, pIH:PTR bitmap24_FILEINFOHEAD, ppa:PTR pixel24
LOCAL img_len:DWORD, pix_offset:DWORD

	invoke setfilepointer, hwnd, 0, 0, FILE_BEGIN
	INVOKE readfile, hwnd, ADDR buffarr, 14, 0, 0
	mov bx, WORD PTR[buffarr]
	cmp bx, 4D42h
	je conti1
	mov eax, 0FFFFFFFFh
	jmp exi
conti1:
	mov ecx, DWORD PTR[buffarr + 2]
	mov edx, DWORD PTR[buffarr + 10]
	mov [pix_offset], edx
	mov edi, [pFH]
	cmp edi,0
	jz skip1
	mov (bitmap24_FILEHEAD PTR[edi]).ftype, bx
	mov (bitmap24_FILEHEAD PTR[edi]).fsize, ecx
	mov (bitmap24_FILEHEAD PTR[edi]).pixoffset, edx
skip1:
	INVOKE readfile, hwnd, ADDR buffarr, 24, 0, 0
	mov ax, WORD PTR[buffarr + 14]
	cmp ax, 24
	je conti2
	mov eax, 0FFFFFFFFh
	jmp exi
conti2:
	mov eax, DWORD PTR[buffarr + 20]
	mov [img_len], eax
	mov edi, [pIH]
	cmp edi, 0
	jz skip2
	INVOKE setfilepointer, hwnd, 14, 0, FILE_BEGIN
	INVOKE readfile, hwnd, edi, 124, 0, 0
skip2:
	mov edi, [ppa]
	cmp edi, 0
	jz exi
	invoke setfilepointer, hwnd, pix_offset, 0, FILE_BEGIN
	mov eax, [img_len]
	INVOKE readfile, hwnd, edi, eax, 0, 0
exi:
	ret
readbitmap24 ENDP

writebitmap PROC , hwnd : HANDLE, pFH : PTR bitmap24_FILEHEAD, pIH : PTR bitmap24_FILEINFOHEAD, ppa : PTR pixel24, pixo:DWORD, wsize:DWORD
	invoke setfilepointer, hwnd, 0, 0, FILE_BEGIN
	mov edi, [pFH]
	cmp edi, 0
	jz skip1
	invoke writefile, hwnd, edi, 14, 0, 0
skip1:
	mov edi, [pIH]
	cmp edi, 0
	jz skip2
	invoke writefile, hwnd, edi, 124, 0, 0
skip2:
	mov edi, [ppa]
	cmp edi, 0
	jz exi
	invoke setfilepointer, hwnd, [pixo], 0, FILE_BEGIN
	invoke writefile, hwnd, edi, [wsize], 0, 0
exi:
	ret
writebitmap ENDP

END