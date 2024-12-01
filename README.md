# Proyecto: Seguidor de Línea 

Este es un proyecto amateur de un **seguidor de línea** diseñado para competir en eventos de robótica y mejorar habilidades en programación y diseño de hardware.

## Componentes

- **Arduino Nano**: Microcontrolador que gestiona la lógica de control y el procesamiento de las señales de los sensores.
- **Regleta QTR-8A (e-Robots)**: Sensor de línea para detectar la posición sobre la línea negra y guiar el robot.
- **Driver DRV8833**: Motor driver utilizado para controlar los motores del robot.
- **Baterías 18650 (3x12V)**: Fuente de energía del robot.
- **Botón de inicio**: Activa el sistema de control del robot.
- **Chasis 3D**: Diseñado en **SolidWorks** e impreso en **PLA**, ofrece una estructura liviana y balanceada.

## Objetivo

Crear un robot seguidor de línea capaz de ajustar su dirección en tiempo real mediante un controlador PID, basado en lecturas ópticas de una línea negra trazada en el suelo.


## Imagen del proyecto

![Seguidor de Línea](https://github.com/Monsivais14/Seguidor-de-Linea-Amateur/raw/main/Seguidor_Linea.jpg)


## Instrucciones de montaje

### Hardware

1. **Arduino Nano**:
   - Conectar los pines del Arduino a la regleta QTR-8A para procesar las señales de los sensores.
   - Conectar el **DRV8833** a los pines digitales del Arduino para controlar los motores.
   - Alimentar el sistema con baterías de **12V**.

2. **Regleta QTR-8A**:
   - Conectar los sensores a los pines analógicos A0-A7 del Arduino para leer la posición de la línea.

3. **Driver DRV8833**:
   - Conectar los motores a los canales del driver para control de dirección y velocidad.

4. **Botón de inicio**:
   - Conectar al pin 2 del Arduino. Este botón activa el sistema de calibración inicial y habilita el modo de funcionamiento del robot.

5. **Chasis**:
   - Ensamblar el chasis impreso en 3D, asegurando un centro de gravedad equilibrado para un movimiento estable.

### Software

El programa principal del proyecto, **QTR8A_3.ino**, implementa un controlador PID básico para que el robot siga la línea de forma precisa.

#### Funciones principales del código

1. **Calibración de sensores**:
   - Los sensores se ajustan para detectar correctamente la línea negra. El LED conectado al pin 13 indica el progreso de la calibración.

2. **Controlador PID**:
   - Parámetros ajustables para mejorar la respuesta del robot:
     - **Kp** (proporcional): Controla la velocidad de corrección.
     - **Ki** (integral): Corrige errores acumulativos.
     - **Kd** (derivativo): Aumenta la respuesta a cambios rápidos.

3. **Seguimiento de la línea**:
   - El robot ajusta las velocidades de los motores en función del error entre la posición actual y el `setpoint` definido (3500).

4. **Acciones correctivas**:
   - Si el robot pierde la línea, se activa una maniobra de retorno para reencontrarla.

5. **Botón de inicio**:
   - Antes de iniciar, el robot permanece en espera hasta que se presione el botón conectado al pin 2. Esto permite iniciar el sistema manualmente y garantizar que los sensores estén listos.

#### Pines utilizados

| Componente           | Pin del Arduino |
|----------------------|-----------------|
| Sensores QTR-8A      | A0-A7           |
| LED de calibración   | 13              |
| Motores              | 5, 6, 9, 10     |
| Botón de inicio      | 2               |

## Cómo funciona

1. **Encendido**:
   - Presiona el botón de inicio para activar el sistema. El robot entra en modo de calibración.

2. **Calibración**:
   - Los sensores detectan los valores mínimos y máximos para calibrar la lectura de la línea.

3. **Seguimiento de la línea**:
   - El robot utiliza los valores calibrados para ajustar las velocidades de los motores en tiempo real, siguiendo la línea negra.

4. **Correcciones**:
   - Si el robot pierde la línea, los motores ajustan la dirección para encontrarla de nuevo.
