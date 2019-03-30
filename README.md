# Ghastlys Bitmap Image Reader/Writer
This library contains functions to read/write information from/to a 16-bit/24-bit/32-bit .bmp image (with std call convention, standard ADTs)

## Dependencies
  1. Windows API
    (tested on Windows 10 platform SDK 10.0.17763.0)

## Installation
  1. Dowload or clone to a new directory.
  
  2. Add directory path to your projects properties.
  
  3. Add `bitmaplibrary.lib` to your projects dependencies list.
  
  4. Make sure to include `bitmap.inc` file in calling program. (this file contains asm function prototypes and standard structures/ADTs)

## Overview
  Contains standard bitmap ADTs/structures with which one can retain all of the bitmap file attributes. This library supports the following:
  1. BITMAPV5INFOHEAD structure.
  2. pixel depth of 16bpp/Argb1555/GrayScale/Rgb555/Rgb565 via `pixel16 STRUCT`.
  3. pixel depth of 24bppRgb via `pixel24 STRUCT`.
  4. pixel depth of 32bpp/Argb/PArgb/Rgb via `pixel32 STRUCT`.
  ### NOTE: Read the bitmap.inc file for structre definition references.
  
  Nevertheless you can still retain ADTs from all pixel formats in bitmap. For refrence structure of the bitmap file, below is a quoted from source:https://en.wikipedia.org/wiki/BMP_file_format
  
  ![alt text](https://upload.wikimedia.org/wikipedia/commons/c/c4/BMPfileFormat.png)
  
## functions

### readbitmap24
  ```
  readbitmapi PROTO, 
     hwnd:HANDLE,        ; handle to the file 
     pFH:PTR bitmap24_FILEHEAD,         ; pointer to bitmap header ADT  
     pIH:PTR bitmap24_FILEINFOHEAD,          ; pointer to bitmapv5 info header ADT 
     ppa:PTR pixel24          ; pointer to pixel ADT
  ```
     
   #### hwnd
handle to file returned by createfile procedure, must have read access.
   
   #### pFH
pointer to `FILEHEAD` structure, this parameter can be NULL.
    
   #### pIH
pointer to `FILEINFOHEAD(BITMAPV5)` structure, this parameter can be NULL.
    
   #### ppa
pointer to `pixel24` structure array, this parameter can be NULL.

   ### returns
If invalid file header is found OR bits per pixel is less than 16 then return value is 0FFFFFFFFh(specifically in eax).

#### NOTE: You can read/write images above 32bpp but you have to explicitly define those structures yourself.

### writebitmap
  ```
  writebitmapi PROTO, 
     hwnd:HANDLE,      ; handle to the file 
     pFH:PTR bitmap24_FILEHEAD,       ; pointer to bitmap header ADT 
     pIH:PTR bitmap24_FILEINFOHEAD,        ; pointer to bitmapv5 info header ADT         
     ppa:PTR pixel24,       ; pointer to pixel ADT        
     pixo:DWORD,         ; explicit pixel offset 
     wsize:DWORD         ; explicit image size
  ```
     
   #### hwnd
handle to file returned by createfile procedure, must have read access.
   
   #### pFH
pointer to `FILEHEAD` structure, this parameter can be NULL.
    
   #### pIH
pointer to `FILEINFOHEAD(BITMAPV5)` structure, this parameter can be NULL.
    
   #### ppa
pointer to `pixel24` structure array, this parameter can be NULL.
    
   #### pixo
explicit offset to pixel array.
    
   #### wsize
explicit pixel array write size.

   ### returns
nothing.

## SAMPLE CALL
The following is a sample call (32 bit environment) from the main function where an image is read and then a "negative transform"(function not included in this library) is applied to it and writen to a newly created bitmap file.  
```
;// open a bitmap image for reading, allocate necessary space on heap to read the data and read the data from the image
	invoke getprocessheap
	mov [heaphandle], eax
	invoke createfile, ADDR filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0
	mov [filehandle], eax
	invoke readbitmapi, [filehandle], ADDR fh, ADDR fih, 0
	invoke heapalloc, [heaphandle], HEAP_ZERO_MEMORY, fih.img_size
	mov [p_img_dat], eax
	invoke readbitmapi, [filehandle], 0, 0, [p_img_dat]
	invoke closehandle, [filehandle]

;// apply a transform on the image data
	mov eax,fih.img_size
	mov edx,0
	mov ebx,6
	div ebx
	invoke negtransform_24, [p_img_dat], eax
	
;// create a newfile and write bitmap headers and image data
	invoke createfile, ADDR newfilename, GENERIC_WRITE, DO_NOT_SHARE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
	mov filehandle, eax
	invoke writebitmapi, [filehandle], ADDR fh, ADDR fih, [p_img_dat], fh.pixoffset, fih.img_size
	invoke heapfree, [heaphandle], 0, [p_img_dat]
	invoke closehandle, [filehandle]
  
```
### SAMPLE OUTPUT

  ![alt text](https://i.imgur.com/NCK14wN.png)
  
  (i do not own rights to the orignal image)
