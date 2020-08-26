#include "ResourceNodeSetupSubsystem.h"

#include "ResourceNodeSetup_Interface.h"
#include "ModResource_Node.h"
#include "SatisfactoryModLoader.h"

void UResourceNodeSetupSubsystem::MergeDependentConfigs() {
	auto& modHandler = SML::GetModHandler();
#if WITH_EDITOR
	TArray<AActor*> SMLInitActors;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), ASMLInitMenu::StaticClass(), SMLInitActors);

	for (int32 i = 0; i < SMLInitActors.Num(); i++)
	{
		if (!SMLInitActors[i]->Implements<UResourceNodeSetup_Interface>()) continue;

		TArray<TSubclassOf<AModResource_Node>> modNodeTypes;
		TArray<FModNodeConfig> modConfig;
		TMap<TSubclassOf<UFGResourceDescriptor>, FFixedNodeStructArray> modReplacedNodes;
		TMap<TSubclassOf<AModResource_Node>, FFixedNodeStructArray> modAddedNodes;

		IResourceNodeSetup_Interface::Execute_GetResourceNodeSetupConfig(
			SMLInitActors[i],
			modNodeTypes,
			modConfig,
			modReplacedNodes,
			modAddedNodes);

		MergeNodeTypeArray(&modNodeTypes);
		MergeConfigArray(&modConfig);
		MergeReplacementMap(&modReplacedNodes);
		MergeFixedMap(&modAddedNodes);

	}

#else
	for (auto& modInitActor : modHandler.ModInitializerActorList) {
		if (!modInitActor->Implements<UResourceNodeSetup_Interface>()) continue;

		TArray<TSubclassOf<AModResource_Node>> modNodeTypes;
		TArray<FModNodeConfig> modConfig;
		TMap<TSubclassOf<UFGResourceDescriptor>, FFixedNodeStructArray> modReplacedNodes;
		TMap<TSubclassOf<AModResource_Node>, FFixedNodeStructArray> modAddedNodes;

		IResourceNodeSetup_Interface::Execute_GetResourceNodeSetupConfig(
			modInitActor.Get(),
			modNodeTypes,
			modConfig,
			modReplacedNodes,
			modAddedNodes);

		MergeNodeTypeArray(&modNodeTypes);
		MergeConfigArray(&modConfig);
		MergeReplacementMap(&modReplacedNodes);
		MergeFixedMap(&modAddedNodes);
	}
#endif
}
