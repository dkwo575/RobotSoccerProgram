# Robot Soccer Software
### Instruction
- There are many errors such as version, configuration error, dependency errors, etc
- To figure out this error, I will suggest this instruction.

1. Use Visual Studio rather than Visual Studio Code. It is easier to compile.
2. This program was compiled in 32 bits, and we will compile this program in 64 bits.
3. To figure out this, project -> properties -> configuration manager -> create x64 in solution platform




### Error
#### ATL error
1. Open Visual Studio Installer, then click modify and Search ATL.
2. Then install the latest version build tool for ATL.

#### Use of MFC and runtime error
- https://m.blog.naver.com/wsi5555/221249199612
- 
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
