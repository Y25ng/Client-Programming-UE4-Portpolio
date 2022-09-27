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
		// UGridPanel* GridPanel_ItemSlots = nullptr; // ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int32> MyItemArray_ch2; // ������ �ִ� ������ ���
/*
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySlot)
		UUserWidget* MyItemSlot;
		*/

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Inventory_Close = nullptr; // �κ��丮 �ݱ� ��ư

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_ConsumableItem_1 = nullptr; // �κ��丮 �Һ� ������ ���1 ���
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_ConsumableItem_2 = nullptr; // �κ��丮 �Һ� ������ ���2 ���
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_ConsumableItem_3 = nullptr; // �κ��丮 �Һ� ������ ���1 ���
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_ConsumableItem_4 = nullptr; // �κ��丮 �Һ� ������ ���2 ���
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		int32 ConsumableItemIndex; // ����� �κ��丮 �Һ� ������ ���

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
		void Btn_Inventory_CloseWindow(); // �κ��丮 �ݱ� ��ư ���� �� ȣ�� �� �Լ�

	UFUNCTION()
		void Btn_Inventory_Use_ConsumableItem_1(); // �κ��丮 �Һ� ������ ���1 ��� �Լ�
	UFUNCTION()
		void Btn_Inventory_Use_ConsumableItem_2(); // �κ��丮 �Һ� ������ ��2 ��� �Լ�
	UFUNCTION()
		void Btn_Inventory_Use_ConsumableItem_3(); // �κ��丮 �Һ� ������ ���3 ��� �Լ�
	UFUNCTION()
		void Btn_Inventory_Use_ConsumableItem_4(); // �κ��丮 �Һ� ������ ��4 ��� �Լ�




	UFUNCTION()
		void Btn_Weapon1_OnEquip(); // �κ��丮 �Һ� ������ ���1 ��� �Լ�
	UFUNCTION()
		void Btn_Weapon2_OnEquip(); // �κ��丮 �Һ� ������ ��2 ��� �Լ�
	UFUNCTION()
		void Btn_Weapon3_OnEquip(); // �κ��丮 �Һ� ������ ���1 ��� �Լ�
	UFUNCTION()
		void Btn_Weapon4_OnEquip(); // �κ��丮 �Һ� ������ ���1 ��� �Լ�

	void Use_ConsumableItem(int32 Index); // �κ��丮 �Һ� ������ ���
	void WeaponChange(int32 index); // ���� ��ü
	
	
};
