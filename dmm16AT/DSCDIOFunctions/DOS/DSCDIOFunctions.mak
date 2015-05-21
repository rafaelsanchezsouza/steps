#
# Borland C++ IDE generated makefile
# Generated 7/29/02 at 11:59:49 AM 
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
LinkerLocalOptsAtDOS_dscdiofunctionsdexe =  -c -Tde
ResLocalOptsAtDOS_dscdiofunctionsdexe = 
BLocalOptsAtDOS_dscdiofunctionsdexe = 
CompInheritOptsAt_dscdiofunctionsdexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_dscdiofunctionsdexe = -x
LinkerOptsAt_dscdiofunctionsdexe = $(LinkerLocalOptsAtDOS_dscdiofunctionsdexe)
ResOptsAt_dscdiofunctionsdexe = $(ResLocalOptsAtDOS_dscdiofunctionsdexe)
BOptsAt_dscdiofunctionsdexe = $(BLocalOptsAtDOS_dscdiofunctionsdexe)

#
# Dependency List
#
Dep_DSCDIOFunctions = \
   dscdiofunctions.exe

DSCDIOFunctions : BccDos.cfg $(Dep_DSCDIOFunctions)
  echo MakeNode

Dep_dscdiofunctionsdexe = \
   ..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib\
   dscdio~1.obj

dscdiofunctions.exe : $(Dep_dscdiofunctionsdexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_dscdiofunctionsdexe) $(LinkerInheritOptsAt_dscdiofunctionsdexe) +
C:\BC5\LIB\c0l.obj+
dscdio~1.obj
$<,$*
..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib+
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\emu.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
dscdio~1.obj :  ..\dscdiofunctions.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_dscdiofunctionsdexe) $(CompInheritOptsAt_dscdiofunctionsdexe) -o$@ ..\dscdiofunctions.c
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
-H=DSCDIOFunctions.csm
-ml
-f
| $@


