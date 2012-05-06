
These are batch scripts for both Linux and Windows. Each will create

a respective package folder to be distributed as a release, provided

the file hierarchy is as it expects. If you use the Visual Studio 

project for Windows and the cmake file for Linux, this should not be

a problem since it all works in harmony.


Please note, though, that the Linux script expects the binary it uses

to be in the "bin" folder. Some IDEs may create a Debug and Release 

folder somewhere, which the script cannot see. If this is the case, 

just move the files out into "bin" when you go to make a package.

For Windows, the "Release" folder is expected, so you cannot build

a package without compiling Release. Packages should be for final

distribution.


