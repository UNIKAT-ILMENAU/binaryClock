EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Timer:MCP7940N-xP U1
U 1 1 60FA7ABA
P 7650 1800
F 0 "U1" H 7650 1311 50  0000 C CNN
F 1 "MCP7940N-xP" H 7650 1220 50  0000 C CNN
F 2 "" H 7650 1800 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20005010F.pdf" H 7650 1800 50  0001 C CNN
	1    7650 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0101
U 1 1 60FC0E98
P 7850 1300
F 0 "#PWR0101" H 7850 1150 50  0001 C CNN
F 1 "+BATT" H 7865 1473 50  0000 C CNN
F 2 "" H 7850 1300 50  0001 C CNN
F 3 "" H 7850 1300 50  0001 C CNN
	1    7850 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 1400 7750 1350
Wire Wire Line
	7750 1350 7850 1350
Wire Wire Line
	7850 1350 7850 1300
Wire Wire Line
	7650 1400 7650 1350
Wire Wire Line
	7650 1350 7550 1350
Wire Wire Line
	7550 1350 7550 1300
$Comp
L power:+5V #PWR0102
U 1 1 60FC5F0F
P 7550 1300
F 0 "#PWR0102" H 7550 1150 50  0001 C CNN
F 1 "+5V" H 7565 1473 50  0000 C CNN
F 2 "" H 7550 1300 50  0001 C CNN
F 3 "" H 7550 1300 50  0001 C CNN
	1    7550 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 60FC6565
P 7650 2450
F 0 "#PWR0103" H 7650 2200 50  0001 C CNN
F 1 "GND" H 7655 2277 50  0000 C CNN
F 2 "" H 7650 2450 50  0001 C CNN
F 3 "" H 7650 2450 50  0001 C CNN
	1    7650 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2450 7650 2200
Text Label 6850 1700 0    50   ~ 0
sda
Wire Wire Line
	6850 1600 7250 1600
Wire Wire Line
	6850 1700 7250 1700
Text Label 6850 1600 0    50   ~ 0
scl
$Comp
L Device:Crystal Y1
U 1 1 60FDB040
P 8550 1800
F 0 "Y1" V 8504 1931 50  0000 L CNN
F 1 "Crystal" V 8595 1931 50  0000 L CNN
F 2 "" H 8550 1800 50  0001 C CNN
F 3 "~" H 8550 1800 50  0001 C CNN
	1    8550 1800
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 60FDC6DB
P 8550 2250
F 0 "C3" H 8665 2296 50  0000 L CNN
F 1 "18p" H 8665 2205 50  0000 L CNN
F 2 "" H 8588 2100 50  0001 C CNN
F 3 "~" H 8550 2250 50  0001 C CNN
	1    8550 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 60FDD393
P 8550 1350
F 0 "C2" H 8665 1396 50  0000 L CNN
F 1 "16p" H 8665 1305 50  0000 L CNN
F 2 "" H 8588 1200 50  0001 C CNN
F 3 "~" H 8550 1350 50  0001 C CNN
	1    8550 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 1900 8250 1900
Wire Wire Line
	8250 1900 8250 2000
Wire Wire Line
	8250 2000 8550 2000
Wire Wire Line
	8550 2000 8550 1950
Wire Wire Line
	8550 1650 8550 1600
Wire Wire Line
	8550 1600 8250 1600
Wire Wire Line
	8250 1600 8250 1700
Wire Wire Line
	8250 1700 8050 1700
Wire Wire Line
	8550 2100 8550 2000
Connection ~ 8550 2000
Wire Wire Line
	8550 1600 8550 1500
Connection ~ 8550 1600
$Comp
L power:GND #PWR0104
U 1 1 60FE3C17
P 8550 2400
F 0 "#PWR0104" H 8550 2150 50  0001 C CNN
F 1 "GND" H 8555 2227 50  0000 C CNN
F 2 "" H 8550 2400 50  0001 C CNN
F 3 "" H 8550 2400 50  0001 C CNN
	1    8550 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 60FE4490
P 8550 1200
F 0 "#PWR0105" H 8550 950 50  0001 C CNN
F 1 "GND" H 8555 1027 50  0000 C CNN
F 2 "" H 8550 1200 50  0001 C CNN
F 3 "" H 8550 1200 50  0001 C CNN
	1    8550 1200
	-1   0    0    1   
