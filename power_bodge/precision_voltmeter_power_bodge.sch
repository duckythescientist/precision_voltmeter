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
L duck:TPS71501__SC70 U1
U 1 1 61527D78
P 3600 3700
F 0 "U1" H 3600 3942 50  0000 C CNN
F 1 "TPS71501__SC70" H 3600 3851 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-353_SC-70-5" H 3600 3925 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps715.pdf" H 3300 4500 50  0001 C CNN
	1    3600 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 615281E5
P 3000 4050
F 0 "C1" H 3115 4096 50  0000 L CNN
F 1 "100n" H 3115 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3038 3900 50  0001 C CNN
F 3 "~" H 3000 4050 50  0001 C CNN
	1    3000 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C4
U 1 1 6152854F
P 5450 4050
F 0 "C4" H 5568 4096 50  0000 L CNN
F 1 "10u" H 5568 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5488 3900 50  0001 C CNN
F 3 "~" H 5450 4050 50  0001 C CNN
	1    5450 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 61528FB4
P 4950 4050
F 0 "C3" H 5065 4096 50  0000 L CNN
F 1 "100n" H 5065 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 4988 3900 50  0001 C CNN
F 3 "~" H 4950 4050 50  0001 C CNN
	1    4950 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 6152931D
P 4600 4300
F 0 "C2" H 4715 4346 50  0000 L CNN
F 1 "10n" H 4715 4255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 4638 4150 50  0001 C CNN
F 3 "~" H 4600 4300 50  0001 C CNN
	1    4600 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 615295EA
P 4200 3900
F 0 "R1" H 4270 3946 50  0000 L CNN
F 1 "2.2Meg" H 4270 3855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4130 3900 50  0001 C CNN
F 3 "~" H 4200 3900 50  0001 C CNN
	1    4200 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 615299BF
P 4200 4300
F 0 "R2" H 4270 4346 50  0000 L CNN
F 1 "470k" H 4270 4255 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4130 4300 50  0001 C CNN
F 3 "~" H 4200 4300 50  0001 C CNN
	1    4200 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 61529CE1
P 3600 4550
F 0 "#PWR0101" H 3600 4300 50  0001 C CNN
F 1 "GND" H 3605 4377 50  0000 C CNN
F 2 "" H 3600 4550 50  0001 C CNN
F 3 "" H 3600 4550 50  0001 C CNN
	1    3600 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 4550 3600 4500
Wire Wire Line
	4200 3700 4200 3750
Wire Wire Line
	3900 3700 4200 3700
Wire Wire Line
	4200 4050 4200 4100
Wire Wire Line
	4200 4100 4000 4100
Wire Wire Line
	4000 4100 4000 3850
Wire Wire Line
	4000 3850 3900 3850
Connection ~ 4200 4100
Wire Wire Line
	4200 4100 4200 4150
Wire Wire Line
	4200 4100 4600 4100
Wire Wire Line
	4600 4100 4600 4150
Wire Wire Line
	4600 4450 4600 4500
Wire Wire Line
	4600 4500 4200 4500
Wire Wire Line
	4200 4500 4200 4450
Wire Wire Line
	3000 3900 3000 3700
Wire Wire Line
	3000 3700 3300 3700
Wire Wire Line
	3000 4200 3000 4500
Wire Wire Line
	3000 4500 3600 4500
Connection ~ 3600 4500
Wire Wire Line
	3600 4500 3600 4000
Wire Wire Line
	3600 4500 4200 4500
Connection ~ 4200 4500
Wire Wire Line
	4950 4200 4950 4500
Wire Wire Line
	4950 4500 4600 4500
Connection ~ 4600 4500
Wire Wire Line
	4950 3900 4950 3700
Wire Wire Line
	4950 3700 4650 3700
Connection ~ 4200 3700
Wire Wire Line
	4950 3700 5450 3700
Wire Wire Line
	5450 3700 5450 3900
Connection ~ 4950 3700
Wire Wire Line
	5450 4200 5450 4500
Wire Wire Line
	5450 4500 4950 4500
Connection ~ 4950 4500
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 6153456D
P 4150 2700
F 0 "J1" V 4114 2412 50  0000 R CNN
F 1 "Conn_01x04" V 4023 2412 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 4150 2700 50  0001 C CNN
F 3 "~" H 4150 2700 50  0001 C CNN
	1    4150 2700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 61536EA8
P 4200 3150
F 0 "#PWR0102" H 4200 2900 50  0001 C CNN
F 1 "GND" H 4205 2977 50  0000 C CNN
F 2 "" H 4200 3150 50  0001 C CNN
F 3 "" H 4200 3150 50  0001 C CNN
	1    4200 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2900 4150 3100
Wire Wire Line
	4150 3100 4200 3100
Wire Wire Line
	4200 3100 4200 3150
Wire Wire Line
	4350 2900 4350 3100
Wire Wire Line
	4350 3100 4200 3100
Connection ~ 4200 3100
Wire Wire Line
	4250 2900 4250 3000
Wire Wire Line
	4250 3000 4650 3000
Wire Wire Line
	4650 3000 4650 3700
Connection ~ 4650 3700
Wire Wire Line
	4650 3700 4200 3700
Wire Wire Line
	4050 2900 4050 3000
Wire Wire Line
	4050 3000 3000 3000
Wire Wire Line
	3000 3000 3000 3700
Connection ~ 3000 3700
Text Notes 4050 4800 0    50   ~ 0
1.205 * (1 + R1/R2) = Vout\n1.205 * (1 + 2.2Meg / 470k) = 6.85V\n
$EndSCHEMATC
