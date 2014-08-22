GSteg
======

A Gtkmm steg library application thing I am doing what has things and bits in it. And slots. And maybe a signal.


Install
======

Basic CMake install process

- `mkdir build`
- `cd build`
- `cmake ..`
- ``make -j`expr $(nproc) + 1` -l$(nproc) `` (The last bit is a useful hack to use make **AS YOU SHOULD** with number of cores + 1, and make sure every core is saturated)
- `./gsteg`


If there **ARE** any bugs, let me know.
