#include "MyGameMode.h"

void AMyGameMode::RegisterSpawner(AActor* Spawner)
{
	if(!Spawner)
	{
		UE_LOG(LogTemp, Error, TEXT("Spawner is null!"))
		return;
	}
}
