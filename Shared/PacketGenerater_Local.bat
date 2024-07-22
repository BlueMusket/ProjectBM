SET solutionPath=C:\Programming\ProjectBM\Server\
SET projectPath=C:\Programming\ProjectBM\Shared\

start "" "%solutionPath%..\ProjectBM\ThirdParty\FlatBuffer\GenerateFlatBuffer.bat" %solutionPath% %projectPath% Shared.fbs

exit