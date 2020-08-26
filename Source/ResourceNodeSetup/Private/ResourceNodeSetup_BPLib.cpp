// ILikeBanas



#include "../Public/ResourceNodeSetup_BPLib.h"
#include "../../Source/SML/mod/actor/SMLInitMod.h"


void UResourceNodeSetup_BPLib::Integer_Sort(UPARAM(ref) TArray <int32> &Array_To_Sort, bool Descending, TArray <int32> &Sorted_Array)
{
	int32 m = Array_To_Sort.Num();          // Return the array size
	int32 a, k;
	bool bDidSwap;

	for (a = 0; a < (m - 1); a++)
	{
		bDidSwap = false;

		if (Descending == true)         // If element 1 is less than element 2 move it back in the array (sorts high to low)
		{
			for (k = 0; k < m - a - 1; k++)
			{
				if (Array_To_Sort[k] < Array_To_Sort[k + 1])
				{
					int32 z;
					z = Array_To_Sort[k];
					Array_To_Sort[k] = Array_To_Sort[k + 1];
					Array_To_Sort[k + 1] = z;
					bDidSwap = true;
				}
			}

			if (bDidSwap == false)      // If no swaps occured array is sorted do not go through last loop
			{
				break;
			}
		}
		else
		{
			Array_To_Sort.Sort();       // If array will be sorted low to high use Unreal's "Sort" function
		}
	}

	Sorted_Array = Array_To_Sort;
}

void UResourceNodeSetup_BPLib::Float_Sort(UPARAM(ref) TArray <float> &Array_To_Sort, bool Descending, TArray <float> &Sorted_Array)
{
	int32 m = Array_To_Sort.Num();      // Return the array size
	int32 a, k;
	bool bDidSwap;

	for (a = 0; a < (m - 1); a++)
	{
		bDidSwap = false;

		if (Descending == true)         // If element 1 is less than element 2 move it back in the array (sorts high to low)
		{
			for (k = 0; k < m - a - 1; k++)
			{
				if (Array_To_Sort[k] < Array_To_Sort[k + 1])
				{
					float z;
					z = Array_To_Sort[k];
					Array_To_Sort[k] = Array_To_Sort[k + 1];
					Array_To_Sort[k + 1] = z;
					bDidSwap = true;
				}
			}

			if (bDidSwap == false)      // If no swaps occured array is sorted do not go through last loop
			{
				break;
			}
		}
		else
		{
			Array_To_Sort.Sort();       // If array will be sorted low to high use Unreal's "Sort" function
		}
	}

	Sorted_Array = Array_To_Sort;
}

void UResourceNodeSetup_BPLib::String_Sort(UPARAM(ref) TArray <FString> &Array_To_Sort, bool Descending, TArray <FString> &Sorted_Array)
{
	Array_To_Sort.Sort();               // Sort array using built in function (sorts A-Z)

	if (Descending == true)
	{
		TArray <FString> newarray;      // Define "temp" holding array
		int x = Array_To_Sort.Num() - 1;

		while (x > -1)
		{
			newarray.Add(Array_To_Sort[x]); // loop through A-Z sorted array and remove element from back and place it in beginning of "temp" array
			--x;
		}

		Array_To_Sort = newarray;   // Set reference array to "temp" array order, array is now Z-A
	}

	Sorted_Array = Array_To_Sort;
}


void UResourceNodeSetup_BPLib::WriteStringToFile(FString Path, FString resultString) {

	FString RelativePath = FPaths::ProjectDir();
	RelativePath.Append(Path);
	FFileHelper::SaveStringToFile(resultString, *RelativePath);
}

TSharedPtr<FJsonObject> UResourceNodeSetup_BPLib::convertUStructToJsonObject(UStruct* Struct, void* ptrToStruct) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		obj->SetField(prop->GetNameCPP(), convertUPropToJsonValue(*prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct)));
	}
	return obj;
}

TSharedPtr<FJsonObject> UResourceNodeSetup_BPLib::convertUStructToJsonObjectWithName(UStruct* Struct, void* ptrToStruct, FString Name) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	obj->SetStringField("Name", Name);
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		obj->SetField(prop->GetName(), convertUPropToJsonValue(*prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct)));
	}
	return obj;
}

