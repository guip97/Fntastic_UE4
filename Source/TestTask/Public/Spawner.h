#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class TESTTASK_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawner();
	
	virtual void Tick(float DeltaTime) override;

	void Select();

	void Deselect();

protected:
	virtual void BeginPlay() override;

private:

	void OnTimer();

	UPROPERTY(EditDefaultsOnly, Category = "Destination", meta = (MakeEditWidget))
	FVector Destination;

	UPROPERTY(EditDefaultsOnly, Category = "Timer")
	FVector2D TimeInterval;

	/**
	 * 1 -> go forward after first timer
	 * 0 -> stay after the first timer
	 * -1 -> go back after the first timer
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Direction", meta = (ClampMin="-1", ClampMax="1"))
	int MoveDirection = 0;
	
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* StatueMesh;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TSubclassOf<AActor> BP_Effect;

	UPROPERTY()
	UMaterialInstanceDynamic* BaseMat;

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	UMaterialInterface* ParentMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Color")
	FLinearColor SelectColor;
	
	UPROPERTY(EditDefaultsOnly, Category = "Color")
	FLinearColor DefaultColor;

	bool bInterpolate = false;

	int CurrentDirection = 0;

	FTimerHandle TimerHandle;
};