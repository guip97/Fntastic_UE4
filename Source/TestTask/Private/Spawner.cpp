#include "Spawner.h"

#include "Kismet/KismetMaterialLibrary.h"

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnerMesh"));
	StatueMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StatueMesh"));

	StatueMesh->SetupAttachment(SpawnerMesh);
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	BaseMat = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, ParentMaterial);
	SpawnerMesh->SetMaterial(0, BaseMat);
}

void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(!bInterpolate)
	{
		return;
	}

	if(CurrentDirection != 0)
	{
		/** Interpolate further */
		FVector LerpedLoc = FMath::Lerp(StatueMesh->GetComponentLocation(), Destination, CurrentDirection *
		                                0.5f * DeltaTime);
		StatueMesh->SetWorldLocation(LerpedLoc);

		if((Destination - StatueMesh->GetComponentLocation()).IsNearlyZero(5.f))
		{
			bInterpolate = false;
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
	}
}

void ASpawner::Select()
{
	BaseMat->SetVectorParameterValue(TEXT("Color"), SelectColor);
}

void ASpawner::Deselect()
{
	BaseMat->SetVectorParameterValue(TEXT("Color"), DefaultColor);

	if(!bInterpolate)
	{
		auto ActorEffect = GetWorld()->SpawnActor<AActor>(BP_Effect, StatueMesh->GetComponentLocation(), StatueMesh->GetComponentRotation());
		ActorEffect->AttachToComponent(StatueMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		
		CurrentDirection = 1;
		OnTimer();
	}
}

void ASpawner::OnTimer()
{
	if(!bInterpolate)
	{
		bInterpolate = true;
	}
	else
	{
		if(CurrentDirection == 1)
		{
			CurrentDirection = MoveDirection;
		}
		else
		{
			CurrentDirection = 1;
		}
	}

	if(MoveDirection == 1)
	{
		return;
	}
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this ,&ASpawner::OnTimer, CurrentDirection == 1 ?
		TimeInterval.X : TimeInterval.Y);
}
