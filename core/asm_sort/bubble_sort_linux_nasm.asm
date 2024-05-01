; Need to make it global so it can be accessed in another file with extern
section	.text
  global asm_bubble_sort
  global asm_bubble_sort_end
  global asm_bubble_sort_swap

; Linux 64 calling conventions
; https://en.wikipedia.org/wiki/X86_calling_conventions#System_V_AMD64_ABI
;
; The first six args are passed in registers: RDI, RSI, RDX, RCX, R8, R9
; Additional arguments are pushed on the stack (right to left)
;
; Volatile registers:
; RAX, RCX, RDX, RDI, RSI, R8, R9, R10, R11
; (callee is free to modify their values)
;
; Non-volatile registers:
; RBX, RSP, RBP, and R12, R13, R14, R15
; (must be preserved by the callee)
;
; No shadow space is provided


; Bubble Sort - Classic
;
; Args:
; rdi -> array
; rsi : array size
asm_bubble_sort:
    ; Calc the address of the last element
    dec rsi                 ; size - 1
    shl rsi, 2              ; rdx * 4 = size of the array in bytes

    mov r11, rdi            ; r11 -> the start of the array
    add r11, rsi            ; r11 -> the last element in the array

.sortloop:
    mov r8, rdi             ; r8 -> the start of the array
    mov r10b, 1             ; sorted = true // no swap occurred

    ; Reading numbers and comparing them
    mov eax, [r8]           ; Read the first number
.swaploop:
    mov edx, [r8+4]         ; Read the next number
    cmp eax, edx            ; Compare current (eax) and next (edx)
    jle .noswap             ; Go to 'noswap' if eax <= edx

    ; Swap values
    mov [r8+4], eax
    mov [r8], edx
    xor r10b, r10b          ; sorted = false // the array is unsorted

    ; After swapping eax already contains the next element
    jmp .nextelem

.noswap:
    mov eax, edx            ; Put the next element into eax
                            ; to avoid another memory access

.nextelem:
    add r8, 4               ; Move pointer to the next element

    cmp r8, r11             ; Reached the last element?
    jb  .swaploop           ; Go to 'swaploop' if r8 < r11

    ; Test whether the array is sorted
    test r10b, r10b
    jz .sortloop            ; Not yet - walk the array one more time

    ; The array is sorted - return
    ret
;asm_bubble_sort endp


; Bubble Sort - End
; First optimisation: exclude the sorted elements
; at the end of the array
;
; Args:
; rdi -> array
; rsi : array size
asm_bubble_sort_end:
    ; Calc the address of the last element
    dec rsi                 ; size - 1
    shl rsi, 2              ; rdx * 4 = size of the array in bytes

    mov r11, rdi            ; r11 -> the start of the array
    add r11, rsi            ; r11 -> the last element in the array

.sortloop:
    mov r8, rdi             ; r8 -> the start of the array
    mov r10b, 1             ; sorted = true // no swap occurred

    ; Reading numbers and comparing them
    mov eax, [r8]           ; Read the first number
.swaploop:
    mov edx, [r8+4]         ; Read the next number
    cmp eax, edx            ; Compare current (eax) and next (edx)
    jle .noswap             ; Go to 'noswap' if eax <= edx

    ; Swap values
    mov [r8+4], eax
    mov [r8], edx
    xor r10b, r10b          ; sorted = false // the array is unsorted

    ; After swapping eax already contains the next element
    jmp .nextelem

.noswap:
    mov eax, edx            ; Put the next element into eax
                            ; to avoid another memory access

.nextelem:
    add r8, 4               ; Move pointer to the next element

    cmp r8, r11             ; Reached the last element?
    jb  .swaploop           ; Go to 'swaploop' if r8 < r11

    ; Test whether the array is sorted
    test r10b, r10b
    jz .sortloop            ; Not yet - walk the array one more time

    ; The array is sorted - return
    ret
;asm_bubble_sort_end endp


; Bubble Sort - Swap
; Second optimisation: exclude all elements after
; the last swap because they're already sorted
;
; Args:
; rdi -> array
; rsi : array size
asm_bubble_sort_swap:
    ; Calc the address of the last element
    dec rsi                 ; size - 1
    shl rsi, 2              ; rdx * 4 = size of the array in bytes

    mov r11, rdi            ; r11 -> the start of the array
    add r11, rsi            ; r11 -> the last element in the array

.sortloop:
    mov r8, rdi             ; r8 -> the start of the array
    mov r10b, 1             ; sorted = true // no swap occurred

    ; Reading numbers and comparing them
    mov eax, [r8]           ; Read the first number
.swaploop:
    mov edx, [r8+4]         ; Read the next number
    cmp eax, edx            ; Compare current (eax) and next (edx)
    jle .noswap             ; Go to 'noswap' if eax <= edx

    ; Swap values
    mov [r8+4], eax
    mov [r8], edx
    xor r10b, r10b          ; sorted = false // the array is unsorted

    ; After swapping eax already contains the next element
    jmp .nextelem

.noswap:
    mov eax, edx            ; Put the next element into eax
                            ; to avoid another memory access

.nextelem:
    add r8, 4               ; Move pointer to the next element

    cmp r8, r11             ; Reached the last element?
    jb  .swaploop           ; Go to 'swaploop' if r8 < r11

    ; Test whether the array is sorted
    test r10b, r10b
    jz .sortloop            ; Not yet - walk the array one more time

    ; The array is sorted - return
    ret
;asm_bubble_sort_swap endp
