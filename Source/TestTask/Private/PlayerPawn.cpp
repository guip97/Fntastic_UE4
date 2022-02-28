#include "PlayerPawn.h"

APlayerPawn::APlayerPawn()
{
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &APlayerPawn::OnClickPressed);
	PlayerInputComponent->BindAction("LeftClick", IE_Released, this, &APlayerPawn::OnClickReleased);
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
	}
}

void APlayerPawn::OnClickPressed()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if(!PlayerController)
	{
		return;
	}
	
	FHitResult HitResult;

	FVector MouseWorldLocation;
	FVector MouseWorldDirection;
	
	PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

	FCollisionQueryParams QueryParams;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, MouseWorldLocation, MouseWorldDirection * TraceLength,
		ECC_Visibility, QueryParams);

	if(bHit)
	{
		if(AActor* Actor = HitResult.GetActor())
		{
			ASpawner* Spawner = Cast<ASpawner>(Actor);

			if(Spawner)
			{
				Spawner->Select();
				SelectedSpawner = Spawner;
			}
		}
	}
}

void APlayerPawn::OnClickReleased()
{
	if(SelectedSpawner)
	{
		SelectedSpawner->Deselect();
	}
}
