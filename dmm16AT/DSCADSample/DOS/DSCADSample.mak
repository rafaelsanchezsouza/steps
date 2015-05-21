#
# Borland C++ IDE generated makefile
# Generated 7/29/02 at 11:57:02 AM 
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
LinkerLocalOptsAtDOS_dscadsampledexe =  -c -Tde
ResLocalOptsAtDOS_dscadsampledexe = 
BLocalOptsAtDOS_dscadsampledexe = 
CompInheritOptsAt_dscadsampledexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_dscadsampledexe = -x
LinkerOptsAt_dscadsampledexe = $(LinkerLocalOptsAtDOS_dscadsampledexe)
ResOptsAt_dscadsampledexe = $(ResLocalOptsAtDOS_dscadsampledexe)
BOptsAt_dscadsampledexe = $(BLocalOptsAtDOS_dscadsampledexe)

#
# Dependency List
#
Dep_DSCADSample = \
   dscadsample.exe

DSCADSample : BccDos.cfg $(Dep_DSCADSample)
  echo MakeNode

Dep_dscadsampledexe = \
   ..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib\
   dscads~1.obj

dscadsample.exe : $(Dep_dscadsampledexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_dscadsampledexe) $(LinkerInheritOptsAt_dscadsampledexe) +
C:\BC5\LIB\c0l.obj+
dscads~1.obj
$<,$*
..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib+
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\emu.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
dscads~1.obj :  ..\dscadsample.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_dscadsampledexe) $(CompInheritOptsAt_dscadsampledexe) -o$@ ..\dscadsample.c
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
-H=DSCADSample.csm
-ml
-f
| $@


