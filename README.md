# Dosimeter

An improved&amp;fixed version of a dosimeter presented at https://www.instructables.com/id/DIY-Arduino-Geiger-Counter/

Change list:
1. Continious monitoring of a radiation level
2. Minor processing of obtained data (calculation of an average and max values)
3. Added a button to change data output and toggle mute of a buzzer
4. Optimized&fixed sketch logic

Display modes to loop through (each one shows current level of radiation togeter wit a following value):
1. average level for the last 60 sec ("avg")
2. max level for the last 60 sec ("max")
3. max level for the whole session time ("Max")
Buzzer can be muted/unmuted by holding down the button for 2+ sec.

PCBs are designed to fit the Kradex Z34 case (https://www.tme.eu/ua/ru/details/z-34/korpusa-universalnye/kradex/z34/)
