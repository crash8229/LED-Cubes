EESchema Schematic File Version 4
LIBS:5x5_LED_Cube_Driver-cache
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 2 2
Title "5x5 LED Cube Matrix"
Date "2019-11-03"
Rev "A1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:LED D1
U 1 1 5DDFF761
P 4750 2900
F 0 "D1" H 4750 2750 50  0000 C CNN
F 1 "LED" H 4743 3025 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 4750 2900 50  0001 C CNN
F 3 "~" H 4750 2900 50  0001 C CNN
	1    4750 2900
	1    0    0    1   
$EndComp
$Comp
L Device:LED D3
U 1 1 5DE04B54
P 5450 2900
F 0 "D3" H 5450 2750 50  0000 C CNN
F 1 "LED" H 5443 3025 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5450 2900 50  0001 C CNN
F 3 "~" H 5450 2900 50  0001 C CNN
	1    5450 2900
	1    0    0    1   
$EndComp
$Comp
L Device:LED D4
U 1 1 5DE057A0
P 5800 2900
F 0 "D4" H 5800 2750 50  0000 C CNN
F 1 "LED" H 5793 3025 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5800 2900 50  0001 C CNN
F 3 "~" H 5800 2900 50  0001 C CNN
	1    5800 2900
	1    0    0    1   
$EndComp
$Comp
L Device:LED D5
U 1 1 5DE060CC
P 6150 2900
F 0 "D5" H 6150 2750 50  0000 C CNN
F 1 "LED" H 6143 3025 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 6150 2900 50  0001 C CNN
F 3 "~" H 6150 2900 50  0001 C CNN
	1    6150 2900
	1    0    0    1   
$EndComp
Text HLabel 4500 2800 0    39   Output ~ 0
Layer1-5
Text HLabel 4500 2950 0    39   Input ~ 0
LED1
Text HLabel 4500 3000 0    39   Input ~ 0
LED2
Text HLabel 4500 3050 0    39   Input ~ 0
LED3
Text HLabel 4500 3100 0    39   Input ~ 0
LED4
Text HLabel 4500 3150 0    39   Input ~ 0
LED5
Wire Wire Line
	4950 3000 4950 2900
Wire Wire Line
	5300 2900 5300 3050
Wire Wire Line
	5300 3050 4500 3050
Wire Wire Line
	4500 3100 5650 3100
Wire Wire Line
	5650 3100 5650 2900
Wire Wire Line
	6000 2900 6000 3150
Wire Wire Line
	6000 3150 4500 3150
Wire Wire Line
	4950 3000 4500 3000
$Comp
L Device:LED D2
U 1 1 5DE3948F
P 5100 2900
F 0 "D2" H 5100 2750 50  0000 C CNN
F 1 "LED" H 5093 3025 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5100 2900 50  0001 C CNN
F 3 "~" H 5100 2900 50  0001 C CNN
	1    5100 2900
	1    0    0    1   
$EndComp
Wire Wire Line
	4500 2800 4900 2800
Wire Wire Line
	6300 2800 6300 2900
Wire Wire Line
	5950 2900 5950 2800
Connection ~ 5950 2800
Wire Wire Line
	5950 2800 6300 2800
Wire Wire Line
	5600 2900 5600 2800
Connection ~ 5600 2800
Wire Wire Line
	5600 2800 5950 2800
Wire Wire Line
	5250 2900 5250 2800
Connection ~ 5250 2800
Wire Wire Line
	5250 2800 5600 2800
Wire Wire Line
	4900 2900 4900 2800
Connection ~ 4900 2800
Wire Wire Line
	4900 2800 5250 2800
Wire Wire Line
	4600 2900 4600 2950
Wire Wire Line
	4600 2950 4500 2950
$Comp
L Device:LED D6
U 1 1 5DE6B1A6
P 4750 3350
F 0 "D6" H 4750 3200 50  0000 C CNN
F 1 "LED" H 4743 3475 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 4750 3350 50  0001 C CNN
F 3 "~" H 4750 3350 50  0001 C CNN
	1    4750 3350
	1    0    0    1   
$EndComp
$Comp
L Device:LED D8
U 1 1 5DE6B1AC
P 5450 3350
F 0 "D8" H 5450 3200 50  0000 C CNN
F 1 "LED" H 5443 3475 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5450 3350 50  0001 C CNN
F 3 "~" H 5450 3350 50  0001 C CNN
	1    5450 3350
	1    0    0    1   
