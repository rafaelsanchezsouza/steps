#
# Borland C++ IDE generated makefile
# Generated 7/29/02 at 11:56:42 AM 
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
LinkerLocalOptsAtDOS_dscadautocaldexe =  -c -Tde
ResLocalOptsAtDOS_dscadautocaldexe = 
BLocalOptsAtDOS_dscadautocaldexe = 
CompInheritOptsAt_dscadautocaldexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_dscadautocaldexe = -x
LinkerOptsAt_dscadautocaldexe = $(LinkerLocalOptsAtDOS_dscadautocaldexe)
ResOptsAt_dscadautocaldexe = $(ResLocalOptsAtDOS_dscadautocaldexe)
BOptsAt_dscadautocaldexe = $(BLocalOptsAtDOS_dscadautocaldexe)

#
# Dependency List
#
Dep_dscADAutoCal = \
   dscadautocal.exe

dscADAutoCal : BccDos.cfg $(Dep_dscADAutoCal)
  echo MakeNode

Dep_dscadautocaldexe = \
   ..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib\
   dscada~1.obj

dscadautocal.exe : $(Dep_dscadautocaldexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_dscadautocaldexe) $(LinkerInheritOptsAt_dscadautocaldexe) +
C:\BC5\LIB\c0l.obj+
dscada~1.obj
$<,$*
..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib+
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\emu.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
dscada~1.obj :  ..\dscadautocal.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_dscadautocaldexe) $(CompInheritOptsAt_dscadautocaldexe) -o$@ ..\dscadautocal.c
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
-H=dscADAutoCal.csm
-ml
-f
| $@


