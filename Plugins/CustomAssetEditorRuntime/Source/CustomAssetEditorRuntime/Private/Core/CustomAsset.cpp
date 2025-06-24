// Garrett Gan All Right Reserved


#include "Core/CustomAsset.h"

#define LOCTEXT_NAMESPACE "CustomAsset"

FString UCustomAsset::ToString()
{
	const FText FormatTemplate = LOCTEXT("MyFormatKey", "SomeData: {0}, SomeNumber: {1}, SomeBool: {2}");
	FText       ResultText     = FText::Format(
	                                 FormatTemplate,
	                                 FText::FromString(SomeData) /* {0} */,
	                                 FText::AsNumber(SomeNumber) /* {1} */,
	                                 SomeBool /* {2} */
		                                 ? FText::FromString(TEXT("True"))
		                                 : FText::FromString(TEXT("False"))
	                                );
	return ResultText.ToString();
}

#undef LOCTEXT_NAMESPACE
