EESchema Schematic File Version 4
LIBS:DigiCtrl2-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 6
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 3600 2550 0    50   Input ~ 0
LED_MUX_0
Text HLabel 3600 2650 0    50   Input ~ 0
VCC
$Comp
L SamacSys_Parts:DMG9933USD-13 Q?
U 1 1 5C85F834
P 3800 2450
AR Path="/5C82D708/5C85F834" Ref="Q?"  Part="1" 
AR Path="/5C83CCD2/5C85F834" Ref="Q?"  Part="1" 
AR Path="/5C8495D2/5C85F834" Ref="Q?"  Part="1" 
AR Path="/5C8524DA/5C85F834" Ref="Q?"  Part="1" 
AR Path="/5C85F834" Ref="Q?"  Part="1" 
AR Path="/5C85097A/5C85F834" Ref="Q5"  Part="1" 
F 0 "Q5" H 4300 2715 50  0000 C CNN
F 1 "DMG9933USD-13" H 4300 2624 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4650 2550 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/DMG9933USD-13.pdf" H 4650 2450 50  0001 L CNN
F 4 "Trans MOSFET P-CH 20V 4.6A Automotive 8-Pin SO T/R" H 4650 2350 50  0001 L CNN "Description"
F 5 "1.75" H 4650 2250 50  0001 L CNN "Height"
F 6 "621-DMG9933USD-13" H 4650 2150 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=621-DMG9933USD-13" H 4650 2050 50  0001 L CNN "Mouser Price/Stock"
F 8 "Diodes Inc." H 4650 1950 50  0001 L CNN "Manufacturer_Name"
F 9 "DMG9933USD-13" H 4650 1850 50  0001 L CNN "Manufacturer_Part_Number"
	1    3800 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2650 3650 2650
Wire Wire Line
	3650 2450 3800 2450
Wire Wire Line
	3600 2650 3650 2650
Connection ~ 3650 2650
Wire Wire Line
	3650 2650 3650 2450
Text HLabel 3600 2750 0    50   Input ~ 0
LED_MUX_1
Wire Wire Line
	3600 2750 3800 2750
Wire Wire Line
	3600 2550 3800 2550
Text HLabel 2500 1150 0    50   Input ~ 0
LED_0
$Comp
L Device:LED D?
U 1 1 5C85F844
P 2750 1150
AR Path="/5C82D708/5C85F844" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F844" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F844" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F844" Ref="D?"  Part="1" 
AR Path="/5C85F844" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F844" Ref="D138"  Part="1" 
F 0 "D138" H 2741 1366 50  0000 C CNN
F 1 "LED" H 2741 1275 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 1150 50  0001 C CNN
F 3 "~" H 2750 1150 50  0001 C CNN
	1    2750 1150
	1    0    0    -1  
$EndComp
Text HLabel 2500 1500 0    50   Input ~ 0
LED_1
$Comp
L Device:LED D?
U 1 1 5C85F84C
P 2750 1500
AR Path="/5C82D708/5C85F84C" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F84C" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F84C" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F84C" Ref="D?"  Part="1" 
AR Path="/5C85F84C" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F84C" Ref="D140"  Part="1" 
F 0 "D140" H 2741 1716 50  0000 C CNN
F 1 "LED" H 2741 1625 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 1500 50  0001 C CNN
F 3 "~" H 2750 1500 50  0001 C CNN
	1    2750 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1500 2600 1500
Text HLabel 2500 1850 0    50   Input ~ 0
LED_2
$Comp
L Device:LED D?
U 1 1 5C85F855
P 2750 1850
AR Path="/5C82D708/5C85F855" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F855" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F855" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F855" Ref="D?"  Part="1" 
AR Path="/5C85F855" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F855" Ref="D142"  Part="1" 
F 0 "D142" H 2741 2066 50  0000 C CNN
F 1 "LED" H 2741 1975 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 1850 50  0001 C CNN
F 3 "~" H 2750 1850 50  0001 C CNN
	1    2750 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1850 2600 1850
Text HLabel 2500 2200 0    50   Input ~ 0
LED_3
$Comp
L Device:LED D?
U 1 1 5C85F85E
P 2750 2200
AR Path="/5C82D708/5C85F85E" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F85E" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F85E" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F85E" Ref="D?"  Part="1" 
AR Path="/5C85F85E" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F85E" Ref="D144"  Part="1" 
F 0 "D144" H 2741 2416 50  0000 C CNN
F 1 "LED" H 2741 2325 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 2200 50  0001 C CNN
F 3 "~" H 2750 2200 50  0001 C CNN
	1    2750 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2200 2600 2200
