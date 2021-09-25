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
L Switch:SW_Push_LED SW1
U 1 1 620FDEBB
P 2600 2900
F 0 "SW1" H 2600 3285 50  0000 C CNN
F 1 "SW_Push_LED" H 2600 3194 50  0000 C CNN
F 2 "duck:tactile-push-button-illuminated_ILS_TA180" H 2600 3200 50  0001 C CNN
F 3 "~" H 2600 3200 50  0001 C CNN
	1    2600 2900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_LED SW2
U 1 1 62100CE4
P 2600 3450
F 0 "SW2" H 2600 3835 50  0000 C CNN
F 1 "SW_Push_LED" H 2600 3744 50  0000 C CNN
F 2 "duck:tactile-push-button-illuminated_ILS_TA180" H 2600 3750 50  0001 C CNN
F 3 "~" H 2600 3750 50  0001 C CNN
	1    2600 3450
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_LED SW3
U 1 1 62101711
P 2600 4000
F 0 "SW3" H 2600 4385 50  0000 C CNN
F 1 "SW_Push_LED" H 2600 4294 50  0000 C CNN
F 2 "duck:tactile-push-button-illuminated_ILS_TA180" H 2600 4300 50  0001 C CNN
F 3 "~" H 2600 4300 50  0001 C CNN
	1    2600 4000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_LED SW4
U 1 1 62101793
P 2600 4550
F 0 "SW4" H 2600 4935 50  0000 C CNN
F 1 "SW_Push_LED" H 2600 4844 50  0000 C CNN
F 2 "duck:tactile-push-button-illuminated_ILS_TA180" H 2600 4850 50  0001 C CNN
F 3 "~" H 2600 4850 50  0001 C CNN
	1    2600 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 621054E8
P 2250 4750
F 0 "#PWR0101" H 2250 4500 50  0001 C CNN
F 1 "GND" H 2255 4577 50  0000 C CNN
F 2 "" H 2250 4750 50  0001 C CNN
F 3 "" H 2250 4750 50  0001 C CNN
	1    2250 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 4750 2250 4550
Wire Wire Line
	2400 2900 2250 2900
Wire Wire Line
	2400 3450 2250 3450
Connection ~ 2250 3450
Wire Wire Line
	2400 4000 2250 4000
Connection ~ 2250 4000
Wire Wire Line
	2400 4550 2250 4550
Connection ~ 2250 4550
$Comp
L Mechanical:MountingHole H1
U 1 1 62106C73
P 2600 5050
F 0 "H1" H 2700 5096 50  0000 L CNN
F 1 "MountingHole" H 2700 5005 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 2600 5050 50  0001 C CNN
F 3 "~" H 2600 5050 50  0001 C CNN
	1    2600 5050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 6210711C
P 2600 5350
F 0 "H2" H 2700 5396 50  0000 L CNN
F 1 "MountingHole" H 2700 5305 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 2600 5350 50  0001 C CNN
F 3 "~" H 2600 5350 50  0001 C CNN
	1    2600 5350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 620FFCF4
P 3100 2900
F 0 "R1" V 2893 2900 50  0000 C CNN
F 1 "LED" V 2984 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3030 2900 50  0001 C CNN
F 3 "~" H 3100 2900 50  0001 C CNN
	1    3100 2900
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 6210D083
P 3500 2800
F 0 "R5" V 3293 2800 50  0000 C CNN
F 1 "22k" V 3384 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3430 2800 50  0001 C CNN
F 3 "~" H 3500 2800 50  0001 C CNN
	1    3500 2800
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 6210DCA0
P 3100 3450
F 0 "R2" V 2893 3450 50  0000 C CNN
F 1 "LED" V 2984 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3030 3450 50  0001 C CNN
F 3 "~" H 3100 3450 50  0001 C CNN
	1    3100 3450
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 6210DD6E
P 3500 3350
F 0 "R6" V 3293 3350 50  0000 C CNN
F 1 "10k" V 3384 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3430 3350 50  0001 C CNN
F 3 "~" H 3500 3350 50  0001 C CNN
	1    3500 3350
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 6210F6F1
P 3100 4000
F 0 "R3" V 2893 4000 50  0000 C CNN
F 1 "LED" V 2984 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3030 4000 50  0001 C CNN
F 3 "~" H 3100 4000 50  0001 C CNN
	1    3100 4000
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 6210F7D7
P 3500 3900
F 0 "R7" V 3293 3900 50  0000 C CNN
F 1 "4.7k" V 3384 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3430 3900 50  0001 C CNN
F 3 "~" H 3500 3900 50  0001 C CNN
	1    3500 3900
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 6210F7E1
P 3100 4550
F 0 "R4" V 2893 4550 50  0000 C CNN
F 1 "LED" V 2984 4550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3030 4550 50  0001 C CNN
F 3 "~" H 3100 4550 50  0001 C CNN
	1    3100 4550
	0    1    1    0   
