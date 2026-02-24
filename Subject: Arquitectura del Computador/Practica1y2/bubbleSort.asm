.data
	mi_array: .word 5, 2, 9, 1, 5, 6
	tamano:   .word 6
	espacio: .asciiz " "
    	n_linea: .asciiz "\n"
.text

.globl main

main:

	la $a0, mi_array    
    	lw $a1, tamano      
    	jal bubbleSort      
    
    	jal imprimirArreglo
    	li $v0, 10
    	syscall

bubbleSort:

	#$a0= array, $a1= n
	#$t0=i, $t1=j, $t3= intercambio

	li $t0, 0	#i=0
	addi $t4, $a1, -1 	#$t4=n-1
	
	forExt:
	bge $t0, $t4, endforExt
	
	li $t3, 0	 #intercambio=0
	li $t1, 0	#j=0
	sub $t5, $a1, $t0
	addi $t5, $t5, -1	#$t5= n-i-1
	  
		forIn:
			bge $t1, $t5, endforIn
			
			#acceder a array[j]
			sll $t6, $t1, 2 	#j*4
			add $t6, $a0, $t6 	# $t6 apunta a array[j]
			lw $t7, 0($t6) 	#$t7=array[j]
			
			#acceder a array[j+1]
			lw $t9, 4($t6)	#$t9= array[j+1]
			
			ble $t7, $t9, endif
			
			if:
				sw $t7, 4($t6)	#el valor guardado en array[j ] se guarda en array[j+1]
				sw $t9, 0($t6)	#el valor guardado en array[j+1] se guarda en array[j]
				li $t3, 1			#intercambio=1
			endif:
			
			addi $t1, $t1, 1
			j forIn
		endforIn:
		beq $t3, $zero, endBlubbleSort
		addi $t0, $t0, 1
		j forExt
		endforExt:
endBlubbleSort:
	jr $ra

imprimirArreglo:
    move $t0, $a0           
    move $t1, $a1           
    li $t2, 0               

	bucleImprimir:
    		bge $t2, $t1, finImprimir 
    
    		
    		lw $a0, 0($t0)          
  		li $v0, 1               
    		syscall
    
   		
    		la $a0, espacio        
    		li $v0, 4
   		syscall
    
    		addi $t0, $t0, 4        
    		addi $t2, $t2, 1        
    		j bucleImprimir

		finImprimir:
    			
    			la $a0, n_linea        
    			li $v0, 4
    			syscall
    
    			jr $ra
