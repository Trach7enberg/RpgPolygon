一.环境部署
1.先打开GenerateProtobuf.bat 里面有如下的内容：
start %~dp0Content\Engine\Binaries\Win64\ProtobufProgram.exe -CompressPath=%~dp0Content\google.rz -OutPutProtobufPath=G:\DigitalHuman\Source\DigitalHuman
将 -OutPutProtobufPath=的内容指向自己的工程源目录.点击生成

2.在项目的build.cs下加入如下内容：
        ShadowVariableWarningLevel = WarningLevel.Off;
 
        bEnableUndefinedIdentifierWarnings = false;
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            bEnableExceptions = true;
        }

        PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");
        PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI=1");
        PublicDefinitions.Add("GOOGLE_PROTOBUF_CMAKE_BUILD");

3.编译，直到成功

二.生成prot代码
1.打开GenerateProtobufCPP.bat 这个文件
%~dp0Content\Engine\Binaries\Win64\protoc.exe --cpp_out=G:/DigitalHuman/Source/DigitalHuman/REF/ .\CPPScriptTestCPPProto.proto
将里面的--cpp-out=设置你自己写的proto里面 ./xxxx这个是指定你自己写的.proto
--cpp_out=你想生成的cpp位置 ./你定义的proto位置

2.点击运行即可生成对应代码。
3.proto的位置目前是相对位置，绝对位置会出错，如果希望指定一个公共的位置，可以拷贝content里面的protoc.exe到自己公共的位置即可

三.CPPScript
这里有赠送方便测试的.proto文件，可以移动到自己工程方便测试，生成代码，以及运行。