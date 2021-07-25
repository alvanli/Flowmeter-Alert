EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "jeu. 02 avril 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 8700 1100 0    60   ~ 0
1(Tx)
Text Label 8700 1200 0    60   ~ 0
0(Rx)
Text Label 8700 1300 0    60   ~ 0
Reset
Text Label 8700 1500 0    60   ~ 0
2
Text Label 8700 1600 0    60   ~ 0
3(**)
Text Label 8700 1700 0    60   ~ 0
4
Text Label 8700 1800 0    60   ~ 0
5(**)
Text Label 8700 1900 0    60   ~ 0
6(**)
Text Label 8700 2000 0    60   ~ 0
7
Text Label 8700 2100 0    60   ~ 0
8
Text Label 8700 2200 0    60   ~ 0
9(**)
Text Label 8700 2300 0    60   ~ 0
10(**/SS)
Text Label 8700 2400 0    60   ~ 0
11(**/MOSI)
Text Label 8700 2500 0    60   ~ 0
12(MISO)
Text Label 10550 2500 0    60   ~ 0
13(SCK)
Text Label 10550 2200 0    60   ~ 0
A0
Text Label 10550 2100 0    60   ~ 0
A1
Text Label 10550 2000 0    60   ~ 0
A2
Text Label 10550 1900 0    60   ~ 0
A3
Text Label 10550 1800 0    60   ~ 0
A4
Text Label 10550 1700 0    60   ~ 0
A5
Text Label 10550 1600 0    60   ~ 0
A6
Text Label 10550 1500 0    60   ~ 0
A7
Text Label 10550 2300 0    60   ~ 0
AREF
Text Label 10550 1300 0    60   ~ 0
Reset
Text Notes 8500 575  0    60   ~ 0
Shield for Arduino Nano
Text Label 10250 950  1    60   ~ 0
Vin
Wire Notes Line
	8475 650  9675 650 
Wire Notes Line
	9675 650  9675 475 
$Comp
L Connector_Generic:Conn_01x15 P2
U 1 1 60E4B3A0
P 9550 1800
F 0 "P2" H 9550 2600 50  0000 C CNN
F 1 "Digital" V 9650 1800 50  0000 C CNN
F 2 "Socket_Arduino_Nano:Socket_Strip_Arduino_1x15" H 9550 1800 50  0001 C CNN
F 3 "" H 9550 1800 50  0000 C CNN
	1    9550 1800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x15 P3
U 1 1 56D740C7
P 9950 1800
F 0 "P3" H 9950 2600 50  0000 C CNN
F 1 "Analog" V 10050 1800 50  0000 C CNN
F 2 "Socket_Arduino_Nano:Socket_Strip_Arduino_1x15" H 9950 1800 50  0001 C CNN
F 3 "" H 9950 1800 50  0000 C CNN
	1    9950 1800
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 60E4B3A2
P 9250 2600
F 0 "#PWR08" H 9250 2350 50  0001 C CNN
F 1 "GND" H 9250 2450 50  0000 C CNN
F 2 "" H 9250 2600 50  0000 C CNN
F 3 "" H 9250 2600 50  0000 C CNN
	1    9250 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 1400 9250 1400
Wire Wire Line
	9250 1400 9250 2600
Wire Wire Line
	9350 1100 8700 1100
Wire Wire Line
	8700 1200 9350 1200
Wire Wire Line
	9350 1300 8700 1300
Wire Wire Line
	8700 1500 9350 1500
Wire Wire Line
	9350 1600 8700 1600
Wire Wire Line
	8700 1700 9350 1700
Wire Wire Line
	9350 1800 8700 1800
Wire Wire Line
	8700 1900 9350 1900
Wire Wire Line
	9350 2000 8700 2000
Wire Wire Line
	8700 2100 9350 2100
Wire Wire Line
	9350 2200 8700 2200
Wire Wire Line
	8700 2300 9350 2300
Wire Wire Line
	9350 2400 8700 2400
Wire Wire Line
	8700 2500 9350 2500
$Comp
L power:GND #PWR010
U 1 1 60E4B3A3
P 10250 2600
F 0 "#PWR010" H 10250 2350 50  0001 C CNN
F 1 "GND" H 10250 2450 50  0000 C CNN
F 2 "" H 10250 2600 50  0000 C CNN
F 3 "" H 10250 2600 50  0000 C CNN
	1    10250 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 2600 10250 1200
