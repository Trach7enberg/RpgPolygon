// Copyright (C) RenZhai.2021.All Rights Reserved.

#include "SimpleProtobufBPLibrary.h"
#include "SimpleProtobuf.h"
#include "UObject/UObjectIterator.h"
#include "UObject/Class.h"
#include "UObject/Field.h"

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif

#if WITH_EDITOR

FName ModuleRelativePath = TEXT("ModuleRelativePath");

void CollectStruct(UStruct* Object, FProto& OutProto);

void UEBaseProtoType(TArray<FProto> &OutDependentStruct)
{
	//FGuid
	{
		FProto &InProto = OutDependentStruct.AddDefaulted_GetRef();
		InProto.OriginalName = TEXT("FGuid");
		InProto.Name = TEXT("FGuidRZ");

		//a
		{
			FProtoElement& ProtoElememt = InProto.Elements.AddDefaulted_GetRef();
			ProtoElememt.ElementName = TEXT("A");
			ProtoElememt.ElementType = TEXT("uint32");
		}
		//b
		{
			FProtoElement& ProtoElememt = InProto.Elements.AddDefaulted_GetRef();
			ProtoElememt.ElementName = TEXT("B");
			ProtoElememt.ElementType = TEXT("uint32");
		}

		//c
		{
			FProtoElement& ProtoElememt = InProto.Elements.AddDefaulted_GetRef();
			ProtoElememt.ElementName = TEXT("C");
			ProtoElememt.ElementType = TEXT("uint32");
		}

		//d
		{
			FProtoElement& ProtoElememt = InProto.Elements.AddDefaulted_GetRef();
			ProtoElememt.ElementName = TEXT("D");
			ProtoElememt.ElementType = TEXT("uint32");
		}
	}

	//FVector
	{
		FProto& InProto = OutDependentStruct.AddDefaulted_GetRef();
		InProto.OriginalName = TEXT("FVector");
		InProto.Name = TEXT("FVectorRZ");

		//a
		{
			FProtoElement& ProtoElememt = InProto.Elements.AddDefaulted_GetRef();
			ProtoElememt.ElementName = TEXT("X");
			ProtoElememt.ElementType = TEXT("float");
		}
		//b
		{
			FProtoElement& ProtoElememt = InProto.Elements.AddDefaulted_GetRef();
			ProtoElememt.ElementName = TEXT("Y");
			ProtoElememt.ElementType = TEXT("float");
		}

		//c
		{
			FProtoElement& ProtoElememt = InProto.Elements.AddDefaulted_GetRef();
			ProtoElememt.ElementName = TEXT("Z");
			ProtoElememt.ElementType = TEXT("float");
		}
	}

	//FVector2D
	{
		FProto& InProto = OutDependentStruct.AddDefaulted_GetRef();
		InProto.OriginalName = TEXT("FVector2D");
		InProto.Name = TEXT("FVector2DRZ");

		//a
		{
			FProtoElement& ProtoElememt = InProto.Elements.AddDefaulted_GetRef();
			ProtoElememt.ElementName = TEXT("X");
			ProtoElememt.ElementType = TEXT("float");
		}
		//b
		{
			FProtoElement& ProtoElememt = InProto.Elements.AddDefaulted_GetRef();
			ProtoElememt.ElementName = TEXT("Y");
			ProtoElememt.ElementType = TEXT("float");
		}
	}

	//FRotator
	{
		FProto& InProto = OutDependentStruct.AddDefaulted_GetRef();
		InProto.OriginalName = TEXT("FRotator");
		InProto.Name = TEXT("FRotatorRZ");

		//a
		{
			FProtoElement& ProtoElememt = InProto.Elements.AddDefaulted_GetRef();
			ProtoElememt.ElementName = TEXT("Pitch");
			ProtoElememt.ElementType = TEXT("float");
		}
		//b
		{
			FProtoElement& ProtoElememt = InProto.Elements.AddDefaulted_GetRef();
			ProtoElememt.ElementName = TEXT("Yaw");
			ProtoElememt.ElementType = TEXT("float");
		}

		//c
		{
			FProtoElement& ProtoElememt = InProto.Elements.AddDefaulted_GetRef();
			ProtoElememt.ElementName = TEXT("Roll");
			ProtoElememt.ElementType = TEXT("float");
		}
	}
}

void BuildStructProperty(FStructProperty* InStructProterty, FProto&OutProto)
{
	if (InStructProterty->Struct)
	{
		CollectStruct(InStructProterty->Struct, OutProto);
	}
}

