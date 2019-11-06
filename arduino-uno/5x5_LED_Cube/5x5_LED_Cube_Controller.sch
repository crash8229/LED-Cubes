EESchema Schematic File Version 4
LIBS:5x5_LED_Cube_Controller-cache
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 2
Title "5x5 LED Cube Controller"
Date "2019-11-03"
Rev "A1"
Comp ""
Comment1 "Power to be supplied by external module."
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	1700 4900 2000 4900
Wire Wire Line
	2000 4900 2000 3900
Wire Wire Line
	1700 5000 2100 5000
Wire Wire Line
	2100 5000 2100 4000
Wire Wire Line
	1700 5100 2200 5100
Wire Wire Line
	2200 5100 2200 3700
Wire Wire Line
	2200 3700 2300 3700
Wire Wire Line
	2100 4000 2500 4000
Wire Wire Line
	2000 3900 2400 3900
Wire Wire Line
	2300 3700 3700 3700
Connection ~ 2300 3700
Wire Wire Line
	2300 1500 2300 3700
Wire Wire Line
	3700 1500 2300 1500
Wire Wire Line
	2400 3900 3700 3900
Connection ~ 2400 3900
Wire Wire Line
	2400 1700 2400 3900
Wire Wire Line
	3700 1700 2400 1700
Wire Wire Line
	2500 4000 3700 4000
Connection ~ 2500 4000
Wire Wire Line
	2500 1800 2500 4000
Wire Wire Line
	3700 1800 2500 1800
Wire Wire Line
	2600 4700 3700 4700
Connection ~ 2600 4700
Wire Wire Line
	2600 2500 3700 2500
Wire Wire Line
	2600 4700 2600 2500
Wire Wire Line
	2700 4900 3700 4900
Wire Wire Line
	2700 2600 2700 4900
Wire Wire Line
	3700 2600 2700 2600
Wire Wire Line
	1700 4700 2600 4700
Wire Wire Line
	5800 4300 6250 4300
Connection ~ 5800 4300
Wire Wire Line
	5800 6550 5800 4300
Connection ~ 5700 4750
Wire Wire Line
	5700 6550 5700 4750
Connection ~ 5600 5200
Wire Wire Line
	5600 6550 5600 5200
Connection ~ 5500 5650
Wire Wire Line
	5500 6550 5500 5650
Connection ~ 5400 6100
Wire Wire Line
	5400 6550 5400 6100
Wire Wire Line
	6000 6400 5950 6400
Connection ~ 6000 6400
Wire Wire Line
	6000 6400 6000 6950
Wire Wire Line
	5400 6100 6250 6100
Wire Wire Line
	5400 4700 5400 6100
Wire Wire Line
	5100 4700 5400 4700
Wire Wire Line
	5500 5650 6250 5650
Wire Wire Line
	5500 4600 5500 5650
Wire Wire Line
	5100 4600 5500 4600
Wire Wire Line
	5600 5200 6250 5200
Wire Wire Line
	5600 4500 5600 5200
Wire Wire Line
	5100 4500 5600 4500
Wire Wire Line
	5700 4750 6250 4750
Wire Wire Line
	5700 4400 5700 4750
Wire Wire Line
	5100 4400 5700 4400
Wire Wire Line
	6050 6400 6000 6400
$Comp
L power:+5V #PWR014
U 1 1 5DC390C0
P 5950 6400
F 0 "#PWR014" H 5950 6250 50  0001 C CNN
F 1 "+5V" H 5965 6573 50  0000 C CNN
F 2 "" H 5950 6400 50  0001 C CNN
F 3 "" H 5950 6400 50  0001 C CNN
	1    5950 6400
	1    0    0    -1  
$EndComp
$Comp
L My_Library:DMG2305UX Q5
U 1 1 5DC390BA
P 6250 6300
F 0 "Q5" V 6200 6550 50  0000 L CNN
F 1 "DMG2305UX" V 6100 6400 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6450 6225 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/DMG2305UX.pdf" H 6250 6300 50  0001 L CNN
	1    6250 6300
	0    1    1    0   
$EndComp
Wire Wire Line
	6050 5950 5950 5950
$Comp
L power:+5V #PWR012
U 1 1 5DC35B0C
P 5950 5950
F 0 "#PWR012" H 5950 5800 50  0001 C CNN
F 1 "+5V" H 5965 6123 50  0000 C CNN
F 2 "" H 5950 5950 50  0001 C CNN
F 3 "" H 5950 5950 50  0001 C CNN
	1    5950 5950
	1    0    0    -1  