Wire Wire Line
	10250 1200 10150 1200
Wire Wire Line
	10150 1100 10250 1100
Wire Wire Line
	10250 1100 10250 950 
$Comp
L power:+5V #PWR012
U 1 1 60E4B3A4
P 10350 950
F 0 "#PWR012" H 10350 800 50  0001 C CNN
F 1 "+5V" V 10350 1150 28  0000 C CNN
F 2 "" H 10350 950 50  0000 C CNN
F 3 "" H 10350 950 50  0000 C CNN
	1    10350 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 950  10350 1400
Wire Wire Line
	10350 1400 10150 1400
$Comp
L power:+3V3 #PWR013
U 1 1 56D74854
P 10450 950
F 0 "#PWR013" H 10450 800 50  0001 C CNN
F 1 "+3.3V" V 10450 1150 28  0000 C CNN
F 2 "" H 10450 950 50  0000 C CNN
F 3 "" H 10450 950 50  0000 C CNN
	1    10450 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 950  10450 2400
Wire Wire Line
	10450 2400 10150 2400
Wire Wire Line
	10550 1300 10150 1300
Wire Wire Line
	10150 1500 10550 1500
Wire Wire Line
	10550 1600 10150 1600
Wire Wire Line
	10550 1700 10150 1700
Wire Wire Line
	10150 1800 10550 1800
Wire Wire Line
	10550 1900 10150 1900
Wire Wire Line
	10550 2000 10150 2000
Wire Wire Line
	10150 2100 10550 2100
Wire Wire Line
	10550 2200 10150 2200
Wire Wire Line
	10550 2300 10150 2300
Wire Wire Line
	10150 2500 10550 2500
Wire Notes Line
	11200 2850 8450 2850
Wire Notes Line
	8450 2850 8450 500 
Text Notes 9650 1100 0    60   ~ 0
1
Text Label 8700 1100 0    60   ~ 0
1(Tx)
Text Label 8700 1200 0    60   ~ 0
0(Rx)
Text Label 8700 1300 0    60   ~ 0
Reset
Text Label 8700 1500 0    60   ~ 0
2
Text Label 8700 1600 0    60   ~ 0
3(**)
Text Label 8700 1700 0    60   ~ 0
4
Text Label 8700 1800 0    60   ~ 0
5(**)
Text Label 8700 1900 0    60   ~ 0
6(**)
Text Label 8700 2000 0    60   ~ 0
7
Text Label 8700 2100 0    60   ~ 0
8
Text Label 8700 2200 0    60   ~ 0
9(**)
Text Label 8700 2300 0    60   ~ 0
10(**/SS)
Text Label 8700 2400 0    60   ~ 0
11(**/MOSI)
Text Label 8700 2500 0    60   ~ 0
12(MISO)
Text Label 10550 2500 0    60   ~ 0
13(SCK)
Text Label 10550 2200 0    60   ~ 0
A0
Text Label 10550 2100 0    60   ~ 0
A1
Text Label 10550 2000 0    60   ~ 0
A2
Text Label 10550 1900 0    60   ~ 0
A3
Text Label 10550 1800 0    60   ~ 0
A4
Text Label 10550 1700 0    60   ~ 0
A5
Text Label 10550 1600 0    60   ~ 0
A6
Text Label 10550 1500 0    60   ~ 0
A7
Text Label 10550 2300 0    60   ~ 0
AREF
Text Label 10550 1300 0    60   ~ 0
Reset
Text Notes 8500 575  0    60   ~ 0
Shield for Arduino Nano
Text Label 10250 950  1    60   ~ 0
Vin
$Comp
L Connector_Generic:Conn_01x15 P1
U 1 1 56D73FAC
P 9550 1800
F 0 "P1" H 9550 2600 50  0000 C CNN
F 1 "Digital" V 9650 1800 50  0000 C CNN
F 2 "Socket_Arduino_Nano:Socket_Strip_Arduino_1x15" H 9550 1800 50  0001 C CNN
F 3 "" H 9550 1800 50  0000 C CNN
	1    9550 1800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x15 P4
