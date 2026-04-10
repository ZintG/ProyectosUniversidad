.data

# Registros simulados del sensor en memoria
PresionControl: .word 0     # Registro para enviar comandos (0x5 = Iniciar)
PresionEstado:  .word 1     # Registro de estado (0: no listo, 1: listo, -1: error)
PresionDatos:   .word 120   # Registro con el valor de la presión

msgPresion: .asciiz "Presion leida: "
msgError:   .asciiz "Error en sensor de presion\n"

.text
.globl main

main:

    # 1. Inicializar el sensor de presión
    jal InicializarSensorPresion

    # 2. Llamar al procedimiento de lectura con lógica de reintento
    jal LeerPresion

    # 3. Evaluar el código de estado devuelto en $v1
    li $t0, -1
    beq $v1, $t0, mostrarError # Si $v1 es -1, el error persiste tras el reintento
    
    # 4. Éxito: Guardar el dato de $v0 y mostrarlo en consola
    move $t1, $v0
    
    li $v0, 4
    la $a0, msgPresion
    syscall

    move $a0, $t1
    li $v0, 1
    syscall

    j fin


mostrarError:
    # Mostrar mensaje de error general
    li $v0, 4
    la $a0, msgError
    syscall


fin:
    # Finalizar ejecución del programa
    li $v0, 10
    syscall


#################################################
# Procedimiento: InicializarSensorPresion
#################################################
InicializarSensorPresion:

    li $t0, 5                # Cargar el comando de inicialización (0x5)
    sw $t0, PresionControl   # Escribir en el registro de control del sensor

espera:
    lw $t1, PresionEstado    # Leer el estado actual del hardware
    li $t2, 1                # Valor de "Lectura válida / Listo"
    beq $t1, $t2, listo      # Si el estado es 1, el sensor está preparado
    j espera                 # Polling: reintentar lectura de estado si es 0

listo:
    jr $ra                   # Retornar al procedimiento que hizo la llamada


#################################################
# Procedimiento: LeerPresion
#################################################
LeerPresion:

    # Gestión de la Pila (Stack)
    # Guardamos $ra porque este procedimiento llamará a InicializarSensorPresion
    addi $sp, $sp, -4
    sw $ra, 0($sp)           

    # Intento de lectura inicial
    lw $t0, PresionEstado    # Cargar estado del sensor

    li $t1, -1               # Valor que representa error transitorio
    beq $t0, $t1, reintento  # Si hay error (-1), saltar a la fase de reintento

    # Caso Éxito (Primer intento)
    lw $v0, PresionDatos     # Obtener el valor de presión en $v0
    li $v1, 0                # Código de estado 0: Lectura correcta
    j salir_leer             # Ir al epílogo para limpiar la pila y salir


reintento:
    # Lógica de Recuperación: Reiniciar y probar de nuevo una vez
    jal InicializarSensorPresion

    lw $t0, PresionEstado    # Volver a verificar el estado tras reiniciar
    li $t1, -1
    beq $t0, $t1, error      # Si sigue en -1, el error es definitivo

    # Caso Éxito (Tras reintento)
    lw $v0, PresionDatos     # Obtener valor de presión
    li $v1, 0                # Código de estado 0: Lectura correcta
    j salir_leer


error:
    # Caso Fallo Definitivo
    li $v0, 0                # Valor por defecto
    li $v1, -1               # Código de estado -1: Error persistente


salir_leer:
    # Epílogo: Restaurar la dirección de retorno original y limpiar pila
    lw $ra, 0($sp)           
    addi $sp, $sp, 4         
    jr $ra                   # Volver al main