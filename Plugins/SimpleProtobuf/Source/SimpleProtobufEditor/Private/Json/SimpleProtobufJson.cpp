// Copyright (C) RenZhai.2021.All Rights Reserved.

#include "Json/SimpleProtobufJson.h"
#include "UObject/SimpleProtobufCompileInfo.h"
#include "UObject/SimpleProtobufInstallInfo.h"
#include "Json.h"

namespace SimpleProtobufJson
{
	void Serialize(USimpleProtobufObject* InObject, FString& OutJsonString)
	{
		TSharedPtr<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter =
			TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJsonString);

		JsonWriter->WriteArrayStart();
		{
			JsonWriter->WriteObjectStart();
			{
				JsonWriter->WriteValue(TEXT("CMD"),TEXT("protobuf"));
				JsonWriter->WriteValue(TEXT("ProtocExe"), FPaths::ConvertRelativePathToFull(InObject->ProtoExe.FilePath));
				JsonWriter->WriteValue(TEXT("bPause"), InObject->bPause);
				JsonWriter->WriteValue(TEXT("CallType"), TEXT("bat"));

				if (InObject->IsA(USimpleProtobufCompileInfo::StaticClass()))
				{
					JsonWriter->WriteValue(TEXT("ProtobufMethod"), TEXT("compile"));
				}
				else
				{
					JsonWriter->WriteValue(TEXT("ProtobufMethod"), TEXT("Install"));
				}

				JsonWriter->WriteArrayStart(TEXT("SrcToTarget"));
				for (auto& Tmp : InObject->Maps)
				{
					JsonWriter->WriteObjectStart();
					{
						JsonWriter->WriteValue(TEXT("Key"), Tmp.Key);
						JsonWriter->WriteValue(TEXT("Value"), Tmp.Value);
					}
					JsonWriter->WriteObjectEnd();
				}
				JsonWriter->WriteArrayEnd();
			}
			JsonWriter->WriteObjectEnd();
		}
		JsonWriter->WriteArrayEnd();
		JsonWriter->Close();
	}

	void Deserialize(const FString& InJsonString, USimpleProtobufObject* InProtobufObject)
	{
		TArray<TSharedPtr<FJsonValue>> JsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(InJsonString);

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			for (auto &Tmp : JsonObject)
			{
				if (const TSharedPtr<FJsonObject>& InObject = Tmp->AsObject())
				{
					InProtobufObject->bPause = InObject->GetBoolField(TEXT("bPause"));

					const TArray<TSharedPtr<FJsonValue>> &InSrcToTargetArray = InObject->GetArrayField(TEXT("SrcToTarget"));
					for (auto &SubTmp : InSrcToTargetArray)
					{
						if (const TSharedPtr<FJsonObject>& InSubTmpObject = SubTmp->AsObject())
						{
							FProtobufMap &InProtobuf = InProtobufObject->Maps.AddDefaulted_GetRef();
							InProtobuf.Key = InSubTmpObject->GetStringField(TEXT("Key"));
							InProtobuf.Value = InSubTmpObject->GetStringField(TEXT("Value"));
						}
					}
				}
			}
		}
	}
}