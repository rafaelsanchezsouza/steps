#
# Borland C++ IDE generated makefile
# Generated 7/29/02 at 12:00:24 PM 
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
LinkerLocalOptsAtDOS_dscuserintdexe =  -c -Tde
ResLocalOptsAtDOS_dscuserintdexe = 
BLocalOptsAtDOS_dscuserintdexe = 
CompInheritOptsAt_dscuserintdexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_dscuserintdexe = -x
LinkerOptsAt_dscuserintdexe = $(LinkerLocalOptsAtDOS_dscuserintdexe)
ResOptsAt_dscuserintdexe = $(ResLocalOptsAtDOS_dscuserintdexe)
BOptsAt_dscuserintdexe = $(BLocalOptsAtDOS_dscuserintdexe)

#
# Dependency List
#
Dep_DSCUserInt = \
   dscuserint.exe

DSCUserInt : BccDos.cfg $(Dep_DSCUserInt)
  echo MakeNode

Dep_dscuserintdexe = \
   ..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib\
   dscuse~1.obj

dscuserint.exe : $(Dep_dscuserintdexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_dscuserintdexe) $(LinkerInheritOptsAt_dscuserintdexe) +
C:\BC5\LIB\c0l.obj+
dscuse~1.obj
$<,$*
..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib+
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\emu.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
dscuse~1.obj :  ..\dscuserint.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_dscuserintdexe) $(CompInheritOptsAt_dscuserintdexe) -o$@ ..\dscuserint.c
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
-H=DSCUserInt.csm
-ml
-f
| $@