$EndComp
$Comp
L My_Library:DMG2305UX Q4
U 1 1 5DC35B06
P 6250 5850
F 0 "Q4" V 6200 6100 50  0000 L CNN
F 1 "DMG2305UX" V 6100 5950 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6450 5775 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/DMG2305UX.pdf" H 6250 5850 50  0001 L CNN
	1    6250 5850
	0    1    1    0   
$EndComp
Wire Wire Line
	6050 5500 5950 5500
$Comp
L power:+5V #PWR011
U 1 1 5DC3229A
P 5950 5500
F 0 "#PWR011" H 5950 5350 50  0001 C CNN
F 1 "+5V" H 5965 5673 50  0000 C CNN
F 2 "" H 5950 5500 50  0001 C CNN
F 3 "" H 5950 5500 50  0001 C CNN
	1    5950 5500
	1    0    0    -1  
$EndComp
$Comp
L My_Library:DMG2305UX Q3
U 1 1 5DC32294
P 6250 5400
F 0 "Q3" V 6200 5650 50  0000 L CNN
F 1 "DMG2305UX" V 6100 5500 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6450 5325 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/DMG2305UX.pdf" H 6250 5400 50  0001 L CNN
	1    6250 5400
	0    1    1    0   
$EndComp
Wire Wire Line
	6050 5050 5950 5050
$Comp
L power:+5V #PWR09
U 1 1 5DC30191
P 5950 5050
F 0 "#PWR09" H 5950 4900 50  0001 C CNN
F 1 "+5V" H 5965 5223 50  0000 C CNN
F 2 "" H 5950 5050 50  0001 C CNN
F 3 "" H 5950 5050 50  0001 C CNN
	1    5950 5050
	1    0    0    -1  
$EndComp
$Comp
L My_Library:DMG2305UX Q2
U 1 1 5DC3018B
P 6250 4950
F 0 "Q2" V 6200 5200 50  0000 L CNN
F 1 "DMG2305UX" V 6100 5050 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6450 4875 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/DMG2305UX.pdf" H 6250 4950 50  0001 L CNN
	1    6250 4950
	0    1    1    0   
$EndComp
Wire Wire Line
	6050 4600 5950 4600
$Comp
L power:+5V #PWR08
U 1 1 5DC23E48
P 5950 4600
F 0 "#PWR08" H 5950 4450 50  0001 C CNN
F 1 "+5V" H 5965 4773 50  0000 C CNN
F 2 "" H 5950 4600 50  0001 C CNN
F 3 "" H 5950 4600 50  0001 C CNN
	1    5950 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 4300 5800 4300
$Comp
L Device:R_Small_US R1
U 1 1 5DBED8D0
P 3400 1300
F 0 "R1" V 3500 1350 50  0000 L CNN
F 1 "2.7K" V 3500 1150 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" H 3400 1300 50  0001 C CNN
F 3 "https://www.newark.com/panasonic/erj-2gej272x/res-thick-film-2k7-5-0-1w-0402/dp/97W7160" H 3400 1300 50  0001 C CNN
	1    3400 1300
	0    1    1    0   
$EndComp
Wire Wire Line
	3700 1300 3500 1300
Wire Wire Line
	4400 900  4000 900 
Wire Wire Line
	4400 5200 4000 5200
$Comp
L power:GND #PWR010
U 1 1 5DC0990B
P 4000 5200
F 0 "#PWR010" H 4000 4950 50  0001 C CNN
F 1 "GND" H 4005 5027 50  0000 C CNN
F 2 "" H 4000 5200 50  0001 C CNN
F 3 "" H 4000 5200 50  0001 C CNN
	1    4000 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 5DC088D5
P 4000 900
F 0 "#PWR01" H 4000 750 50  0001 C CNN
F 1 "+5V" H 4015 1073 50  0000 C CNN
F 2 "" H 4000 900 50  0001 C CNN
F 3 "" H 4000 900 50  0001 C CNN
	1    4000 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 3100 4000 3100
Wire Wire Line
	4400 3000 4750 3000
$Comp
L power:GND #PWR03
U 1 1 5DC0729E
P 4750 3000
F 0 "#PWR03" H 4750 2750 50  0001 C CNN
F 1 "GND" H 4755 2827 50  0000 C CNN
F 2 "" H 4750 3000 50  0001 C CNN
F 3 "" H 4750 3000 50  0001 C CNN
	1    4750 3000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR04