$EndComp
Connection ~ 7550 1350
Wire Wire Line
	2850 1100 2750 1100
$Comp
L power:+5V #PWR0106
U 1 1 60FD4D71
P 2850 1100
F 0 "#PWR0106" H 2850 950 50  0001 C CNN
F 1 "+5V" V 2865 1228 50  0000 L CNN
F 2 "" H 2850 1100 50  0001 C CNN
F 3 "" H 2850 1100 50  0001 C CNN
	1    2850 1100
	0    1    1    0   
$EndComp
Connection ~ 2400 1700
Wire Wire Line
	2450 1700 2400 1700
Wire Wire Line
	2400 1700 2350 1700
Wire Wire Line
	2400 1850 2400 1700
$Comp
L power:GND #PWR0107
U 1 1 60FD2643
P 2400 1850
F 0 "#PWR0107" H 2400 1600 50  0001 C CNN
F 1 "GND" H 2405 1677 50  0000 C CNN
F 2 "" H 2400 1850 50  0001 C CNN
F 3 "" H 2400 1850 50  0001 C CNN
	1    2400 1850
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J2
U 1 1 60FCFE26
P 2450 1300
F 0 "J2" H 2507 1767 50  0000 C CNN
F 1 "USB_B_Micro" H 2507 1676 50  0000 C CNN
F 2 "" H 2600 1250 50  0001 C CNN
F 3 "~" H 2600 1250 50  0001 C CNN
	1    2450 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 1350 7450 1350
Wire Wire Line
	7150 1350 7100 1350
$Comp
L power:GND #PWR0108
U 1 1 6115E05F
P 7100 1350
F 0 "#PWR0108" H 7100 1100 50  0001 C CNN
F 1 "GND" H 7105 1177 50  0000 C CNN
F 2 "" H 7100 1350 50  0001 C CNN
F 3 "" H 7100 1350 50  0001 C CNN
	1    7100 1350
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 61158066
P 7300 1350
F 0 "C1" H 7415 1396 50  0000 L CNN
F 1 "100n" H 7415 1305 50  0000 L CNN
F 2 "" H 7338 1200 50  0001 C CNN
F 3 "~" H 7300 1350 50  0001 C CNN
	1    7300 1350
	0    -1   -1   0   
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 611F233A
P 5000 1800
F 0 "BT1" H 5118 1896 50  0000 L CNN
F 1 "Battery_Cell" H 5118 1805 50  0000 L CNN
F 2 "" V 5000 1860 50  0001 C CNN
F 3 "~" V 5000 1860 50  0001 C CNN
	1    5000 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0109
U 1 1 611F308A
P 5000 1600
F 0 "#PWR0109" H 5000 1450 50  0001 C CNN
F 1 "+BATT" H 5015 1773 50  0000 C CNN
F 2 "" H 5000 1600 50  0001 C CNN
F 3 "" H 5000 1600 50  0001 C CNN
	1    5000 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 611F3827
P 5000 1900
F 0 "#PWR0110" H 5000 1650 50  0001 C CNN
F 1 "GND" H 5005 1727 50  0000 C CNN
F 2 "" H 5000 1900 50  0001 C CNN
F 3 "" H 5000 1900 50  0001 C CNN
	1    5000 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 1100 1600 1100
$Comp
L power:+5V #PWR0111
U 1 1 611ED4CB
P 1700 1100
F 0 "#PWR0111" H 1700 950 50  0001 C CNN
F 1 "+5V" V 1715 1228 50  0000 L CNN
F 2 "" H 1700 1100 50  0001 C CNN
F 3 "" H 1700 1100 50  0001 C CNN
	1    1700 1100
	0    1    1    0   
$EndComp
Connection ~ 1250 1700
Wire Wire Line
	1300 1700 1250 1700
Wire Wire Line
	1250 1700 1200 1700
Wire Wire Line
	1250 1850 1250 1700
$Comp
L power:GND #PWR0112
U 1 1 611ED4D9
P 1250 1850
F 0 "#PWR0112" H 1250 1600 50  0001 C CNN
F 1 "GND" H 1255 1677 50  0000 C CNN
F 2 "" H 1250 1850 50  0001 C CNN
F 3 "" H 1250 1850 50  0001 C CNN
	1    1250 1850
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J1
U 1 1 611ED4E3
P 1300 1300
F 0 "J1" H 1357 1767 50  0000 C CNN
F 1 "USB_B_Micro" H 1357 1676 50  0000 C CNN
F 2 "" H 1450 1250 50  0001 C CNN
F 3 "~" H 1450 1250 50  0001 C CNN
	1    1300 1300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0113
