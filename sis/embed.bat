@echo off

REM make basic sis

makesis MorseTexter-no-embed.pkg MorseTexter0.sis

copy MorseTexter0.sis MorseTexter.bin


REM make sis with one embedded sis

makesis MorseTexter.pkg

copy MorseTexter.sis MorseTexter1.sis
copy MorseTexter.sis MorseTexter.bin


REM make sis with two embedded sis

makesis MorseTexter.pkg

copy MorseTexter.sis MorseTexter2.sis
copy MorseTexter.sis MorseTexter.bin


move MorseTexter.SIS MorseTexter.sis
