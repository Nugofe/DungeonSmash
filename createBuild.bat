@REM change working directory to current dir where the .bat is located  (by default, the workdir is the directory from where the .bat is called)
pushd %~dp0

@REM get current date and hour
for /f "tokens=2 delims==" %%a in ('wmic OS Get localdatetime /value') do set "dt=%%a"
set "YY=%dt:~2,2%" & set "YYYY=%dt:~0,4%" & set "MM=%dt:~4,2%" & set "DD=%dt:~6,2%"
set "HH=%dt:~8,2%" & set "Min=%dt:~10,2%" & set "Sec=%dt:~12,2%"
set "fullstamp=%YYYY%-%MM%-%DD%__%HH%-%Min%-%Sec%"

@REM create a folder in the $(SolutionDir) called "ProjectBuild_Date_Hour" 
md .\ProjectBuild__%fullstamp%

@REM copy .exe and glut.dll into the new folder
xcopy /s .\bin\UbiAPI\Release\x64\*.exe .\ProjectBuild__%fullstamp%
xcopy /s .\bin\UbiAPI\Release\x64\*.dll .\ProjectBuild__%fullstamp%

@REM copy Assets folder into the new folder
xcopy /E /I .\Assets .\ProjectBuild__%fullstamp%\Assets

@REM move the folder to the route C:\Users\nugof\Dropbox
move .\ProjectBuild__%fullstamp% C:\Users\nugof\Dropbox\Ubisoft\ProjectBuilds

@REM restore working directory
popd