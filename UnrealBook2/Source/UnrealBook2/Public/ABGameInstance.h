// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "ABGameInstance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FABCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FABCharacterData():
		Level(1),
		MaxHp(100),
		Attack(10),
		DropExp(10),
		NextExp(30)
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float MaxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float DropExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float NextExp;

};

UCLASS()
class UNREALBOOK2_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UABGameInstance();

	void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;

	FABCharacterData* GetABCharacterData(int32 Level);

	FStreamableManager StreamableManager;

private:
	UPROPERTY(VisibleAnywhere, Category = Data)
	UDataTable* CharacterDataTable;
};
