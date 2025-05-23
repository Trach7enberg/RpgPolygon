# Standalone
start "UnrealEngine standalone1" "D:\Epic\UE_5.2\Engine\Binaries\Win64\UnrealEditor.exe" "D:\Epic\Projects\PuzzlePlatforms\PuzzlePlatforms.uproject" /Game/ThirdPerson/Maps/ThirdPersonMap -game -log

# Headless Dedicated server
start "UnrealEngine server 1" "D:\UnRealEngine\UE_5.4\Engine\Binaries\Win64\UnrealEditor.exe" "E:\OneDrive\Unreal\UE5Project\Multiplayer\OnlineMenuSystem\OnlineMenuSystem.uproject" /Game/ThirdPerson/Maps/Test -server -log

# Client
start "UnrealEngine client 1" "D:\UnRealEngine\UE_5.4\Engine\Binaries\Win64\UnrealEditor.exe" "E:\OneDrive\Unreal\UE5Project\Multiplayer\OnlineMenuSystem\OnlineMenuSystem.uproject" -port=7779 -game -log
