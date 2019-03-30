;-----------------------------------
; Standard symbolic constants
;-----------------------------------
HANDLE TEXTEQU <DWORD>
CreateFile EQU <CreateFileA>

HEAP_ZERO_MEMORY			  = 00000008h
NULL                            = 0

DO_NOT_SHARE                    = 0
FILE_SHARE_READ                 = 1
FILE_SHARE_WRITE                = 2
FILE_SHARE_DELETE               = 4

FILE_ATTRIBUTE_READONLY         = 1
FILE_ATTRIBUTE_HIDDEN           = 2
FILE_ATTRIBUTE_SYSTEM           = 4
FILE_ATTRIBUTE_DIRECTORY        = 10h
FILE_ATTRIBUTE_ARCHIVE          = 20h
FILE_ATTRIBUTE_DEVICE           = 40h
FILE_ATTRIBUTE_NORMAL           = 80h
FILE_ATTRIBUTE_TEMPORARY        = 100h
FILE_ATTRIBUTE_SPARSE_FILE      = 200h
FILE_ATTRIBUTE_REPARSE_POINT    = 400h
FILE_ATTRIBUTE_COMPRESSED       = 800h
FILE_ATTRIBUTE_OFFLINE          =    1000h
FILE_ATTRIBUTE_NOT_CONTENT_INDEXED = 2000h
FILE_ATTRIBUTE_ENCRYPTED           = 4000h

FILE_READ_DATA = 1
FILE_WRITE_DATA = 2
FILE_APPEND_DATA = 4
FILE_DELETE_CHILD = 40h

CREATE_NEW         = 1
CREATE_ALWAYS      = 2
OPEN_EXISTING      = 3
OPEN_ALWAYS        = 4
TRUNCATE_EXISTING  = 5

FILE_BEGIN         =  0
FILE_CURRENT       =  1
FILE_END           =  2

INVALID_HANDLE_VALUE = -1

GENERIC_READ     = 80000000h
GENERIC_WRITE    = 40000000h
GENERIC_EXECUTE  = 20000000h
GENERIC_ALL      = 10000000h

;-----------------------------------
; Standard structures
;-----------------------------------

bitmap24_FILEHEAD STRUCT 
     ftype WORD ?
     fsize DWORD ?
     reserved DWORD 0
     pixoffset DWORD ?
bitmap24_FILEHEAD ENDS 

bitmap24_FILEINFOHEAD STRUCT
     ihsize DWORD ?
     img_width DWORD ?
     img_height DWORD ?
     planesbits DWORD ?
     compression DWORD ?
     img_size DWORD ?
     x_ppm DWORD ?
     y_ppm DWORD ?
     cLUT DWORD ?
     impcolor DWORD ?
     rbm DWORD ?
     gbm DWORD ?
     bbm DWORD ?
     abm DWORD ?
     cst DWORD ?
     cse BYTE 36 DUP(?)
     grc DWORD ?
     ggc DWORD ?
     gbc DWORD ?
     intent DWORD ?
     ICC_dat DWORD ?
     ICC_size DWORD ?
     reserved DWORD 0
bitmap24_FILEINFOHEAD ENDS

pixel16 STRUCT
	BGRA WORD ?
pixel16 ENDS

pixel24 STRUCT
     B BYTE ?
     G BYTE ?
     R BYTE ?
pixel24 ENDS

pixel32 STRUCT
	B BYTE ?
	G BYTE ?
	R BYTE ?
	A BYTE ?
pixel32 ENDS

;-----------------------------------
; Prototype table
;-----------------------------------

GetProcessHeap PROTO

HeapFree PROTO,
	hHeap:HANDLE,		; handle to heap with memory block
	dwFlags : DWORD,		; heap free options
	lpMem : DWORD		; pointer to block to be freed


HeapDestroy PROTO,
	hHeap:HANDLE		; heap handle

HeapCreate PROTO,
	flOptions:DWORD,		; heap allocation options
	dwInitialSize : DWORD,		; initial heap size, in bytes
	dwMaximumSize : DWORD		; maximum heap size, in bytes

HeapAlloc PROTO,
	hHeap:HANDLE,		; handle to private heap block
	dwFlags : DWORD,		; heap allocation control flags
	dwBytes : DWORD		; number of bytes to allocate

readbitmapi PROTO, 
     hwnd:HANDLE,		; handle to the file 
     pFH:PTR bitmap24_FILEHEAD,         ; pointer to bitmap header ADT  
     pIH:PTR bitmap24_FILEINFOHEAD,          ; pointer to bitmapv5 info header ADT 
     ppa:PTR pixel24          ; pointer to pixel ADT

writebitmapi PROTO, 
     hwnd:HANDLE,      ; handle to the file 
     pFH:PTR bitmap24_FILEHEAD,       ; pointer to bitmap header ADT 
     pIH:PTR bitmap24_FILEINFOHEAD,        ; pointer to bitmapv5 info header ADT         
     ppa:PTR pixel24,       ; pointer to pixel ADT        
     pixo:DWORD,         ; explicit pixel offset 
     wsize:DWORD         ; explicit image size

CloseHandle PROTO,		; close file handle
	hObject:DWORD

CreateFile PROTO,		; create new file
	lpFilename:PTR BYTE,		; ptr to filename
	dwDesiredAccess:DWORD,		; access mode
	dwShareMode:DWORD,		; share mode
	lpSecurityAttributes:DWORD,  		; pointer to security attributes
	dwCreationDisposition:DWORD,		; file creation options
	dwFlagsAndAttributes:DWORD,		; file attributes
	hTemplateFile:DWORD		; handle to template file

ReadFile PROTO,		; read buffer from input file
	hFile:HANDLE,		; input handle
	lpBuffer:PTR BYTE,		; ptr to buffer
	nNumberOfBytesToRead:DWORD,		; num bytes to read
	lpNumberOfBytesRead:PTR DWORD,	; bytes actually read
	lpOverlapped:PTR DWORD		; ptr to asynchronous info

WriteFile PROTO,		; write buffer to output file
	hFile:HANDLE,		; output handle
	lpBuffer:PTR BYTE,		; pointer to buffer
	nNumberOfBytesToWrite:DWORD,		; size of buffer
	lpNumberOfBytesWritten:PTR DWORD,	; num bytes written
	lpOverlapped:PTR DWORD		; ptr to asynchronous info

SetFilePointer PROTO,		; set the file pointer position
	hFile:HANDLE,		; file handle
	lDistanceToMove:SDWORD,		; bytes to move pointer
	lpDistanceToMoveHigh:PTR SDWORD,	; ptr to bytes to move, high
	dwMoveMethod:DWORD		; starting point

