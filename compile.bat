@set GBDK=C:\gbdk\bin\
%GBDK%lcc -Wa-l -Wl-m -Wl-j -c -o bank0.o bank0.c
%GBDK%lcc -Wa-l -Wl-m -Wl-j -Wf-bo2 -c -o bank2.o bank2.c
%GBDK%lcc -Wa-l -Wl-m -Wl-j -Wf-bo3 -c -o bank3.o bank3.c
%GBDK%lcc -Wa-l -Wl-m -Wl-j -Wf-bo4 -c -o bank4.o bank4.c
%GBDK%lcc -Wa-l -Wl-m -Wl-j -Wf-bo20 -c -o bank20.o bank20.c
%GBDK%lcc -Wa-l -Wl-m -Wl-j -Wf-ba0 -c -o banksave.o banksave.c
%GBDK%lcc -Wa-l -Wl-m -Wl-yt0x1B -Wl-yo32 -Wl-ya1 -Wm-yc -o dungeon.gbc bank0.o bank2.o bank3.o bank4.o bank20.o banksave.o
%GBDK%lcc -Wa-l -Wl-m -Wl-yt0x1B -Wl-yo32 -Wl-ya1 -o dungeon.gb bank0.o bank2.o bank3.o bank4.o bank20.o banksave.o
del *.o *.asm *.adb *.lst *.map *.ihx *.sym *.cdb