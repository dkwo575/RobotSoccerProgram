# Robot Soccer Software
### Instruction
- There are many errors such as version, configuration error, dependency errors, etc
- To figure out this error, I will suggest this instruction.

1. Use Visual Studio rather than Visual Studio Code. It is easier to compile.
2. This program was compiled in 32 bits, and we will compile this program in 64 bits.
3. To figure out this, project -> properties -> configuration manager -> create x64 in solution platform




### Error
#### Platform error
1. Project property -> general -> change platform toolset to the latest version.

#### ATL error
1. Open Visual Studio Installer, then click modify and Search ATL.
2. Then install the latest version build tool for ATL.

#### Use of MFC and runtime error,  Error C1189
1. Project > Properties > General > Use of MFC  => Use MFC in a Static Library or Use MFC in a Shared DLL
2. Project > Properties > C/C++ > Code Generation > Runtime Library  => Multi-Threaded DLL (/MTd) or Multi-Threaded Debug DLL (/MDd)
- link: https://m.blog.naver.com/wsi5555/221249199612

#### C1047 error, compiler version error
1. Open project Setting -> c/c++ -> command line, then check this option is in there or not (/source-charset:utf-8 and /execution-charset:utf-8)
2. Project setting -> c/c++ -> check compiler version
3. Project setting -> Linker -> add link of library

#### Program run error
1. The program is not open on some Windows 10 and Windows 11 computers.
2. The application is open and closed directly. The program crashed with the ntdll.dll file, which is a core program in Windows

#### Compile to 64-bit
1. To upgrade the program, if it is compiled in 64-bit, it shows an LNK2001 error, which is a linking error.
2. The error means that the current compiled program and library file cannot linked.
3. The reason is that the current library file is made under 32-bit, and it's suitable for 32-bit programs.
4. Therefore, If this program is compiled 64bit, it cannot link.

#### Compile to 32-bit
1. If I compile this program in 32-bit, it is successfully compiled.
2. However, sometimes the program turns off directly after opening.
3. To check the error, open the event viewer. Press window key + R and enter eventvwr.msc.
4. When you see the event viewer, the user can find errors in the program.
5. This program keeps crashing with the ntdll.dll file.

#### Migrating C/C++ from 32-bit to 64-bit
1. Project Property -> Configuration Manager -> add x64 platform
2. property -> Linker -> advanced -> change to MachineX64 (MACHINE:X64)
3. property ->c/c++ -> preprocessor -> delete WIN32 and add _WIN64
4. Change library or header file to 64bit
5. Change variable type

- int -> INT64, __int64, long long
- long -> LONG64, __int64, long long
- unsigned int -> UINT64, usigned __int64, unsigned long long
- unsigned long -> ULONG64, usigned __int64, unsigned long long

- variable type which end _PTR, it changed variable type depends on compiler type is 32bit or 64bit.
- ex) INT_PTR, UINT_PTR, LONG_PTR, ULONG_PTR

6. If this program works in 32-bit and 64-bit together, we need to change the variables like in this example.
- (ex) int -> INT_PTR, UINT -> UINT_PTR ...
- void onTimer(UINT nIDEvent)  ==> void onTimer(UINT_PTR nIDEvent)

7. change function
- EX) LONG onAcadKeepFocus(UINT, LONG) ==> LRESULT onAcadKeepFocus(WPARAM wParam, LPARAM lParam)


