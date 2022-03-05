// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ABAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBOOK2_API AABAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AABAIController();

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
private:

	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
