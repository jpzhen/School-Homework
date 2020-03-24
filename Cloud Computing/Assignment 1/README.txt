To compile program, please run the bash script by:
    $ chmod u+x build.sh
    $ ./build.sh

After, there should be an ass1.exe, please run with mono by:
    $ mono ass1.exe args1 args2

To run with prefined arugements, please run the "run.sh" script by:
    $ chmod u+x build.sh
    $ ./run.sh

- The program is build on MacOS and tested on Windows and MacOS.
- If possible please run on MacOS
- Only dependency is System.Net.Http
- The build.sh uses csc /r:System.Net.Http.dll
- MUST include /r:System.Net.Http.dll to compile!
- My dotnet --version: 3.1.100