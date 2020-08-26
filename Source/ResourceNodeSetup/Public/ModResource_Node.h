// ILikeBanas

#pragma once

#include "CoreMinimal.h"
#include "FGResourceDescriptor.h"

#include "Resources/FGResourceNode.h"
#include "ModResource_Node.generated.h"

/**
 * 
 */



USTRUCT(BlueprintType)
struct FModNodeSingleConfig {
	GENERATED_BODY()
public:
	FModNodeSingleConfig();

	// Insert the Class the Node should be replaced with , and its Chance to become a Resource of this type.
	// Note:: While choosing a Descriptor here, a NodeClass that implements this descriptor will always be prefered
	// if existing. If not existing , an aviable one with that Resource will be chosen. The SUM of all Chances must equal to 1
	// otherwise every float untill the SUM of 1 is reached is accounted for , the rest will be ignored.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TMap<TSubclassOf<class AModResource_Node>, float> ReplacementAndChance;

	// Use Amounts ? If False -> unchanged
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool useAmounts;


	// Use Amounts ? If False -> unchanged
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 BaseAmount;

	// Chance for Amount:Infinite Summ of all AmountChances must equal to 1 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float AmountChanceInfinite;
	// Chance for Amount:Rich Summ of all AmountChances must equal to 1 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float AmountChanceRich;
	// Chance for Amount:Normal Summ of all AmountChances must equal to 1 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float AmountChanceNormal;
	// Chance for Amount:Poor Summ of all AmountChances must equal to 1 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float AmountChancePoor;

	// Use Amounts ? If False -> leave unchanged
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool UsePurity;
	// Chance for Purity:Impure Summ of all PurityChances must equal to 1 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float PurityChanceImpure;
	// Chance for Purity:Normal Summ of all PurityChances must equal to 1 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float PurityChanceNormal;
	// Chance for Purity:Pure Summ of all PurityChances must equal to 1 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float PurityChancePure;

};

USTRUCT(BlueprintType)
struct FModNodeConfig {
	GENERATED_BODY()
public:
	FModNodeConfig();
	// Insert Resources of Nodes you want to Change with a Config Entry 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString DisplayName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UTexture2D * Icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TMap<TSubclassOf<class UFGResourceDescriptor>, FModNodeSingleConfig> config;

};


USTRUCT(BlueprintType)
struct FFixedNodeStruct{
	GENERATED_BODY()
public:
	FFixedNodeStruct();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TEnumAsByte<EResourceAmount> Amount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TEnumAsByte<EResourcePurity> Purity; 
	// When Infinite this has no effect
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 AmountLeft;
	// if used to Replace only Location is comapred
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FTransform Position;

};

USTRUCT(BlueprintType)
struct FFixedNodeStructArray {
	GENERATED_BODY()
public:
	FFixedNodeStructArray();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class AModResource_Node> NodeClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray<FFixedNodeStruct> Nodes;

};


USTRUCT(BlueprintType)
struct FModRourceNode_Config
{
	GENERATED_BODY()
public:
	FModRourceNode_Config();

	// Should this resource be never Limited? -> Always Infinite -> Block manual edit
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
		bool NeverFinite = false;

	// Can this type of Node be consideres when randomly generating NodeTypes?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool AllowInRandom = true;

	// Can this be found in the Popup when manually assigning Node Types?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool AllowManualAssign = true;

	// Consider this local Offsets, except for Scale.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FTransform LocalSpawnLocation;

	~FModRourceNode_Config() = default;

};

UCLASS()
class AModResource_Node : public AFGResourceNode
{
	GENERATED_BODY()

	virtual void PreSaveGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	virtual void BeginPlay() override;
public:


	void Init();

	UFUNCTION(BlueprintCallable, Category = "Resources")
		static void ReConstruct(AModResource_Node * selfref, FFixedNodeStruct structIn);

	virtual int32 ExtractResource_Implementation(int32 amount) override;


	/** Mod Config Settings*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SimpleDisplay, Category = "Resources")
		FModRourceNode_Config  Settings;
	
	/** How Many is Left */
	UPROPERTY(SaveGame)
		int32 SavedAmountLeft;

	/** How pure the resource is */
	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Resources")
		TEnumAsByte<EResourcePurity> nPurity;

	/** Amount of the resource */
	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Resources")
		TEnumAsByte<EResourceAmount> nAmount;



};
