SET solutionPath=%1
SET projectPath=%2

start "" "%solutionPath%..\ProjectBM\ThirdParty\FlatBuffer\GenerateFlatBuffer.bat" %solutionPath% %projectPath% Shared.fbs

exit