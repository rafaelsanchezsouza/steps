#
# Borland C++ IDE generated makefile
# Generated 6/11/2004 at 6:21:58 PM 
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
LinkerLocalOptsAtDOS_measurereferencesdexe =  -c -Tde
ResLocalOptsAtDOS_measurereferencesdexe = 
BLocalOptsAtDOS_measurereferencesdexe = 
CompInheritOptsAt_measurereferencesdexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_measurereferencesdexe = -x
LinkerOptsAt_measurereferencesdexe = $(LinkerLocalOptsAtDOS_measurereferencesdexe)
ResOptsAt_measurereferencesdexe = $(ResLocalOptsAtDOS_measurereferencesdexe)
BOptsAt_measurereferencesdexe = $(BLocalOptsAtDOS_measurereferencesdexe)

#
# Dependency List
#
Dep_MeasureReferences = \
   measurereferences.exe

MeasureReferences : BccDos.cfg $(Dep_MeasureReferences)
  echo MakeNode

Dep_measurereferencesdexe = \
   ..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib\
   measur~1.obj

measurereferences.exe : $(Dep_measurereferencesdexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_measurereferencesdexe) $(LinkerInheritOptsAt_measurereferencesdexe) +
C:\BC5\LIB\c0l.obj+
measur~1.obj
$<,$*
..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib+
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\emu.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
measur~1.obj :  ..\measurereferences.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_measurereferencesdexe) $(CompInheritOptsAt_measurereferencesdexe) -o$@ ..\measurereferences.c
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
-H=MeasureReference.csm
-ml
-f
| $@


