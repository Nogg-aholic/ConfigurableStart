#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ModResource_Node.h"

#include "ResourceNodeSetupSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class RESOURCENODESETUP_API UResourceNodeSetupSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString SaveString;

	UFUNCTION(BlueprintCallable, Category = "ResourceNodeSetup")
	void MergeDependentConfigs();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<AModResource_Node>> AddedNodeTypes;

	// Loadable Presets for the Node Randomizer
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FModNodeConfig> ModConfig;

	// Fixed Spawnpoints that will replace existing Nodes , Position is used to Find the Node.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<TSubclassOf<UFGResourceDescriptor>, FFixedNodeStructArray> ReplaceExisting;

	// Fixed Spawnpoints that will also be present regardless of Generation
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<TSubclassOf<AModResource_Node>, FFixedNodeStructArray> FixedSpawnLocations;

private:
	FORCEINLINE void MergeNodeTypeArray(const TArray<TSubclassOf<AModResource_Node>>* nodeTypes)
	{
		for (auto nodeTypeItem : *nodeTypes) AddedNodeTypes.AddUnique(nodeTypeItem);
	}

	FORCEINLINE void MergeConfigArray(const TArray<FModNodeConfig>* configs)
	{
		for (auto configItem : *configs) ModConfig.Add(configItem);
	}

	FORCEINLINE void MergeReplacementMap(const TMap<TSubclassOf<UFGResourceDescriptor>, FFixedNodeStructArray>* nodes)
	{
		for (auto& nodeArrItem : *nodes) {
			if (ReplaceExisting.Contains(nodeArrItem.Key)) {
				ReplaceExisting[nodeArrItem.Key].Nodes.Append(nodeArrItem.Value.Nodes);
			}
			else {
				ReplaceExisting.Add(nodeArrItem.Key, nodeArrItem.Value);
			}
		}
	}

	FORCEINLINE void MergeFixedMap(const TMap<TSubclassOf<AModResource_Node>, FFixedNodeStructArray>* nodes)
	{
		for (auto& nodeArrItem : *nodes) {
			if (FixedSpawnLocations.Contains(nodeArrItem.Key)) {
				FixedSpawnLocations[nodeArrItem.Key].Nodes.Append(nodeArrItem.Value.Nodes);
			}
			else {
				FixedSpawnLocations.Add(nodeArrItem.Key, nodeArrItem.Value);
			}
		}
	}
};