U 1 1 5DC04361
P 4000 3100
F 0 "#PWR04" H 4000 2950 50  0001 C CNN
F 1 "+5V" H 4015 3273 50  0000 C CNN
F 2 "" H 4000 3100 50  0001 C CNN
F 3 "" H 4000 3100 50  0001 C CNN
	1    4000 3100
	1    0    0    -1  
$EndComp
$Comp
L Driver_LED:TLC5940NT U1
U 1 1 5DBE8911
P 4400 1900
F 0 "U1" H 4400 2950 50  0000 C CNN
F 1 "TLC5940NT" H 4400 3050 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 4450 925 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlc5940.pdf" H 4000 2600 50  0001 C CNN
	1    4400 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Network05_US RN1
U 1 1 5DBE7F7D
P 5600 6750
F 0 "RN1" H 5888 6796 50  0000 L CNN
F 1 "4.7K" H 5888 6705 50  0000 L CNN
F 2 "Resistor_THT:R_Array_SIP6" V 5975 6750 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 5600 6750 50  0001 C CNN
	1    5600 6750
	1    0    0    1   
$EndComp
$Comp
L My_Library:DMG2305UX Q1
U 1 1 5DBE6712
P 6250 4500
F 0 "Q1" V 6200 4750 50  0000 L CNN
F 1 "DMG2305UX" V 6100 4600 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6450 4425 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/DMG2305UX.pdf" H 6250 4500 50  0001 L CNN
	1    6250 4500
	0    1    1    0   
$EndComp
Connection ~ 4000 900 
Connection ~ 4000 3100
$Comp
L Driver_LED:TLC5940NT U2
U 1 1 5DBE9F69
P 4400 4100
F 0 "U2" H 4400 2800 50  0000 C CNN
F 1 "TLC5940NT" H 4400 2900 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 4450 3125 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlc5940.pdf" H 4000 4800 50  0001 C CNN
	1    4400 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 900  3600 1400
Wire Wire Line
	3600 1400 3700 1400
Wire Wire Line
	3600 900  4000 900 
Wire Wire Line
	3600 3100 3600 3600
Wire Wire Line
	3600 3600 3700 3600
Wire Wire Line
	3600 3100 4000 3100
$Comp
L power:GND #PWR02
U 1 1 5DD21A8D
P 3050 1200
F 0 "#PWR02" H 3050 950 50  0001 C CNN
F 1 "GND" H 3055 1027 50  0000 C CNN
F 2 "" H 3050 1200 50  0001 C CNN
F 3 "" H 3050 1200 50  0001 C CNN
	1    3050 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 1200 3200 1200
Wire Wire Line
	3300 1300 3200 1300
Wire Wire Line
	3200 1300 3200 1200
Connection ~ 3200 1200
Wire Wire Line
	3200 1200 3050 1200
$Comp
L Device:R_Small_US R2
U 1 1 5DD2D000
P 3400 3500
F 0 "R2" V 3500 3550 50  0000 L CNN
F 1 "2.7K" V 3500 3350 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" H 3400 3500 50  0001 C CNN
F 3 "https://www.newark.com/panasonic/erj-2gej272x/res-thick-film-2k7-5-0-1w-0402/dp/97W7160" H 3400 3500 50  0001 C CNN
	1    3400 3500
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5DD2D006
P 3050 3400
F 0 "#PWR05" H 3050 3150 50  0001 C CNN
F 1 "GND" H 3055 3227 50  0000 C CNN
F 2 "" H 3050 3400 50  0001 C CNN
F 3 "" H 3050 3400 50  0001 C CNN
	1    3050 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3400 3200 3400
Wire Wire Line
	3300 3500 3200 3500
Wire Wire Line
	3200 3500 3200 3400
Connection ~ 3200 3400
Wire Wire Line
	3200 3400 3050 3400
Wire Wire Line
	3700 3500 3500 3500
