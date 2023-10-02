#include "CogEngineWindow_Spawn.h"

//--------------------------------------------------------------------------------------------------------------------------
void UCogEngineWindow_Spawn::PreRender(ImGuiWindowFlags& WindowFlags)
{
    Super::PreRender(WindowFlags);
}

//--------------------------------------------------------------------------------------------------------------------------
void UCogEngineWindow_Spawn::RenderContent()
{
    Super::RenderContent();

    if (Asset == nullptr)
    {
        return;
    }

    for (const FCogEngineSpawnGroup& SpawnGroup : Asset->SpawnGroups)
    {
        RenderSpawnGroup(SpawnGroup);
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void UCogEngineWindow_Spawn::RenderSpawnGroup(const FCogEngineSpawnGroup& SpawnGroup)
{
    int32 GroupIndex = 0;

    ImGui::PushStyleColor(ImGuiCol_Header,          IM_COL32(66, 66, 66, 79));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered,   IM_COL32(62, 62, 62, 204));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive,    IM_COL32(86, 86, 86, 255));

    if (ImGui::CollapsingHeader(TCHAR_TO_ANSI(*SpawnGroup.Name), ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::PushID(GroupIndex);

        const bool PushColor = (SpawnGroup.Color != FColor::Transparent);
        if (PushColor)
        {
            FCogWindowWidgets::PushBackColor(FCogImguiHelper::ToImVec4(SpawnGroup.Color));
        }

        static int32 SelectedAssetIndex = -1;
        int32 AssetIndex = 0;

        for (const FCogEngineSpawnEntry& SpawnEntry : SpawnGroup.Spawns)
        {
            if (RenderSpawnAsset(SpawnEntry, SelectedAssetIndex == GroupIndex))
            {
                SelectedAssetIndex = AssetIndex;
            }

            AssetIndex++;
        }

        if (PushColor)
        {
            FCogWindowWidgets::PopBackColor();
        }

        ImGui::PopID();
        GroupIndex++;
    }

    ImGui::PopStyleColor(3);
}

//--------------------------------------------------------------------------------------------------------------------------
bool UCogEngineWindow_Spawn::RenderSpawnAsset(const FCogEngineSpawnEntry& SpawnEntry, bool IsLastSelected)
{
    bool IsPressed = false;

    ImGui::PushStyleColor(ImGuiCol_Button, IsLastSelected ? ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive) : ImGui::GetStyleColorVec4(ImGuiCol_Button));
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.0f, 0.5f));

    FString EntryName;
    if (SpawnEntry.Asset != nullptr)
    {
        EntryName = SpawnEntry.Asset->GetName();
    }
    else
    {
        EntryName = GetNameSafe(SpawnEntry.Class);
    }

    if (ImGui::Button(TCHAR_TO_ANSI(*EntryName), ImVec2(-1, 0)))
    {
        if (ACogEngineReplicator* Replicator = FCogEngineModule::Get().GetLocalReplicator())
        {
            Replicator->Server_Spawn(SpawnEntry);
        }
    }

    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor(1);

    return IsPressed;
}