@echo off
gen >int
sol <int >out
bf <int >bf_out
fc out bf_out
if errorlevel 1 exit
test