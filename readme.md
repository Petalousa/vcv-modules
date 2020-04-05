# Making a module

## Panel Design

make `.svg` file

run 



# Notes

You cannot connect VCV and a DAW using a VST bridge: 
- https://vcvrack.com/manual/FAQ#is-vcv-rack-available-as-a-vst-au-aax-plugin-for-daws
- https://www.reddit.com/r/vcvrack/comments/deen9b/where_the_hell_is_bridge_vst/


## MIDI

library used to read midi: https://github.com/craigsapp/midifile

work that I'm using as reference: https://github.com/WrongPeople/WrongPeopleVCV


## Compiling and Installing Plugin


### GENERATE MODULE
`../Rack-SDK/helper.py createmodule <NAME> res/<NAME>.svg src/<NAME>.cpp`

add the following to plugin.hpp
`extern Model* <NAME>;`

add the following to plugin.cpp
`p->addModel(modelLabel);`

### COMPILE
run the following command in MSYS2 MinGW 64-bit!

```bash
RACK_DIR="../Rack-SDK" make install
```