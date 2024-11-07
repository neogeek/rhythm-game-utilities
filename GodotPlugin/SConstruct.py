#!/usr/bin/env python

import os
import sys

env = SConscript("godot-cpp/SConstruct")

env.Append(CPPPATH=["include/", "../include"])
sources = Glob("include/*.cpp")

if env["platform"] == "macos":
    file_name = "libRhythmGameUtilities.{}.{}".format(env["platform"], env["target"])

    library = env.SharedLibrary(
        "build/addons/RhythmGameUtilities/{}.framework/{}".format(file_name, file_name),
        source=sources
    )
else:
    library = env.SharedLibrary(
        "build/addons/RhythmGameUtilities/libRhythmGameUtilities{}{}"
            .format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

gdextension_copy = env.Command(
    target="build/addons/RhythmGameUtilities/RhythmGameUtilities.gdextension",
    source="RhythmGameUtilities.gdextension",
    action=Copy("$TARGET", "$SOURCE")
)

env.Depends(gdextension_copy, library)

Default(library)

Default(gdextension_copy)
