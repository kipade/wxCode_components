# =========================================================================
#     This makefile was generated by
#     Bakefile 0.2.8 (http://www.bakefile.org)
#     Do not modify, all changes will be overwritten!
# =========================================================================



# -------------------------------------------------------------------------
# These are configurable options:
# -------------------------------------------------------------------------

# C++ compiler 
CXX = wpp386

# Standard flags for C++ 
CXXFLAGS = 

# Standard preprocessor flags (common for CC and CXX) 
CPPFLAGS = 

# Standard linker flags 
LDFLAGS = 

# Use DLL build of wx library? [0,1]
#   0 - Static
#   1 - DLL
WX_SHARED = 0

# Use Unicode build of wxWidgets? [0,1]
#   0 - ANSI
#   1 - Unicode
WX_UNICODE = 0

# Use debug build of wxWidgets (define __WXDEBUG__)? [0,1]
#   0 - Release
#   1 - Debug
WX_DEBUG = 1

# Version of the wx library to build against. 
WX_VERSION = 28

# Use monolithic build of wxWidgets? [0,1]
#   0 - Multilib
#   1 - Monolithic
WX_MONOLITHIC = 0

# The directory where wxWidgets library is installed 
WX_DIR = $(%WXWIN)

# Build this wxCode component as DLL or as static library? [0,1]
#   0 - Static
#   1 - DLL
SHARED = 0



# -------------------------------------------------------------------------
# Do not modify the rest of this file!
# -------------------------------------------------------------------------

# Speed up compilation a bit:
!ifdef __LOADDLL__
!  loaddll wcc      wccd
!  loaddll wccaxp   wccdaxp
!  loaddll wcc386   wccd386
!  loaddll wpp      wppdi86
!  loaddll wppaxp   wppdaxp
!  loaddll wpp386   wppd386
! if $(__VERSION__) >= 1280
!  loaddll wlink    wlinkd
! else
!  loaddll wlink    wlink
! endif
!  loaddll wlib     wlibd
!endif

# We need these variables in some bakefile-made rules:
WATCOM_CWD = $+ $(%cdrive):$(%cwd) $-

### Conditionally set variables: ###

WX3RDPARTYLIBPOSTFIX =
!ifeq WX_DEBUG 1
WX3RDPARTYLIBPOSTFIX = d
!endif
_BUILDDIR_SHARED_SUFFIX =
!ifeq SHARED 0
_BUILDDIR_SHARED_SUFFIX = 
!endif
!ifeq SHARED 1
_BUILDDIR_SHARED_SUFFIX = _dll
!endif
__mmwx_lib___depname =
!ifeq SHARED 0
__mmwx_lib___depname = &
	..\lib\wat_$(____mmwx_lib__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_mmwx.lib
!endif
__mmwx_dll___depname =
!ifeq SHARED 1
__mmwx_dll___depname = &
	..\lib\wat_$(____mmwx_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_mmwx.dll
!endif
____mmwx_lib__DIRNAME_SHARED_SUFFIX_FILENAMES =
!ifeq SHARED 0
____mmwx_lib__DIRNAME_SHARED_SUFFIX_FILENAMES = lib
!endif
!ifeq SHARED 1
____mmwx_lib__DIRNAME_SHARED_SUFFIX_FILENAMES = dll
!endif
____mmwx =
!ifeq WX_DEBUG 0
____mmwx = -ot -ox
!endif
!ifeq WX_DEBUG 1
____mmwx = -od
!endif
____mmwx_1 =
!ifeq WX_DEBUG 0
____mmwx_1 = -d0
!endif
!ifeq WX_DEBUG 1
____mmwx_1 = -d2
!endif
____mmwx_2 =
!ifeq WX_DEBUG 0
____mmwx_2 = 
!endif
!ifeq WX_DEBUG 1
____mmwx_2 = debug all
!endif
____mmwx_dll__DIRNAME_SHARED_SUFFIX_FILENAMES =
!ifeq WX_SHARED 0
____mmwx_dll__DIRNAME_SHARED_SUFFIX_FILENAMES = lib
!endif
!ifeq WX_SHARED 1
____mmwx_dll__DIRNAME_SHARED_SUFFIX_FILENAMES = dll
!endif
__WXLIB_CORE_NAME_p =
!ifeq WX_MONOLITHIC 0
__WXLIB_CORE_NAME_p = wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_core.lib
!endif
__WXLIB_BASE_NAME_p =
!ifeq WX_MONOLITHIC 0
__WXLIB_BASE_NAME_p = wxbase$(WX_VERSION)$(WXLIBPOSTFIX).lib
!endif
!ifeq WX_MONOLITHIC 1
__WXLIB_BASE_NAME_p = wxmsw$(WX_VERSION)$(WXLIBPOSTFIX).lib
!endif
____WX_SHARED =
!ifeq WX_SHARED 0
____WX_SHARED = 
!endif
!ifeq WX_SHARED 1
____WX_SHARED = -dWXUSINGDLL
!endif
__WXUNICODE_DEFINE_p =
!ifeq WX_UNICODE 1
__WXUNICODE_DEFINE_p = -d_UNICODE
!endif
__WXDEBUG_DEFINE_p =
!ifeq WX_DEBUG 1
__WXDEBUG_DEFINE_p = -d__WXDEBUG__
!endif
WXLIBPOSTFIX =
!ifeq WX_DEBUG 0
!ifeq WX_UNICODE 1
WXLIBPOSTFIX = u
!endif
!endif
!ifeq WX_DEBUG 1
!ifeq WX_UNICODE 0
WXLIBPOSTFIX = d
!endif
!endif
!ifeq WX_DEBUG 1
!ifeq WX_UNICODE 1
WXLIBPOSTFIX = ud
!endif
!endif
WXLIBPATH =
!ifeq WX_SHARED 0
WXLIBPATH = \lib\wat_lib
!endif
!ifeq WX_SHARED 1
WXLIBPATH = \lib\wat_dll
!endif

### Variables: ###

MMWX_LIB_CXXFLAGS = $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) &
	$(__WXDEBUG_DEFINE_p) -d__WXMSW__ &
	-i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include &
	$(____mmwx) $(____mmwx_1) -wx -i=..\include $(CPPFLAGS) $(CXXFLAGS)
MMWX_LIB_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmDbase.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmDropMenu.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmDropMonth.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmDropWindow.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmHyperBitmap.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmHyperText.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmLogonDialog.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmMAPIMail.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmMonthCtrl.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmMultiButton.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmNavigator.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmTextStretch.obj
MMWX_DLL_CXXFLAGS = -bd $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) &
	$(__WXDEBUG_DEFINE_p) -d__WXMSW__ &
	-i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include &
	$(____mmwx) $(____mmwx_1) -wx -i=..\include -dWXMAKINGDLL_MMWX $(CPPFLAGS) &
	$(CXXFLAGS)