U 1 1 60FF7A20
P 2000 3200
F 0 "#PWR0113" H 2000 3050 50  0001 C CNN
F 1 "+5V" H 2015 3373 50  0000 C CNN
F 2 "" H 2000 3200 50  0001 C CNN
F 3 "" H 2000 3200 50  0001 C CNN
	1    2000 3200
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 61255740
P 2000 3350
F 0 "R6" H 2070 3396 50  0000 L CNN
F 1 "47k" H 2070 3305 50  0000 L CNN
F 2 "" V 1930 3350 50  0001 C CNN
F 3 "~" H 2000 3350 50  0001 C CNN
	1    2000 3350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1500 4750 1500 4350
Connection ~ 1500 4750
Wire Wire Line
	1500 4350 1500 3950
Connection ~ 1500 4350
Wire Wire Line
	1500 4950 1500 4750
Connection ~ 2000 3950
Wire Wire Line
	2000 4000 2000 3950
Wire Wire Line
	2000 4750 2000 4700
Wire Wire Line
	2000 4350 2000 4300
Connection ~ 2000 4350
Wire Wire Line
	2000 4400 2000 4350
Wire Wire Line
	1900 3950 2000 3950
$Comp
L Switch:SW_Push SW1
U 1 1 61255347
P 1700 3950
F 0 "SW1" H 1700 4235 50  0000 C CNN
F 1 "SW_Push" H 1700 4144 50  0000 C CNN
F 2 "" H 1700 4150 50  0001 C CNN
F 3 "~" H 1700 4150 50  0001 C CNN
	1    1700 3950
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 60FE618D
P 2000 4550
F 0 "R9" H 2070 4596 50  0000 L CNN
F 1 "68k" H 2070 4505 50  0000 L CNN
F 2 "" V 1930 4550 50  0001 C CNN
F 3 "~" H 2000 4550 50  0001 C CNN
	1    2000 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 60FE5BF1
P 2000 4150
F 0 "R8" H 2070 4196 50  0000 L CNN
F 1 "24k" H 2070 4105 50  0000 L CNN
F 2 "" V 1930 4150 50  0001 C CNN
F 3 "~" H 2000 4150 50  0001 C CNN
	1    2000 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 60FF8242
P 1500 4950
F 0 "#PWR0114" H 1500 4700 50  0001 C CNN
F 1 "GND" H 1505 4777 50  0000 C CNN
F 2 "" H 1500 4950 50  0001 C CNN
F 3 "" H 1500 4950 50  0001 C CNN
	1    1500 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 4750 2000 4750
Wire Wire Line
	1900 4350 2000 4350
$Comp
L Switch:SW_Push SW2
U 1 1 60FEEB8A
P 1700 4350
F 0 "SW2" H 1700 4635 50  0000 C CNN
F 1 "SW_Push" H 1700 4544 50  0000 C CNN
F 2 "" H 1700 4550 50  0001 C CNN
F 3 "~" H 1700 4550 50  0001 C CNN
	1    1700 4350
	-1   0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 60FEF24C
P 1700 4750
F 0 "SW3" H 1700 5035 50  0000 C CNN
F 1 "SW_Push" H 1700 4944 50  0000 C CNN
F 2 "" H 1700 4950 50  0001 C CNN
F 3 "~" H 1700 4950 50  0001 C CNN
	1    1700 4750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9550 4550 10450 4550
Wire Wire Line
	10300 5050 10450 5050
Wire Wire Line
	10450 5050 10450 4850
Connection ~ 10300 5050
Wire Wire Line
	10150 5050 10300 5050
Wire Wire Line
	9550 4750 10150 4750
$Comp
L power:+5V #PWR0115
U 1 1 6124670E
P 10300 5050
F 0 "#PWR0115" H 10300 4900 50  0001 C CNN
F 1 "+5V" H 10315 5223 50  0000 C CNN
F 2 "" H 10300 5050 50  0001 C CNN
F 3 "" H 10300 5050 50  0001 C CNN
	1    10300 5050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 6123D27B