void CollectStruct(UStruct* Object,FProto &OutProto)
{
	OutProto.OriginalName = TEXT("F") + Object->GetName();
	OutProto.Name = OutProto.OriginalName + TEXT("RZ");

	UE_LOG(LogTemp, Log, TEXT("Name: %s"), *OutProto.OriginalName);
	for (TFieldIterator<FProperty> PropertyIt(Object); PropertyIt; ++PropertyIt)
	{
		if (FProperty* Property = *PropertyIt)
		{
			FProtoElement& InElement = OutProto.Elements.AddDefaulted_GetRef();
			InElement.ElementName = Property->GetName();
			InElement.ElementType = Property->GetCPPType();

			OutProto.Includes.Append(*Property->GetMetaDataMap());
			if (UObject *InObject = Property->GetOwner<UObject>())
			{
				if (InObject->GetOuter())
				{
					OutProto.WhichModule = InObject->GetOuter()->GetName();
					OutProto.WhichModule.RemoveFromStart(TEXT("/Script/"));
				}	
			}

			//只收集结构体
			if (FStructProperty* InMyStruct = CastField<FStructProperty>(Property))
			{
				BuildStructProperty(InMyStruct, InElement.Struct.AddDefaulted_GetRef());
			}
			//对数组的处理
			else if (InElement.ElementType.Equals(TEXT("TMap")))
			{
				if (const FMapProperty* MapProperty = CastField<FMapProperty>(Property))
				{
					if (MapProperty->KeyProp && MapProperty->ValueProp)
					{
						InElement.ElementTypes.AddDefaulted_GetRef() = MapProperty->KeyProp->GetCPPType();
						InElement.ElementTypes.AddDefaulted_GetRef() = MapProperty->ValueProp->GetCPPType();
					
						if (FStructProperty* InKeyStructProterty = CastField<FStructProperty>(MapProperty->KeyProp))
						{
							BuildStructProperty(InKeyStructProterty, InElement.Struct.AddDefaulted_GetRef());
						}

						if (FStructProperty* InValueStructProterty = CastField<FStructProperty>(MapProperty->ValueProp))
						{
							BuildStructProperty(InValueStructProterty, InElement.Struct.AddDefaulted_GetRef());
						}
					}
				}
			}
			else if (InElement.ElementType.Equals(TEXT("TArray")))
			{
				if (const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
				{
					if (ArrayProperty->Inner)
					{
						InElement.ElementTypes.AddDefaulted_GetRef() = ArrayProperty->Inner->GetCPPType();

						if (FStructProperty *InStructProterty = CastField<FStructProperty>(ArrayProperty->Inner))
						{
							BuildStructProperty(InStructProterty, InElement.Struct.AddDefaulted_GetRef());
						}
					}
				}
			}
			else if (InElement.ElementType.Equals(TEXT("TSet")))
			{
				if (const FSetProperty* SetProperty = CastField<FSetProperty>(Property))
				{
					if (SetProperty->ElementProp)
					{
						InElement.ElementTypes.AddDefaulted_GetRef() = SetProperty->ElementProp->GetCPPType();
					
						if (FStructProperty* InStructProterty = CastField<FStructProperty>(SetProperty->ElementProp))
						{
							BuildStructProperty(InStructProterty, InElement.Struct.AddDefaulted_GetRef());
						}
					}
				}
			}
		}
	}
}

bool CollectStructCode(TArray<FProto> &OutProto, const FString& InMetaTag)
{
	for (TObjectIterator<UStruct> It; It; ++It)
	{
		if (UStruct* Object = *It)
		{
			if (Object->HasMetaData(*InMetaTag))
			{
				FProto& InProto = OutProto.AddDefaulted_GetRef();
				CollectStruct(Object, InProto);
			}
		}
	}

	return OutProto.Num() > 0;
}

bool CollectEnumCode(TArray<FProto>& OutProto, const FString& InMetaTag)
{
	for (TObjectIterator<UEnum> It; It; ++It)
	{
		if (UEnum* Object = *It)
		{
			if (Object->HasMetaData(*InMetaTag))
			{
				FProto& InProto = OutProto.AddDefaulted_GetRef();
				InProto.Name = Object->GetName() + TEXT("RZ");
				InProto.OriginalName = Object->GetName();

				UE_LOG(LogTemp, Log, TEXT("Name: %s"), *InProto.OriginalName);

				FString EnumHead = FString::Printf(TEXT("%s::"),*InProto.OriginalName);
				for (int32 i = 0; i < Object->GetMaxEnumValue(); i++)
				{
					FProtoElement& InElement = InProto.Elements.AddDefaulted_GetRef();

					// 获取枚举成员的名称
					InElement.ElementName = Object->GetNameByIndex(i).ToString();
					InElement.ElementName.RemoveFromStart(EnumHead);

					// 获取枚举成员的显示名（如果有的话）
					FText EnumDisplayName = Object->GetDisplayNameTextByIndex(i);

					// 在这里可以执行你想要的操作，例如打印名称
					UE_LOG(LogTemp, Log, TEXT("Enum Member: %s - Display Name: %s"), *InElement.ElementName, *EnumDisplayName.ToString());
				}
			}
		}
	}

	return OutProto.Num() > 0;
}

FString ToProtoType(const FString& UEType,bool bEnumMapKey = false)
{
	if (!UEType.IsEmpty())
	{
		if (UEType.Equals(TEXT("FString")) || UEType.Equals(TEXT("FText")) || UEType.Equals(TEXT("FName")))
		{
			return TEXT("string");
		}
		else if (UEType.Equals(TEXT("uint8")) || UEType.Equals(TEXT("int8")))
		{
			return TEXT("int32");
		}
		else if (UEType.Equals(TEXT("TMap")))
		{
			return TEXT("map");
		}
		else if (UEType.Equals(TEXT("FDateTime")) || UEType.Equals(TEXT("FTimespan")))
		{
			return TEXT("int64");
		}
		else if (UEType.Equals(TEXT("TArray")) || UEType.Equals(TEXT("TSet")))
		{
			return TEXT("repeated");
		}
		else if (UEType[0] == TEXT('E'))//代表枚举
		{
			if (bEnumMapKey)
			{
				return TEXT("int32");
			}	
		}
	}

	return UEType;
}

void GenerateEnumCode(const TArray<FProto> &InProtos,TArray<FString> &OutCodes)
{
	//构建枚举
	for (auto &Tmp : InProtos)
	{
		OutCodes.Add(FString::Printf(TEXT("enum %s"),*Tmp.Name));
		OutCodes.Add(TEXT("{"));
		for(int32 i = 0;i < Tmp.Elements.Num() ;i++)
		{
			OutCodes.Add(FString::Printf(TEXT("\t%s = %i;"), *Tmp.Elements[i].ElementName,i));
		}
		OutCodes.Add(TEXT("}"));

		OutCodes.Add(TEXT(""));
	}
}

void GenerateStructCode(const TArray<FProto>& InProtos, TArray<FString>& OutCodes)
{
	OutCodes.Add(TEXT(""));

	for (auto& Tmp : InProtos)
	{
		OutCodes.Add(FString::Printf(TEXT("message %s"), *Tmp.Name));
		OutCodes.Add(TEXT("{"));
		for (int32 i = 0; i < Tmp.Elements.Num(); i++)
		{
			if (Tmp.Elements[i].ElementType.Equals(TEXT("TMap")))
			{
				if (Tmp.Elements[i].ElementTypes.Num() == 2)
				{
					OutCodes.Add(FString::Printf(TEXT("\t%s<%s,%s> %s = %i;"),
						*ToProtoType(Tmp.Elements[i].ElementType),
						*ToProtoType(Tmp.Elements[i].ElementTypes[0],true),//需要特殊处理 枚举不能为key
						*ToProtoType(Tmp.Elements[i].ElementTypes[1]),
						*Tmp.Elements[i].ElementName,
						i + 1));
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Spawn Map Error"));
				}
			}
			else if (Tmp.Elements[i].ElementType.Equals(TEXT("TArray")) ||
				Tmp.Elements[i].ElementType.Equals(TEXT("TSet")))
			{
				if (Tmp.Elements[i].ElementTypes.Num() == 1)
				{
					OutCodes.Add(FString::Printf(TEXT("\t%s %s %s = %i;"),
						*ToProtoType(Tmp.Elements[i].ElementType),
						*ToProtoType(Tmp.Elements[i].ElementTypes[0]),
						*Tmp.Elements[i].ElementName,
						i + 1));
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Spawn Array Error"));
				}
			}
			else
			{
				OutCodes.Add(FString::Printf(TEXT("\t%s %s = %i;"),
					*ToProtoType(Tmp.Elements[i].ElementType),
					*Tmp.Elements[i].ElementName,
					i + 1));
			}	
		}
		OutCodes.Add(TEXT("}"));

		OutCodes.Add(TEXT(""));
	}
}

void CorrectionType(const TArray<FProto>& BaseProto,TArray<FProtoElement> &Elements)
{
	for (auto &Tmp : Elements)//每一个成员变量
	{
		for (auto &SubTmp : BaseProto)//在标准中寻找
		{
			if (Tmp.ElementType.Equals(SubTmp.OriginalName))//是否有一样名字的
			{
				Tmp.ElementType = SubTmp.Name;//修正
			}
			else	//可能是容器
			{
				for (auto& ElementType : Tmp.ElementTypes)
				{
					if (ElementType.Equals(SubTmp.OriginalName))//是否有一样名字的
					{
						ElementType = SubTmp.Name;//修正
						break;
					}
				}
			}
		}
	}
}

void HandleEnumAndStructProto(const TArray<FProto>& BaseProto, const TArray<FProto>& InProtoEnum, TArray<FProto>& OutProtoStructs)
{
	//修正UE基础的元素
	for (auto& Tmp : OutProtoStructs)
	{
		//对每个元素的类型进行修正
		CorrectionType(BaseProto, Tmp.Elements);
	}

	//修正枚举的元素
	for (auto& Tmp : OutProtoStructs)
	{
		//对每个元素的类型进行修正
		CorrectionType(InProtoEnum, Tmp.Elements);
	}

	//修正自定义结构体的元素
	for (auto& Tmp : OutProtoStructs)
	{
		//对每个元素的类型进行修正
		CorrectionType(OutProtoStructs, Tmp.Elements);
	}
}

bool USimpleProtobufBPLibrary::GenerateProtoCode(
	const TArray<FString>& InGenerateProtoPaths,
	const TArray<FString>& InImportProtoFile,
	const FString& InGenerateProtoFilename,
	const FString& InMetaTag)
{
	int32 ErrorCount = 0;

	TArray<FProto> BaseProto;
	UEBaseProtoType(BaseProto);

	TArray<FProto> ProtoStructs;
	if (!CollectStructCode(ProtoStructs, InMetaTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("Struct not found"));
	}

	TArray<FProto> ProtoEnum;
	if (!CollectEnumCode(ProtoEnum, InMetaTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("enum not found"));
	}

	//主要修正名字的后缀 防止后面生成的代码重复
	HandleEnumAndStructProto(BaseProto, ProtoEnum, ProtoStructs);

	//构建Proto头代码
	TArray<FString> ProtoCodes;
	{
		ProtoCodes.Add(TEXT("syntax=\"proto3\";"));
		ProtoCodes.Add(FString::Printf(TEXT("package %s;"), *InGenerateProtoFilename));
		for (auto& Tmp : InImportProtoFile)
		{
			if (!Tmp.IsEmpty())
			{
				ProtoCodes.Add(FString::Printf(TEXT("import \"%s\";"), *Tmp));
			}
		}
	}

	ProtoCodes.Add(TEXT(""));

	//生成UE的默认基础结构
	GenerateStructCode(BaseProto, ProtoCodes);

	//自定义结构
	//生成枚举和结构体
	GenerateEnumCode(ProtoEnum, ProtoCodes);
	GenerateStructCode(ProtoStructs, ProtoCodes);

	for (auto& Tmp : InGenerateProtoPaths)
	{
		FString ProtoPaths = Tmp / InGenerateProtoFilename + TEXT(".proto");
		FPaths::NormalizeFilename(ProtoPaths);

		if (!FFileHelper::SaveStringArrayToFile(ProtoCodes, *ProtoPaths))
		{
			UE_LOG(LogTemp, Error, TEXT("Generation failed[%s]."), *ProtoPaths);
			ErrorCount++;
		}
	}

	return ErrorCount == 0;
}

void BuildToolTip(const FProto& InProto,TArray<FString>& OutConversion)
{
	if (InProto.Includes.Contains(TEXT("Comment")))
	{
		OutConversion.Add(FString::Printf(TEXT("//%s"), *InProto.Includes["Comment"]));
	}
	else if (InProto.Includes.Contains(TEXT("ToolTip")))
	{
		OutConversion.Add(FString::Printf(TEXT("//%s"), *InProto.Includes["ToolTip"]));
	}
}

void Buildh(
	const FString &APIName,
	const FString& InFilename, 
	const FString &InGenerateProtoFilename,
	const FProto &InProto,
	TArray<FString> &OutConversion)
{
	FString OriginalName = InProto.OriginalName;
	OriginalName.RemoveFromStart(TEXT("F"));

	OutConversion.Add(FString::Printf(TEXT("\tbool %s %sToBytes(const %s &InStruct,TArray<uint8> &OutBytes);"), *APIName, *OriginalName,*InProto.OriginalName));
	OutConversion.Add(FString::Printf(TEXT("\tbool %s BytesTo%s(const TArray<uint8> &InBytes,%s &OutStruct);"), *APIName, *OriginalName,*InProto.OriginalName));
	OutConversion.Add(FString::Printf(TEXT("\tvoid %s %ssToBytes(const TArray<%s> &InStruct,TArray<TArray<uint8>> &OutBytes);"), *APIName, *OriginalName, *InProto.OriginalName));
	OutConversion.Add(FString::Printf(TEXT("\tvoid %s BytesTo%ss(const TArray<TArray<uint8>> &InBytes,TArray<%s> &OutStruct);"), *APIName, *OriginalName, *InProto.OriginalName));

	OutConversion.Add(TEXT(""));
}

void GenerateHBytesConversion(
	const TArray<FProto> &InBaseProto,
	const TArray<FProto> &InProtoStructs,
	const FString& APIName,
	const FString& InFilename,
	const FString& InGenerateProtoFilename,
	const FString& InMetaTag,
	TArray<FString> &OutConversionContent)
{
	OutConversionContent.Add(FString::Printf(TEXT("namespace %s"), *InFilename));
	OutConversionContent.Add(TEXT("{"));
	{
		for (auto &Tmp : InBaseProto)
		{
			Buildh(APIName, InFilename, InGenerateProtoFilename,Tmp, OutConversionContent);
		}

		for (auto& Tmp : InProtoStructs)
		{
			Buildh(APIName, InFilename, InGenerateProtoFilename, Tmp, OutConversionContent);
		}
	}

	OutConversionContent.Add(TEXT("}"));
}

void BuildToBytesElement(
	const FString &InTable,
	const FString &InPointer,
	const FString &InProtoStructName,
	const FString& InUEStructName,
	const FProtoElement &InProtoElement,
	const FString& InGenerateProtoFilename,
	TArray<FString>& OutConversion)
{
	if (!InProtoElement.ElementType.IsEmpty())
	{
		if (InProtoElement.ElementType.Equals(TEXT("TMap")))
		{
			FString MapName = FString::Printf(TEXT("%s_Map"), *InProtoElement.ElementName);
			FString MapElementName = FString::Printf(TEXT("%s_Tmp"), *InProtoElement.ElementName);

			OutConversion.Add(FString::Printf(TEXT("%sauto *%s = %s%smutable_%s();"), *InTable, *MapName, *InProtoStructName, *InPointer, *InProtoElement.ElementName.ToLower()));
			OutConversion.Add(FString::Printf(TEXT("%sfor(auto &%s : %s.%s)"), *InTable, *MapElementName, *InUEStructName, *InProtoElement.ElementName));
			OutConversion.Add(InTable + TEXT("{"));
			if (InProtoElement.ElementTypes.Num() == 2)
			{
				FString ValueName = FString::Printf(TEXT("Value_%s"), *InProtoElement.ElementName);
				if (InProtoElement.Struct.Num() > 0)
				{
					int32 InValue = INDEX_NONE;
					//构建Key
					if (InProtoElement.ElementTypes[0].Equals(TEXT("FString"))) //直接构建
					{
						InValue = 0;

						OutConversion.Add(FString::Printf(TEXT("%s\tauto &%s = (*%s)[TCHAR_TO_UTF8(*%s.Key)];"),
							*InTable,
							*ValueName,
							*MapName,
							*MapElementName));
					}
					else if (InProtoElement.ElementType.Equals(TEXT("FText")) ||
						InProtoElement.ElementType.Equals(TEXT("FName")))
					{
						InValue = 0;

						OutConversion.Add(FString::Printf(TEXT("%s\tauto &%s = (*%s)[TCHAR_TO_UTF8(*%s.Key.ToString())];"), *InTable, *ValueName, *MapName, *MapElementName));
					}
					else if (InProtoElement.ElementTypes[0][0] == TEXT('F'))//结构体 需要构建结构
					{
						InValue = 1;

						//构建key [不清楚key到底是结构体还是基础数据类型]
						FString KeyName = FString::Printf(TEXT("Key_%s"), *InProtoElement.ElementName);
						OutConversion.Add(FString::Printf(TEXT("%s\t%s::%s %s;"), *InTable, *InGenerateProtoFilename, *InProtoElement.ElementTypes[0], *KeyName));

						for (auto& Tmp : InProtoElement.Struct[0].Elements)
						{
							BuildToBytesElement(InTable + TEXT("\t"), TEXT("->"), KeyName, Tmp.ElementName, Tmp, InGenerateProtoFilename, OutConversion);
						}
					}
					else
					{
						InValue = 0;
						OutConversion.Add(FString::Printf(TEXT("%s\tauto &%s = (*%s)[%s.Key];"), *InTable, *ValueName, *MapName, *MapElementName));
					}

					//构建Value
					for (auto& Tmp : InProtoElement.Struct[InValue].Elements)
					{
						BuildToBytesElement(
							InTable + TEXT("\t"),
							TEXT("."),
							ValueName,
							MapElementName + TEXT(".Value"),
							Tmp,
							InGenerateProtoFilename,
							OutConversion);
					}
				}
			}

			OutConversion.Add(InTable + TEXT("}"));
		}
		else if (InProtoElement.ElementType.Equals(TEXT("FString")))
		{
			OutConversion.Add(FString::Printf(TEXT("%s%s%sset_%s(TCHAR_TO_UTF8(*%s.%s));"), *InTable, *InProtoStructName, *InPointer, *InProtoElement.ElementName.ToLower(), *InUEStructName, *InProtoElement.ElementName));
		}
		else if (InProtoElement.ElementType.Equals(TEXT("FText")) || 
			InProtoElement.ElementType.Equals(TEXT("FName")))
		{
			OutConversion.Add(FString::Printf(TEXT("%s%s%sset_%s(TCHAR_TO_UTF8(*%s.%s.ToString()));"), *InTable, *InProtoStructName, *InPointer, *InProtoElement.ElementName.ToLower(), *InUEStructName, *InProtoElement.ElementName));
		}
		else if (InProtoElement.ElementType.Equals(TEXT("TArray")) || 
			InProtoElement.ElementType.Equals(TEXT("TSet")))
		{
			if (InProtoElement.ElementTypes.Num() == 1)
			{
				FString ArrayName = FString::Printf(TEXT("%s_Array"), *InProtoElement.ElementName);
				FString ArrayElementName = FString::Printf(TEXT("%s_Tmp"), *InProtoElement.ElementName);

				OutConversion.Add(FString::Printf(TEXT("%sauto *%s = %s%smutable_%s();"), *InTable, *ArrayName, *InProtoStructName, *InPointer, *InProtoElement.ElementName.ToLower()));
				OutConversion.Add(FString::Printf(TEXT("%sfor(auto &%s : %s.%s)"), *InTable, *ArrayElementName,*InUEStructName, *InProtoElement.ElementName));
				OutConversion.Add(InTable + TEXT("{"));
				{
					if (InProtoElement.Struct.Num() > 0)
					{
						OutConversion.Add(FString::Printf(TEXT("%s\tauto *Elememt = %s->Add();"),
							*InTable,
							*ArrayName));

						for (auto& Tmp : InProtoElement.Struct[0].Elements)
						{
							BuildToBytesElement(InTable + TEXT("\t"),
								TEXT("->"), 
								TEXT("Elememt"),
								ArrayElementName,
								Tmp, 
								InGenerateProtoFilename, 
								OutConversion);
						}
					}
					else if (InProtoElement.ElementTypes.Num() > 0)
					{
						if (InProtoElement.ElementTypes[0][0] == TEXT('E'))//枚举
						{
							OutConversion.Add(FString::Printf(TEXT("%s\t%s->Add((%s::%sRZ)%s);"),
								*InTable,
								*ArrayName,
								*InGenerateProtoFilename,
								*InProtoElement.ElementType,
								*ArrayElementName));
						}
						else if (InProtoElement.ElementTypes[0].Equals(TEXT("FString")))
						{
							OutConversion.Add(FString::Printf(TEXT("%s\t%s->Add_%s(TCHAR_TO_UTF8(*%s));"),
								*InTable,
								*ArrayName,
								*InProtoElement.ElementName.ToLower(),
								*ArrayElementName));
						}
						else if (InProtoElement.ElementTypes[0].Equals(TEXT("FName")) || 
							InProtoElement.ElementTypes[0].Equals(TEXT("FText")))
						{
							OutConversion.Add(FString::Printf(TEXT("%s\t%s->Add_%s(TCHAR_TO_UTF8(*%s.ToString()));"),
								*InTable,
								*ArrayName,
								*InProtoElement.ElementName.ToLower(),
								*ArrayElementName));
						}
						else
						{
							OutConversion.Add(FString::Printf(TEXT("%s\t%s->Add(%s);"),
								*InTable,
								*ArrayName,
								
								*ArrayElementName));
						}
					}
					else
					{
						ensure(0);//不应该走到这里
					}
				}
				OutConversion.Add(InTable + TEXT("}"));
			}
		}
		else if (InProtoElement.ElementType[0] == TEXT('F'))//结构体
		{			
			if (InProtoElement.Struct.Num() > 0)
			{
				if (InProtoElement.Struct[0].Elements.Num() > 0)
				{
					FString GuidString = FGuid::NewGuid().ToString();
					FString StructName = FString::Printf(TEXT("%s_%s_Struct"), *InProtoElement.ElementName, *GuidString.RightChop(28));

					OutConversion.Add(FString::Printf(TEXT("%sauto * %s = %s%smutable_%s();"),
						*InTable,
						*StructName,
						*InProtoStructName,
						*InPointer,
						*InProtoElement.ElementName.ToLower()));

					OutConversion.Add(InTable + TEXT("{"));
					{
						for (auto& Tmp : InProtoElement.Struct[0].Elements)
						{
							BuildToBytesElement(InTable + TEXT("\t"), TEXT("->"), StructName, InUEStructName + TEXT(".") + InProtoElement.ElementName, Tmp, InGenerateProtoFilename, OutConversion);
						}
					}
					OutConversion.Add(InTable + TEXT("}"));
				}
			}
		}
		else if (InProtoElement.ElementType[0] == TEXT('E'))//枚举
		{
			FString ElementType = InProtoElement.ElementType;
			ElementType.RemoveFromEnd(TEXT("RZ"));

			OutConversion.Add(FString::Printf(TEXT("%s%s%sset_%s((%s::%sRZ)%s.%s);"),
				*InTable, 
				*InProtoStructName,
				*InPointer,
				*InProtoElement.ElementName.ToLower(),
				*InGenerateProtoFilename,
				*ElementType,
				*InUEStructName,
				*InProtoElement.ElementName));
		}
		else //普通类型
		{
			OutConversion.Add(FString::Printf(TEXT("%s%s%sset_%s(%s.%s);"), *InTable, *InProtoStructName,*InPointer,*InProtoElement.ElementName.ToLower(),*InUEStructName, *InProtoElement.ElementName));
		}
	}
}

FString BuildBytesToParam(const FString& InProtoStructName,const FString& InElementType)
{
	if (InElementType[0] == TEXT('E'))//枚举
	{
		FString EType = InElementType;
		EType.RemoveFromEnd(TEXT("RZ"));

		return FString::Printf(TEXT("(%s)%s"),*EType,*InProtoStructName);
	}
	else if (InElementType.Equals(TEXT("FString")) ||
		InElementType.Equals(TEXT("FName")))
	{
		return FString::Printf(TEXT("UTF8_TO_TCHAR(%s.c_str())"),*InProtoStructName);
	}
	else if (InElementType.Equals(TEXT("FText")))
	{
		return FString::Printf(TEXT("FText::FromString(UTF8_TO_TCHAR(%s.c_str()))"),
			*InProtoStructName);
	}
	else
	{
		return InProtoStructName;
	}
}

void BuildBytesToElement(
	const FString& InTable,
	const FString& InPointer,
	const FString& InProtoStructName,
	const FString& InUEStructName,
	const FProtoElement& InProtoElement,
	const FString& InGenerateProtoFilename,
	TArray<FString>& OutConversion)
{
	if (!InProtoElement.ElementType.IsEmpty())
	{
		if (InProtoElement.ElementType.Equals(TEXT("TMap")))
		{
			FString MapElementName = FString::Printf(TEXT("%s_Tmp"), *InProtoElement.ElementName);

			OutConversion.Add(FString::Printf(TEXT("%sfor (const auto& %s : %s.%s())"),
				*InTable,
				*MapElementName,
				*InProtoStructName,
				*InProtoElement.ElementName.ToLower()));
			
			OutConversion.Add(InTable + TEXT("{"));
			if (InProtoElement.ElementTypes.Num() == 2)
			{
				FString KeyMapName = FString::Printf(TEXT("%s_KeyMap"), *InProtoElement.ElementName);
				FString ValueMapName = FString::Printf(TEXT("%s_ValueMap"), *InProtoElement.ElementName);
				FString KeyValueString;

				int32 InValueIndex = INDEX_NONE;

				//确定 key
				if (InProtoElement.ElementTypes[0] != TEXT("FString") && 
					InProtoElement.ElementTypes[0][0] == TEXT('F'))
				{
					if (InProtoElement.Struct.Num() > 0)
					{
						OutConversion.Add(FString::Printf(TEXT("%s\t%s %s;"),
							*InTable,
							*InProtoElement.ElementType,
							*KeyMapName));

						OutConversion.Add(TEXT(""));

						for (auto& Tmp : InProtoElement.Struct[0].Elements)
						{
							BuildBytesToElement(InTable + TEXT("\t"),
								TEXT("."),
								MapElementName + TEXT(".first"),
								KeyMapName,
								Tmp,
								InGenerateProtoFilename,
								OutConversion);
						}

						KeyValueString = KeyMapName;

						InValueIndex = 1;
					}
				}
				else
				{
					InValueIndex = 0;
					KeyValueString = BuildBytesToParam(MapElementName + TEXT(".first"), InProtoElement.ElementTypes[0]);
				}

				//添加key
				OutConversion.Add(FString::Printf(TEXT("%s\tauto &%s = %s.Add(%s);"),
					*InTable,
					*ValueMapName,
					*(InUEStructName + TEXT(".") + InProtoElement.ElementName),
					*KeyValueString));

				//准备value
				if (InProtoElement.ElementTypes[1] != TEXT("FString") &&
					InProtoElement.ElementTypes[1][0] == TEXT('F'))
				{
					for (auto& Tmp : InProtoElement.Struct[InValueIndex].Elements)
					{
						BuildBytesToElement(InTable + TEXT("\t"),
							TEXT("."),
							MapElementName + TEXT(".second"),
							ValueMapName,
							Tmp,
							InGenerateProtoFilename,
							OutConversion);
					}
				}
				else
				{
					KeyValueString = BuildBytesToParam(MapElementName + TEXT(".second"), InProtoElement.ElementTypes[1]);
				
					OutConversion.Add(FString::Printf(TEXT("%s\t%s = %s;"),
						*InTable,
						*ValueMapName,
						*KeyValueString));
				}
			}
			OutConversion.Add(InTable + TEXT("}"));
		}
		else if (InProtoElement.ElementType.Equals(TEXT("FString"))||
			 InProtoElement.ElementType.Equals(TEXT("FName")))
		{
			OutConversion.Add(FString::Printf(TEXT("%s%s.%s = UTF8_TO_TCHAR(%s.%s().c_str());"),
				*InTable,
				*InUEStructName,
				*InProtoElement.ElementName,
				*InProtoStructName,
				*InProtoElement.ElementName.ToLower()));
		}
		else if (InProtoElement.ElementType.Equals(TEXT("FText")))
		{
			OutConversion.Add(FString::Printf(TEXT("%s%s.%s = FText::FromString(UTF8_TO_TCHAR(%s.%s().c_str()));"),
				*InTable,
				*InUEStructName,
				*InProtoElement.ElementName,
				*InProtoStructName, 
				*InProtoElement.ElementName.ToLower()));
		}
		else if (InProtoElement.ElementType.Equals(TEXT("TArray")) ||
			InProtoElement.ElementType.Equals(TEXT("TSet")))
		{
			if (InProtoElement.ElementTypes.Num() == 1)
			{
				FString ArrayName = FString::Printf(TEXT("%s_Array"), *InProtoElement.ElementName);
				FString ArrayElementName = FString::Printf(TEXT("%s_Tmp"), *InProtoElement.ElementName);

				OutConversion.Add(FString::Printf(TEXT("%sfor (auto &%s : %s.%s())"), 
					*InTable, 
					*ArrayElementName,
					*InProtoStructName,
					*InProtoElement.ElementName.ToLower()));

				OutConversion.Add(InTable + TEXT("{"));
				{
					if (InProtoElement.Struct.Num() > 0)
					{
						OutConversion.Add(FString::Printf(TEXT("%s\tauto &%s = %s.%s.AddDefaulted_GetRef();"),
							*InTable,
							*ArrayName,
							*InUEStructName,
							*InProtoElement.ElementName));

						OutConversion.Add(TEXT(""));

						for (auto& Tmp : InProtoElement.Struct[0].Elements)
						{
							BuildBytesToElement(InTable + TEXT("\t"),
								TEXT("."),
								ArrayElementName,
								ArrayName,
								Tmp,
								InGenerateProtoFilename,
								OutConversion);
						}
					}
					else if (InProtoElement.ElementTypes.Num() > 0)
					{
						FString ValueString = BuildBytesToParam(ArrayElementName,InProtoElement.ElementTypes[0]);
						{
							OutConversion.Add(FString::Printf(TEXT("%s\t%s.Add(%s);"),
								*InTable,
								*(InUEStructName + TEXT(".") + InProtoElement.ElementName),
								*ValueString));
						}
					}
					else
					{
						ensure(0);//不应该走到这里
					}
				}
				OutConversion.Add(InTable + TEXT("}"));
			}
		}
		else if (InProtoElement.ElementType[0] == TEXT('F'))//结构体
		{
			if (InProtoElement.Struct.Num() > 0)
			{
				if (InProtoElement.Struct[0].Elements.Num() > 0)
				{
					FString GuidString = FGuid::NewGuid().ToString();
					FString StructName = FString::Printf(TEXT("%s_%s_Struct"), *InProtoElement.ElementName, *GuidString.RightChop(28));

					OutConversion.Add(FString::Printf(TEXT("%sauto &%s = %s%s%s();"),
						*InTable,
						*StructName,
						*InProtoStructName,
						*InPointer,
						*InProtoElement.ElementName.ToLower()));

					OutConversion.Add(InTable + TEXT("{"));
					{
						for (auto& Tmp : InProtoElement.Struct[0].Elements)
						{
							BuildBytesToElement(InTable + TEXT("\t"),
								TEXT("."),
								StructName,
								InUEStructName + TEXT(".") + InProtoElement.ElementName,
								Tmp,
								InGenerateProtoFilename,
								OutConversion);
						}
					}

					OutConversion.Add(InTable + TEXT("}"));
				}
			}
		}
		else if (InProtoElement.ElementType[0] == TEXT('E'))//枚举
		{
			FString EType = InProtoElement.ElementType;

			EType.RemoveFromEnd(TEXT("RZ"));
			OutConversion.Add(FString::Printf(TEXT("%s%s.%s = (%s)%s.%s();"),
				*InTable,
				*InUEStructName,
				*InProtoElement.ElementName,
				*EType,
				*InProtoStructName,
				*InProtoElement.ElementName.ToLower()));
		}
		else //普通类型
		{
			OutConversion.Add(FString::Printf(TEXT("%s%s.%s = %s.%s();"),
				*InTable,
				*InUEStructName,
				*InProtoElement.ElementName,
				*InProtoStructName,
				*InProtoElement.ElementName.ToLower()));
		}
	}
}

void BuildToBytesCpp(
	const FString& InFilename,
	const FString& InGenerateProtoFilename,
	const FProto& InProto,
	TArray<FString>& OutConversion)
{
	FString OriginalName = InProto.OriginalName;
	OriginalName.RemoveFromStart(TEXT("F"));

	OutConversion.Add(FString::Printf(TEXT("\tbool %sToBytes(const %s &InStruct,TArray<uint8> &OutBytes)"),*OriginalName,*InProto.OriginalName));
	OutConversion.Add(TEXT("\t{"));
	{
		FString StructName = TEXT("RegistInfoRZ");
		OutConversion.Add(FString::Printf(TEXT("\t\t%s::%s %s;"),*InGenerateProtoFilename,*InProto.Name,*StructName));
		OutConversion.Add(TEXT(""));

		for (auto &Tmp :InProto.Elements)
		{
			BuildToBytesElement(TEXT("\t\t"),TEXT("."),StructName,TEXT("InStruct"), Tmp, InGenerateProtoFilename, OutConversion);
		}

		OutConversion.Add(TEXT(""));

		OutConversion.Add(TEXT("\t\tint32 Size = RegistInfoRZ.ByteSizeLong();"));
		OutConversion.Add(TEXT("\t\tOutBytes.SetNum(Size);"));
		OutConversion.Add(TEXT(""));
		OutConversion.Add(FString::Printf(TEXT("\t\treturn %s.SerializeToArray(OutBytes.GetData(), Size);"),*StructName));
	}
	OutConversion.Add(TEXT("\t}"));
}

void BuildMultipleToBytesCpp(
	const FString& InFilename,
	const FString& InGenerateProtoFilename,
	const FProto& InProto,
	TArray<FString>& OutConversion)
{
	FString OriginalName = InProto.OriginalName;
	OriginalName.RemoveFromStart(TEXT("F"));

	OutConversion.Add(FString::Printf(TEXT("\tvoid %ssToBytes(const TArray<%s> &InStruct,TArray<TArray<uint8>> &OutBytes)"), *OriginalName, *InProto.OriginalName));
	OutConversion.Add(TEXT("\t{"));
	{TArray<TArray<uint8>> OutBytes;
	
		OutConversion.Add(TEXT("\t\tfor(auto &Tmp : InStruct)"));
		OutConversion.Add(TEXT("\t\t{"));
		{
			OutConversion.Add(TEXT("\t\t\tauto &BytesElement= OutBytes.AddDefaulted_GetRef();"));
			OutConversion.Add(FString::Printf(TEXT("\t\t\t%sToBytes(Tmp,BytesElement);"),*OriginalName));
		}
		OutConversion.Add(TEXT("\t\t}"));
	}
	OutConversion.Add(TEXT("\t}"));
}

void BuildBytesToMultipleCpp(
	const FString& InFilename,
	const FString& InGenerateProtoFilename,
	const FProto& InProto,
	TArray<FString>& OutConversion)
{
	FString OriginalName = InProto.OriginalName;
	OriginalName.RemoveFromStart(TEXT("F"));

	OutConversion.Add(FString::Printf(TEXT("\tvoid BytesTo%ss(const TArray<TArray<uint8>> &InBytes,TArray<%s> &OutStructs)"), *OriginalName, *InProto.OriginalName));
	OutConversion.Add(TEXT("\t{"));
	{TArray<TArray<uint8>> OutBytes;

	OutConversion.Add(TEXT("\t\tfor(auto &Tmp : InBytes)"));
	OutConversion.Add(TEXT("\t\t{"));
	{
		OutConversion.Add(TEXT("\t\t\tauto &NewElement= OutStructs.AddDefaulted_GetRef();"));
		OutConversion.Add(FString::Printf(TEXT("\t\t\tBytesTo%s(Tmp,NewElement);"), *OriginalName));
	}
	OutConversion.Add(TEXT("\t\t}"));
	}
	OutConversion.Add(TEXT("\t}"));
}

void BuildBytesToCpp(
	const FString& InFilename,
	const FString& InGenerateProtoFilename,
	const FProto& InProto,
	TArray<FString>& OutConversion)
{
	FString OriginalName = InProto.OriginalName;
	OriginalName.RemoveFromStart(TEXT("F"));

	OutConversion.Add(FString::Printf(TEXT("\tbool BytesTo%s(const TArray<uint8> &InBytes,%s &OutStruct)"), *OriginalName, *InProto.OriginalName));
	OutConversion.Add(TEXT("\t{"));
	{
		FString StructName = TEXT("RegistInfoRZ");
		OutConversion.Add(FString::Printf(TEXT("\t\t%s::%s %s;"), *InGenerateProtoFilename, *InProto.Name, *StructName));
		OutConversion.Add(TEXT(""));

		OutConversion.Add(TEXT("\t\tif(RegistInfoRZ.ParseFromArray(InBytes.GetData(), InBytes.Num()))"));
		OutConversion.Add(TEXT("\t\t{"));
		{
			for (auto& Tmp : InProto.Elements)
			{
				BuildBytesToElement(
					TEXT("\t\t\t"),
					TEXT("."),
					StructName,
					TEXT("OutStruct"),
					Tmp, 
					InGenerateProtoFilename,
					OutConversion);
			}
		}
		OutConversion.Add(TEXT(""));
		OutConversion.Add(TEXT("\t\t\treturn true;"));
		OutConversion.Add(TEXT("\t\t}"));
		OutConversion.Add(TEXT(""));
		OutConversion.Add(TEXT("\t\treturn false;"));
	}
	OutConversion.Add(TEXT("\t}"));
}

void GenerateCPPBytesConversion(
	const TArray<FString> &CPPIncludes,
	const TArray<FProto>& InBaseProto,
	const TArray<FProto>& InProtoStructs,
	const FString& APIName,
	const FString& InFilename,
	const FString& InGenerateProtoFilename,
	const FString& InMetaTag,
	TArray<FString>& OutConversionContent)
{
	OutConversionContent.Add(TEXT("// Copyright (C) RenZhai.2024.All Rights Reserved."));
	
	OutConversionContent.Add(TEXT(""));

	for (auto &Tmp : CPPIncludes)
	{
		OutConversionContent.Add(FString::Printf(TEXT("#include \"%s.h\""),*Tmp));
	}

	OutConversionContent.Add(TEXT(""));

	OutConversionContent.Add(FString::Printf(TEXT("namespace %s"), *InFilename));
	OutConversionContent.Add(TEXT("{"));
	{
		OutConversionContent.Add(TEXT("\t//Mainly targeting individual situations."));
		OutConversionContent.Add(TEXT("\t//Base UE Structure"));
		for (auto& Tmp : InBaseProto)
		{	
			BuildToBytesCpp(InFilename, InGenerateProtoFilename, Tmp, OutConversionContent);
			OutConversionContent.Add(TEXT(""));
			BuildBytesToCpp(InFilename, InGenerateProtoFilename, Tmp, OutConversionContent);
			OutConversionContent.Add(TEXT(""));
		}

		OutConversionContent.Add(TEXT("\t//Custom Structure"));
		for (auto& Tmp : InProtoStructs)
		{		
			BuildToBytesCpp(InFilename, InGenerateProtoFilename, Tmp, OutConversionContent);
			OutConversionContent.Add(TEXT(""));
			BuildBytesToCpp(InFilename, InGenerateProtoFilename, Tmp, OutConversionContent);
			OutConversionContent.Add(TEXT(""));
		}
		
		OutConversionContent.Add(TEXT("\t//Targeting multiple situations."));
		OutConversionContent.Add(TEXT("\t//Base UE Structure"));
		//针对多种情况
		for (auto& Tmp : InBaseProto)
		{
			BuildMultipleToBytesCpp(InFilename, InGenerateProtoFilename, Tmp, OutConversionContent);
			OutConversionContent.Add(TEXT(""));
			BuildBytesToMultipleCpp(InFilename, InGenerateProtoFilename, Tmp, OutConversionContent);
			OutConversionContent.Add(TEXT(""));
		}

		//针对多种情况
		OutConversionContent.Add(TEXT("\t//Custom Structure"));
		for (auto& Tmp : InProtoStructs)
		{
			BuildMultipleToBytesCpp(InFilename, InGenerateProtoFilename, Tmp, OutConversionContent);
			OutConversionContent.Add(TEXT(""));
			BuildBytesToMultipleCpp(InFilename, InGenerateProtoFilename, Tmp, OutConversionContent);
			OutConversionContent.Add(TEXT(""));
		}
	}

	OutConversionContent.Add(TEXT("}"));
}

bool USimpleProtobufBPLibrary::GenerateBytesConversion(
	const TArray<FString>& CPPIncludes,
	const FString& APIName,
	const FString& InFilename,
	const FString& InHPath,
	const FString& InCPPPath,
	const FString& InGenerateProtoFilename,
	const FString& InMetaTag)
{
	int32 ErrorCount = 0;

	TArray<FProto> BaseProto;
	UEBaseProtoType(BaseProto);

	TArray<FProto> ProtoStructs;
	if (!CollectStructCode(ProtoStructs, InMetaTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("Struct not found"));
	}

	TArray<FProto> ProtoEnum;
	if (!CollectEnumCode(ProtoEnum, InMetaTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("enum not found"));
	}

	//主要修正名字的后缀 防止后面生成的代码重复
	HandleEnumAndStructProto(BaseProto, ProtoEnum, ProtoStructs);

	TArray<FString> HFiles;
	{
		HFiles.Add(TEXT("// Copyright (C) RenZhai.2024.All Rights Reserved."));
		HFiles.Add("");
		HFiles.Add(TEXT("#pragma once"));
		HFiles.Add("");

		TMap<FString, FString> SelfIncludes;
		TArray<FString> WhichModules;

		for (auto &Tmp : ProtoStructs)
		{
			if (Tmp.Includes.Contains(ModuleRelativePath))
			{
				FString RelativePath = Tmp.Includes[ModuleRelativePath];
				RelativePath.RemoveFromStart(TEXT("Public/"));

				SelfIncludes.Add(RelativePath,Tmp.WhichModule);
			}
		}	

		for (auto &Tmp: SelfIncludes)
		{
			HFiles.Add(FString::Printf(TEXT("#include \"%s\"//This header file belongs to this [%s] module, make sure it is already included."),
				*Tmp.Key,
				*Tmp.Value));
		}

		HFiles.Add("");
	}

	GenerateHBytesConversion(
		BaseProto,
		ProtoStructs,
		APIName,
		InFilename,
		InGenerateProtoFilename,
		InMetaTag,
		HFiles);

	TArray<FString> CPPFiles;
	GenerateCPPBytesConversion(
		CPPIncludes,
		BaseProto,
		ProtoStructs,
		APIName,
		InFilename,
		InGenerateProtoFilename,
		InMetaTag,
		CPPFiles);

	if (HFiles.Num() > 0)
	{
		if (FFileHelper::SaveStringArrayToFile(HFiles, 
			*(InHPath / InFilename + TEXT(".h")), 
			FFileHelper::EEncodingOptions::ForceUTF8))
		{
			if (CPPFiles.Num() > 0)
			{
				if (FFileHelper::SaveStringArrayToFile(CPPFiles, 
					*(InCPPPath / InFilename + TEXT(".cpp")),
					FFileHelper::EEncodingOptions::ForceUTF8))
				{
					return true;
				}
			}
		}
	}

	return false;
}

#else
bool USimpleProtobufBPLibrary::GenerateProtoCode(
	const TArray<FString>& InGenerateProtoPaths,
	const TArray<FString>& InImportProtoFile,
	const FString& InGenerateProtoFilename,
	const FString& InMetaTag)
{
	return false;
}

bool USimpleProtobufBPLibrary::GenerateBytesConversion(
	const TArray<FString>& Includes,
	const FString& APIName,
	const FString& InFilename,
	const FString& InHPath,
	const FString& InCPPPath,
	const FString& InGenerateProtoFilename,
	const FString& InMetaTag)
{
	return false;
}

#endif

/*
* 基础教学
* 标量值类型
*	double				-	对应C++中的double，								64位浮点数。
*	float				-	对应C++中的float，								32位浮点数。
*	int32				-	对应C++中的int32_t，								使用变长编码，适合32位整数。
*	int64				-	对应C++中的int64_t，								使用变长编码，适合64位整数。
*	uint32				-	对应C++中的uint32_t，								使用变长编码，适合无符号32位整数。
*	uint64				-	对应C++中的uint64_t，								使用变长编码，适合无符号64位整数。
*	sint32				-	对应C++中的int32_t，								使用变长编码，有符号整数优化。
*	sint64				-	对应C++中的int64_t，								使用变长编码，有符号整数优化。
*	fixed32				-	对应C++中的uint32_t，								固定长度32位，无符号。
*	fixed64				-	对应C++中的uint64_t，								固定长度64位，无符号。
*	sfixed32			-	对应C++中的int32_t，								固定长度32位，有符号。
*	sfixed64			-	对应C++中的int64_t，								固定长度64位，有符号。
*	bool				-	对应C++中的bool，									布尔类型。
*	string				-	对应C++中的std::string，							UTF-8或ASCII编码的字符串。
*	bytes				-	对应C++中的std::string或std::vector<char>，		用于存储任意字节序列。
* 
* 复合类型
* 	消息类型 (Message)	-	自定义复杂类型，可以包含上述标量值类型以及其他消息类型。
* 							在C++中，每个消息类型都会被编译成一个类。
* 
* 	枚举类型 (Enum)		-	定义一组命名的整数常量。在C++中，protobuf枚举被编译为一个特殊的枚举类。
* 
* 特殊类型
* 	repeated字段			-	用于表示字段可以重复任意次数，类似于C++中的std::vector<T>，
* 							其中T是上述任意protobuf类型。
* 
* 	map字段				-	用于表示键值对的集合，类似于C++中的std::map<KeyType,ValueType>
* 							其中KeyType可以是任意标量值类型（除了float和double）
* 							ValueType可以是标量值类型或消息类型
*/

#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif
