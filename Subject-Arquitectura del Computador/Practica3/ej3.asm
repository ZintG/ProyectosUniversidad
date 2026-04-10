.data
TensionControl: .word 0      # Escribir 1 aquí inicia la toma de tensión
TensionEstado:  .word 1      # 0: midiendo, 1: medición completada
TensionSistol:  .word 120    # Registro con el resultado de presión sistólica
TensionDiastol: .word 80     # Registro con el resultado de presión diastólica

msg1: .asciiz "Presion Sistolica: "
msg2: .asciiz "\nPresion Diastolica: "

.text
.globl main

main:
    # 1. Llamar al controlador del dispositivo
    jal controlador_tension

    move $s0, $v0            # Guardar sistólica en $s0
    move $s1, $v1            # Guardar diastólica en $s1

    # 2. Mostrar etiqueta de la sistólica
    li $v0, 4                # Servicio 4: imprimir cadena
    la $a0, msg1             # Cargar dirección de msg1
    syscall

    # 3. Mostrar el valor de la sistólica
    move $a0, $s0            # Colocar el valor guardado en $a0
    li $v0, 1                # Servicio 1: imprimir entero
    syscall

    # 4. Mostrar etiqueta de la diastólica
    li $v0, 4                # Servicio 4: imprimir cadena
    la $a0, msg2             # Cargar dirección de msg2
    syscall

    # 5. Mostrar el valor de la diastólica
    move $a0, $s1            # Colocar el valor guardado en $a0
    li $v0, 1                # Servicio 1: imprimir entero
    syscall

fin:
    # Finalizar el programa limpiamente
    li $v0, 10
    syscall


#################################################
# Procedimiento: controlador_tension
#################################################
controlador_tension:
    li $t0, 1                # Cargar valor de inicio (1)
    sw $t0, TensionControl   # Ordenar al hardware que empiece a medir

espera_tension:
    lw $t1, TensionEstado    # Leer el estado actual del dispositivo
    beq $t1, $zero, espera_tension # Si el estado es 0 (midiendo), repetir bucle

    # El hardware ya puso el estado en 1, los datos son válidos
    lw $v0, TensionSistol    # Retornar primer valor en $v0
    lw $v1, TensionDiastol   # Retornar segundo valor en $v1

    # Regresar al programa principal
    jr $ra