Text HLabel 2500 2550 0    50   Input ~ 0
LED_4
$Comp
L Device:LED D?
U 1 1 5C85F867
P 2750 2550
AR Path="/5C82D708/5C85F867" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F867" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F867" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F867" Ref="D?"  Part="1" 
AR Path="/5C85F867" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F867" Ref="D146"  Part="1" 
F 0 "D146" H 2741 2766 50  0000 C CNN
F 1 "LED" H 2741 2675 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 2550 50  0001 C CNN
F 3 "~" H 2750 2550 50  0001 C CNN
	1    2750 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2550 2600 2550
Text HLabel 2500 2900 0    50   Input ~ 0
LED_5
$Comp
L Device:LED D?
U 1 1 5C85F870
P 2750 2900
AR Path="/5C82D708/5C85F870" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F870" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F870" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F870" Ref="D?"  Part="1" 
AR Path="/5C85F870" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F870" Ref="D148"  Part="1" 
F 0 "D148" H 2741 3116 50  0000 C CNN
F 1 "LED" H 2741 3025 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 2900 50  0001 C CNN
F 3 "~" H 2750 2900 50  0001 C CNN
	1    2750 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2900 2600 2900
Text HLabel 2500 3250 0    50   Input ~ 0
LED_6
$Comp
L Device:LED D?
U 1 1 5C85F879
P 2750 3250
AR Path="/5C82D708/5C85F879" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F879" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F879" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F879" Ref="D?"  Part="1" 
AR Path="/5C85F879" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F879" Ref="D150"  Part="1" 
F 0 "D150" H 2741 3466 50  0000 C CNN
F 1 "LED" H 2741 3375 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 3250 50  0001 C CNN
F 3 "~" H 2750 3250 50  0001 C CNN
	1    2750 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 3250 2600 3250
Text HLabel 2500 3600 0    50   Input ~ 0
LED_7
$Comp
L Device:LED D?
U 1 1 5C85F882
P 2750 3600
AR Path="/5C82D708/5C85F882" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F882" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F882" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F882" Ref="D?"  Part="1" 
AR Path="/5C85F882" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F882" Ref="D152"  Part="1" 
F 0 "D152" H 2741 3816 50  0000 C CNN
F 1 "LED" H 2741 3725 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 3600 50  0001 C CNN
F 3 "~" H 2750 3600 50  0001 C CNN
	1    2750 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 3600 2600 3600
Text HLabel 2500 3950 0    50   Input ~ 0
LED_8
$Comp
L Device:LED D?
U 1 1 5C85F88B
P 2750 3950
AR Path="/5C82D708/5C85F88B" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F88B" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F88B" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F88B" Ref="D?"  Part="1" 
AR Path="/5C85F88B" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F88B" Ref="D154"  Part="1" 
F 0 "D154" H 2741 4166 50  0000 C CNN
F 1 "LED" H 2741 4075 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 3950 50  0001 C CNN
F 3 "~" H 2750 3950 50  0001 C CNN
	1    2750 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 3950 2600 3950
Text HLabel 2500 4300 0    50   Input ~ 0
LED_9
$Comp
L Device:LED D?
U 1 1 5C85F894
P 2750 4300
AR Path="/5C82D708/5C85F894" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F894" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F894" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F894" Ref="D?"  Part="1" 
AR Path="/5C85F894" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F894" Ref="D156"  Part="1" 
F 0 "D156" H 2741 4516 50  0000 C CNN
F 1 "LED" H 2741 4425 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 4300 50  0001 C CNN
F 3 "~" H 2750 4300 50  0001 C CNN
	1    2750 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 4300 2600 4300
Text HLabel 2500 4650 0    50   Input ~ 0
LED_10
$Comp
L Device:LED D?
U 1 1 5C85F89D
P 2750 4650
AR Path="/5C82D708/5C85F89D" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F89D" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F89D" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F89D" Ref="D?"  Part="1" 
AR Path="/5C85F89D" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F89D" Ref="D158"  Part="1" 
F 0 "D158" H 2741 4866 50  0000 C CNN
F 1 "LED" H 2741 4775 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 4650 50  0001 C CNN
F 3 "~" H 2750 4650 50  0001 C CNN
	1    2750 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 4650 2600 4650
