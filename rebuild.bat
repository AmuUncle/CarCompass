del /f /s /q  ".\Makefile*"


set CUR_PATH=%~dp0
set INCLUDE_PATH=%CUR_PATH%\include
set SOURCE_PATH=%CUR_PATH%\source
set UI_PATH=%CUR_PATH%\ui
set RES_PATH=%CUR_PATH%\res

if not exist %INCLUDE_PATH% md %INCLUDE_PATH%
if not exist %SOURCE_PATH% md %SOURCE_PATH%
if not exist %UI_PATH% md %UI_PATH%
if not exist %RES_PATH% md %RES_PATH%

move "*.h" %INCLUDE_PATH%
move "*.cpp" %SOURCE_PATH%
move "*.ui" %UI_PATH%
move "*.qrc" %RES_PATH%
