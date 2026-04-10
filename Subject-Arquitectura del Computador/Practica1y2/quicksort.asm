.data

arr: .word 5,4,2,1,3
n: .word 5
space: .asciiz " "

.text
.globl main

main:

	la $a0,arr		# a0 = arr
	li $a1,0		# a1 = 0
	
	lw $t0,n		# a2 = n - 1
	addi $a2,$t0,-1
	
	jal quicksort		# quicksort(arr,0,n-1)
	
	li $t1,0		# i = 0
	la $t2,arr		# cargamos base de arr
	lw $t3,n		# limite
	
	print_for:
		slt $t4,$t1,$t3	# for i = 0 to n do
		beq $t4,$zero,end_for
		
		sll $t5,$t1,2	# i = i * 4
		add $t5,$t2,$t5	# &a[i]
		lw $a0,0($t5)	# a0 = arr[i]
		
		li $v0,1	# print(arr[i])
		syscall		
		
		li $v0,4	# print(" ")
		la $a0,space
		syscall
		
		addi $t1,$t1,1	# i++
		j print_for
	end_for:
	
	li $v0,10		# return
	syscall

partition:
    			    # primero se calcula el valor y la direccion del pivote
    sll  $t0, $a2, 2        # offset high
    add  $t0, $a0, $t0      # $t0 = &arr[high] 
    lw   $t9, 0($t0)        # $t9 = valor del pivote
    
    addi $t1, $a1, -1       # i = low - 1
    move $t2, $a1           # j = low
    
    loop:
        bge  $t2, $a2, endloop
        
        # cargar arr[j]
        sll  $t3, $t2, 2
        add  $t3, $a0, $t3  # $t3 = &arr[j]
        lw   $t4, 0($t3)    # $t4 = arr[j]
        
        bge  $t4, $t9, next_it
        
        # swap arr[i] y arr[j]
        addi $t1, $t1, 1    # i++
        
        sll  $t5, $t1, 2
        add  $t5, $a0, $t5  # $t5 = &arr[i]
        lw   $t6, 0($t5)    # $t6 = arr[i]
        
        sw   $t4, 0($t5)    # arr[i] = arr[j]
        sw   $t6, 0($t3)    # arr[j] = temp
    
    next_it:
        addi $t2, $t2, 1    # j++
        j    loop

    endloop:
        # colocamos el pivote en su lugar 
        addi $t1, $t1, 1    # i + 1
        
        sll  $t5, $t1, 2    # offset (i+1)
        
        add  $t5, $a0, $t5  # sumamos a $a0
        
        lw   $t6, 0($t5)    # cargar quien estaba en i+1
                
        sw   $t9, 0($t5)    # arr[i+1] = pivote
        sw   $t6, 0($t0)    # arr[high] = el que estaba en i+1
        
        move $v0, $t1       # retornamos índice i+1
        jr   $ra

quicksort:

    # if (low >= high) return
    bge  $a1, $a2, return_qs
    
    # stack frame 20 bytes (ra, a0, a1, a2, y un espacio para pivote)
    addi $sp, $sp, -20
    sw   $ra, 16($sp)
    sw   $a0, 12($sp)
    sw   $a1, 8($sp)
    sw   $a2, 4($sp)
    
    jal  partition
    
    sw   $v0, 0($sp)        # guardar pivote en la pila
    
    # llamada por la izquierda
    lw   $a1, 8($sp)        # restaurar low
    lw   $v0, 0($sp)        # leer pivote 
    addi $a2, $v0, -1       # high = p - 1
    jal  quicksort
    
    # llamada por la derecha
    lw   $a0, 12($sp)       # restaurar arr 
    lw   $a2, 4($sp)        # restaurar high original
    lw   $v0, 0($sp)        # leer pivote de nuevo
    addi $a1, $v0, 1        # low = p + 1
    jal  quicksort
    
    # retornamos stack y salida
    lw   $ra, 16($sp)
    addi $sp, $sp, 20
    return_qs:
    jr   $ra