Text HLabel 2500 5000 0    50   Input ~ 0
LED_11
$Comp
L Device:LED D?
U 1 1 5C85F8A6
P 2750 5000
AR Path="/5C82D708/5C85F8A6" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F8A6" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F8A6" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F8A6" Ref="D?"  Part="1" 
AR Path="/5C85F8A6" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F8A6" Ref="D160"  Part="1" 
F 0 "D160" H 2741 5216 50  0000 C CNN
F 1 "LED" H 2741 5125 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 5000 50  0001 C CNN
F 3 "~" H 2750 5000 50  0001 C CNN
	1    2750 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 5000 2600 5000
Text HLabel 2500 5350 0    50   Input ~ 0
LED_12
$Comp
L Device:LED D?
U 1 1 5C85F8AF
P 2750 5350
AR Path="/5C82D708/5C85F8AF" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F8AF" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F8AF" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F8AF" Ref="D?"  Part="1" 
AR Path="/5C85F8AF" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F8AF" Ref="D162"  Part="1" 
F 0 "D162" H 2741 5566 50  0000 C CNN
F 1 "LED" H 2741 5475 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 5350 50  0001 C CNN
F 3 "~" H 2750 5350 50  0001 C CNN
	1    2750 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 5350 2600 5350
Text HLabel 2500 5700 0    50   Input ~ 0
LED_13
$Comp
L Device:LED D?
U 1 1 5C85F8B8
P 2750 5700
AR Path="/5C82D708/5C85F8B8" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F8B8" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F8B8" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F8B8" Ref="D?"  Part="1" 
AR Path="/5C85F8B8" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F8B8" Ref="D164"  Part="1" 
F 0 "D164" H 2741 5916 50  0000 C CNN
F 1 "LED" H 2741 5825 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 5700 50  0001 C CNN
F 3 "~" H 2750 5700 50  0001 C CNN
	1    2750 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 5700 2600 5700
Text HLabel 2500 6050 0    50   Input ~ 0
LED_14
$Comp
L Device:LED D?
U 1 1 5C85F8C1
P 2750 6050
AR Path="/5C82D708/5C85F8C1" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F8C1" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F8C1" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F8C1" Ref="D?"  Part="1" 
AR Path="/5C85F8C1" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F8C1" Ref="D166"  Part="1" 
F 0 "D166" H 2741 6266 50  0000 C CNN
F 1 "LED" H 2741 6175 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 6050 50  0001 C CNN
F 3 "~" H 2750 6050 50  0001 C CNN
	1    2750 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 6050 2600 6050
Text HLabel 2500 6400 0    50   Input ~ 0
LED_15
$Comp
L Device:LED D?
U 1 1 5C85F8CA
P 2750 6400
AR Path="/5C82D708/5C85F8CA" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F8CA" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F8CA" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F8CA" Ref="D?"  Part="1" 
AR Path="/5C85F8CA" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F8CA" Ref="D168"  Part="1" 
F 0 "D168" H 2741 6616 50  0000 C CNN
F 1 "LED" H 2741 6525 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 2750 6400 50  0001 C CNN
F 3 "~" H 2750 6400 50  0001 C CNN
	1    2750 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 6400 2600 6400
Wire Wire Line
	4800 2550 4800 2450
Wire Wire Line
	2900 1150 2900 1500
Connection ~ 2900 1500
Wire Wire Line
	2900 1500 2900 1850
Connection ~ 2900 1850
Wire Wire Line
	2900 1850 2900 2200
Connection ~ 2900 2200
Wire Wire Line
	2900 2200 2900 2550
Connection ~ 2900 2550
Wire Wire Line
	2900 2550 2900 2900
Connection ~ 2900 2900
Wire Wire Line
	2900 2900 2900 3250
Connection ~ 2900 3250
Wire Wire Line
	2900 3250 2900 3600
Connection ~ 2900 3600
Wire Wire Line
	2900 3600 2900 3950
Connection ~ 2900 3950
Wire Wire Line
	2900 3950 2900 4300
Connection ~ 2900 4300
Wire Wire Line
	2900 4300 2900 4650
Connection ~ 2900 4650
Wire Wire Line
	2900 4650 2900 5000
