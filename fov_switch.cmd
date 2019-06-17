@echo SHOC 1.0003:  1 = FOV67.50,  2 = FOV75,  3 = FOV83,  4 = FOV85,  5 = FOV90
@echo *
@echo *
@echo SHOC 1.0004:  6 = FOV67.50,  7 = FOV75,  8 = FOV83,  9 = FOV85, 10 = FOV90
@echo *
@echo *
@echo SHOC 1.0005: 11 = FOV67.50, 12 = FOV75, 13 = FOV83, 14 = FOV85, 15 = FOV90
@echo *
@echo *
@echo SHOC 1.0006: 16 = FOV67.50, 17 = FOV75, 18 = FOV83, 19 = FOV85, 20 = FOV90
@echo *
@echo *
@echo build 3120:  21 = FOV67.50, 22 = FOV75, 23 = FOV83, 24 = FOV85, 25 = FOV90
@echo *
@echo *
@echo CS 1.5.04-1.5.06: 26 = FOV67.50, 27 = FOV75, 28 = FOV83, 29 = FOV85, 30 = FOV90
@echo *
@echo *
@echo CS 1.5.07: 31 = FOV67.50, 32 = FOV75, 33 = FOV83, 34 = FOV85, 35 = FOV90
@echo *
@echo *
@echo CS 1.5.10: 36 = FOV67.50, 37 = FOV75, 38 = FOV83, 39 = FOV85, 40 = FOV90
@echo *
@Set /p var="Enter 1-40:"
if %var%==1 copy /y "bin\10003_fov6750.dll" "bin\xrGame.dll"
if %var%==2 copy /y "bin\10003_fov75.dll" "bin\xrGame.dll"
if %var%==3 copy /y "bin\10003_fov83.dll" "bin\xrGame.dll"
if %var%==4 copy /y "bin\10003_fov85.dll" "bin\xrGame.dll"
if %var%==5 copy /y "bin\10003_fov90.dll" "bin\xrGame.dll"
if %var%==6 copy /y "bin\10004_fov6750.dll" "bin\xrGame.dll"
if %var%==7 copy /y "bin\10004_fov75.dll" "bin\xrGame.dll"
if %var%==8 copy /y "bin\10004_fov83.dll" "bin\xrGame.dll"
if %var%==9 copy /y "bin\10004_fov85.dll" "bin\xrGame.dll"
if %var%==10 copy /y "bin\10004_fov90.dll" "bin\xrGame.dll"
if %var%==11 copy /y "bin\10005_fov6750.dll" "bin\xrGame.dll"
if %var%==12 copy /y "bin\10005_fov75.dll" "bin\xrGame.dll"
if %var%==13 copy /y "bin\10005_fov83.dll" "bin\xrGame.dll"
if %var%==14 copy /y "bin\10005_fov85.dll" "bin\xrGame.dll"
if %var%==15 copy /y "bin\10005_fov90.dll" "bin\xrGame.dll"
if %var%==16 copy /y "bin\10006_fov6750.dll" "bin\xrGame.dll"
if %var%==17 copy /y "bin\10006_fov75.dll" "bin\xrGame.dll"
if %var%==18 copy /y "bin\10006_fov83.dll" "bin\xrGame.dll"
if %var%==19 copy /y "bin\10006_fov85.dll" "bin\xrGame.dll"
if %var%==20 copy /y "bin\10006_fov90.dll" "bin\xrGame.dll"
if %var%==21 copy /y "bin\3120_fov6750.dll" "bin\xrGame.dll"
if %var%==22 copy /y "bin\3120_fov75.dll" "bin\xrGame.dll"
if %var%==23 copy /y "bin\3120_fov83.dll" "bin\xrGame.dll"
if %var%==24 copy /y "bin\3120_fov85.dll" "bin\xrGame.dll"
if %var%==25 copy /y "bin\3120_fov90.dll" "bin\xrGame.dll"
if %var%==26 copy /y "bin\1504_fov6750.dll" "bin\xrGame.dll"
if %var%==27 copy /y "bin\1504_fov75.dll" "bin\xrGame.dll"
if %var%==28 copy /y "bin\1504_fov83.dll" "bin\xrGame.dll"
if %var%==29 copy /y "bin\1504_fov85.dll" "bin\xrGame.dll"
if %var%==30 copy /y "bin\1504_fov90.dll" "bin\xrGame.dll"
if %var%==31 copy /y "bin\1507_fov6750.dll" "bin\xrGame.dll"
if %var%==32 copy /y "bin\1507_fov75.dll" "bin\xrGame.dll"
if %var%==33 copy /y "bin\1507_fov83.dll" "bin\xrGame.dll"
if %var%==34 copy /y "bin\1507_fov85.dll" "bin\xrGame.dll"
if %var%==35 copy /y "bin\1507_fov90.dll" "bin\xrGame.dll"
if %var%==36 copy /y "bin\1510_fov6750.dll" "bin\xrGame.dll"
if %var%==37 copy /y "bin\1510_fov75.dll" "bin\xrGame.dll"
if %var%==38 copy /y "bin\1510_fov83.dll" "bin\xrGame.dll"
if %var%==39 copy /y "bin\1510_fov85.dll" "bin\xrGame.dll"
if %var%==40 copy /y "bin\1510_fov90.dll" "bin\xrGame.dll"