; ask MASM to respect casing (by default MASM is case insensitive)
        option  casemap:none

            .const

            .data

            .code

public asm_quick_sort_ludvig
public asm_quick_sort_alex

asm_quick_sort_ludvig proc
    ; TODO to be implemented
    ret
asm_quick_sort_ludvig endp


;------------------------------------------------


; Quicksort in Assembly
;
; Args:
; rcx -> array,
; rdx : array size
asm_quick_sort_alex proc
    cmp     rdx, 2
    ; if rdx < 2 -> return
    jb      exit_qs
    ; if rdx == 2
    je      sort_2elements

    dec     rdx             ; size - 1
    xor     r8, r8
    push    rdi
    push    rsi
    mov     rdi, rcx
    mov     rsi, rdx
    ; rdi -> array
    ; r8  : low  (inclusive)
    ; rsi : high (inclusive)
    call    quick_sort_alex
    pop     rsi
    pop     rdi
    ret

sort_2elements:
    mov     eax, [rcx]
    mov     edx, [rcx+4]
    cmp     eax, edx
    jle     exit_qs

    ; Swap the elements
    mov     [rcx+4], eax
    mov     [rcx], edx

exit_qs:
    ret
asm_quick_sort_alex endp


; Implements Lomuto partitioning scheme:
; https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme
; It chooses the last element of the range as the pivot.

; rdi -> array,
; r8  : low  (inclusive)
; rsi : high (inclusive)
; returns the index in rax
partition_Lomuto_alex proc
    mov     r9d, [rdi+rsi*4]    ; pivot
    lea     r10, [r8-1]         ; i = (low - 1)

    mov     rdx, r8             ; j = low
looparray:
    mov     eax, [rdi+rdx*4]    ; eax = arr[j]
    cmp     eax, r9d
    jge     to_next

    inc     r10                 ; i++
    mov     ecx, [rdi+r10*4]
    mov     [rdi+r10*4], eax
    mov     [rdi+rdx*4], ecx

to_next:
    inc     rdx
    cmp     rdx, rsi
    jb      looparray

    inc     r10
    mov     eax, [rdi+r10*4]
    mov     ecx, [rdi+rsi*4]
    mov     [rdi+rsi*4], eax
    mov     [rdi+r10*4], ecx

    mov     rax, r10

    ret
partition_Lomuto_alex endp


; rdi -> array,
; r8  : low  (inclusive)
; rsi : high (inclusive)
quick_sort_alex proc
    cmp     rsi, r8
    ; if rsi >= r8
    jbe     exit

    call    partition_Lomuto_alex
    cmp     rax, 1
    jb      right_half

    ; Left half
    push    rsi
    push    rax
    dec     rax
    mov     rsi, rax
    call    quick_sort_alex
    pop     rax
    pop     rsi

right_half:
    inc     rax
    mov     r8, rax
    jmp     quick_sort_alex

exit:
    ret
quick_sort_alex endp


end ; end of assembly file
