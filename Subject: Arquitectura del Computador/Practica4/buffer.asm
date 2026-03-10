.data

buffer:      .space 100       # Espacio en memoria para 100 caracteres
buf_w:       .word 0          # Indice de escritura (donde guarda la interrupcion)
buf_r:       .word 0          # Indice de lectura (desde donde imprime el main)

msg_out:     .asciiz "\n20 segundos - buffer guardado: "
msg_vacio:   .asciiz "(vacio)"
msg_rep:     .asciiz "\n\nIniciando nuevo ciclo de 20s...\n"

.kdata
# Registros de respaldo para el Kernel (ISR)
save_at: .word 0
save_t0: .word 0
save_t1: .word 0
save_t2: .word 0
save_t3: .word 0

.text
.globl main
main:
    # 1. Habilitar interrupciones del teclado
    li $t0, 0xFFFF0000
    lw $t1, 0($t0)
    ori $t1, $t1, 2          # Forzamos el bit 1 del registro de control a '1'
    sw $t1, 0($t0)

reiniciar_ciclo:
    # 2. Tomar la hora de inicio (Milisegundos)
    li $v0, 30
    syscall
    move $s0, $a0            # Guardamos el tiempo inicial en $s0

    # Imprimir mensaje de inicio
    li $v0, 4
    la $a0, msg_rep
    syscall

loop_principal:
    # 3. Consultar la hora actual constantemente
    li $v0, 30
    syscall
    
    # Calcular tiempo transcurrido: actual - inicio
    subu $t0, $a0, $s0
    
    # Verificar si pasaron 20,000 milisegundos (20 segundos)
    li $t1, 20000
    bltu $t0, $t1, loop_principal # Si es menor a 20s, sigue esperando

    # --- PASARON LOS 20 SEGUNDOS ---
    # Imprimir mensaje de aviso
    li $v0, 4
    la $a0, msg_out
    syscall

    # 4. Imprimir el contenido del buffer circular
    lw $t2, buf_r            # Cargar indice de lectura
    lw $t3, buf_w            # Cargar indice de escritura
    beq $t2, $t3, imprimir_vacio # Si son iguales, el buffer esta vacio

loop_impresion:
    beq $t2, $t3, fin_impresion  # Si lectura alcanzo a escritura, terminamos
    
    # Cargar el caracter desde buffer[buf_r]
    la $t0, buffer
    add $t0, $t0, $t2
    lb $a0, 0($t0)           
    
    # Imprimir caracter (syscall 11)
    li $v0, 11                   
    syscall

    # Avanzar indice de lectura de forma circular
    addi $t2, $t2, 1
    blt $t2, 100, no_wrap_r
    li $t2, 0                # Si llega a 100, vuelve a 0 (Circular)
no_wrap_r:
    j loop_impresion

imprimir_vacio:
    li $v0, 4
    la $a0, msg_vacio
    syscall

fin_impresion:
    # Actualizar el indice de lectura en memoria (Vacia el buffer)
    sw $t2, buf_r
    
    j reiniciar_ciclo        # Repetir infinitamente


##################################################
# RUTINA DE SERVICIO DE INTERRUPCION (ISR)
##################################################
.ktext 0x80000180
    
    # 1. Salvar el contexto (Guardar registros)
    .set noat               
    sw $at, save_at
    .set at
    sw $t0, save_t0
    sw $t1, save_t1
    sw $t2, save_t2
    sw $t3, save_t3

    # 2. Leer la tecla pulsada
    li $t0, 0xFFFF0000      
    lw $t2, 4($t0)          # Leemos el codigo ASCII desde 0xFFFF0004

    # 3. Filtro de mayusculas (ASCII 65 al 90)
    blt $t2, 65, salir_interrupcion  
    bgt $t2, 90, salir_interrupcion  

    # 4. Guardar en el buffer circular
    lw $t1, buf_w           # Cargar indice de escritura
    la $t0, buffer          
    add $t0, $t0, $t1       
    sb $t2, 0($t0)          # Escribir la letra en buffer[buf_w]

    # Calcular siguiente posicion de escritura
    addi $t1, $t1, 1
    blt $t1, 100, no_wrap_w
    li $t1, 0               # Si llega a 100, vuelve a 0 (Circular)
no_wrap_w:
    
    # Verificar si el buffer esta lleno (escritura alcanzo a lectura)
    lw $t3, buf_r
    bne $t1, $t3, guardar_w
    
    # Si esta lleno, empujamos el indice de lectura (sobrescribimos lo viejo)
    addi $t3, $t3, 1
    blt $t3, 100, no_wrap_r_isr
    li $t3, 0
no_wrap_r_isr:
    sw $t3, buf_r           # Guardamos el nuevo indice de lectura

guardar_w:
    sw $t1, buf_w           # Guardamos el nuevo indice de escritura

salir_interrupcion:
    # 5. Restaurar el contexto
    .set noat
    lw $at, save_at
    .set at
    lw $t0, save_t0
    lw $t1, save_t1
    lw $t2, save_t2
    lw $t3, save_t3

    # 6. Retornar al programa principal
    eret