P 10150 4900
F 0 "R5" H 10220 4946 50  0000 L CNN
F 1 "4.7k" H 10220 4855 50  0000 L CNN
F 2 "" V 10080 4900 50  0001 C CNN
F 3 "~" H 10150 4900 50  0001 C CNN
	1    10150 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 6123AC0B
P 10450 4700
F 0 "R3" H 10520 4746 50  0000 L CNN
F 1 "4.7k" H 10520 4655 50  0000 L CNN
F 2 "" V 10380 4700 50  0001 C CNN
F 3 "~" H 10450 4700 50  0001 C CNN
	1    10450 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 3800 8950 3850
Connection ~ 8950 3800
Wire Wire Line
	8950 3800 8750 3800
Wire Wire Line
	8950 3750 8950 3800
$Comp
L Device:C C4
U 1 1 611F4277
P 8600 3800
F 0 "C4" H 8715 3846 50  0000 L CNN
F 1 "100n" H 8715 3755 50  0000 L CNN
F 2 "" H 8638 3650 50  0001 C CNN
F 3 "~" H 8600 3800 50  0001 C CNN
	1    8600 3800
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 611F426D
P 8400 3800
F 0 "#PWR0116" H 8400 3550 50  0001 C CNN
F 1 "GND" H 8405 3627 50  0000 C CNN
F 2 "" H 8400 3800 50  0001 C CNN
F 3 "" H 8400 3800 50  0001 C CNN
	1    8400 3800
	0    1    1    0   
$EndComp
Wire Wire Line
	8450 3800 8400 3800
Text Label 9950 4550 2    50   ~ 0
scl
Text Label 9950 4750 2    50   ~ 0
sda
Text Label 10250 4350 2    50   ~ 0
row1
Text Label 10250 4150 2    50   ~ 0
row3
Text Label 10250 4250 2    50   ~ 0
row2
Text Label 10250 4450 2    50   ~ 0
row0
Wire Wire Line
	9550 4350 10250 4350
Wire Wire Line
	9550 4150 10250 4150
Wire Wire Line
	9550 4250 10250 4250
Wire Wire Line
	9550 4450 10250 4450
Wire Wire Line
	8950 5750 8950 5650
$Comp
L power:GND #PWR0117
U 1 1 60FC90E2
P 8950 5750
F 0 "#PWR0117" H 8950 5500 50  0001 C CNN
F 1 "GND" H 8955 5577 50  0000 C CNN
F 2 "" H 8950 5750 50  0001 C CNN
F 3 "" H 8950 5750 50  0001 C CNN
	1    8950 5750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0118
U 1 1 60FC7D65
P 8950 3750
F 0 "#PWR0118" H 8950 3600 50  0001 C CNN
F 1 "+5V" H 8965 3923 50  0000 C CNN
F 2 "" H 8950 3750 50  0001 C CNN
F 3 "" H 8950 3750 50  0001 C CNN
	1    8950 3750
	1    0    0    -1  
$EndComp
$Comp
L MCU_Microchip_ATtiny:ATtiny84V-10PU U2
U 1 1 60FA63B0
P 8950 4750
F 0 "U2" H 8420 4796 50  0000 R CNN
F 1 "ATtiny84V-10PU" H 8420 4705 50  0000 R CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 8950 4750 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/doc8006.pdf" H 8950 4750 50  0001 C CNN
	1    8950 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 3800 2000 3950
Wire Wire Line
	2000 3500 2000 3800
Connection ~ 2000 3800
Wire Wire Line
	2000 3800 2350 3800
Text Label 2350 3800 2    50   ~ 0
sw
$Comp
L Device:R R2
U 1 1 6184C83E
P 6250 3450
F 0 "R2" V 6043 3450 50  0000 C CNN
F 1 "82" V 6134 3450 50  0000 C CNN
F 2 "" V 6180 3450 50  0001 C CNN
F 3 "~" H 6250 3450 50  0001 C CNN
	1    6250 3450
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 6184C848
P 6250 2950
F 0 "R1" V 6043 2950 50  0000 C CNN
F 1 "82" V 6134 2950 50  0000 C CNN
F 2 "" V 6180 2950 50  0001 C CNN
F 3 "~" H 6250 2950 50  0001 C CNN
	1    6250 2950
	0    1    1    0   
$EndComp
Text Label 5400 5250 1    50   ~ 0
col23
Text Label 4500 5250 1    50   ~ 0
col01
Wire Wire Line
	5400 4900 5400 5250
