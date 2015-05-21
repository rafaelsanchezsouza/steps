#
# Borland C++ IDE generated makefile
# Generated 7/29/02 at 11:58:05 AM 
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
LinkerLocalOptsAtDOS_dscadscanintdexe =  -c -Tde
ResLocalOptsAtDOS_dscadscanintdexe = 
BLocalOptsAtDOS_dscadscanintdexe = 
CompInheritOptsAt_dscadscanintdexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_dscadscanintdexe = -x
LinkerOptsAt_dscadscanintdexe = $(LinkerLocalOptsAtDOS_dscadscanintdexe)
ResOptsAt_dscadscanintdexe = $(ResLocalOptsAtDOS_dscadscanintdexe)
BOptsAt_dscadscanintdexe = $(BLocalOptsAtDOS_dscadscanintdexe)

#
# Dependency List
#
Dep_DSCADScanInt = \
   dscadscanint.exe

DSCADScanInt : BccDos.cfg $(Dep_DSCADScanInt)
  echo MakeNode

Dep_dscadscanintdexe = \
   ..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib\
   dscads~1.obj

dscadscanint.exe : $(Dep_dscadscanintdexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_dscadscanintdexe) $(LinkerInheritOptsAt_dscadscanintdexe) +
C:\BC5\LIB\c0l.obj+
dscads~1.obj
$<,$*
..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib+
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\emu.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
dscads~1.obj :  ..\dscadscanint.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_dscadscanintdexe) $(CompInheritOptsAt_dscadscanintdexe) -o$@ ..\dscadscanint.c
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
-H=DSCADScanInt.csm
-ml
-f
| $@


