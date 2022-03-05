// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "ABCharacter.h"
#include "ABAIController.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.f;

	if (nullptr == World)
		return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollsionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollsionQueryParam
	);

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			AABCharacter* Character = Cast<AABCharacter>(OverlapResult.GetActor());
			if (Character)
			{
				if (Character->GetController()->IsPlayerController())
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(AABAIController::TargetKey, Character);
					DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.5f);
					DrawDebugPoint(World, Character->GetActorLocation(), 10.f, FColor::Blue, false, 0.5f);
					DrawDebugLine(World, Center, Character->GetActorLocation(), FColor::Blue, false, 0.5f);
					return;
				}
			}
		}
	}


	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AABAIController::TargetKey, nullptr);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.5f);

}
