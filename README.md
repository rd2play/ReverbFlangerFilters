This is a JUCE framework C++ implementation of various DSP algorithms for a Schroeder Reverbator, flanger, general comb filter and other filters. Anyone familiar with JUCE can turn on/off those different components.

The solution includes a unit test project using GoogleTest for testing several components.

The Schroeder Reverbator implements this approach: https://ccrma.stanford.edu/~jos/pasp/Schroeder_Reverberators.html

The flanger and filters are derived from the book <a href="https://www.amazon.com/DAFX-Digital-Audio-Effects-Z%C3%B6-ebook/dp/B005HF2HFE/ref=sr_1_5?crid=3O1NF7P74ZSAD&keywords=dafx+digital+audio+effects&qid=1686806010&sprefix=dafx%2Caps%2C271&sr=8-5">DAFX: Digital Audio Effects</a> 2nd Edition, by Zölzer, Izer).

Hat tip to https://github.com/JanWilczek

(<i>Disclaimer</i>: the GUI is rather spartan, to say the least. The purpose of this project is to purely write a clean and efficient implementation of the algorithms in C++, not to have a finished plug in.
