<####>
# msbuild Phoenix.sln 
# msbuild /nologo /t:Rebuild;Win32;ARM /p:Configuration=Release Phoenix.sln

IEX -Command "msbuild /nologo  /t:Rebuild;Win32;ARM /p:Configuration=Release Phoenix.sln"