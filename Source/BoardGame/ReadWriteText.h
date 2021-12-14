// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteText.generated.h"

/**
 * 
 */
UCLASS()
class BOARDGAME_API UReadWriteText : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "LoadText"))
		static bool LoadText(FString FileName, FString& SaveText);

	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "SaveText"))
		static bool SaveText(FString SaveText, FString FileName);

	
};