Connection ~ 2900 5000
Wire Wire Line
	2900 5000 2900 5350
Connection ~ 2900 5350
Wire Wire Line
	2900 5350 2900 5700
Connection ~ 2900 5700
Wire Wire Line
	2900 5700 2900 6050
Connection ~ 2900 6050
Wire Wire Line
	2900 6050 2900 6400
Wire Wire Line
	4900 1150 4900 2450
Wire Wire Line
	4900 2450 4800 2450
Connection ~ 4800 2450
Text HLabel 1450 1150 0    50   Input ~ 0
LED_0
$Comp
L Device:LED D?
U 1 1 5C85F8F4
P 1700 1150
AR Path="/5C82D708/5C85F8F4" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F8F4" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F8F4" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F8F4" Ref="D?"  Part="1" 
AR Path="/5C85F8F4" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F8F4" Ref="D137"  Part="1" 
F 0 "D137" H 1691 1366 50  0000 C CNN
F 1 "LED" H 1691 1275 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 1150 50  0001 C CNN
F 3 "~" H 1700 1150 50  0001 C CNN
	1    1700 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1150 1550 1150
Text HLabel 1450 1500 0    50   Input ~ 0
LED_1
$Comp
L Device:LED D?
U 1 1 5C85F8FD
P 1700 1500
AR Path="/5C82D708/5C85F8FD" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F8FD" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F8FD" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F8FD" Ref="D?"  Part="1" 
AR Path="/5C85F8FD" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F8FD" Ref="D139"  Part="1" 
F 0 "D139" H 1691 1716 50  0000 C CNN
F 1 "LED" H 1691 1625 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 1500 50  0001 C CNN
F 3 "~" H 1700 1500 50  0001 C CNN
	1    1700 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1500 1550 1500
Text HLabel 1450 1850 0    50   Input ~ 0
LED_2
$Comp
L Device:LED D?
U 1 1 5C85F906
P 1700 1850
AR Path="/5C82D708/5C85F906" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F906" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F906" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F906" Ref="D?"  Part="1" 
AR Path="/5C85F906" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F906" Ref="D141"  Part="1" 
F 0 "D141" H 1691 2066 50  0000 C CNN
F 1 "LED" H 1691 1975 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 1850 50  0001 C CNN
F 3 "~" H 1700 1850 50  0001 C CNN
	1    1700 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1850 1550 1850
Text HLabel 1450 2200 0    50   Input ~ 0
LED_3
$Comp
L Device:LED D?
U 1 1 5C85F90F
P 1700 2200
AR Path="/5C82D708/5C85F90F" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F90F" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F90F" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F90F" Ref="D?"  Part="1" 
AR Path="/5C85F90F" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F90F" Ref="D143"  Part="1" 
F 0 "D143" H 1691 2416 50  0000 C CNN
F 1 "LED" H 1691 2325 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 2200 50  0001 C CNN
F 3 "~" H 1700 2200 50  0001 C CNN
	1    1700 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 2200 1550 2200
Text HLabel 1450 2550 0    50   Input ~ 0
LED_4
$Comp
L Device:LED D?
U 1 1 5C85F918
P 1700 2550
AR Path="/5C82D708/5C85F918" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F918" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F918" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F918" Ref="D?"  Part="1" 
AR Path="/5C85F918" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F918" Ref="D145"  Part="1" 
F 0 "D145" H 1691 2766 50  0000 C CNN
F 1 "LED" H 1691 2675 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 2550 50  0001 C CNN
F 3 "~" H 1700 2550 50  0001 C CNN
	1    1700 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 2550 1550 2550
Text HLabel 1450 2900 0    50   Input ~ 0
LED_5
$Comp
L Device:LED D?
U 1 1 5C85F921
P 1700 2900
AR Path="/5C82D708/5C85F921" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F921" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F921" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F921" Ref="D?"  Part="1" 
AR Path="/5C85F921" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F921" Ref="D147"  Part="1" 
F 0 "D147" H 1691 3116 50  0000 C CNN
F 1 "LED" H 1691 3025 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 2900 50  0001 C CNN
F 3 "~" H 1700 2900 50  0001 C CNN
	1    1700 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 2900 1550 2900
