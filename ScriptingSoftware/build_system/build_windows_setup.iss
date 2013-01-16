; -- RD-Tester.iss --

[Setup]
AppName=RD-Tester
AppVersion=1.0
DefaultDirName={pf}\DKM
DefaultGroupName=DKM RD-Tester Utilities
;UninstallDisplayIcon={app}\Uninstall.exe
Compression=lzma2
SolidCompression=yes

[Files]
Source: "Binaries\dist\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
;Name: "{group}\My Program"; Filename: "{app}\MyProg.exe"
