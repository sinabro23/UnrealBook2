// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CHARACTERDATA(TEXT("DataTable'/Game/_Game/Data/ABCharacterData.ABCharacterData'"));
	if (DT_CHARACTERDATA.Succeeded())
	{
		CharacterDataTable = DT_CHARACTERDATA.Object;
	}

}

void UABGameInstance::Init()
{
	Super::Init();
}

void UABGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UABGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}

FABCharacterData* UABGameInstance::GetABCharacterData(int32 Level)
{
	return CharacterDataTable->FindRow<FABCharacterData>(*FString::FromInt(Level), TEXT(""));
}
