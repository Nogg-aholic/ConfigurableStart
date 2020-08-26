#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ModResource_Node.h"

#include "ResourceNodeSetup_Interface.generated.h"

UINTERFACE(MinimalAPI,Blueprintable)
class UResourceNodeSetup_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RESOURCENODESETUP_API IResourceNodeSetup_Interface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetResourceNodeSetupConfig(
		TArray<TSubclassOf<AModResource_Node>>& AddedNodeTypes,
		TArray<FModNodeConfig>& Config,
		TMap<TSubclassOf<UFGResourceDescriptor>, FFixedNodeStructArray>& ReplaceExisting,
		TMap<TSubclassOf<AModResource_Node>, FFixedNodeStructArray>& FixedSpawnLocations) const;
};