Wire Wire Line
	4500 4900 4500 5250
Text Label 6400 3450 0    50   ~ 0
row1
Connection ~ 5650 3750
Wire Wire Line
	5400 3750 5650 3750
Wire Wire Line
	5650 4250 5650 3750
Connection ~ 5650 4250
Wire Wire Line
	5400 4250 5650 4250
Wire Wire Line
	5650 4750 5650 4250
Wire Wire Line
	5400 4750 5650 4750
Wire Wire Line
	5200 4750 5200 4250
Wire Wire Line
	4950 4750 5200 4750
Wire Wire Line
	5200 4250 5200 3750
Connection ~ 5200 4250
Wire Wire Line
	4950 4250 5200 4250
Wire Wire Line
	5200 3750 5200 3250
Connection ~ 5200 3750
Wire Wire Line
	4950 3750 5200 3750
Wire Wire Line
	4750 3750 4750 3250
Connection ~ 4750 3750
Wire Wire Line
	4500 3750 4750 3750
Wire Wire Line
	4750 4250 4750 3750
Connection ~ 4750 4250
Wire Wire Line
	4500 4250 4750 4250
Wire Wire Line
	4750 4750 4750 4250
Wire Wire Line
	4500 4750 4750 4750
Wire Wire Line
	4300 4750 4300 4250
Wire Wire Line
	4050 4750 4300 4750
Wire Wire Line
	4300 4250 4300 3750
Connection ~ 4300 4250
Wire Wire Line
	4050 4250 4300 4250
Wire Wire Line
	4300 3750 4300 3250
Connection ~ 4300 3750
Wire Wire Line
	4050 3750 4300 3750
Wire Wire Line
	5650 3250 5400 3250
Wire Wire Line
	5200 3250 4950 3250
Wire Wire Line
	4750 3250 4500 3250
Wire Wire Line
	4300 3250 4050 3250
$Comp
L Device:LED D16
U 1 1 6184C89C
P 5400 4600
F 0 "D16" V 5439 4482 50  0000 R CNN
F 1 "LED" V 5348 4482 50  0000 R CNN
F 2 "" H 5400 4600 50  0001 C CNN
F 3 "~" H 5400 4600 50  0001 C CNN
	1    5400 4600
	0    1    1    0   
$EndComp
$Comp
L Device:LED D15
U 1 1 6184C8A6
P 4950 4600
F 0 "D15" V 4989 4482 50  0000 R CNN
F 1 "LED" V 4898 4482 50  0000 R CNN
F 2 "" H 4950 4600 50  0001 C CNN
F 3 "~" H 4950 4600 50  0001 C CNN
	1    4950 4600
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D14
U 1 1 6184C8B0
P 4500 4600
F 0 "D14" V 4539 4482 50  0000 R CNN
F 1 "LED" V 4448 4482 50  0000 R CNN
F 2 "" H 4500 4600 50  0001 C CNN
F 3 "~" H 4500 4600 50  0001 C CNN
	1    4500 4600
	0    1    1    0   
$EndComp
$Comp
L Device:LED D13
U 1 1 6184C8BA
P 4050 4600
F 0 "D13" V 4089 4482 50  0000 R CNN
F 1 "LED" V 3998 4482 50  0000 R CNN
F 2 "" H 4050 4600 50  0001 C CNN
F 3 "~" H 4050 4600 50  0001 C CNN
	1    4050 4600
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D12
U 1 1 6184C8C4
P 5400 4100
F 0 "D12" V 5439 3982 50  0000 R CNN
F 1 "LED" V 5348 3982 50  0000 R CNN
F 2 "" H 5400 4100 50  0001 C CNN
F 3 "~" H 5400 4100 50  0001 C CNN
	1    5400 4100
	0    1    1    0   
$EndComp
$Comp
L Device:LED D11
U 1 1 6184C8CE
P 4950 4100
F 0 "D11" V 4989 3982 50  0000 R CNN
F 1 "LED" V 4898 3982 50  0000 R CNN
F 2 "" H 4950 4100 50  0001 C CNN
F 3 "~" H 4950 4100 50  0001 C CNN
	1    4950 4100
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D10
U 1 1 6184C8D8
P 4500 4100
F 0 "D10" V 4539 3982 50  0000 R CNN
F 1 "LED" V 4448 3982 50  0000 R CNN
F 2 "" H 4500 4100 50  0001 C CNN
F 3 "~" H 4500 4100 50  0001 C CNN
	1    4500 4100
	0    1    1    0   
