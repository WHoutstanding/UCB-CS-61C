.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# =================================================================
argmax:

    # Prologue
    bne a1, x0, loop_start
    ret

loop_start:
    add t0, a0, x0
    add t1, x0, x0
    add t2, x0, x0
    addi sp, sp, -8
    sw s0, 0(sp)
    sw s1, 4(sp)
    mv s1, x0
    addi s1, s1, -2048
    jal x0, loop_continue

loop_continue:
    beq t1, a1, loop_end
    lw s0, 0(t0)
    blt s0, s1, continue
    mv s1, s0
    mv t2, t1
continue:
    addi t0, t0, 4
    addi t1, t1, 1
    jal x0, loop_continue

loop_end:
    mv a0, t2
    lw s0, 0(sp)
    lw s1, 4(sp)
    addi sp, sp, 8
    # Epilogue
    ret
