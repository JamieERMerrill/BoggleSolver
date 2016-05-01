set build_dir=%1
set target_dir=%2

echo Copying from %build_dir%
echo Copying to %target_dir%

if not exist "%target_dir%\data" mkdir "%target_dir%\data"
xcopy /Y /S "%build_dir%\data\*" "%target_dir%\data"