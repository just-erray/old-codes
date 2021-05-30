@echo off
gen >in
sol <in >out
test <in >bf
fc out bf
if errorlevel 1 exit
try