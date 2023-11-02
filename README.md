# ELO301 - Grupo 8
Este repositorio contiene los archivos para el ramo de  Diseño de Equipos Electrónicos.

Revisión más nueva: Rev3
## Diseño
El documento de diseño y sus revisiones se encuentran en la carpeta de ```Diseño```.

## Esquemático
En la carpeta ```WIFI_Shield_Rev1``` se encuentra la primera revisión del esquemático junto a su Bill Of Materials en formato ```.csv```. 
El esquemático en sí está en la ruta ```WIFI_Shield_Rev1/WIFI_Shield_Rev1/SCHEMATIC_R1.sch```.

## Librerías
Las iteraciones anteriores de las librerías hechas por el grupo se encuentran en la carpeta ```Librerías``` . Las finalmente usadas se encuentran en su respectiva carpeta de proyecto.

## Diseño de la PCB

Contenido dentro de ```/WIFI_Shield_Rev2/WIFI_Shield_Rev2/SCHEMATIC_R1.brd```. Los archivos de manufactura se encuentran en ```/WIFI_Shield_Rev2/WIFI_SHIELD_2023-10-30.zip```

## Historial de revisiones

Rev 1: Revisión inicial.

Rev 2: Se ajustaron un par de pines para facilitar el ruteo y se ajustó la librería de la NUCLEO para eliminar los pines sin usar. 

Rev 3: Sustituídas las resistencias de 0 Ohm (R11, R12, R13 y R14) que separaban la UART y las resistencias para el EN (R16 y R17) hacia MCU o programador por 3 sets de jumpers 3x1.

Agregadas instrucciones para usar los jumpers al otro lado de la placa.