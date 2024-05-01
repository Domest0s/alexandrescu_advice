; ask MASM to respect casing (by default MASM is case insensitive)
        option  casemap:none

            .const

            .data

            .code

; Win64 calling conventions
; https://en.wikipedia.org/wiki/X86_calling_conventions#Microsoft_x64_calling_convention
;
; The first four args are passed in registers: RCX, RDX, R8, R9
; Additional arguments are pushed on the stack (right to left)
;
; https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170#callercallee-saved-registers
; Volatile registers: RAX, RCX, RDX, R8, R9, R10, R11
; (callee is free to modify their values)
;
; Non-volatile registers:
; RBX, RBP, RDI, RSI, RSP, R12, R13, R14, and R15
; (must be preserved by the callee)
;
; The caller must allocate 32 bytes of shadow space before calling a function


; Bubble Sort - Classic
;
; void asm_bubble_sort(int32_t* array, unit64 array_size)
;                               rcx           rdx
public asm_bubble_sort
asm_bubble_sort proc
    ; Calc the address of the last element
    dec rdx                 ; size - 1
    shl rdx, 2              ; rdx * 4 = size of the array in bytes

    mov r11, rcx            ; r11 -> the start of the array
    add r11, rdx            ; r11 -> the last element in the array

sortloop:
    mov r8, rcx             ; r8 -> the start of the array
    mov r10b, 1             ; sorted = true // no swap occurred

    ; Reading numbers and comparing them
    mov eax, [r8]           ; Read the first number
swaploop:
    mov edx, [r8+4]         ; Read the next number
    cmp eax, edx            ; Compare current (eax) and next (edx)
    jle noswap              ; Go to 'noswap' if eax <= edx

    ; Swap values
    mov [r8+4], eax
    mov [r8], edx
    xor r10b, r10b          ; sorted = false // the array is unsorted

    ; After swapping eax already contains the next element
    jmp nextelem

noswap:
    mov eax, edx            ; Put the next element into eax
                            ; to avoid another memory access

nextelem:
    add r8, 4               ; Move pointer to the next element

    cmp r8, r11             ; Reached the last element?
    jb  swaploop            ; Go to 'swaploop' if r8 < r11

    ; Test whether the array is sorted
    test r10b, r10b
    jz sortloop             ; Not yet - walk the array one more time

    ; The array is sorted - return
    ret
asm_bubble_sort endp


; Bubble Sort - Classic - loop whole array untill things get sorted
;
; void asm_bubble_sort_by_ivan(int32_t* array, unit64 array_size)
;                                    rcx           rdx
public asm_bubble_sort_by_ivan
asm_bubble_sort_by_ivan proc
  ; if size is 0 or 1, exit without sorting
  cmp rdx, 1
  ja do_sort  ; jump if Above
  ret

  do_sort:
  lea rdx, [rcx + 4 * rdx - 4]   ; tail = array[size - 1]
  
  big_loop:
    mov r8, 1   ; r8 - sorted? - yes, unless we swap
  
    mov r9, rcx ; r9 - address of current element
    inner_loop:
      mov r10d, [r9]      ; r10d - value of current element
      mov r11d, [r9 + 4]  ; r11d - value of next element
      cmp r10d, r11d

      jbe post_swap
      ; swap elements
        mov [r9], r11d
        mov [r9 + 4], r10d
        
        mov r8, 0 ; swap took place, set sorted to NO,
      post_swap:
        add r9, 4
        cmp r9, rdx
        jb inner_loop
    
    cmp r8,0
    jz big_loop;

  ret
asm_bubble_sort_by_ivan endp



; Bubble Sort - End
; First optimisation: exclude the sorted elements
; at the end of the array
;
; Args:
; rcx -> array,
; rdx : array size
public asm_bubble_sort_end
asm_bubble_sort_end proc
    ; Calc the address of the last element
    dec rdx                 ; size - 1
    shl rdx, 2              ; rdx * 4 = size of the array in bytes

    mov r11, rcx            ; r11 -> the start of the array
    add r11, rdx            ; r11 -> the last element in the array

sortloop:
    mov r8, rcx             ; r8 -> the start of the array
    mov r10b, 1             ; sorted = true // no swap occurred

    ; Reading numbers and comparing them
    mov eax, [r8]           ; Read the first number
swaploop:
    mov edx, [r8+4]         ; Read the next number
    cmp eax, edx            ; Compare current (eax) and next (edx)
    jle noswap              ; Go to 'noswap' if eax <= edx

    ; Swap values
    mov [r8+4], eax
    mov [r8], edx
    xor r10b, r10b          ; sorted = false // the array is unsorted

    ; After swapping eax already contains the next element
    jmp nextelem

noswap:
    mov eax, edx            ; Put the next element into eax
                            ; to avoid another memory access

nextelem:
    add r8, 4               ; Move pointer to the next element

    cmp r8, r11             ; Reached the last element?
    jb  swaploop            ; Go to 'swaploop' if r8 < r11

    ; Test whether the array is sorted
    test r10b, r10b
    jz sortloop             ; Not yet - walk the array one more time

    ; The array is sorted - return
    ret
asm_bubble_sort_end endp


; Bubble Sort - End
; Second optimisation: exclude all elements after
; the last swap because they're already sorted
;
; Args:
; rcx -> array,
; rdx : array size
public asm_bubble_sort_swap
asm_bubble_sort_swap proc
    ; Calc the address of the last element
    dec rdx                 ; size - 1
    shl rdx, 2              ; rdx * 4 = size of the array in bytes

    mov r11, rcx            ; r11 -> the start of the array
    add r11, rdx            ; r11 -> the last element in the array

sortloop:
    mov r8, rcx             ; r8 -> the start of the array
    mov r10b, 1             ; sorted = true // no swap occurred

    ; Reading numbers and comparing them
    mov eax, [r8]           ; Read the first number
swaploop:
    mov edx, [r8+4]         ; Read the next number
    cmp eax, edx            ; Compare current (eax) and next (edx)
    jle noswap              ; Go to 'noswap' if eax <= edx

    ; Swap values
    mov [r8+4], eax
    mov [r8], edx
    xor r10b, r10b          ; sorted = false // the array is unsorted

    ; After swapping eax already contains the next element
    jmp nextelem

noswap:
    mov eax, edx            ; Put the next element into eax
                            ; to avoid another memory access

nextelem:
    add r8, 4               ; Move pointer to the next element

    cmp r8, r11             ; Reached the last element?
    jb  swaploop            ; Go to 'swaploop' if r8 < r11

    ; Test whether the array is sorted
    test r10b, r10b
    jz sortloop             ; Not yet - walk the array one more time

    ; The array is sorted - return
    ret
asm_bubble_sort_swap endp


end ; end of assembly file
