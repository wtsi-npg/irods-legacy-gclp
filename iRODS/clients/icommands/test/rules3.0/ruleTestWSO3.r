myTestRule {
# Input parameters are: 
#   File descriptor 
#   Optional length to read  
# Output Parameter is: 
#   Buffer holding the data read 
# Output from running the example is: 
  for (*I = 0 ; *I < 4 ; *I = *I + 1) {
    acRunWorkFlow("/raja8/home/rods/msso/mssop1/mssop1.run",*R_BUF);
    msiBytesBufToStr(*R_BUF, *Str);
    writeLine("stdout", *Str);
  } 
} 
INPUT *Obj="/raja8/home/rods/msso/mssop1/mssop1.run", *Flag="O_RDONLY", *OFlags="objPath=*Obj++++openFlags=*Flag", *Len=100
OUTPUT ruleExecOut, *Str 