U 1 1 60E4B3A1
P 9950 1800
F 0 "P4" H 9950 2600 50  0000 C CNN
F 1 "Analog" V 10050 1800 50  0000 C CNN
F 2 "Socket_Arduino_Nano:Socket_Strip_Arduino_1x15" H 9950 1800 50  0001 C CNN
F 3 "" H 9950 1800 50  0000 C CNN
	1    9950 1800
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 56D7422C
P 9250 2600
F 0 "#PWR07" H 9250 2350 50  0001 C CNN
F 1 "GND" H 9250 2450 50  0000 C CNN
F 2 "" H 9250 2600 50  0000 C CNN
F 3 "" H 9250 2600 50  0000 C CNN
	1    9250 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 56D746ED
P 10250 2600
F 0 "#PWR09" H 10250 2350 50  0001 C CNN
F 1 "GND" H 10250 2450 50  0000 C CNN
F 2 "" H 10250 2600 50  0000 C CNN
F 3 "" H 10250 2600 50  0000 C CNN
	1    10250 2600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 56D747E8
P 10350 950
F 0 "#PWR011" H 10350 800 50  0001 C CNN
F 1 "+5V" V 10350 1150 28  0000 C CNN
F 2 "" H 10350 950 50  0000 C CNN
F 3 "" H 10350 950 50  0000 C CNN
	1    10350 950 
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR014
U 1 1 60E4B3A5
P 10450 950
F 0 "#PWR014" H 10450 800 50  0001 C CNN
F 1 "+3.3V" V 10450 1150 28  0000 C CNN
F 2 "" H 10450 950 50  0000 C CNN
F 3 "" H 10450 950 50  0000 C CNN
	1    10450 950 
	1    0    0    -1  
$EndComp
Text Notes 9650 1100 0    60   ~ 0
1
Wire Wire Line
	5750 1600 6400 1600
Text Label 6400 1600 2    60   ~ 0
11(**/MOSI)
Wire Wire Line
	6400 1500 5750 1500
Text Label 6400 1500 2    60   ~ 0
12(MISO)
Wire Wire Line
	5750 1400 6150 1400
Text Label 6150 1400 0    60   ~ 0
13(SCK)
Wire Wire Line
	4600 2000 5250 2000
Wire Wire Line
	4600 1100 4600 2000
Wire Wire Line
	5250 800  5250 700 
Wire Wire Line
	4600 800  5250 800 
$Comp
L RF:NRF24L01_Breakout U1
U 1 1 60E5486D
P 5250 1300
F 0 "U1" H 5629 1254 50  0000 L CNN
F 1 "NRF24L01_Breakout" H 5629 1345 50  0000 L CNN
F 2 "nrf:NRF24L01" H 5400 1900 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 5250 1200 50  0001 C CNN
	1    5250 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	5250 1900 5250 2000
Connection ~ 5250 700 
$Comp
L power:GND #PWR01
U 1 1 60E4A5A7
P 5250 700
F 0 "#PWR01" H 5250 450 50  0001 C CNN
F 1 "GND" H 5255 527 50  0000 C CNN
F 2 "" H 5250 700 50  0001 C CNN
F 3 "" H 5250 700 50  0001 C CNN
	1    5250 700 
	-1   0    0    1   
$EndComp
$Comp
L Device:C C1
U 1 1 60E58688
P 4600 950
F 0 "C1" H 4715 996 50  0000 L CNN
F 1 "C" H 4715 905 50  0000 L CNN
F 2 "Capacitor_THT:C_Axial_L3.8mm_D2.6mm_P10.00mm_Horizontal" H 4638 800 50  0001 C CNN
F 3 "~" H 4600 950 50  0001 C CNN
	1    4600 950 
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR02
U 1 1 60E8BAC3
P 5250 2000
F 0 "#PWR02" H 5250 1850 50  0001 C CNN
F 1 "+3.3V" V 5250 2200 28  0000 C CNN
F 2 "" H 5250 2000 50  0000 C CNN
F 3 "" H 5250 2000 50  0000 C CNN
	1    5250 2000
	-1   0    0    1   
