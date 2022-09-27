// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProject2GameMode.generated.h"

UCLASS(minimalapi)
class AMyProject2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyProject2GameMode();

protected:
	virtual void BeginPlay()override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		UUserWidget* CurrentWidget; // 가지고 있는 위젯
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> HUDWidget; // 타입을 UUserWidget으로 제한
};



