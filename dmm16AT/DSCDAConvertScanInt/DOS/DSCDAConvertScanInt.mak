#
# Borland C++ IDE generated makefile
# Generated 7/29/02 at 11:59:31 AM 
#
.AUTODEPEND


#
# Borland C++ tools
#
IMPLIB  = Implib
BCCDOS  = Bcc +BccDos.cfg 
TLINK   = TLink
TLIB    = TLib
TASM    = Tasm
#
# IDE macros
#


#
# Options
#
IDE_LinkFLAGSDOS =  -LC:\BC5\LIB
IDE_BFLAGS = 
LinkerLocalOptsAtDOS_dscdaconvertscanintdexe =  -c -Tde
ResLocalOptsAtDOS_dscdaconvertscanintdexe = 
BLocalOptsAtDOS_dscdaconvertscanintdexe = 
CompInheritOptsAt_dscdaconvertscanintdexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_dscdaconvertscanintdexe = -x
LinkerOptsAt_dscdaconvertscanintdexe = $(LinkerLocalOptsAtDOS_dscdaconvertscanintdexe)
ResOptsAt_dscdaconvertscanintdexe = $(ResLocalOptsAtDOS_dscdaconvertscanintdexe)
BOptsAt_dscdaconvertscanintdexe = $(BLocalOptsAtDOS_dscdaconvertscanintdexe)

#
# Dependency List
#
Dep_DSCDAConvertScanInt = \
   dscdaconvertscanint.exe

DSCDAConvertScanInt : BccDos.cfg $(Dep_DSCDAConvertScanInt)
  echo MakeNode

Dep_dscdaconvertscanintdexe = \
   ..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib\
   dscdac~1.obj

dscdaconvertscanint.exe : $(Dep_dscdaconvertscanintdexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_dscdaconvertscanintdexe) $(LinkerInheritOptsAt_dscdaconvertscanintdexe) +
C:\BC5\LIB\c0l.obj+
dscdac~1.obj
$<,$*
..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib+
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\emu.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
dscdac~1.obj :  ..\dscdaconvertscanint.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_dscdaconvertscanintdexe) $(CompInheritOptsAt_dscdaconvertscanintdexe) -o$@ ..\dscdaconvertscanint.c
|

# Compiler configuration file
BccDos.cfg : 
   Copy &&|
-W-
-w
-R
-v
-vi
-H
-H=DSCDAConvertScanInt.csm
-ml
-f
| $@


