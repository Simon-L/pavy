# PaVy

**Heavy patch player using PulseAudio.**

A simple script that downloads, compiles and runs Heavy source code, generated from a Pd patch.

Heavy is a framework made by Enzienaudio for creating interactive sound and music for games, instruments or installations. [More information](https://enzienaudio.com)

Example usage:  
```
$ ./pavy.sh https://enzienaudio.com/h/FergusL/drones/5/c/src/drones.c.zip
Using patch url: https://enzienaudio.com/h/FergusL/drones/5/c/src/drones.c.zip
Patchname: drones
Downloading and extracting patch sources...
Archive:  drones.c.zip
  inflating: heavy/HvTable.c         
  inflating: heavy/HvControlRandom.c  
  inflating: heavy/HvMessage.h       
  inflating: heavy/HvUtils.c         
  inflating: heavy/Heavy_drones.h    
  inflating: heavy/HvMessagePool.h   
  inflating: heavy/HvControlUnop.c   
  inflating: heavy/HvLightPipe.c     
  inflating: heavy/HeavyContext.hpp  
  inflating: heavy/HeavyContextInterface.hpp  
  inflating: heavy/HvSignalPhasor.h  
  inflating: heavy/Heavy_drones.hpp  
  inflating: heavy/HvHeavy.cpp       
  inflating: heavy/HvHeavy.h         
  inflating: heavy/HvMath.h          
  inflating: heavy/HvControlUnop.h   
  inflating: heavy/HvHeavyInternal.h  
  inflating: heavy/HvControlRandom.h  
  inflating: heavy/HvLightPipe.h     
  inflating: heavy/HvSignalPhasor.c  
  inflating: heavy/HvUtils.h         
  inflating: heavy/HvMessageQueue.c  
  inflating: heavy/HvSignalVar.c     
  inflating: heavy/Heavy_drones.cpp  
  inflating: heavy/HvControlSlice.h  
  inflating: heavy/HvMessageQueue.h  
  inflating: heavy/HeavyContext.cpp  
  inflating: heavy/HvControlBinop.h  
  inflating: heavy/HvMessage.c       
  inflating: heavy/HvTable.h         
  inflating: heavy/HvMessagePool.c   
  inflating: heavy/HvSignalVar.h     
  inflating: heavy/HvControlBinop.c  
  inflating: heavy/HvControlSlice.c  
Compiling
Done. Running patch.
Audio channels: 2
```

## Usage

This script is very basic and takes a single argument that *must* be a path to the C sources for a patch on the Heavy website, this link can be copied like the following:

![](http://pix.toile-libre.org/upload/img/1511740192.png)

##### Thoughts

It is assumed as part of *why this repo?* that you are interested in the C/C++ sources rather than plugin sources or precompiled binaries of your patch. Likely, you might want to compile the code again for specific targets afterwards. I made this script for testing patches easily on Linux on my way to running patches on Arduino boards!

You will need **libpulse-dev**, **gcc**, **g++** and **wget**:  
`sudo apt install build-essential libpulse-dev wget`

-----------

Powered by ![Powered by Heavy](https://enzienaudio.com/static/img/heavy_logo_prod_wtxt.svg)