$EndComp
$Comp
L Device:R R8
U 1 1 6210F7EB
P 3500 4450
F 0 "R8" V 3293 4450 50  0000 C CNN
F 1 "1.8k" V 3384 4450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3430 4450 50  0001 C CNN
F 3 "~" H 3500 4450 50  0001 C CNN
	1    3500 4450
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J1
U 1 1 6211274E
P 5200 3550
F 0 "J1" H 5280 3542 50  0000 L CNN
F 1 "Conn_01x08" H 5280 3451 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 5200 3550 50  0001 C CNN
F 3 "~" H 5200 3550 50  0001 C CNN
	1    5200 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 62113103
P 4900 4100
F 0 "#PWR0102" H 4900 3850 50  0001 C CNN
F 1 "GND" H 4905 3927 50  0000 C CNN
F 2 "" H 4900 4100 50  0001 C CNN
F 3 "" H 4900 4100 50  0001 C CNN
	1    4900 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 4100 4900 3950
Wire Wire Line
	4900 3950 5000 3950
Wire Wire Line
	2950 4000 2800 4000
Wire Wire Line
	2800 4550 2950 4550
Wire Wire Line
	2800 3450 2950 3450
Wire Wire Line
	2950 2900 2800 2900
Wire Wire Line
	2800 4450 3350 4450
Wire Wire Line
	3350 3900 2800 3900
Wire Wire Line
	2800 3350 3350 3350
Wire Wire Line
	3350 2800 2800 2800
Wire Wire Line
	3650 4450 3750 4450
Wire Wire Line
	3750 4450 3750 3900
Wire Wire Line
	3750 2800 3650 2800
Wire Wire Line
	3650 3350 3750 3350
Connection ~ 3750 3350
Wire Wire Line
	3750 3350 3750 2800
Wire Wire Line
	3650 3900 3750 3900
Connection ~ 3750 3900
Wire Wire Line
	3750 3900 3750 3350
$Comp
L Device:R R9
U 1 1 62119773
P 3750 2550
F 0 "R9" H 3680 2504 50  0000 R CNN
F 1 "10k" H 3680 2595 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3680 2550 50  0001 C CNN
F 3 "~" H 3750 2550 50  0001 C CNN
	1    3750 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	3750 2700 3750 2800
Connection ~ 3750 2800
Wire Wire Line
	5000 3250 4900 3250
Wire Wire Line
	4900 3250 4900 2300
Wire Wire Line
	4900 2300 3750 2300
Wire Wire Line
	3750 2300 3750 2400
Wire Wire Line
	3750 3350 5000 3350
Wire Wire Line
	3250 2900 4400 2900
Wire Wire Line
	4400 2900 4400 3550
Wire Wire Line
	4400 3550 5000 3550
Wire Wire Line
	5000 3650 4250 3650
Wire Wire Line
	4250 3650 4250 3450
Wire Wire Line
	4250 3450 3250 3450
Wire Wire Line
	3250 4000 4250 4000
Wire Wire Line
	4250 4000 4250 3750
Wire Wire Line
	4250 3750 5000 3750
Wire Wire Line
	5000 3850 4400 3850
Wire Wire Line
	4400 3850 4400 4550
Wire Wire Line
	4400 4550 3250 4550
$Comp
L power:GNDA #PWR?
U 1 1 62132A8A
P 1950 4750
F 0 "#PWR?" H 1950 4500 50  0001 C CNN
F 1 "GNDA" H 1955 4577 50  0000 C CNN
F 2 "" H 1950 4750 50  0001 C CNN
F 3 "" H 1950 4750 50  0001 C CNN
	1    1950 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 4000 2250 4550
Wire Wire Line
	2250 3450 2250 4000
Wire Wire Line
	2250 2900 2250 3450
Wire Wire Line
	1950 2800 2400 2800
Wire Wire Line
	1950 2800 1950 3350
Wire Wire Line
	2400 4450 1950 4450
Connection ~ 1950 4450
Wire Wire Line
	1950 4450 1950 4750
Wire Wire Line
	2400 3900 1950 3900
Connection ~ 1950 3900
Wire Wire Line
	1950 3900 1950 4450
Wire Wire Line
	2400 3350 1950 3350
Connection ~ 1950 3350
Wire Wire Line
	1950 3350 1950 3900
$Comp
L power:GNDA #PWR?
U 1 1 6213F6CA
P 4650 4100
F 0 "#PWR?" H 4650 3850 50  0001 C CNN
F 1 "GNDA" H 4655 3927 50  0000 C CNN
F 2 "" H 4650 4100 50  0001 C CNN
F 3 "" H 4650 4100 50  0001 C CNN
	1    4650 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 4100 4650 3450
Wire Wire Line
	4650 3450 5000 3450
Text Notes 3700 5350 0    50   ~ 0
Resistors for LEDS at 5V\nBlue: 1k\nRed: 680\nYellow/Green: 120
$EndSCHEMATC