$EndComp
$Comp
L Device:LED D9
U 1 1 6184C8E2
P 4050 4100
F 0 "D9" V 4089 3982 50  0000 R CNN
F 1 "LED" V 3998 3982 50  0000 R CNN
F 2 "" H 4050 4100 50  0001 C CNN
F 3 "~" H 4050 4100 50  0001 C CNN
	1    4050 4100
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D8
U 1 1 6184C8EC
P 5400 3600
F 0 "D8" V 5439 3482 50  0000 R CNN
F 1 "LED" V 5348 3482 50  0000 R CNN
F 2 "" H 5400 3600 50  0001 C CNN
F 3 "~" H 5400 3600 50  0001 C CNN
	1    5400 3600
	0    1    1    0   
$EndComp
$Comp
L Device:LED D6
U 1 1 6184C8F6
P 4500 3600
F 0 "D6" V 4539 3482 50  0000 R CNN
F 1 "LED" V 4448 3482 50  0000 R CNN
F 2 "" H 4500 3600 50  0001 C CNN
F 3 "~" H 4500 3600 50  0001 C CNN
	1    4500 3600
	0    1    1    0   
$EndComp
$Comp
L Device:LED D5
U 1 1 6184C900
P 4050 3600
F 0 "D5" V 4089 3482 50  0000 R CNN
F 1 "LED" V 3998 3482 50  0000 R CNN
F 2 "" H 4050 3600 50  0001 C CNN
F 3 "~" H 4050 3600 50  0001 C CNN
	1    4050 3600
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D4
U 1 1 6184C90A
P 5400 3100
F 0 "D4" V 5439 2982 50  0000 R CNN
F 1 "LED" V 5348 2982 50  0000 R CNN
F 2 "" H 5400 3100 50  0001 C CNN
F 3 "~" H 5400 3100 50  0001 C CNN
	1    5400 3100
	0    1    1    0   
$EndComp
$Comp
L Device:LED D2
U 1 1 6184C914
P 4500 3100
F 0 "D2" V 4539 2982 50  0000 R CNN
F 1 "LED" V 4448 2982 50  0000 R CNN
F 2 "" H 4500 3100 50  0001 C CNN
F 3 "~" H 4500 3100 50  0001 C CNN
	1    4500 3100
	0    1    1    0   
$EndComp
Text Label 6400 2950 0    50   ~ 0
row0
Text Label 6400 3950 0    50   ~ 0
row2
Text Label 6400 4450 0    50   ~ 0
row3
$Comp
L Device:LED D7
U 1 1 6184C921
P 4950 3600
F 0 "D7" V 4989 3482 50  0000 R CNN
F 1 "LED" V 4898 3482 50  0000 R CNN
F 2 "" H 4950 3600 50  0001 C CNN
F 3 "~" H 4950 3600 50  0001 C CNN
	1    4950 3600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5650 3750 5650 3250
$Comp
L Device:LED D3
U 1 1 6184C92D
P 4950 3100
F 0 "D3" V 4989 2982 50  0000 R CNN
F 1 "LED" V 4898 2982 50  0000 R CNN
F 2 "" H 4950 3100 50  0001 C CNN
F 3 "~" H 4950 3100 50  0001 C CNN
	1    4950 3100
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D1
U 1 1 6184C938
P 4050 3100
F 0 "D1" V 4089 2982 50  0000 R CNN
F 1 "LED" V 3998 2982 50  0000 R CNN
F 2 "" H 4050 3100 50  0001 C CNN
F 3 "~" H 4050 3100 50  0001 C CNN
	1    4050 3100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5650 4750 5650 4900
Connection ~ 5650 4750
Wire Wire Line
	5200 4900 5200 4750
Connection ~ 5200 4750
Wire Wire Line
	4300 4750 4300 4900
Wire Wire Line
	4300 4900 4500 4900
Connection ~ 4300 4750
Wire Wire Line
	4750 4900 4750 4750
Connection ~ 4750 4750
Connection ~ 4500 4900
Connection ~ 5400 4900
Wire Wire Line
	5400 4900 5200 4900
Wire Wire Line
	5400 4900 5650 4900
