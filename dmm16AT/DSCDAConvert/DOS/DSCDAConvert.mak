#
# Borland C++ IDE generated makefile
# Generated 7/29/02 at 11:58:42 AM 
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
LinkerLocalOptsAtDOS_dscdaconvertdexe =  -c -Tde
ResLocalOptsAtDOS_dscdaconvertdexe = 
BLocalOptsAtDOS_dscdaconvertdexe = 
CompInheritOptsAt_dscdaconvertdexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_dscdaconvertdexe = -x
LinkerOptsAt_dscdaconvertdexe = $(LinkerLocalOptsAtDOS_dscdaconvertdexe)
ResOptsAt_dscdaconvertdexe = $(ResLocalOptsAtDOS_dscdaconvertdexe)
BOptsAt_dscdaconvertdexe = $(BLocalOptsAtDOS_dscdaconvertdexe)

#
# Dependency List
#
Dep_DSCDAConvert = \
   dscdaconvert.exe

DSCDAConvert : BccDos.cfg $(Dep_DSCDAConvert)
  echo MakeNode

Dep_dscdaconvertdexe = \
   ..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib\
   dscdac~1.obj

dscdaconvert.exe : $(Dep_dscdaconvertdexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_dscdaconvertdexe) $(LinkerInheritOptsAt_dscdaconvertdexe) +
C:\BC5\LIB\c0l.obj+
dscdac~1.obj
$<,$*
..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib+
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\emu.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
dscdac~1.obj :  ..\dscdaconvert.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_dscdaconvertdexe) $(CompInheritOptsAt_dscdaconvertdexe) -o$@ ..\dscdaconvert.c
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
-H=DSCDAConvert.csm
-ml
-f
| $@