$EndComp
$Comp
L Device:LED D9
U 1 1 5DE6B1B2
P 5800 3350
F 0 "D9" H 5800 3200 50  0000 C CNN
F 1 "LED" H 5793 3475 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5800 3350 50  0001 C CNN
F 3 "~" H 5800 3350 50  0001 C CNN
	1    5800 3350
	1    0    0    1   
$EndComp
$Comp
L Device:LED D10
U 1 1 5DE6B1B8
P 6150 3350
F 0 "D10" H 6150 3200 50  0000 C CNN
F 1 "LED" H 6143 3475 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 6150 3350 50  0001 C CNN
F 3 "~" H 6150 3350 50  0001 C CNN
	1    6150 3350
	1    0    0    1   
$EndComp
Text HLabel 4500 3400 0    39   Input ~ 0
LED6
Text HLabel 4500 3450 0    39   Input ~ 0
LED7
Text HLabel 4500 3500 0    39   Input ~ 0
LED8
Text HLabel 4500 3550 0    39   Input ~ 0
LED9
Text HLabel 4500 3600 0    39   Input ~ 0
LED10
Wire Wire Line
	4950 3450 4950 3350
Wire Wire Line
	5300 3350 5300 3500
Wire Wire Line
	5300 3500 4500 3500
Wire Wire Line
	4500 3550 5650 3550
Wire Wire Line
	5650 3550 5650 3350
Wire Wire Line
	6000 3350 6000 3600
Wire Wire Line
	6000 3600 4500 3600
Wire Wire Line
	4950 3450 4500 3450
$Comp
L Device:LED D7
U 1 1 5DE6B1CC
P 5100 3350
F 0 "D7" H 5100 3200 50  0000 C CNN
F 1 "LED" H 5093 3475 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5100 3350 50  0001 C CNN
F 3 "~" H 5100 3350 50  0001 C CNN
	1    5100 3350
	1    0    0    1   
$EndComp
Wire Wire Line
	6300 3250 6300 3350
Wire Wire Line
	5950 3350 5950 3250
Connection ~ 5950 3250
Wire Wire Line
	5950 3250 6300 3250
Wire Wire Line
	5600 3350 5600 3250
Connection ~ 5600 3250
Wire Wire Line
	5600 3250 5950 3250
Wire Wire Line
	5250 3350 5250 3250
Connection ~ 5250 3250
Wire Wire Line
	5250 3250 5600 3250
Wire Wire Line
	4900 3350 4900 3250
Wire Wire Line
	4900 3250 5250 3250
Wire Wire Line
	4600 3350 4600 3400
Wire Wire Line
	4600 3400 4500 3400
Wire Wire Line
	6300 3250 6300 2900
Connection ~ 6300 3250
Connection ~ 6300 2900
$Comp
L Device:LED D11
U 1 1 5DE7180F
P 4750 3800
F 0 "D11" H 4750 3650 50  0000 C CNN
F 1 "LED" H 4743 3925 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 4750 3800 50  0001 C CNN
F 3 "~" H 4750 3800 50  0001 C CNN
	1    4750 3800
	1    0    0    1   
$EndComp
$Comp
L Device:LED D13
U 1 1 5DE71815
P 5450 3800
F 0 "D13" H 5450 3650 50  0000 C CNN
F 1 "LED" H 5443 3925 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5450 3800 50  0001 C CNN
F 3 "~" H 5450 3800 50  0001 C CNN
	1    5450 3800
	1    0    0    1   
$EndComp
$Comp
L Device:LED D14
U 1 1 5DE7181B
P 5800 3800
F 0 "D14" H 5800 3650 50  0000 C CNN
F 1 "LED" H 5793 3925 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5800 3800 50  0001 C CNN
F 3 "~" H 5800 3800 50  0001 C CNN
	1    5800 3800
	1    0    0    1   
$EndComp
$Comp
L Device:LED D15
U 1 1 5DE71821
P 6150 3800
F 0 "D15" H 6150 3650 50  0000 C CNN
F 1 "LED" H 6143 3925 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 6150 3800 50  0001 C CNN
F 3 "~" H 6150 3800 50  0001 C CNN
	1    6150 3800
	1    0    0    1   
