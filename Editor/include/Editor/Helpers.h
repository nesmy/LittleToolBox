#pragma once
#include <FA.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_raylib.h>
#include "Auxiliaries/ECS.h"


#define FONT_FILE "Resources/Fonts/Roboto-Medium.ttf"
#define ICON_FONT "Resources/Fonts/fa-solid-900.ttf"
#define SHADER_VERSION "#version 130"

#define REGULAR_FONT_SIZE 17
#define SMALL_FONT_SIZE 15

#define LABEL_SPACING  130
#define MENUBAR_HEIHT  50

#define ASSET_SPACING  10
#define ASSET_SIZE  90

// helper macros
#define LINE_HEIGHT() ImGui::GetTextLineHeight()
#define USE_SMALL_FONT() ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[1])
#define USE_REGULAR_FONT() ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[0])
#define TEXT_HEIGHT() ImGui::GetTextLineHeight() + (2.0f * ImGui::GetStyle().FramePadding.y)