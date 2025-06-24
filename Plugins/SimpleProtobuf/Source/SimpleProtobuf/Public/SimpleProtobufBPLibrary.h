// Copyright (C) RenZhai.2021.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SimpleProtobufType.h"
#include "SimpleProtobufBPLibrary.generated.h"

/*
 * DocURL：			    https://renzhai.net/420.html
 * Here's how to develop the current plug-in
 * MarketplaceURL :     https://www.aboutcg.org/courseDetails/1269/introduce
 * If you want to learn more about the UE4 tutorial, please refer to:
 * URL :				https://zhuanlan.zhihu.com/p/60117613
 * If you want to learn about the series of tutorials and related plug-ins, you can follow my blog
 * URL :				http://renzhai.net/
 * If you want to know our next course arrangement,
 * you can search the WeChat public house for your attention, then we will push a lot of technical articles.
 * Sina blog            https://weibo.com/bzrz/profile?S=6cm7d0 // this blog hasn't been used for three or four years now.
 * Maybe you can re enable the first connection later
*/

UCLASS()
class SIMPLEPROTOBUF_API USimpleProtobufBPLibrary : public UObject
{
	GENERATED_BODY()

public:
	//将引擎里面的标记后代码生成指定内容
	UFUNCTION(BlueprintCallable, Category = "Proto")
	static bool GenerateProtoCode(
		const TArray<FString>& InGenerateProtoPaths,
		const TArray<FString>& InImportProtoFile,
		const FString& InGenerateProtoFilename = TEXT("ProtoCode"),
		const FString& InMetaTag = TEXT("Proto"));

	//将引擎里面的标记后代码生成指定内容
	UFUNCTION(BlueprintCallable, Category = "Proto")
	static bool GenerateBytesConversion(
		const TArray<FString>& Includes,
		const FString& APIName,
		const FString& InFilename,
		const FString& InHPath,
		const FString& InCPPPath,
		const FString& InGenerateProtoFilename = TEXT("ProtoCode"),
		const FString& InMetaTag = TEXT("Proto"));
};