$EndComp
Text HLabel 4500 3850 0    39   Input ~ 0
LED11
Text HLabel 4500 3900 0    39   Input ~ 0
LED12
Text HLabel 4500 3950 0    39   Input ~ 0
LED13
Text HLabel 4500 4000 0    39   Input ~ 0
LED14
Text HLabel 4500 4050 0    39   Input ~ 0
LED15
Wire Wire Line
	4950 3900 4950 3800
Wire Wire Line
	5300 3800 5300 3950
Wire Wire Line
	5300 3950 4500 3950
Wire Wire Line
	4500 4000 5650 4000
Wire Wire Line
	5650 4000 5650 3800
Wire Wire Line
	6000 3800 6000 4050
Wire Wire Line
	6000 4050 4500 4050
Wire Wire Line
	4950 3900 4500 3900
$Comp
L Device:LED D12
U 1 1 5DE71834
P 5100 3800
F 0 "D12" H 5100 3650 50  0000 C CNN
F 1 "LED" H 5093 3925 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5100 3800 50  0001 C CNN
F 3 "~" H 5100 3800 50  0001 C CNN
	1    5100 3800
	1    0    0    1   
$EndComp
Wire Wire Line
	6300 3700 6300 3800
Wire Wire Line
	5950 3800 5950 3700
Connection ~ 5950 3700
Wire Wire Line
	5950 3700 6300 3700
Wire Wire Line
	5600 3800 5600 3700
Connection ~ 5600 3700
Wire Wire Line
	5600 3700 5950 3700
Wire Wire Line
	5250 3800 5250 3700
Connection ~ 5250 3700
Wire Wire Line
	5250 3700 5600 3700
Wire Wire Line
	4900 3800 4900 3700
Wire Wire Line
	4900 3700 5250 3700
Wire Wire Line
	4600 3800 4600 3850
Wire Wire Line
	4600 3850 4500 3850
Wire Wire Line
	6300 3700 6300 3350
Connection ~ 6300 3700
$Comp
L Device:LED D16
U 1 1 5DE7782F
P 4750 4250
F 0 "D16" H 4750 4100 50  0000 C CNN
F 1 "LED" H 4743 4375 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 4750 4250 50  0001 C CNN
F 3 "~" H 4750 4250 50  0001 C CNN
	1    4750 4250
	1    0    0    1   
$EndComp
$Comp
L Device:LED D18
U 1 1 5DE77835
P 5450 4250
F 0 "D18" H 5450 4100 50  0000 C CNN
F 1 "LED" H 5443 4375 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5450 4250 50  0001 C CNN
F 3 "~" H 5450 4250 50  0001 C CNN
	1    5450 4250
	1    0    0    1   
$EndComp
$Comp
L Device:LED D19
U 1 1 5DE7783B
P 5800 4250
F 0 "D19" H 5800 4100 50  0000 C CNN
F 1 "LED" H 5793 4375 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5800 4250 50  0001 C CNN
F 3 "~" H 5800 4250 50  0001 C CNN
	1    5800 4250
	1    0    0    1   
$EndComp
$Comp
L Device:LED D20
U 1 1 5DE77841
P 6150 4250
F 0 "D20" H 6150 4100 50  0000 C CNN
F 1 "LED" H 6143 4375 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 6150 4250 50  0001 C CNN
F 3 "~" H 6150 4250 50  0001 C CNN
	1    6150 4250
	1    0    0    1   
$EndComp
Text HLabel 4500 4300 0    39   Input ~ 0
LED16
Text HLabel 4500 4350 0    39   Input ~ 0
LED17
Text HLabel 4500 4400 0    39   Input ~ 0
LED18
Text HLabel 4500 4450 0    39   Input ~ 0
LED19
Text HLabel 4500 4500 0    39   Input ~ 0
LED20
Wire Wire Line
	4950 4350 4950 4250
Wire Wire Line
	5300 4250 5300 4400
Wire Wire Line
	5300 4400 4500 4400
Wire Wire Line
	4500 4450 5650 4450
Wire Wire Line
	5650 4450 5650 4250
Wire Wire Line
	6000 4250 6000 4500
Wire Wire Line
	6000 4500 4500 4500
Wire Wire Line
	4950 4350 4500 4350
$Comp
L Device:LED D17
U 1 1 5DE77854
P 5100 4250
F 0 "D17" H 5100 4100 50  0000 C CNN
F 1 "LED" H 5093 4375 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5100 4250 50  0001 C CNN
F 3 "~" H 5100 4250 50  0001 C CNN
	1    5100 4250
	1    0    0    1   
