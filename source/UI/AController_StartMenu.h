// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/UniformGridSlot.h"
#include "AController_StartMenu.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AAController_StartMenu : public APlayerController
{
	GENERATED_BODY()

public:

	AAController_StartMenu();

	virtual void BeginPlay()override;

	void ChangeMouseSetting();

	void SetDungeonLev(int32 Value); // 플레이어가 속한 던전 레벨 할당
	int32 GetDungeonLev(); // 플레이어가 속한 던전 레벨 반환

	void ShowGameMenu(); // 게임 메뉴 오픈 함수
	void CloseGameMenu(); // 게임 메뉴를 닫는 함수
	void ShowInventory(); // 인벤토리 오픈 함수
	UFUNCTION(BlueprintCallable, Category = "MyUI")
		void CloseInventory(); // 인벤토리를 닫는 함수

	void WeaponAttack(); // 공격 버튼을 누를 시 호출
	void Skill1(); // 스킬1 버튼 누를 시 호출
	void Skill2(); // 스킬1 버튼 누를 시 호출
	void ChangeWeapon(); // 무기교체 버튼을 누를 시 호출

	void ShowDieUI(); // 플레이어가 죽었을 때의 Widget을 오픈

	void UseConsumableItem(int32 ConsumableItemIndex); // 소비 아이템 사용

protected:
	void SetupInputComponent()override;

private:

	int32 DungeonLev;

	bool isShowGameMenu; // 게임 메뉴 위젯이 오픈되어 있는지에 대한 여부
	bool isShowInventory; // 게임 인벤토리 위젯이 오픈되어 있는지에 대한 여부

	TSubclassOf<class UUserWidget>uiItemSlotBPClass;
	UUserWidget* uiItemSlotWidget; // 슬롯 UI

	TSubclassOf<class UUserWidget>uiGameBPClass;
	UUserWidget* uiGameWidget; // 게임 기본 UI

	TSubclassOf<class UUserWidget>uiGameMenuBPClass;
	UUserWidget* uiGameMenuWidget; // 게임 메뉴 UI

	TSubclassOf<class UUserWidget>uiInventoryBPClass;
	UUserWidget* uiInventoryWidget; // 게임 인벤토리 UI

	TSubclassOf<class UUserWidget>uiLevelSelectBPClass;
	UUserWidget* uiLevelSelectWidget; // 던전 레벨 선택 UI

	TSubclassOf<class UUserWidget>uiGameDieBPClass;
	UUserWidget* uiGameDieWidget; // 플레이어가 죽었을 때 출력할 UI
};
