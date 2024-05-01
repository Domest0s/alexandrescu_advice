; Need to make it global so it can be accessed in another file with extern
section	.text
  global asm_quick_sort_ludvig
  global asm_quick_sort_alex

; reference:
; input args order rdi, rsi, rdx, rcx, r8, r9 then the stack in reverse order.


; TODO Implement QuickSort in Assembler

; Input Arguments:
; rdi : array pointer
; rsi : number of elemetns
asm_quick_sort_ludvig:

 ; base condition - if length is 0, 1?
 ; if rsi > 1 then jump to more_than_1
 cmp rsi, 1
 ja .more_than_1
 ret
.more_than_1:

 ; base condition - if length is 2?
 cmp rsi, 2
 ja .more_than_2
 ; swap the elements if not sorted
 mov eax, [rdi]
 mov ebx, [rdi+4]
 cmp eax, ebx
 jle .finish
 mov [rdi], ebx
 mov [rdi+4], eax
 jmp .finish
.more_than_2:

mov r10, 0
mov r11, rsi
dec r11
call partition_ludvig  ; partition(A, 0, length-1)
; Now rax is pivot index


 ; Assuming length is >= 3:
 ; We will call partition to get a pivot and elements moved around
 ; and then call ourselves recursively on the sides
push rdi
push rsi
push rax

 mov rsi, rax
 call asm_quick_sort_ludvig ; asm_quick_sort(rdi, rax)

pop rax
pop rsi
pop rdi

push rdi
push rsi
push rax

 sub rsi, rax
 shl rax, 2
 add rdi, rax
 call asm_quick_sort_ludvig ; asm_quick_sort(rdi+rax, hi-rax)

pop rax
pop rsi
pop rdi

.finish:
ret


; Partition(array, low, high)
; picks a pivot elemement,
; moves elements so that everything left of pivot is less, everything above is larger or eq,
; and returns index to pivot.
; This implements the Lomuto partition scheme
; https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme
; parameters:
; r10: low index (inclusive)  AKA 'lo'
; r11: high index (inclusive) AKA 'hi'
; return: rax
partition_ludvig:
 ; First, pick an element as the pivot.
 ; We pick the last element and read its value
 mov r12d, [rdi+r11*4]  ; r12d is pivot value

 ; rbx is i, an index into the array
 mov rbx, r10
 dec rbx                ; i = lo-1

; rcx is j, an index into the array
 mov rcx, r10           ; j = lo

 ; Looping j(rcx) from lo to hi-1
 dec rcx                ; for the loop step
.loop_start:
 inc rcx                ; loop step

; Current element in the array at j
 mov eax, [rdi+rcx*4]   ; read element j into eax
 cmp eax, r12d          ; compare element j with pivot
 jge .loop_end          ; if A[j] < pivot (else continue)

 ; i+1 is unknown whether it's smaller,
 ; But the current element is known to be less than pivot,
 ; So we swap them and can then make i larger
 inc rbx                ; increment i
 mov edx, [rdi+rbx*4]   ; swap elements i and j
 mov [rdi+rbx*4], eax
 mov [rdi+rcx*4], edx

.loop_end:
 cmp rcx, r11
 jb .loop_start

; swap the pivot itself
 inc rbx
 mov eax, [rdi+rbx*4]
 mov [rdi+rbx*4], r12d
 mov [rdi+r11*4], eax
 mov rax, rbx
 ret


;------------------------------------------------


; rdi -> array, rsi : array size
asm_quick_sort_alex:
    cmp     rsi, 2
    ; if rsi < 2 -> return
    jb      .exit_qs
    ; if rsi == 2
    je      .sort_2elements

    dec     rsi             ; size - 1
    xor     r8, r8
    ; r8 = low and rsi = high
    jmp quick_sort_alex

.sort_2elements:
    mov     eax, [rdi]
    mov     edx, [rdi+4]
    cmp     eax, edx
    jle     .exit_qs

    ; Swap the elements
    mov     [rdi+4], eax
    mov     [rdi], edx

.exit_qs:
    ret
;asm_quick_sort endp


; Implements Lomuto partitioning scheme:
; https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme
; It chooses the last element of the range as the pivot.

; rdi -> array,
; r8  : low  (inclusive)
; rsi : high (inclusive)
; returns the index in rax
partition_Lomuto_alex:
    mov     r9d, [rdi+rsi*4]    ; pivot
    mov     r10, r8             ; i = (low - 1)
    dec     r10

    mov     rdx, r8             ; j = low
.loop:
    mov     eax, [rdi+rdx*4]    ; eax = arr[j]
    cmp     eax, r9d
    jge     .to_next

    inc     r10                 ; i++
    mov     ecx, [rdi+r10*4]
    mov     [rdi+r10*4], eax
    mov     [rdi+rdx*4], ecx

.to_next:
    inc     rdx
    cmp     rdx, rsi
    jb      .loop

    inc     r10
    mov     eax, [rdi+r10*4]
    mov     ecx, [rdi+rsi*4]
    mov     [rdi+rsi*4], eax
    mov     [rdi+r10*4], ecx

    mov     rax, r10

    ret
; partition_Lomuto endp


; rdi -> array,
; r8  : low  (inclusive)
; rsi : high (inclusive)
quick_sort_alex:
    cmp     rsi, r8
    ; if rsi >= r8
    jbe     .exit

    call    partition_Lomuto_alex
    cmp     rax, 1
    jb      .right_half

    ; Left half
    push    rsi
    push    r8
    push    rax
    dec     rax
    mov     rsi, rax
    call    quick_sort_alex
    pop     rax
    pop     r8
    pop     rsi

.right_half:
    inc     rax
    mov     r8, rax
    call    quick_sort_alex

.exit:
    ret
; quick_sort endp
