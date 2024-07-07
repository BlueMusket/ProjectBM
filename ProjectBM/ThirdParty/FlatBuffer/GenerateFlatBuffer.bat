SET solutionPath=%1
SET outPath=%2
SET fbs=%3

echo MakeFlat %fbs%

cd /d %solutionPath%..\ProjectBM\ThirdParty\FlatBuffer

start "" "flatc.exe" -c -o %outPath% %outPath%\%fbs%

pause

exit