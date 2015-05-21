#
# Borland C++ IDE generated makefile
# Generated 7/29/02 at 11:59:11 AM 
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
LinkerLocalOptsAtDOS_dscdaconvertscandexe =  -c -Tde
ResLocalOptsAtDOS_dscdaconvertscandexe = 
BLocalOptsAtDOS_dscdaconvertscandexe = 
CompInheritOptsAt_dscdaconvertscandexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_dscdaconvertscandexe = -x
LinkerOptsAt_dscdaconvertscandexe = $(LinkerLocalOptsAtDOS_dscdaconvertscandexe)
ResOptsAt_dscdaconvertscandexe = $(ResLocalOptsAtDOS_dscdaconvertscandexe)
BOptsAt_dscdaconvertscandexe = $(BLocalOptsAtDOS_dscdaconvertscandexe)

#
# Dependency List
#
Dep_DSCDAConvertScan = \
   dscdaconvertscan.exe

DSCDAConvertScan : BccDos.cfg $(Dep_DSCDAConvertScan)
  echo MakeNode

Dep_dscdaconvertscandexe = \
   ..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib\
   dscdac~1.obj

dscdaconvertscan.exe : $(Dep_dscdaconvertscandexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_dscdaconvertscandexe) $(LinkerInheritOptsAt_dscdaconvertscandexe) +
C:\BC5\LIB\c0l.obj+
dscdac~1.obj
$<,$*
..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib+
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\emu.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
dscdac~1.obj :  ..\dscdaconvertscan.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_dscdaconvertscandexe) $(CompInheritOptsAt_dscdaconvertscandexe) -o$@ ..\dscdaconvertscan.c
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
-H=DSCDAConvertScan.csm
-ml
-f
| $@