$EndComp
Connection ~ 5250 2000
$Comp
L Device:Speaker LS1
U 1 1 60E5AC0D
P 7550 750
F 0 "LS1" H 7720 746 50  0000 L CNN
F 1 "Speaker" H 7720 655 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 7550 550 50  0001 C CNN
F 3 "~" H 7540 700 50  0001 C CNN
	1    7550 750 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 60E74D34
P 7050 850
F 0 "#PWR06" H 7050 600 50  0001 C CNN
F 1 "GND" H 7055 677 50  0000 C CNN
F 2 "" H 7050 850 50  0001 C CNN
F 3 "" H 7050 850 50  0001 C CNN
	1    7050 850 
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 60E74D3A
P 7200 850
F 0 "R4" V 6993 850 50  0000 C CNN
F 1 "R" V 7084 850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7130 850 50  0001 C CNN
F 3 "~" H 7200 850 50  0001 C CNN
	1    7200 850 
	0    -1   -1   0   
$EndComp
$Comp
L Display_Character:WC1602A DS?
U 1 1 60EADF53
P 6250 3050
F 0 "DS?" H 6300 2950 50  0000 C CNN
F 1 "WC1602A" H 6300 3050 50  0000 C CNN
F 2 "Display:WC1602A" H 6250 2150 50  0001 C CIN
F 3 "http://www.wincomlcd.com/pdf/WC1602A-SFYLYHTC06.pdf" H 6950 3050 50  0001 C CNN
	1    6250 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60EAEC01
P 6250 3850
F 0 "#PWR?" H 6250 3600 50  0001 C CNN
F 1 "GND" H 6255 3677 50  0000 C CNN
F 2 "" H 6250 3850 50  0001 C CNN
F 3 "" H 6250 3850 50  0001 C CNN
	1    6250 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60EB2F42
P 6250 2250
F 0 "#PWR?" H 6250 2100 50  0001 C CNN
F 1 "+5V" V 6250 2450 28  0000 C CNN
F 2 "" H 6250 2250 50  0000 C CNN
F 3 "" H 6250 2250 50  0000 C CNN
	1    6250 2250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60EB2F49
P 6250 2250
F 0 "#PWR?" H 6250 2100 50  0001 C CNN
F 1 "+5V" V 6250 2450 28  0000 C CNN
F 2 "" H 6250 2250 50  0000 C CNN
F 3 "" H 6250 2250 50  0000 C CNN
	1    6250 2250
	1    0    0    -1  
$EndComp
Connection ~ 6250 2250
$Comp
L power:GND #PWR?
U 1 1 60EB7B3E
P 6950 2450
F 0 "#PWR?" H 6950 2200 50  0001 C CNN
F 1 "GND" H 6955 2277 50  0000 C CNN
F 2 "" H 6950 2450 50  0001 C CNN
F 3 "" H 6950 2450 50  0001 C CNN
	1    6950 2450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60EB9286
P 6800 2450
F 0 "R?" V 6593 2450 50  0000 C CNN
F 1 "R" V 6684 2450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6730 2450 50  0001 C CNN
F 3 "~" H 6800 2450 50  0001 C CNN
	1    6800 2450
	0    1    1    0   
$EndComp
Text Label 5200 2650 0    60   ~ 0
7
Wire Wire Line
	5850 2650 5200 2650
Text Label 5200 2650 0    60   ~ 0
7
$Comp
L power:GND #PWR?
U 1 1 60EBC2D4
P 5850 2550
F 0 "#PWR?" H 5850 2300 50  0001 C CNN
F 1 "GND" H 5855 2377 50  0000 C CNN
F 2 "" H 5850 2550 50  0001 C CNN
F 3 "" H 5850 2550 50  0001 C CNN
	1    5850 2550
	0    1    1    0   
$EndComp
Text Label 5200 2450 0    60   ~ 0
6(**)
Wire Wire Line
	5200 2450 5850 2450
Text Label 5200 2450 0    60   ~ 0
6(**)
Text Label 5200 3350 0    60   ~ 0
5(**)
Wire Wire Line
	5850 3350 5200 3350
Text Label 5200 3350 0    60   ~ 0
5(**)
Text Label 5200 3450 0    60   ~ 0
4
Wire Wire Line
	5200 3450 5850 3450
Text Label 5200 3450 0    60   ~ 0
4
Text Label 5200 3550 0    60   ~ 0
3(**)
Wire Wire Line
	5850 3550 5200 3550
