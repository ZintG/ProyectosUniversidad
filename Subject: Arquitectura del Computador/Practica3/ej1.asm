.data

LuzControl: .word 0
LuzEstado:  .word 0
LuzDatos:   .word 750

msg1: .asciiz "Luminosidad: "
msg2: .asciiz "Error en el sensor\n"
msg3: .asciiz "Error de inicializacion en el sensor\n"

.text
.globl main

main:

    # 1. Intentar inicializar el sensor
    jal InicializarSensorLuz
    
    # 2. Verificar si hubo error en la fase de inicio
    li $t0, -1
    beq $v0, $t0, fallo_inicio

    # 3. Intentar leer la luminosidad
    jal LeerLuminosidad

    # 4. Verificar codigo de estado de la lectura
    li $t0,-1
    beq $v1,$t0,mostrarError
    
    # 5. Guardar valor leido y mostrar resultados
    move $t1,$v0

    li $v0, 4
    la $a0, msg1
    syscall

    move $a0, $t1
    li $v0, 1
    syscall

    j fin

fallo_inicio:
    # Salto específico si falla la inicialización
    jal MostrarErrorInicializacion
    j fin

mostrarError:
    # Salto si el sensor falla durante la lectura
    li $v0, 4
    la $a0, msg2
    syscall

fin:
    # Terminar el programa de forma segura
    li $v0, 10
    syscall


##################################################
# Procedimiento: InicializarSensorLuz
##################################################
InicializarSensorLuz:

    li $t0, 1
    sw $t0, LuzControl   # Escribir 0x1 para inicializar

espera:
    lw $t1, LuzEstado    # Leer estado del sensor
    
    li $t2, 1
    beq $t1, $t2, listo  # Si es 1, el sensor está listo
    
    li $t2, -1
    beq $t1, $t2, error_init # Si es -1, hay error de hardware
    
    j espera             # Polling: seguir esperando si es 0

listo:
    li $v0, 0            # Retornar 0
    jr $ra

error_init:
    li $v0, -1           # Retornar -1 (Fallo de Inicio)
    jr $ra


##################################################
# Procedimiento: LeerLuminosidad
##################################################
LeerLuminosidad:

    lw $t0, LuzEstado    # Verificar estado antes de leer datos
    li $t1, -1
    beq $t0, $t1, error  # Si el estado es error, saltar

    lw $v0, LuzDatos     # Obtener valor de luminosidad
    li $v1, 0            # Código 0: lectura correcta
    jr $ra

error:
    li $v0, 0
    li $v1, -1           # Código -1: error en lectura
    jr $ra

##################################################
# Procedimiento: MostrarErrorInicializacion
##################################################
MostrarErrorInicializacion:
    li $v0, 4
    la $a0, msg3         # Imprimir el nuevo mensaje consistente
    syscall
    jr $ra