Text HLabel 1450 3250 0    50   Input ~ 0
LED_6
$Comp
L Device:LED D?
U 1 1 5C85F92A
P 1700 3250
AR Path="/5C82D708/5C85F92A" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F92A" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F92A" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F92A" Ref="D?"  Part="1" 
AR Path="/5C85F92A" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F92A" Ref="D149"  Part="1" 
F 0 "D149" H 1691 3466 50  0000 C CNN
F 1 "LED" H 1691 3375 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 3250 50  0001 C CNN
F 3 "~" H 1700 3250 50  0001 C CNN
	1    1700 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 3250 1550 3250
Text HLabel 1450 3600 0    50   Input ~ 0
LED_7
$Comp
L Device:LED D?
U 1 1 5C85F933
P 1700 3600
AR Path="/5C82D708/5C85F933" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F933" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F933" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F933" Ref="D?"  Part="1" 
AR Path="/5C85F933" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F933" Ref="D151"  Part="1" 
F 0 "D151" H 1691 3816 50  0000 C CNN
F 1 "LED" H 1691 3725 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 3600 50  0001 C CNN
F 3 "~" H 1700 3600 50  0001 C CNN
	1    1700 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 3600 1550 3600
Text HLabel 1450 3950 0    50   Input ~ 0
LED_8
$Comp
L Device:LED D?
U 1 1 5C85F93C
P 1700 3950
AR Path="/5C82D708/5C85F93C" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F93C" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F93C" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F93C" Ref="D?"  Part="1" 
AR Path="/5C85F93C" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F93C" Ref="D153"  Part="1" 
F 0 "D153" H 1691 4166 50  0000 C CNN
F 1 "LED" H 1691 4075 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 3950 50  0001 C CNN
F 3 "~" H 1700 3950 50  0001 C CNN
	1    1700 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 3950 1550 3950
Text HLabel 1450 4300 0    50   Input ~ 0
LED_9
$Comp
L Device:LED D?
U 1 1 5C85F945
P 1700 4300
AR Path="/5C82D708/5C85F945" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F945" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F945" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F945" Ref="D?"  Part="1" 
AR Path="/5C85F945" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F945" Ref="D155"  Part="1" 
F 0 "D155" H 1691 4516 50  0000 C CNN
F 1 "LED" H 1691 4425 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 4300 50  0001 C CNN
F 3 "~" H 1700 4300 50  0001 C CNN
	1    1700 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 4300 1550 4300
Text HLabel 1450 4650 0    50   Input ~ 0
LED_10
$Comp
L Device:LED D?
U 1 1 5C85F94E
P 1700 4650
AR Path="/5C82D708/5C85F94E" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F94E" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F94E" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F94E" Ref="D?"  Part="1" 
AR Path="/5C85F94E" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F94E" Ref="D157"  Part="1" 
F 0 "D157" H 1691 4866 50  0000 C CNN
F 1 "LED" H 1691 4775 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 4650 50  0001 C CNN
F 3 "~" H 1700 4650 50  0001 C CNN
	1    1700 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 4650 1550 4650
Text HLabel 1450 5000 0    50   Input ~ 0
LED_11
$Comp
L Device:LED D?
U 1 1 5C85F957
P 1700 5000
AR Path="/5C82D708/5C85F957" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F957" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F957" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F957" Ref="D?"  Part="1" 
AR Path="/5C85F957" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F957" Ref="D159"  Part="1" 
F 0 "D159" H 1691 5216 50  0000 C CNN
F 1 "LED" H 1691 5125 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 5000 50  0001 C CNN
F 3 "~" H 1700 5000 50  0001 C CNN
	1    1700 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 5000 1550 5000
Text HLabel 1450 5350 0    50   Input ~ 0
LED_12
$Comp
L Device:LED D?
U 1 1 5C85F960
P 1700 5350
AR Path="/5C82D708/5C85F960" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F960" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F960" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F960" Ref="D?"  Part="1" 
AR Path="/5C85F960" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F960" Ref="D161"  Part="1" 
F 0 "D161" H 1691 5566 50  0000 C CNN
F 1 "LED" H 1691 5475 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 5350 50  0001 C CNN
F 3 "~" H 1700 5350 50  0001 C CNN
	1    1700 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 5350 1550 5350