$Comp
L Device:R R4
U 1 1 6184C834
P 6250 3950
F 0 "R4" V 6043 3950 50  0000 C CNN
F 1 "82" V 6134 3950 50  0000 C CNN
F 2 "" V 6180 3950 50  0001 C CNN
F 3 "~" H 6250 3950 50  0001 C CNN
	1    6250 3950
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 6184C2B8
P 6250 4450
F 0 "R7" V 6043 4450 50  0000 C CNN
F 1 "82" V 6134 4450 50  0000 C CNN
F 2 "" V 6180 4450 50  0001 C CNN
F 3 "~" H 6250 4450 50  0001 C CNN
	1    6250 4450
	0    1    1    0   
$EndComp
Wire Wire Line
	4500 4900 4750 4900
Wire Wire Line
	9550 5050 9900 5050
Wire Wire Line
	9550 5150 9900 5150
Text Label 9900 5050 2    50   ~ 0
col01
Text Label 9900 5150 2    50   ~ 0
col23
Text Label 9900 4650 2    50   ~ 0
sw
Wire Wire Line
	9900 4650 9550 4650
Connection ~ 4950 2950
Connection ~ 4950 3450
Connection ~ 4950 3950
Connection ~ 4950 4450
Wire Wire Line
	4050 2950 4500 2950
Connection ~ 4500 2950
Wire Wire Line
	4500 2950 4950 2950
Wire Wire Line
	4050 3450 4500 3450
Connection ~ 4500 3450
Wire Wire Line
	4500 3450 4950 3450
Wire Wire Line
	4050 3950 4500 3950
Connection ~ 4500 3950
Wire Wire Line
	4500 3950 4950 3950
Wire Wire Line
	4050 4450 4500 4450
Connection ~ 4500 4450
Wire Wire Line
	4500 4450 4950 4450
Wire Wire Line
	4950 4450 5400 4450
Connection ~ 5400 4450
Wire Wire Line
	5400 4450 6100 4450
Wire Wire Line
	4950 3950 5400 3950
Connection ~ 5400 3950
Wire Wire Line
	5400 3950 6100 3950
Wire Wire Line
	4950 3450 5400 3450
Connection ~ 5400 3450
Wire Wire Line
	5400 3450 6100 3450
Wire Wire Line
	4950 2950 5400 2950
Connection ~ 5400 2950
Wire Wire Line
	5400 2950 6100 2950
Text Label 10000 4850 2    50   ~ 0
photodiode
Wire Wire Line
	10000 4850 9550 4850
$Comp
L Device:D_Photo D?
U 1 1 6183A88B
P 1500 6200
F 0 "D?" V 1404 6358 50  0000 L CNN
F 1 "D_Photo" V 1495 6358 50  0000 L CNN
F 2 "" H 1450 6200 50  0001 C CNN
F 3 "~" H 1450 6200 50  0001 C CNN
	1    1500 6200
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 6183B33F
P 1500 6650
F 0 "R?" H 1570 6696 50  0000 L CNN
F 1 "10k" H 1570 6605 50  0000 L CNN
F 2 "" V 1430 6650 50  0001 C CNN
F 3 "~" H 1500 6650 50  0001 C CNN
	1    1500 6650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 6183B9C2
P 1500 5850
F 0 "#PWR?" H 1500 5700 50  0001 C CNN
F 1 "+5V" H 1515 6023 50  0000 C CNN
F 2 "" H 1500 5850 50  0001 C CNN
F 3 "" H 1500 5850 50  0001 C CNN
	1    1500 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6183CB50
P 1500 7000
F 0 "#PWR?" H 1500 6750 50  0001 C CNN
F 1 "GND" H 1505 6827 50  0000 C CNN
F 2 "" H 1500 7000 50  0001 C CNN
F 3 "" H 1500 7000 50  0001 C CNN
	1    1500 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 7000 1500 6800
Wire Wire Line
	1500 6500 1500 6400
Wire Wire Line
	1500 6000 1500 5850
Wire Wire Line
	1500 6400 2050 6400
Connection ~ 1500 6400
Wire Wire Line
	1500 6400 1500 6300
Text Label 2050 6400 2    50   ~ 0
photodiode
Wire Wire Line
	6850 1900 7250 1900
Text Label 6850 1900 0    50   ~ 0
mfp
$EndSCHEMATC
