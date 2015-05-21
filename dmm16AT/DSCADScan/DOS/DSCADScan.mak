#
# Borland C++ IDE generated makefile
# Generated 7/29/02 at 11:57:47 AM 
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
LinkerLocalOptsAtDOS_dscadscandexe =  -c -Tde
ResLocalOptsAtDOS_dscadscandexe = 
BLocalOptsAtDOS_dscadscandexe = 
CompInheritOptsAt_dscadscandexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_dscadscandexe = -x
LinkerOptsAt_dscadscandexe = $(LinkerLocalOptsAtDOS_dscadscandexe)
ResOptsAt_dscadscandexe = $(ResLocalOptsAtDOS_dscadscandexe)
BOptsAt_dscadscandexe = $(BLocalOptsAtDOS_dscadscandexe)

#
# Dependency List
#
Dep_DSCADScan = \
   dscadscan.exe

DSCADScan : BccDos.cfg $(Dep_DSCADScan)
  echo MakeNode

Dep_dscadscandexe = \
   ..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib\
   dscads~1.obj

dscadscan.exe : $(Dep_dscadscandexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_dscadscandexe) $(LinkerInheritOptsAt_dscadscandexe) +
C:\BC5\LIB\c0l.obj+
dscads~1.obj
$<,$*
..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib+
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\emu.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
dscads~1.obj :  ..\dscadscan.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_dscadscandexe) $(CompInheritOptsAt_dscadscandexe) -o$@ ..\dscadscan.c
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
-H=DSCADScan.csm
-ml
-f
| $@


