// ILikeBanas

#include "../Public/ModResource_Node.h"
#include "util/Logging.h"

FModRourceNode_Config::FModRourceNode_Config() {};
FFixedNodeStruct::FFixedNodeStruct() {};
FFixedNodeStructArray::FFixedNodeStructArray() {};
FModNodeSingleConfig::FModNodeSingleConfig() {};
FModNodeConfig::FModNodeConfig() { };

void AModResource_Node::Init()
{
	if(Settings.NeverFinite)
		mAmount = EResourceAmount::RA_Infinite;
	else
		mAmount = nAmount;
	mPurity = nPurity;
	mResourcesLeft = SavedAmountLeft;
	if (mAmount != EResourceAmount::RA_Infinite)
	{
		FString out = "Resource Amount Left : ";
		FString Nm = out.Append(FString::FromInt(mResourcesLeft));
		SML::Logging::error(*Nm);

	}
}

void AModResource_Node::PreSaveGame_Implementation(int32 saveVersion, int32 gameVersion)
{
	SavedAmountLeft = mResourcesLeft;
	AFGResourceNode::PreSaveGame_Implementation(saveVersion, gameVersion);
}

void AModResource_Node::BeginPlay()
{
	AActor::BeginPlay();
	Init();

}



void AModResource_Node::ReConstruct(AModResource_Node * selfref, FFixedNodeStruct structIn)
{
	selfref->nAmount = structIn.Amount;
	selfref->nPurity = structIn.Purity;
	selfref->mResourcesLeft = structIn.AmountLeft;
	selfref->SavedAmountLeft = structIn.AmountLeft;
	selfref->Init();
}

int32 AModResource_Node::ExtractResource_Implementation(int32 amount)
{
	if (mAmount == EResourceAmount::RA_Infinite)
		return Super::ExtractResource_Implementation(amount);
	
	int32 before = mResourcesLeft;
	int32 removed = Super::ExtractResource_Implementation(amount);
	
	if(before == mResourcesLeft)
		mResourcesLeft = mResourcesLeft - removed;
	else
	{
		// should check if enough was actually removed but for now this seems to work
	}

	if (mResourcesLeft > 0)
		return removed;
	else
		return 0;
}

