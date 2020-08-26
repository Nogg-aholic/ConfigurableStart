// ILikeBanas

#pragma once

#include "Core.h"
#include "Engine.h"
#include <string>
#include "../../Source/SML/util/Logging.h"
#include "../../Source/SML/mod/ModHandler.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "SML/util/Logging.h"
#include "FGResourceScanner.h"
#include "ResourceNodeSetup_BPLib.generated.h"

/**
 * 
 */
UCLASS()
class UResourceNodeSetup_BPLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		// Sort an Array of Integers
		UFUNCTION(BlueprintCallable, Category = "Sorting Functions")
		static void  Integer_Sort(UPARAM(ref) TArray <int32> &Array_To_Sort, bool Descending, TArray <int32> &Sorted_Array);
	// Sort an Array of Floats																							
	UFUNCTION(BlueprintCallable, Category = "Sorting Functions")
		static void  Float_Sort(UPARAM(ref) TArray <float> &Array_To_Sort, bool Descending, TArray <float> &Sorted_Array);
	// Sort an Array of Strings
	UFUNCTION(BlueprintCallable, Category = "Sorting Functions")
		static void  String_Sort(UPARAM(ref) TArray <FString> &Array_To_Sort, bool Descending, TArray <FString> &Sorted_Array);


	UFUNCTION(BlueprintCallable, Category = "FileSystem Functions")
		static bool LoadStringFromFile(UPARAM(ref)FString& String, FString  FileName)
	{
		const TCHAR* Test = *FileName;
		return FFileHelper::LoadFileToString(String, Test);
	}

	UFUNCTION(BlueprintCallable, Category = "FileSystem Functions")
		static bool FindFilesInPath(UPARAM(ref)TArray<FString>& Result, FString InPath, bool Files, bool Directories)
	{
		const TCHAR* Test = *InPath;
		IFileManager::Get().FindFiles(Result, Test, Files, Directories);
		return true;
	}

	UFUNCTION(BlueprintCallable, Category = "FileSystem Functions")
		static FORCEINLINE bool VerifyOrCreateDirectory(const FString& TestDir)
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		if (!PlatformFile.DirectoryExists(*TestDir))
		{
			PlatformFile.CreateDirectory(*TestDir);

			if (!PlatformFile.DirectoryExists(*TestDir))
			{
				return false;
			}
		}
		return true;
	}

	UFUNCTION(BlueprintCallable, Category = "FileSystem Functions")
		static void WriteStringToFile(FString Path, FString resultString);


public:

	static TSharedPtr<FJsonValue> convertUPropToJsonValue(UProperty* prop, void* ptrToProp);
	static FString SanitizeJsonString(FString write, bool some);
	UClass * GetActiveLoadClass(const FModPakLoadEntry & entry, bool isMenuWorld);
	static TSharedPtr<FJsonObject> convertUStructToJsonObject(UStruct* Struct, void* ptrToStruct);
	static TSharedPtr<FJsonObject> convertUStructToJsonObjectWithName(UStruct * Struct, void * ptrToStruct, FString Name);
	UFUNCTION(BlueprintPure, Category = "Map")
	static FVector2D LocationToMapLocation(FVector InLoc);
	UFUNCTION(BlueprintPure, Category = "Map")
	static FVector MaptoWorldLocation(FVector2D InLoc);
	UFUNCTION(BlueprintCallable, Category = "Map")
	static void RebuildScannerMap(AFGResourceScanner * ref);
	static void convertJsonObjectToUStruct(TSharedPtr<FJsonObject> json, UStruct* Struct, void* ptrToStruct);
	static void convertJsonValueToUProperty(TSharedPtr<FJsonValue> json, UProperty* prop, void* ptrToProp);






	UFUNCTION(BlueprintCallable, Category = "Json", CustomThunk, meta = (CustomStructureParam = "Structure"))
		static void GetStructAsJson(UPARAM(ref)FString &String, UProperty *Structure);

	DECLARE_FUNCTION(execGetStructAsJson)
	{
		PARAM_PASSED_BY_REF(String, UStrProperty, FString);
		Stack.Step(Stack.Object, NULL);

		UStructProperty* StructureProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);

		void* StructurePtr = Stack.MostRecentPropertyAddress;

		P_FINISH;
		InternalGetStructAsJson(StructureProperty, StructurePtr, String);
	}
	static void InternalGetStructAsJson(UStructProperty *Structure, void * StructurePtr, FString &String);

	TArray<TSubclassOf<ASMLInitMod>>  GetModActors(UWorld * World, bool bIsMenuWorld);


	UFUNCTION(BlueprintCallable, Category = "Json", CustomThunk, meta = (CustomStructureParam = "Structure"))
		static void StructfromJson(const FString& String, UPARAM(ref) UProperty*& Structure);

	DECLARE_FUNCTION(execStructfromJson) {
		FString String;
		Stack.StepCompiledIn<UStrProperty>(&String);
		Stack.Step(Stack.Object, NULL);

		UStructProperty* Struct = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;

		P_FINISH;

		TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(*String);
		FJsonSerializer Serializer;
		TSharedPtr<FJsonObject> result;
		Serializer.Deserialize(reader, result);
		convertJsonObjectToUStruct(result, Struct->Struct, StructPtr);
	}



};