$EndComp
Wire Wire Line
	6300 4150 6300 4250
Wire Wire Line
	5950 4250 5950 4150
Connection ~ 5950 4150
Wire Wire Line
	5950 4150 6300 4150
Wire Wire Line
	5600 4250 5600 4150
Connection ~ 5600 4150
Wire Wire Line
	5600 4150 5950 4150
Wire Wire Line
	5250 4250 5250 4150
Connection ~ 5250 4150
Wire Wire Line
	5250 4150 5600 4150
Wire Wire Line
	4900 4250 4900 4150
Wire Wire Line
	4900 4150 5250 4150
Wire Wire Line
	4600 4250 4600 4300
Wire Wire Line
	4600 4300 4500 4300
Wire Wire Line
	6300 4150 6300 3800
Connection ~ 6300 4150
$Comp
L Device:LED D21
U 1 1 5DE7D1DA
P 4750 4700
F 0 "D21" H 4750 4550 50  0000 C CNN
F 1 "LED" H 4743 4825 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 4750 4700 50  0001 C CNN
F 3 "~" H 4750 4700 50  0001 C CNN
	1    4750 4700
	1    0    0    1   
$EndComp
$Comp
L Device:LED D23
U 1 1 5DE7D1E0
P 5450 4700
F 0 "D23" H 5450 4550 50  0000 C CNN
F 1 "LED" H 5443 4825 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5450 4700 50  0001 C CNN
F 3 "~" H 5450 4700 50  0001 C CNN
	1    5450 4700
	1    0    0    1   
$EndComp
$Comp
L Device:LED D24
U 1 1 5DE7D1E6
P 5800 4700
F 0 "D24" H 5800 4550 50  0000 C CNN
F 1 "LED" H 5793 4825 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5800 4700 50  0001 C CNN
F 3 "~" H 5800 4700 50  0001 C CNN
	1    5800 4700
	1    0    0    1   
$EndComp
$Comp
L Device:LED D25
U 1 1 5DE7D1EC
P 6150 4700
F 0 "D25" H 6150 4550 50  0000 C CNN
F 1 "LED" H 6143 4825 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 6150 4700 50  0001 C CNN
F 3 "~" H 6150 4700 50  0001 C CNN
	1    6150 4700
	1    0    0    1   
$EndComp
Text HLabel 4500 4750 0    39   Input ~ 0
LED21
Text HLabel 4500 4800 0    39   Input ~ 0
LED22
Text HLabel 4500 4850 0    39   Input ~ 0
LED23
Text HLabel 4500 4900 0    39   Input ~ 0
LED24
Text HLabel 4500 4950 0    39   Input ~ 0
LED25
Wire Wire Line
	4950 4800 4950 4700
Wire Wire Line
	5300 4700 5300 4850
Wire Wire Line
	5300 4850 4500 4850
Wire Wire Line
	4500 4900 5650 4900
Wire Wire Line
	5650 4900 5650 4700
Wire Wire Line
	6000 4700 6000 4950
Wire Wire Line
	6000 4950 4500 4950
Wire Wire Line
	4950 4800 4500 4800
$Comp
L Device:LED D22
U 1 1 5DE7D1FF
P 5100 4700
F 0 "D22" H 5100 4550 50  0000 C CNN
F 1 "LED" H 5093 4825 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 5100 4700 50  0001 C CNN
F 3 "~" H 5100 4700 50  0001 C CNN
	1    5100 4700
	1    0    0    1   
$EndComp
Wire Wire Line
	6300 4600 6300 4700
Wire Wire Line
	5950 4700 5950 4600
Connection ~ 5950 4600
Wire Wire Line
	5950 4600 6300 4600
Wire Wire Line
	5600 4700 5600 4600
Connection ~ 5600 4600
Wire Wire Line
	5600 4600 5950 4600
Wire Wire Line
	5250 4700 5250 4600
Connection ~ 5250 4600
Wire Wire Line
	5250 4600 5600 4600
Wire Wire Line
	4900 4700 4900 4600
Wire Wire Line
	4900 4600 5250 4600
Wire Wire Line
	4600 4700 4600 4750
Wire Wire Line
	4600 4750 4500 4750
Wire Wire Line
	6300 4600 6300 4250
Connection ~ 6300 4600
Connection ~ 6300 3350
Connection ~ 6300 3800
Connection ~ 6300 4250
$EndSCHEMATC
