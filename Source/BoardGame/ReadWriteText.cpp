// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadWriteText.h"

bool UReadWriteText::LoadText(FString FileName, FString& SaveText)
{
    return FFileHelper::LoadFileToString(SaveText, *(FPaths::ProjectContentDir() +  "MapConfiguration/" + FileName));
}

bool UReadWriteText::SaveText(FString SaveText, FString FileName)
{
    return FFileHelper::SaveStringToFile(SaveText, *(FPaths::ProjectContentDir() + "MapConfiguration/" + FileName));
}

