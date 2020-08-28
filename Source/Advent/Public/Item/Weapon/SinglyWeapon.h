

#pragma once
#include "CoreMinimal.h"
#include "Weapon.h"
#include "SinglyWeapon.generated.h"


UCLASS(BlueprintType, Blueprintable, abstract)
class ADVENT_API ASinglyWeapon : public AWeapon
{
	GENERATED_BODY()

public:

/*	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ACartridge> Cartridge;*/

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		float Strength;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		int Ammo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int MaxAmmo;

	virtual void Shot(bool IsActiv) override;

	virtual void SetData(const FString& NewData) override;

	virtual FString GetData() override;

};