FVector2D UResourceNodeSetup_BPLib::LocationToMapLocation(FVector InLoc) {
		
	return FVector2D(((InLoc.X + 325342.0f) / 752718.f), ((InLoc.Y + 376359.0f) / 752468.f));
}

FVector UResourceNodeSetup_BPLib::MaptoWorldLocation(FVector2D InLoc) {

	return FVector(((InLoc.X  * 752718.f) - 325342.0f), ((InLoc.Y * 752468.f) - 376359.0f),0.f);
}


void UResourceNodeSetup_BPLib::RebuildScannerMap(AFGResourceScanner * ref) {
	ref->GenerateNodeClustersAccessor();
}

void UResourceNodeSetup_BPLib::convertJsonObjectToUStruct(TSharedPtr<FJsonObject> json, UStruct* Struct, void* ptrToStruct) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		FString FieldName;
		FieldName = prop->GetName();
		auto field = json->TryGetField(FieldName);
		if (!field.IsValid()) continue;
		convertJsonValueToUProperty(field, *prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct));
	}
}

void UResourceNodeSetup_BPLib::convertJsonValueToUProperty(TSharedPtr<FJsonValue> json, UProperty* prop, void* ptrToProp) {
	if (auto strProp = Cast<UStrProperty>(prop)) {
		strProp->SetPropertyValue(ptrToProp, json->AsString());
	}
	else if (auto fProp = Cast<UFloatProperty>(prop)) {
		fProp->SetPropertyValue(ptrToProp, json->AsNumber());
	}
	else if (auto iProp = Cast<UIntProperty>(prop)) {
		iProp->SetPropertyValue(ptrToProp, json->AsNumber());
	}
	else if (auto bProp = Cast<UBoolProperty>(prop)) {
		bProp->SetPropertyValue(ptrToProp, json->AsBool());
	}
	else if (auto u8Prop = Cast<UInt8Property>(prop)) {
		uint8 Int8Prop = json->AsNumber();
		int64 res = Int8Prop;
		void* EnumyPtr = u8Prop->ContainerPtrToValuePtr<void>(ptrToProp);
		Cast<UInt8Property>(prop)->SetIntPropertyValue(EnumyPtr, res);
	}
	else if (auto eProp = Cast<UEnumProperty>(prop)) {
		UByteProperty* ByteProp = Cast<UByteProperty>(eProp->GetUnderlyingProperty());
		int64 ENumb = json->AsNumber();
		void* EnumPtr = eProp->ContainerPtrToValuePtr<void>(ptrToProp);
		ByteProp->SetIntPropertyValue(EnumPtr, ENumb);
	}
	else if (auto byProp = Cast<UByteProperty>(prop)) {
		FString ByteProp = json->AsString();
		void* BytePtr = byProp->ContainerPtrToValuePtr<void>(ptrToProp);
		Cast<UByteProperty>(prop)->SetNumericPropertyValueFromString(BytePtr, *ByteProp);
	}
	else if (auto UnProp = Cast<UNumericProperty>(prop)) {
		int64 NumericProp = json->AsNumber();
		void* EnumxPtr = UnProp->ContainerPtrToValuePtr<void>(ptrToProp);
		Cast<UNumericProperty>(prop)->SetIntPropertyValue(EnumxPtr, NumericProp);
	}
	else if (auto aProp = Cast<UArrayProperty>(prop)) {
		FScriptArrayHelper helper(aProp, ptrToProp);
		helper.EmptyValues();
		TArray<TSharedPtr<FJsonValue>> jsonArr = json->AsArray();
		for (int i = 0; i < jsonArr.Num(); i++) {
			int64 valueIndex = helper.AddValue();
			convertJsonValueToUProperty(jsonArr[i], aProp->Inner, helper.GetRawPtr(valueIndex));
		}
	}
	else if (auto cProp = Cast<UClassProperty>(prop)) {
		FSoftObjectPath CppName = json->AsString();
		UObject* LoadedObject = FSoftObjectPath(json->AsString()).TryLoad();
		UClass * CastResult = Cast<UClass>(LoadedObject);
		cProp->SetPropertyValue(ptrToProp, CastResult);
	}
	else if (auto uProp = Cast<UObjectProperty>(prop)) {
		UObject* uObj = FSoftObjectPath(json->AsString()).TryLoad();
		uProp->SetPropertyValue(ptrToProp, uObj);
	}
	else if (auto sProp = Cast<UStructProperty>(prop)) {
		convertJsonObjectToUStruct(json->AsObject(), sProp->Struct, ptrToProp);
	}
}