$Sheet
S 8000 1100 1150 5400
U 5DD345F8
F0 "5x5_LED_Cube_Matrix" 50
F1 "5x5_LED_Cube_Matrix.sch" 50
F2 "LED1" O L 8000 1200 50 
F3 "LED2" O L 8000 1300 50 
F4 "LED3" O L 8000 1400 50 
F5 "LED4" O L 8000 1500 50 
F6 "LED5" O L 8000 1600 50 
F7 "LED6" O L 8000 1700 50 
F8 "LED7" O L 8000 1800 50 
F9 "LED8" O L 8000 1900 50 
F10 "LED9" O L 8000 2000 50 
F11 "LED10" O L 8000 2100 50 
F12 "LED11" O L 8000 2200 50 
F13 "LED12" O L 8000 2300 50 
F14 "LED13" O L 8000 2400 50 
F15 "LED14" O L 8000 2500 50 
F16 "LED15" O L 8000 2600 50 
F17 "LED16" O L 8000 2700 50 
F18 "LED17" O L 8000 3400 50 
F19 "LED18" O L 8000 3500 50 
F20 "LED19" O L 8000 3600 50 
F21 "LED20" O L 8000 3700 50 
F22 "LED21" O L 8000 3800 50 
F23 "LED22" O L 8000 3900 50 
F24 "LED23" O L 8000 4000 50 
F25 "LED24" O L 8000 4100 50 
F26 "LED25" O L 8000 4200 50 
F27 "Layer1" I L 8000 4600 50 
F28 "Layer2" I L 8000 5050 50 
F29 "Layer3" I L 8000 5500 50 
F30 "Layer4" I L 8000 5950 50 
F31 "Layer5" I L 8000 6400 50 
$EndSheet
Wire Wire Line
	5100 1200 8000 1200
Wire Wire Line
	8000 1300 5100 1300
Wire Wire Line
	5100 1400 8000 1400
Wire Wire Line
	8000 1500 5100 1500
Wire Wire Line
	5100 1600 8000 1600
Wire Wire Line
	8000 1700 5100 1700
Wire Wire Line
	5100 1800 8000 1800
Wire Wire Line
	8000 1900 5100 1900
Wire Wire Line
	5100 2000 8000 2000
Wire Wire Line
	8000 2100 5100 2100
Wire Wire Line
	5100 2200 8000 2200
Wire Wire Line
	8000 2300 5100 2300
Wire Wire Line
	5100 2400 8000 2400
Wire Wire Line
	8000 2500 5100 2500
Wire Wire Line
	5100 2600 8000 2600
Wire Wire Line
	8000 2700 5100 2700
Wire Wire Line
	5100 3400 8000 3400
Wire Wire Line
	8000 3500 5100 3500
Wire Wire Line
	5100 3600 8000 3600
Wire Wire Line
	8000 3700 5100 3700
Wire Wire Line
	8000 3800 5100 3800
Wire Wire Line
	5100 3900 8000 3900
Wire Wire Line
	8000 4000 5100 4000
Wire Wire Line
	8000 4100 5100 4100
Wire Wire Line
	8000 4200 5100 4200
Wire Wire Line
	6450 4600 8000 4600
Wire Wire Line
	8000 5050 6450 5050
Wire Wire Line
	6450 5500 8000 5500
Wire Wire Line
	8000 5950 6450 5950
Wire Wire Line
	6450 6400 8000 6400
$Comp
L Device:R_Small_US R3
U 1 1 5DDDA881
P 1700 3900
F 0 "R3" V 1800 3950 50  0000 L CNN
F 1 "4.7K" V 1800 3750 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 1700 3900 50  0001 C CNN
F 3 "https://www.newark.com/panasonic/erj-2gej272x/res-thick-film-2k7-5-0-1w-0402/dp/97W7160" H 1700 3900 50  0001 C CNN
	1    1700 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	2000 3900 1800 3900
Connection ~ 2000 3900
$Comp
L power:+5V #PWR06
U 1 1 5DDE067D
P 1400 3900
F 0 "#PWR06" H 1400 3750 50  0001 C CNN
F 1 "+5V" H 1415 4073 50  0000 C CNN
F 2 "" H 1400 3900 50  0001 C CNN
F 3 "" H 1400 3900 50  0001 C CNN
	1    1400 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 3900 1400 3900
Text Label 1700 4700 2    50   ~ 0
ArduinoD13
Text Label 1700 4800 2    50   ~ 0
ArduinoD11
Text Label 1700 4900 2    50   ~ 0
ArduinoD10
Text Label 1700 5000 2    50   ~ 0
ArduinoD9
Text Label 1700 5100 2    50   ~ 0
ArduinoD3
Wire Wire Line
	1700 4800 3700 4800
Wire Wire Line
	5400 6950 6000 6950
$EndSCHEMATC
