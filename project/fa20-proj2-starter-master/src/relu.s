.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
# 	a0 (int*) is the pointer to the array
#	a1 (int)  is the # of elements in the array
# Returns:
#	None
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 78.
# ==============================================================================
relu:
    # Prologue
    bne a0, x0, loop_start
    ret 

loop_start:
    addi sp, sp, -4
    sw s0, 0(sp)
    add t0, x0, x0
    add t1, a0, x0
    jal x0, loop_continue



loop_continue:
    beq t0, a1, loop_end
    addi t0, t0, 1
    lw s0, 0(t1)
    addi t1, t1, 4
    bge s0, x0, loop_continue
    mv s0, x0
    addi t1, t1, -4
    sw s0, 0(t1)
    addi t1, t1, 4
    jal x0, loop_continue

loop_end:
    lw s0, 0(sp)
    addi sp, sp, 4
    # Epilogue
	ret
