#pragma once

#include "CoreMinimal.h"
#include "Spawner.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS(Blueprintable)
class TESTTASK_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	void OnClickPressed();

	void OnClickReleased();

	UPROPERTY(EditDefaultsOnly, Category = "Line trace", meta = (ClampMin="0.0"))
	float TraceLength = 5000.f;

	UPROPERTY()
	ASpawner* SelectedSpawner;
};