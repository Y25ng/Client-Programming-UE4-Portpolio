// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Components/GridPanel.h"
#include "MyBasicCharacter.h"
#include "UI_Inventory_Widget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UUI_Inventory_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	// UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		// UGridPanel* GridPanel_ItemSlots = nullptr; // 슬롯

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int32> MyItemArray_ch2; // 가지고 있는 아이템 목록
/*
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySlot)
		UUserWidget* MyItemSlot;
		*/

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Inventory_Close = nullptr; // 인벤토리 닫기 버튼

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_ConsumableItem_1 = nullptr; // 인벤토리 소비 아이템 목록1 사용
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_ConsumableItem_2 = nullptr; // 인벤토리 소비 아이템 목록2 사용
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_ConsumableItem_3 = nullptr; // 인벤토리 소비 아이템 목록1 사용
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_ConsumableItem_4 = nullptr; // 인벤토리 소비 아이템 목록2 사용
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		int32 ConsumableItemIndex; // 사용할 인벤토리 소비 아이템 목록

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Weapon1 = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Weapon2 = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Weapon3 = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Weapon4 = nullptr;

protected:

	UFUNCTION()
		void Btn_Inventory_CloseWindow(); // 인벤토리 닫기 버튼 누를 시 호출 될 함수

	UFUNCTION()
		void Btn_Inventory_Use_ConsumableItem_1(); // 인벤토리 소비 아이템 목록1 사용 함수
	UFUNCTION()
		void Btn_Inventory_Use_ConsumableItem_2(); // 인벤토리 소비 아이템 목룍2 사용 함수
	UFUNCTION()
		void Btn_Inventory_Use_ConsumableItem_3(); // 인벤토리 소비 아이템 목록3 사용 함수
	UFUNCTION()
		void Btn_Inventory_Use_ConsumableItem_4(); // 인벤토리 소비 아이템 목룍4 사용 함수




	UFUNCTION()
		void Btn_Weapon1_OnEquip(); // 인벤토리 소비 아이템 목록1 사용 함수
	UFUNCTION()
		void Btn_Weapon2_OnEquip(); // 인벤토리 소비 아이템 목룍2 사용 함수
	UFUNCTION()
		void Btn_Weapon3_OnEquip(); // 인벤토리 소비 아이템 목록1 사용 함수
	UFUNCTION()
		void Btn_Weapon4_OnEquip(); // 인벤토리 소비 아이템 목록1 사용 함수

	void Use_ConsumableItem(int32 Index); // 인벤토리 소비 아이템 사용
	void WeaponChange(int32 index); // 무기 교체
	
	
};
