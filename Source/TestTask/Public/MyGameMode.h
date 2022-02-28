#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

UCLASS(Blueprintable)
class TESTTASK_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	void RegisterSpawner(AActor* Spawner);
};