TSharedPtr<FJsonValue> UResourceNodeSetup_BPLib::convertUPropToJsonValue(UProperty* prop, void* ptrToProp) {
	if (auto strProp = Cast<UStrProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(strProp->GetPropertyValue(ptrToProp)));
	}
	else if (auto fProp = Cast<UFloatProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(fProp->GetPropertyValue(ptrToProp)));
	}
	else if (auto iProp = Cast<UIntProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(iProp->GetPropertyValue(ptrToProp)));
	}
	else if (auto bProp = Cast<UBoolProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueBoolean(bProp->GetPropertyValue(ptrToProp)));
	}
	else if (auto eProp = Cast<UEnumProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(eProp->GetUnderlyingProperty()->GetSignedIntPropertyValue(ptrToProp)));
	}
	else if (auto nProp = Cast<UNumericProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(nProp->GetUnsignedIntPropertyValue(ptrToProp)));
	}
	else if (auto aProp = Cast<UArrayProperty>(prop)) {
		auto& arr = aProp->GetPropertyValue(ptrToProp);
		TArray<TSharedPtr<FJsonValue>> jsonArr;
		for (int i = 0; i < arr.Num(); i++) {
			jsonArr.Add(convertUPropToJsonValue(aProp->Inner, (void*)((size_t)arr.GetData() + i * aProp->Inner->ElementSize)));
		}
		return TSharedPtr<FJsonValue>(new FJsonValueArray(jsonArr));
	}
	else if (auto cProp = Cast<UClassProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(cProp->GetPropertyValue(ptrToProp)->GetPathName()));
	}
	else if (auto oProp = Cast<UObjectProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(oProp->GetPropertyValue(ptrToProp)->GetPathName()));
	}
	else if (auto sProp = Cast<UStructProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueObject(convertUStructToJsonObject(sProp->Struct, ptrToProp)));
	}
	else return TSharedPtr<FJsonValue>(new FJsonValueNull());
}

FString UResourceNodeSetup_BPLib::SanitizeJsonString(FString write, bool some)
{
	using namespace std;
	// {\r\n\t\"Table\":
	FString VariableName = write;
	FString replace;
	VariableName.Split("[", nullptr, &replace, ESearchCase::IgnoreCase, ESearchDir::FromStart);
	replace.Split("]", &VariableName, nullptr, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	if (some)
	{
		replace = "[";
		VariableName.Append("]");
	}
	else
	{
		replace = "";
	}
	replace.Append(*VariableName);
	using namespace std;
	string str = TCHAR_TO_UTF8(*replace);
	int size = str.length();
	for (int j = 0; j <= size; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			if (str[i] == ' ')
			{
				str.erase(str.begin() + i);
			}
		}
	}

	return str.c_str();
}

UClass* UResourceNodeSetup_BPLib::GetActiveLoadClass(const FModPakLoadEntry& entry, bool isMenuWorld) {
	return isMenuWorld ? static_cast<UClass*>(entry.MenuInitClass) : static_cast<UClass*>(entry.ModInitClass);
}

void UResourceNodeSetup_BPLib::InternalGetStructAsJson(UStructProperty *Structure, void* StructurePtr, FString &String)
{
	TSharedPtr<FJsonObject> JsonObject = convertUStructToJsonObject(Structure->Struct, StructurePtr);
	FString write;
	TSharedRef<TJsonWriter<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>> JsonWriter = TJsonWriterFactory<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>::Create(&write); //Our Writer Factory
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	String = write;
}

TArray<TSubclassOf<ASMLInitMod>> UResourceNodeSetup_BPLib::GetModActors(UWorld* World, bool bIsMenuWorld) {
	//ModInitializerActorList.Empty();
	FModHandler& ModHandler = SML::GetModHandler();
	TArray<FModPakLoadEntry> mods = ModHandler.ModPakInitializers;
	TArray<TSubclassOf<ASMLInitMod>> arr;
	for(int32 i = 0; i < mods.Num(); i ++)
	{
		arr.Add(mods[i].ModInitClass);
	}
	return arr;
}