.data

msg_verde:    .asciiz "Semaforo en verde, esperando pulsador\n"
msg_pulsado:  .asciiz "Pulsador activado: en 20 segundos, cambia a amarillo\n"
msg_amarillo: .asciiz "Semaforo en amarillo, en 10 segundos, semaforo en rojo\n"
msg_rojo:     .asciiz "Semaforo en rojo, en 30 segundos, semaforo en verde\n"


flag_pulsador: .word 0   # 0 = nadie ha pulsado s, 1 = se pulso s

.kdata

save_at: .word 0
save_t0: .word 0
save_t1: .word 0

.text
.globl main
main:
    # 1. habilitar interrupciones del teclado
    li $t0, 0xFFFF0000
    lw $t1, 0($t0)
    ori $t1, $t1, 2
    sw $t1, 0($t0)


estado_verde:
    # imprimir mensaje de estado verde
    li $v0, 4
    la $a0, msg_verde
    syscall

    # asegurarnos de que la bandera esté en 0 al iniciar el ciclo
    sw $zero, flag_pulsador

esperar_pulsador:
    # Bucle infinito: solo saldremos de aquí cuando la interrupción cambie la bandera a 1
    lw $t0, flag_pulsador
    beq $t0, 0, esperar_pulsador



transicion_amarillo:
    # imprimir que alguien pulso el boton
    li $v0, 4
    la $a0, msg_pulsado
    syscall

    # tomar la hora de inicio
    li $v0, 30
    syscall
    move $s0, $a0       # guardar tiempo de inicio en $s0

loop_20s:
    li $v0, 30
    syscall
    subu $t0, $a0, $s0
    li $t1, 20000       # 20,000 milisegundos = 20 segundos
    bltu $t0, $t1, loop_20s



estado_amarillo:
    # imprimir mensaje de estado amarillo
    li $v0, 4
    la $a0, msg_amarillo
    syscall

    # tomar la hora de inicio para los 10s
    li $v0, 30
    syscall
    move $s0, $a0

loop_10s:
    li $v0, 30
    syscall
    subu $t0, $a0, $s0
    li $t1, 10000       # 10,000 milisegundos = 10 segundos
    bltu $t0, $t1, loop_10s



estado_rojo:
    # imprimir mensaje de estado rojo
    li $v0, 4
    la $a0, msg_rojo
    syscall

    # tomar la hora de inicio para los 30s
    li $v0, 30
    syscall
    move $s0, $a0

loop_30s:
    li $v0, 30
    syscall
    subu $t0, $a0, $s0
    li $t1, 30000       # 30,000 milisegundos = 30 segundos
    bltu $t0, $t1, loop_30s

    # el ciclo terminó, regresamos al verde inicial
    j estado_verde



# proteccion contra interrupciones
.ktext 0x80000180

    .set noat
    sw $at, save_at
    .set at
    sw $t0, save_t0
    sw $t1, save_t1

    # leer la tecla que causó la interrupción
    li $t0, 0xFFFF0000
    lw $t1, 4($t0)

    # filtrar si la tecla fue s minuscula o mayuscula
    bne $t1, 115, salir_interrupcion # si no es la 's', ignorar y salir

    # 4. sí fue la 's': encender la bandera 
    li $t1, 1
    sw $t1, flag_pulsador

salir_interrupcion:
    # restaurar contexto y regresar
    .set noat
    lw $at, save_at
    .set at
    lw $t0, save_t0
    lw $t1, save_t1
    eret