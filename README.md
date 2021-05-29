# StereoPingPongDelay
Implemented (mostly ported by constructing fxobjects library object) the delay plugin described in the textbook "Designing Audio Effects Plugins in C++ 2nd Ed." in JUCE.

Open the .jucer project file, make sure:
filters.h
fxobjects.cpp
fxobjects.h
guiconstants.h
PluginEditor.cpp
PluginEditor.h
PluginProcessor.cpp
PluginProcessor.h

are all in the project "src" folder. No other files are needed. You will need JUCE installed on your computer.
And so long as you know how to use JUCE/VS you should be good.

Alternatively just download StereoPingPongDelay.vst3 and add it to your DAW VST plugin directory instead of building it yourself.

There is def. more work to do, better ways to do a few things
-linear mixing of fast parameter changes esp. ratio,
-improving GUI which is literally the least I could have done for it to run... you have to resize the window before using.
-guiconstants.h shouldn't be necessary, I am pretty sure all I'm using is a single alias in one of the fxobjects/filter files

May work on making a library of sorts of all the textbook effects plugins for easy use in one project (or even 1 plugin).
Perhaps using the "AudioProcessorGraph" juce class and porting the fxobjects code for JUCE specifically
