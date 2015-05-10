; (c) 2015 psce4all project. All rights reserved.
; Released under GPL v2 license. Read LICENSE for more details.

.code

AtomicChangeEmulatorState PROC
    mov             eax, dword ptr [rcx]
	mov             r10, rcx
loop_again:
    mov             ecx, eax
    and             ecx, 0FFFFFFF0h
    or              ecx, edx
    lock cmpxchg    dword ptr [r10], ecx
    jne             loop_again
    ret
AtomicChangeEmulatorState ENDP

end
