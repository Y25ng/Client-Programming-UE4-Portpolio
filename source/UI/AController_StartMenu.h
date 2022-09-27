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

	void SetDungeonLev(int32 Value); // �÷��̾ ���� ���� ���� �Ҵ�
	int32 GetDungeonLev(); // �÷��̾ ���� ���� ���� ��ȯ

	void ShowGameMenu(); // ���� �޴� ���� �Լ�
	void CloseGameMenu(); // ���� �޴��� �ݴ� �Լ�
	void ShowInventory(); // �κ��丮 ���� �Լ�
	UFUNCTION(BlueprintCallable, Category = "MyUI")
		void CloseInventory(); // �κ��丮�� �ݴ� �Լ�

	void WeaponAttack(); // ���� ��ư�� ���� �� ȣ��
	void Skill1(); // ��ų1 ��ư ���� �� ȣ��
	void Skill2(); // ��ų1 ��ư ���� �� ȣ��
	void ChangeWeapon(); // ���ⱳü ��ư�� ���� �� ȣ��

	void ShowDieUI(); // �÷��̾ �׾��� ���� Widget�� ����

	void UseConsumableItem(int32 ConsumableItemIndex); // �Һ� ������ ���

protected:
	void SetupInputComponent()override;

private:

	int32 DungeonLev;

	bool isShowGameMenu; // ���� �޴� ������ ���µǾ� �ִ����� ���� ����
	bool isShowInventory; // ���� �κ��丮 ������ ���µǾ� �ִ����� ���� ����

	TSubclassOf<class UUserWidget>uiItemSlotBPClass;
	UUserWidget* uiItemSlotWidget; // ���� UI

	TSubclassOf<class UUserWidget>uiGameBPClass;
	UUserWidget* uiGameWidget; // ���� �⺻ UI

	TSubclassOf<class UUserWidget>uiGameMenuBPClass;
	UUserWidget* uiGameMenuWidget; // ���� �޴� UI

	TSubclassOf<class UUserWidget>uiInventoryBPClass;
	UUserWidget* uiInventoryWidget; // ���� �κ��丮 UI

	TSubclassOf<class UUserWidget>uiLevelSelectBPClass;
	UUserWidget* uiLevelSelectWidget; // ���� ���� ���� UI

	TSubclassOf<class UUserWidget>uiGameDieBPClass;
	UUserWidget* uiGameDieWidget; // �÷��̾ �׾��� �� ����� UI
};
