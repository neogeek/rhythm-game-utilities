@echo off

if not defined VCINSTALLDIR (
    echo Please run this script from x64 Native Tools Command Prompt for VS.
    exit /b 1
)

mkdir build

cl /EHsc /std:c++17 /c include/RhythmGameUtilities/RhythmGameUtilities.cpp /Fo:build\RhythmGameUtilities.obj
link /DLL /MACHINE:X64 /OUT:build\libRhythmGameUtilities.dll /IMPLIB:build\libRhythmGameUtilities.lib build\RhythmGameUtilities.obj

del build\RhythmGameUtilities.obj

mkdir UnityPackage\Libs\Windows
mkdir RhythmGameUtilities\Libs\Windows

copy build\libRhythmGameUtilities.dll UnityPackage\Libs\Windows
copy build\libRhythmGameUtilities.dll RhythmGameUtilities\Libs\Windows
