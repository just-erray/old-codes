@echo off
gen >int 
sol <int >out 
bf <int >out_bf
fc out out_bf
if errorlevel 1 exit
test