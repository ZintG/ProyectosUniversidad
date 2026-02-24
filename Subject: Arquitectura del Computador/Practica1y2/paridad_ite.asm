.data

msg: .asciiz "Ingrese un 'n': "

.text

.globl main

main:
	li $v0,4	# imprimir mensaje de entrada
	la $a0,msg	
	syscall
	
	li $v0,5	# leer nro
	syscall
	move $a0,$v0
	
	jal parity	# llamada a la funcion
	
	move $a0,$v0	# guarda la salida en a0
	li $v0,1	# imprime la salida
	syscall
	
	li $v0,10	# 'return'
	syscall
	
parity:
	li $v0,0	# resultado inicial
	li $t0,1	# constante = 1
	
	loop:
		beq $a0,$zero,fin_loop	# Si n = 0 parar el ciclo
		sub $v0,$t0,$v0		# res = 1 - res
		addi $a0,$a0,-1		# decrementar el contador (n = n - 1)
		
		j loop			# iterar
	fin_loop:
	jr $ra				# retornar valor
		