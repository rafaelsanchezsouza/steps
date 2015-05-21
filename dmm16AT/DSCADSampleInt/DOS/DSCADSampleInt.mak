#
# Borland C++ IDE generated makefile
# Generated 7/29/02 at 11:57:28 AM 
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
LinkerLocalOptsAtDOS_dscadsampleintdexe =  -c -Tde
ResLocalOptsAtDOS_dscadsampleintdexe = 
BLocalOptsAtDOS_dscadsampleintdexe = 
CompInheritOptsAt_dscadsampleintdexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_dscadsampleintdexe = -x
LinkerOptsAt_dscadsampleintdexe = $(LinkerLocalOptsAtDOS_dscadsampleintdexe)
ResOptsAt_dscadsampleintdexe = $(ResLocalOptsAtDOS_dscadsampleintdexe)
BOptsAt_dscadsampleintdexe = $(BLocalOptsAtDOS_dscadsampleintdexe)

#
# Dependency List
#
Dep_DSCADSampleInt = \
   dscadsampleint.exe

DSCADSampleInt : BccDos.cfg $(Dep_DSCADSampleInt)
  echo MakeNode

Dep_dscadsampleintdexe = \
   ..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib\
   dscads~1.obj

dscadsampleint.exe : $(Dep_dscadsampleintdexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_dscadsampleintdexe) $(LinkerInheritOptsAt_dscadsampleintdexe) +
C:\BC5\LIB\c0l.obj+
dscads~1.obj
$<,$*
..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib+
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\emu.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
dscads~1.obj :  ..\dscadsampleint.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_dscadsampleintdexe) $(CompInheritOptsAt_dscadsampleintdexe) -o$@ ..\dscadsampleint.c
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
-H=DSCADSampleInt.csm
-ml
-f
| $@