Text HLabel 1450 5700 0    50   Input ~ 0
LED_13
$Comp
L Device:LED D?
U 1 1 5C85F969
P 1700 5700
AR Path="/5C82D708/5C85F969" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F969" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F969" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F969" Ref="D?"  Part="1" 
AR Path="/5C85F969" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F969" Ref="D163"  Part="1" 
F 0 "D163" H 1691 5916 50  0000 C CNN
F 1 "LED" H 1691 5825 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 5700 50  0001 C CNN
F 3 "~" H 1700 5700 50  0001 C CNN
	1    1700 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 5700 1550 5700
Text HLabel 1450 6050 0    50   Input ~ 0
LED_14
$Comp
L Device:LED D?
U 1 1 5C85F972
P 1700 6050
AR Path="/5C82D708/5C85F972" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F972" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F972" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F972" Ref="D?"  Part="1" 
AR Path="/5C85F972" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F972" Ref="D165"  Part="1" 
F 0 "D165" H 1691 6266 50  0000 C CNN
F 1 "LED" H 1691 6175 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 6050 50  0001 C CNN
F 3 "~" H 1700 6050 50  0001 C CNN
	1    1700 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 6050 1550 6050
Text HLabel 1450 6400 0    50   Input ~ 0
LED_15
$Comp
L Device:LED D?
U 1 1 5C85F97B
P 1700 6400
AR Path="/5C82D708/5C85F97B" Ref="D?"  Part="1" 
AR Path="/5C83CCD2/5C85F97B" Ref="D?"  Part="1" 
AR Path="/5C8495D2/5C85F97B" Ref="D?"  Part="1" 
AR Path="/5C8524DA/5C85F97B" Ref="D?"  Part="1" 
AR Path="/5C85F97B" Ref="D?"  Part="1" 
AR Path="/5C85097A/5C85F97B" Ref="D167"  Part="1" 
F 0 "D167" H 1691 6616 50  0000 C CNN
F 1 "LED" H 1691 6525 50  0000 C CNN
F 2 "footprints:LED_0805_2012Metric_NO_SILKSCREEN" H 1700 6400 50  0001 C CNN
F 3 "~" H 1700 6400 50  0001 C CNN
	1    1700 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 6400 1550 6400
Wire Wire Line
	1850 1150 1850 1500
Connection ~ 1850 1500
Wire Wire Line
	1850 1500 1850 1850
Connection ~ 1850 1850
Wire Wire Line
	1850 1850 1850 2200
Connection ~ 1850 2200
Wire Wire Line
	1850 2200 1850 2550
Connection ~ 1850 2550
Wire Wire Line
	1850 2550 1850 2900
Connection ~ 1850 2900
Wire Wire Line
	1850 2900 1850 3250
Connection ~ 1850 3250
Wire Wire Line
	1850 3250 1850 3600
Connection ~ 1850 3600
Wire Wire Line
	1850 3600 1850 3950
Connection ~ 1850 3950
Wire Wire Line
	1850 3950 1850 4300
Connection ~ 1850 4300
Wire Wire Line
	1850 4300 1850 4650
Connection ~ 1850 4650
Wire Wire Line
	1850 4650 1850 5000
Connection ~ 1850 5000
Wire Wire Line
	1850 5000 1850 5350
Connection ~ 1850 5350
Wire Wire Line
	1850 5350 1850 5700
Connection ~ 1850 5700
Wire Wire Line
	1850 5700 1850 6050
Connection ~ 1850 6050
Wire Wire Line
	1850 6050 1850 6400
Wire Wire Line
	1850 1150 1850 950 
Wire Wire Line
	1850 950  5050 950 
Wire Wire Line
	5050 950  5050 2750
Wire Wire Line
	5050 2750 4800 2750
Connection ~ 1850 1150
Wire Wire Line
	4800 2650 4800 2750
Connection ~ 4800 2750
Wire Wire Line
	2500 1150 2600 1150
Wire Wire Line
	2900 1150 4900 1150
Connection ~ 2900 1150
$Comp
L Device:C C?
U 1 1 5C9E9148
P 3500 2200
AR Path="/5C9E9148" Ref="C?"  Part="1" 
AR Path="/5C85097A/5C9E9148" Ref="C20"  Part="1" 
F 0 "C20" V 3248 2200 50  0000 C CNN
F 1 "100n" V 3339 2200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3538 2050 50  0001 C CNN
F 3 "~" H 3500 2200 50  0001 C CNN
	1    3500 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 2200 3650 2450
Text HLabel 3250 2200 0    50   Input ~ 0
GND
Wire Wire Line
	3250 2200 3350 2200
$EndSCHEMATC
