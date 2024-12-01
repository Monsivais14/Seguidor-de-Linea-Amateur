# Proyecto Seguidor de Línea 

Este es un proyecto amateur de un **seguidor de línea** 

## Componentes

- **Arduino Nano**: Microcontrolador que gestiona la lógica de control y el procesamiento de las señales de los sensores.
- **Regleta QTR-8A (e-Robots)**: Sensor de línea para detectar la posición sobre la línea negra y guiar el robot.
- **Driver DRV8833**: Motor driver utilizado para controlar los motores del robot.
- **Baterías 18650 (3x12V)**: Fuente de energía del robot.
- **Chasis 3D**: El diseño fue realizado en **SolidWorks** y el modelo impreso en **PLA**.

## Objetivo

Este proyecto consiste en un robot seguidor de línea que es capaz de seguir una línea trazada en el suelo utilizando sensores ópticos. El robot ajusta su dirección en tiempo real para mantenerse sobre la línea.

# Imagen 
![Seguidor de Línea](https://github.com/Monsivais14/Seguidor-de-Linea-Amateur/raw/main/Seguidor_Linea.jpg)

## Instrucciones de montaje

### Hardware

1. **Arduino Nano**: 
   - Conectar los pines del Arduino a los pines correspondientes de la regleta QTR-8A para leer las señales de los sensores.
   - Conectar el **DRV8833** a los pines de control de los motores y al Arduino.
   - Las baterías de **12V** alimentan el sistema a través del driver.

2. **Regleta QTR-8A**:
   - La regleta tiene 8 sensores, cada uno conectado a un pin de entrada analógica del Arduino. 
   - Estos sensores detectan la línea y envían una señal analógica al Arduino.

3. **Motor Driver (DRV8833)**:
   - Controla la dirección y velocidad de los motores en función de las señales del Arduino.

4. **Motores**:
   - Conectar los motores al driver, asegurándose de que estén correctamente alineados para el movimiento del robot.

5. **Chasis**:
   - El chasis 3D impreso en **PLA** proporciona la estructura para los componentes y es diseñado para mantener un centro de gravedad equilibrado para un movimiento estable.

### Software

El código principal del proyecto se llama **QTR8A_3.ino** y se utiliza para controlar los motores del robot en función de los datos proporcionados por los sensores QTR-8A.

#### Descripción del código

El código implementa un controlador PID básico para permitir que el robot siga una línea trazada en el suelo. Los parámetros PID son ajustables para mejorar el rendimiento del seguimiento de la línea.

- **Kp**: Ganancia proporcional. Controla la rapidez con la que el robot se ajusta a su error de posición.
- **Ki**: Ganancia integral. Ayuda a corregir el error acumulado durante el tiempo.
- **Kd**: Ganancia derivativa. Controla la velocidad de reacción ante cambios bruscos en la señal de los sensores.

#### Funcionamiento

1. **Calibración de los sensores**:
   El robot inicia en un modo de calibración, donde los sensores se ajustan para detectar correctamente la línea. Durante este proceso, los LED indicarán cuando se está calibrando y cuándo ha terminado.
   
2. **Seguimiento de la línea**:
   En el ciclo principal (`loop`), el robot lee las posiciones de los sensores QTR-8A y calcula el error entre la posición deseada (un valor de referencia, `setpoint`) y la posición detectada de la línea. 
   
3. **Control PID**:
   El error calculado se pasa a través de un controlador PID que ajusta las velocidades de los motores para corregir la dirección del robot:
   - Si el robot se desvía de la línea, el PID ajusta la velocidad de los motores para que el robot regrese a la línea.
   
4. **Acción de corrección**:
   Dependiendo de la posición de los sensores:
   - Si el robot está completamente desviado de la línea (posición 0 o 7000), ajusta los motores para realizar un giro de corrección.
   - Si el robot está cerca de la línea (posición entre 0 y 7000), ajusta ambos motores para seguir la línea.

#### Códigos y pines

- **Pines del Arduino**:
   - **QTR Sensors**: Los sensores están conectados a los pines analógicos del Arduino (A0-A7).
   - **Motores**: Los motores están conectados a los pines digitales del Arduino (pines 5, 6, 9, 10).
   - **LED de calibración**: Conectado al pin 13.
   - **Botón de inicio**: Conectado al pin 2.

## Cómo funciona

El robot utiliza los 8 sensores de la regleta QTR-8A para detectar la línea. El código procesa las lecturas de los sensores y ajusta los motores en consecuencia. Si el robot se desvía hacia un lado, el código corrige la dirección para mantener el seguimiento de la línea.

