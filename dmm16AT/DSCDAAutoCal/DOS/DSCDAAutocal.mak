#
# Borland C++ IDE generated makefile
# Generated 7/29/02 at 11:58:22 AM 
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
LinkerLocalOptsAtDOS_dscdaautocaldexe =  -c -Tde
ResLocalOptsAtDOS_dscdaautocaldexe = 
BLocalOptsAtDOS_dscdaautocaldexe = 
CompInheritOptsAt_dscdaautocaldexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_dscdaautocaldexe = -x
LinkerOptsAt_dscdaautocaldexe = $(LinkerLocalOptsAtDOS_dscdaautocaldexe)
ResOptsAt_dscdaautocaldexe = $(ResLocalOptsAtDOS_dscdaautocaldexe)
BOptsAt_dscdaautocaldexe = $(BLocalOptsAtDOS_dscdaautocaldexe)

#
# Dependency List
#
Dep_DSCDAAutocal = \
   dscdaautocal.exe

DSCDAAutocal : BccDos.cfg $(Dep_DSCDAAutocal)
  echo MakeNode

Dep_dscdaautocaldexe = \
   ..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib\
   dscdaa~1.obj

dscdaautocal.exe : $(Dep_dscdaautocaldexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_dscdaautocaldexe) $(LinkerInheritOptsAt_dscdaautocaldexe) +
C:\BC5\LIB\c0l.obj+
dscdaa~1.obj
$<,$*
..\..\..\..\current\dev\build\dos\dscudbcl\lib\dscudbcl.lib+
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\emu.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
dscdaa~1.obj :  ..\dscdaautocal.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_dscdaautocaldexe) $(CompInheritOptsAt_dscdaautocaldexe) -o$@ ..\dscdaautocal.c
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
-H=DSCDAAutocal.csm
-ml
-f
| $@