Text Label 5200 3550 0    60   ~ 0
3(**)
Text Label 5200 3650 0    60   ~ 0
2
Wire Wire Line
	5200 3650 5850 3650
Text Label 5200 3650 0    60   ~ 0
2
$Comp
L power:GND #PWR?
U 1 1 60EC73B7
P 6650 2850
F 0 "#PWR?" H 6650 2600 50  0001 C CNN
F 1 "GND" H 6655 2677 50  0000 C CNN
F 2 "" H 6650 2850 50  0001 C CNN
F 3 "" H 6650 2850 50  0001 C CNN
	1    6650 2850
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60EC9EF5
P 6950 2750
F 0 "#PWR?" H 6950 2600 50  0001 C CNN
F 1 "+5V" V 6950 2950 28  0000 C CNN
F 2 "" H 6950 2750 50  0000 C CNN
F 3 "" H 6950 2750 50  0000 C CNN
	1    6950 2750
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60EC9EFB
P 6950 2750
F 0 "#PWR?" H 6950 2600 50  0001 C CNN
F 1 "+5V" V 6950 2950 28  0000 C CNN
F 2 "" H 6950 2750 50  0000 C CNN
F 3 "" H 6950 2750 50  0000 C CNN
	1    6950 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	6950 2750 6650 2750
Connection ~ 6950 2750
Text Label 6400 1100 2    60   ~ 0
9(**)
Wire Wire Line
	5750 1100 6400 1100
Text Label 6400 1100 2    60   ~ 0
9(**)
Text Label 6400 1300 2    60   ~ 0
10(**/SS)
Wire Wire Line
	6400 1300 5750 1300
Text Label 6400 1300 2    60   ~ 0
10(**/SS)
Text Label 6950 750  2    60   ~ 0
A2
Wire Wire Line
	6950 750  7350 750 
Text Label 6950 750  2    60   ~ 0
A2
$Comp
L alvin:joystick U?
U 1 1 60EEFA48
P 7600 1950
F 0 "U?" H 7878 1754 50  0000 L CNN
F 1 "joystick" H 7878 1663 50  0000 L CNN
F 2 "" H 7750 2050 50  0001 C CNN
F 3 "" H 7750 2050 50  0001 C CNN
	1    7600 1950
	1    0    0    -1  
$EndComp
Text Label 7500 1500 1    60   ~ 0
A0
Wire Wire Line
	7500 1500 7500 1900
Text Label 7500 1500 1    60   ~ 0
A0
Text Label 7600 1500 1    60   ~ 0
A1
Wire Wire Line
	7600 1900 7600 1500
Text Label 7600 1500 1    60   ~ 0
A1
$Comp
L power:+5V #PWR?
U 1 1 60EF7360
P 7700 1450
F 0 "#PWR?" H 7700 1300 50  0001 C CNN
F 1 "+5V" V 7700 1650 28  0000 C CNN
F 2 "" H 7700 1450 50  0000 C CNN
F 3 "" H 7700 1450 50  0000 C CNN
	1    7700 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 1450 7700 1900
$Comp
L power:+5V #PWR?
U 1 1 60EF7367
P 7700 1450
F 0 "#PWR?" H 7700 1300 50  0001 C CNN
F 1 "+5V" V 7700 1650 28  0000 C CNN
F 2 "" H 7700 1450 50  0000 C CNN
F 3 "" H 7700 1450 50  0000 C CNN
	1    7700 1450
	1    0    0    -1  
$EndComp
Connection ~ 7700 1450
Text Label 7400 1250 3    60   ~ 0
8
Wire Wire Line
	7400 1250 7400 1900
Text Label 7400 1250 3    60   ~ 0
8
$Comp
L power:GND #PWR?
U 1 1 60EFC592
P 8000 1750
F 0 "#PWR?" H 8000 1500 50  0001 C CNN
F 1 "GND" H 8005 1577 50  0000 C CNN
F 2 "" H 8000 1750 50  0001 C CNN
F 3 "" H 8000 1750 50  0001 C CNN
	1    8000 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 1900 7800 1550
Wire Wire Line
	7800 1550 8000 1550
Wire Wire Line
	8000 1550 8000 1750
$EndSCHEMATC
