# Pruebas para la placa

## Testpoints

- TP1: 3V3
- TP2: Botón

## Listado de resistencias de 0 ohm

- R2: Alimentación Sensor
- R5: Alimentación ESP32
- R6: 3V3 botón
- R15: 3V3 del programador
- R20: Conexión botón
- R21: Alimentación LED verde

## Hardware

- Verificar continuidad
- Verificar que no hayan cortocircuitos en soldaduras
- Probar sensor y ESP
- Botón: Tester en modo continuidad con una terminal en R6 y la otra en TP2

## Sensor

- Soldar resistencia R2 para energizar sensor

- Definir macro  ``` SENSOR_TEST_EN``` en ``main.c`` como 1 para iniciar el firmware en modo prueba

- Obtener ID y mediciones desde UART2. Iluminar y cubrir el sensor para ver valores máximos y mínimos

## ESP32
- Soldar R5
- Ver conexión con MCU
- Correr firmware para que envíe valor del clock a ThingSpeak usando el macro ``SEND_CLK`` de ``main.c`` en 1
- Conectar BOOT a tierra