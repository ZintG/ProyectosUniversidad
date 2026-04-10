.data

msg: .asciiz "Ingrese un 'n': "

.text

.globl main

main:
	li $v0,4	# imprime mensaje de entrada
	la $a0,msg
	
	li $v0,5	# lectura de entrada ('scanf()')
	syscall
	move $a0,$v0
	
	jal parity	# llamada a la funcion de paridad
	
	move $a0,$v0	# guarda la salida de la funcion en $a0
	li $v0,1	# y la imprime
	syscall
	
	li $v0,10	# 'return'
	syscall
	
parity:
	beq $a0,$zero,caso_base # Si n = 0 -> pasar al caso base
	
	addi $sp,$sp,-8		# reserva de espacio en la pila
	sw $ra,4($sp)
	sw $a0,0($sp)
	
	addi $a0,$a0,-1		# n - 1
		
	jal parity 		# llamada recursiva
	
	lw $a0,0($sp)		# recuperamos el n original
	lw $ra,4($sp)		# y el valor de retorno
	addi $sp,$sp,8
	
	li $t0,1		
	sub $v0,$t0,$v0		# 1 - n - 1
	
	jr $ra			# retornar valor
	
	
	caso_base:
		li $v0,0	# retornar 0
		jr $ra