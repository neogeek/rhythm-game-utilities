#!/usr/bin/env python

import os
import sys

env = SConscript("godot-cpp/SConstruct")

env.Append(CPPPATH=["include/", "../include"])
sources = Glob("include/*.cpp")

library = env.SharedLibrary(
    "build/addons/RhythmGameUtilities/libRhythmGameUtilities.{}.{}"
        .format(env["platform"], env["target"]),
    source=sources
)

gdextension_copy = env.Command(
    target="build/addons/RhythmGameUtilities/RhythmGameUtilities.gdextension",
    source="RhythmGameUtilities.gdextension",
    action=Copy("$TARGET", "$SOURCE")
)

env.Depends(gdextension_copy, library)

Default(library)

Default(gdextension_copy)
