#
# Borland C++ IDE generated makefile
# Generated 7/29/02 at 12:00:05 PM 
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
LinkerLocalOptsAtDOS_dscsetuserintdexe =  -c -Tde
ResLocalOptsAtDOS_dscsetuserintdexe = 
BLocalOptsAtDOS_dscsetuserintdexe = 
CompInheritOptsAt_dscsetuserintdexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_dscsetuserintdexe = -x
LinkerOptsAt_dscsetuserintdexe = $(LinkerLocalOptsAtDOS_dscsetuserintdexe)
ResOptsAt_dscsetuserintdexe = $(ResLocalOptsAtDOS_dscsetuserintdexe)
BOptsAt_dscsetuserintdexe = $(BLocalOptsAtDOS_dscsetuserintdexe)

#
# Dependency List
#
Dep_DSCSetUserInt = \
   dscsetuserint.exe

DSCSetUserInt : BccDos.cfg $(Dep_DSCSetUserInt)
  echo MakeNode

Dep_dscsetuserintdexe = \
   ..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib\
   dscset~1.obj

dscsetuserint.exe : $(Dep_dscsetuserintdexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_dscsetuserintdexe) $(LinkerInheritOptsAt_dscsetuserintdexe) +
C:\BC5\LIB\c0l.obj+
dscset~1.obj
$<,$*
..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib+
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\emu.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
dscset~1.obj :  ..\dscsetuserint.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_dscsetuserintdexe) $(CompInheritOptsAt_dscsetuserintdexe) -o$@ ..\dscsetuserint.c
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
-H=DSCSetUserInt.csm
-ml
-f
| $@


