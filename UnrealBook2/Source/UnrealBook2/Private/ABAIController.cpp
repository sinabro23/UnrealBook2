// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "ABCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AABAIController::HomePosKey(TEXT("HomePos"));
const FName AABAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AABAIController::TargetKey(TEXT("Target"));

AABAIController::AABAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTOBJECT(TEXT("BehaviorTree'/Game/_Game/AI/BT_ABCharacter.BT_ABCharacter'"));
	if (BTOBJECT.Succeeded())
	{
		BTAsset = BTOBJECT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBOBJECT(TEXT("BlackboardData'/Game/_Game/AI/BB_ABCharacter.BB_ABCharacter'"));
	if (BBOBJECT.Succeeded())
	{
		BBAsset = BBOBJECT.Object;
	}
}

void AABAIController::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			//UE_LOG(LogTemp, Warning, TEXT("behaviortree 작동 실패"));
		}
	}
}

void AABAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}

}

void AABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	
}

void AABAIController::OnUnPossess()
{
	Super::OnUnPossess();
	
}