MMWX_DLL_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmDbase.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmDropMenu.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmDropMonth.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmDropWindow.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmHyperBitmap.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmHyperText.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmLogonDialog.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmMAPIMail.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmMonthCtrl.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmMultiButton.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmNavigator.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmTextStretch.obj
MMWXTEST_CXXFLAGS = $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) &
	$(__WXDEBUG_DEFINE_p) -d__WXMSW__ &
	-i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include &
	$(____mmwx) $(____mmwx_1) -wx -i=..\include $(CPPFLAGS) $(CXXFLAGS)
MMWXTEST_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_dbmm.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_dbwx.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_mmwxTest.obj


all : watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)
watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX) :
	-if not exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX) mkdir watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)

### Targets: ###

all : .SYMBOLIC test_for_selected_wxbuild $(__mmwx_lib___depname) $(__mmwx_dll___depname) ..\samples\mmwxTest.exe

clean : .SYMBOLIC 
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.obj del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.obj
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.res del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.res
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.lbc del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.lbc
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.ilk del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.ilk
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.pch del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.pch
	-if exist ..\lib\wat_$(____mmwx_lib__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_mmwx.lib del ..\lib\wat_$(____mmwx_lib__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_mmwx.lib
	-if exist ..\lib\wat_$(____mmwx_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_mmwx.dll del ..\lib\wat_$(____mmwx_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_mmwx.dll
	-if exist ..\lib\wat_$(____mmwx_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_mmwx.lib del ..\lib\wat_$(____mmwx_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_mmwx.lib
	-if exist ..\samples\mmwxTest.exe del ..\samples\mmwxTest.exe

test_for_selected_wxbuild :  
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo ----------------------------------------------------------------------------
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo The selected wxWidgets build is not available!
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo Please use the options prefixed with WX_ to select another wxWidgets build.
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo ----------------------------------------------------------------------------
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	exit 1

!ifeq SHARED 0
..\lib\wat_$(____mmwx_lib__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_mmwx.lib :  make_dir_mmwx_lib  $(MMWX_LIB_OBJECTS)
	@%create watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib.lbc
	@for %i in ($(MMWX_LIB_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib.lbc +%i
	wlib -q -p4096 -n -b $^@ @watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib.lbc
!endif

make_dir_mmwx_lib :  
	if not exist ..\lib\wat_$(____mmwx_lib__DIRNAME_SHARED_SUFFIX_FILENAMES) mkdir ..\lib\wat_$(____mmwx_lib__DIRNAME_SHARED_SUFFIX_FILENAMES)

!ifeq SHARED 1
..\lib\wat_$(____mmwx_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_mmwx.dll :  make_dir_mmwx_dll  $(MMWX_DLL_OBJECTS)
	@%create watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll.lbc
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll.lbc option quiet
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll.lbc name $^@
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll.lbc option caseexact
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll.lbc  libpath $(WX_DIR)$(WXLIBPATH) $(____mmwx_2) libpath ..$(WXLIBPATH) $(LDFLAGS)
	@for %i in ($(MMWX_DLL_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll.lbc file %i
	@for %i in ( $(__WXLIB_CORE_NAME_p) $(__WXLIB_BASE_NAME_p) wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll.lbc library %i
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll.lbc
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll.lbc system nt_dll
	wlink @watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll.lbc
	wlib -q -n -b ..\lib\wat_$(____mmwx_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_mmwx.lib +$^@
!endif

make_dir_mmwx_dll :  
	if not exist ..\lib\wat_$(____mmwx_dll__DIRNAME_SHARED_SUFFIX_FILENAMES) mkdir ..\lib\wat_$(____mmwx_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)

..\samples\mmwxTest.exe :  $(MMWXTEST_OBJECTS) make_sample_dir_mmwxTest watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_dbmm.res watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_dbwx.res watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_mmwxTest.res $(__mmwx_lib___depname)
	@%create watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest.lbc
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest.lbc option quiet
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest.lbc name $^@
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest.lbc option caseexact
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest.lbc  libpath $(WX_DIR)$(WXLIBPATH) $(____mmwx_2) libpath ..$(WXLIBPATH) system nt_win ref '_WinMain@16'  $(LDFLAGS)
	@for %i in ($(MMWXTEST_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest.lbc file %i
	@for %i in ( ..\lib\wat_$(____mmwx_lib__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_mmwx.lib $(__WXLIB_CORE_NAME_p) $(__WXLIB_BASE_NAME_p) wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest.lbc library %i
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest.lbc option resource=watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_dbmm.res watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_dbwx.res watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_mmwxTest.res
	@for %i in () do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest.lbc option stack=%i
	wlink @watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest.lbc

make_sample_dir_mmwxTest :  
	if not exist ..\samples mkdir ..\samples

tarball :  
	make distclean
	-cd ..\..
	-tar -cvzf mmwx.tar.gz --exclude="*~" --exclude="*.log" --exclude="*.o*" --exclude="*.a" --exclude=".svn" --exclude="autom4te.cache" mmwx\*

zip :  clean
	del ..\..\mmwx.zip
	-cd ..\..
	-zip -r9 mmwx.zip mmwx -x "*.pdb" -x "*.log" -x "*.o*"

docs :  
	-cd ..\docs
	-doxygen

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmDbase.obj :  .AUTODEPEND ..\src\mmDbase.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmDropMenu.obj :  .AUTODEPEND ..\src\mmDropMenu.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmDropMonth.obj :  .AUTODEPEND ..\src\mmDropMonth.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmDropWindow.obj :  .AUTODEPEND ..\src\mmDropWindow.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmHyperBitmap.obj :  .AUTODEPEND ..\src\mmHyperBitmap.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmHyperText.obj :  .AUTODEPEND ..\src\mmHyperText.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmLogonDialog.obj :  .AUTODEPEND ..\src\mmLogonDialog.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmMAPIMail.obj :  .AUTODEPEND ..\src\mmMAPIMail.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmMonthCtrl.obj :  .AUTODEPEND ..\src\mmMonthCtrl.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmMultiButton.obj :  .AUTODEPEND ..\src\mmMultiButton.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmNavigator.obj :  .AUTODEPEND ..\src\mmNavigator.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_lib_mmTextStretch.obj :  .AUTODEPEND ..\src\mmTextStretch.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmDbase.obj :  .AUTODEPEND ..\src\mmDbase.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmDropMenu.obj :  .AUTODEPEND ..\src\mmDropMenu.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmDropMonth.obj :  .AUTODEPEND ..\src\mmDropMonth.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmDropWindow.obj :  .AUTODEPEND ..\src\mmDropWindow.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmHyperBitmap.obj :  .AUTODEPEND ..\src\mmHyperBitmap.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmHyperText.obj :  .AUTODEPEND ..\src\mmHyperText.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmLogonDialog.obj :  .AUTODEPEND ..\src\mmLogonDialog.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmMAPIMail.obj :  .AUTODEPEND ..\src\mmMAPIMail.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmMonthCtrl.obj :  .AUTODEPEND ..\src\mmMonthCtrl.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmMultiButton.obj :  .AUTODEPEND ..\src\mmMultiButton.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmNavigator.obj :  .AUTODEPEND ..\src\mmNavigator.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwx_dll_mmTextStretch.obj :  .AUTODEPEND ..\src\mmTextStretch.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWX_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_dbmm.obj :  .AUTODEPEND ..\samples\dbmm.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWXTEST_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_dbwx.obj :  .AUTODEPEND ..\samples\dbwx.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWXTEST_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_mmwxTest.obj :  .AUTODEPEND ..\samples\mmwxTest.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MMWXTEST_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_dbmm.res :  .AUTODEPEND ..\samples\dbmm.rc
	wrc -q -ad -bt=nt -r -fo=$^@  $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) $(__WXDEBUG_DEFINE_p) -d__WXMSW__ -i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include -i=..\include -i=..\samples $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_dbwx.res :  .AUTODEPEND ..\samples\dbwx.rc
	wrc -q -ad -bt=nt -r -fo=$^@  $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) $(__WXDEBUG_DEFINE_p) -d__WXMSW__ -i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include -i=..\include -i=..\samples $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\mmwxTest_mmwxTest.res :  .AUTODEPEND ..\samples\mmwxTest.rc
	wrc -q -ad -bt=nt -r -fo=$^@  $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) $(__WXDEBUG_DEFINE_p) -d__WXMSW__ -i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include -i=..\include -i=..\samples $<

