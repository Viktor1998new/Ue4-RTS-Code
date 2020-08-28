
#include "SinglyWeapon.h"

void ASinglyWeapon::Shot(bool IsActiv) {
	
	if (Ammo != 0)
	{
		Ammo = FMath::Max<float>(Ammo - 1, 0);
		K2_OnShot();
	}
}

FString ASinglyWeapon::GetData()
{
	return "Ammo:" + FString::FromInt(Ammo) + ",Strength:" + FString::SanitizeFloat(Strength);
}

void ASinglyWeapon::SetData(const FString& NewData)
{

	if (NewData.IsEmpty())
	return;

	TArray<FString> Parsed;
	NewData.ParseIntoArray(Parsed, *FString(","), true);

	for (int i = 0; i < Parsed.Num(); i++)
	{
		TArray<FString> SesParsed;
		Parsed[i].ParseIntoArray(SesParsed, *FString(":"), true);

		if (SesParsed[0] == "Ammo")
			Ammo = FCString::Atoi(*SesParsed[1]);

		if (SesParsed[0] == "Strength")
			Strength = FCString::Atoi(*SesParsed[1]);
	}
}